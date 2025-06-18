/*!
 * @file entry.c
 *
 * @copyright
 * Copyright 2025 Anivice Ives
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * @brief This file defines entry point from assembly second stage loader
 **/

#include "string.h"
#include "printk.h"
#include "rtc.h"
#include "types.h"
#include "irq.h"
#include "die.h"
#include "ide.h"
#include "syscall.h"
#include "marco.h"
#include "ldt.h"

/*!
 * @brief Enable FPU
 */
static void enable_fpu(void)
{
    uint32_t cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1UL << 2);   /* clear EM */
    cr0 &= ~(1UL << 3);   /* clear TS */
    cr0 |=  (1UL << 5);   /* set NE: report FP errors via #MF */
    __asm__ volatile ("mov %0, %%cr0" :: "r"(cr0));
    __asm__ volatile ("fninit");     /* initialise x87 state */
}

static void install_irq(void)
{
    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t)&idt;
    irq_dummies_init();

    __asm__ volatile (
        "   cli                                     \n\t"
        "   lidt        (%%eax)                     \n\t"
        : : "a"((uint32_t)&idt_descriptor) : "memory", "cc"
    );

    for (int i = 0; i < 256; i++)
    {
        idt_set_gate(i, (uint32_t)irq_dummy_table[i], 0x10, 0x8E);
    }

    __asm__ volatile ("sti");
}

typedef struct __attribute__((packed)) int_frame_privchg {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t user_esp;
    uint32_t user_ss;
} int_frame_privchg_t;

__attribute__((naked))           /* suppress C prologue/epilogue */
void build_and_iret(int_frame_privchg_t *f)
{
    __asm__ __volatile__ (
        "mov  4(%esp), %eax \n\t"   /* eax = pointer to frame      */
        "pushl 16(%eax)     \n\t"   /* SS  */
        "pushl 12(%eax)     \n\t"   /* ESP */
        "pushl  8(%eax)     \n\t"   /* EFLAGS */
        "pushl  4(%eax)     \n\t"   /* CS  */
        "pushl  0(%eax)     \n\t"   /* EIP */
    );

    __asm__ volatile("lldt %%ax" :: "a"(0x30):"cc", "memory");
    __asm__ volatile("ltr %%ax" :: "a"(0x38):"cc", "memory");
    __asm__ volatile ("iret");
}

/*!
 * @brief Kernel entry point and stage dispatcher.
 * This function is responsible for invoking different dispatchers to finish the boot sequence.
 * This function is directly jumped from stage 2 loader and should never ever return (no return address in stack frame)
 * @return None, and is marked with [[noreturn]], so no return code is generated for main()
 */
[[noreturn]]
__attribute__((section(".kernel_entry_point")))
void main(void)
{
    enable_fpu();
    install_irq();
    rtc_irq_init();
    init_syscall();
    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");

    // report on CPU
    struct {
        uint32_t eax;
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t zero;
    } result = {};
    __asm__ volatile
    (
        "xor %%eax, %%eax   \n\t"
        "cpuid              \n\t"
        : "=a"(result.eax), "=b"(result.ebx), "=c"(result.ecx), "=d"(result.edx) ::
    );
    if (result.eax != 0)
    {
        printk("CPU: %s\n", (const char*)&result.ebx);
    }

    char * p = (char*)0x200000;
    (void)disk_read(p, 0, 1);
    segment_descriptor_t * descriptor = LOCAL_DESCRIPTOR_TABLE;
    memset(descriptor, 0, sizeof(segment_descriptor_t));
    descriptor[1] = make_descriptor(0, 0x000FFFFF, 0xFA, 0xC0);
    descriptor[2] = make_descriptor(0, 0x000FFFFF, 0xF2, 0xC0);

    tss_descriptor_t * tss = TASK_STATE_SEGMENT;
    uint32_t helper = 0;
    __asm__ volatile ("mov %%ds, %%eax" : "=a"(helper) ::);
    tss->ss0 = helper;
    __asm__ volatile ("mov %%esp, %%eax" : "=a"(helper) ::);
    tss->esp0 = helper;
    tss->iomap_base = sizeof(*tss);
    tss->eip = (uint32_t)0x200000;
    __asm__ volatile ("mov %%cs, %%eax" : "=a"(helper) ::);
    tss->cs = helper;

    int_frame_privchg_t frame = {
        .eip = (uint32_t)0x200000,
        .cs = 0xF,
        .eflags = 0x202,
        .user_esp = (uint32_t)0x200FFF,
        .user_ss = (uint32_t)0x17,
    };

    build_and_iret(&frame);

    /////////////////////////////////////////////////////////////
    die("Unexpected reach of the end of kernel entry point!");
}

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
#include "idt.h"
#include "irq.h"
#include "die.h"
#include "marco.h"

/*!
 * @brief Enable FPU
 */
static NO_PLEASE_DONT_OPTIMIZE
void enable_fpu()
{
    uint32_t cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1UL << 2);   /* clear EM */
    cr0 &= ~(1UL << 3);   /* clear TS */
    cr0 |=  (1UL << 5);   /* set NE: report FP errors via #MF */
    __asm__ volatile ("mov %0, %%cr0" :: "r"(cr0));
    __asm__ volatile ("fninit");     /* initialise x87 state */
}

static NO_PLEASE_DONT_OPTIMIZE
void install_irq()
{
    __asm__ volatile ("cli" ::: "memory");
    irq_dummies_init();

    for (unsigned i = 0; i < 256; ++i) {
        idt_set_gate(i, (uint32_t)irq_dummy_table[i], 0x10, 0x8E);
    }

    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t)idt;
    __asm__ volatile ("lidt %0" : : "m"(idt_descriptor) : "memory");
}

// typedef struct __attribute__((packed)) int_frame_privchg {
//     uint32_t eip;
//     uint32_t cs;
//     uint32_t eflags;
//     uint32_t user_esp;
//     uint32_t user_ss;
// } int_frame_privchg_t;

// __attribute__((naked, optimize(0)))           /* suppress C prologue/epilogue */
// void build_and_iret(int_frame_privchg_t *f)
// {
//     __asm__ __volatile__ (
//         "mov  4(%esp), %eax \n\t"   /* eax = pointer to frame      */
//         "pushl 16(%eax)     \n\t"   /* SS  */
//         "pushl 12(%eax)     \n\t"   /* ESP */
//         "pushl  8(%eax)     \n\t"   /* EFLAGS */
//         "pushl  4(%eax)     \n\t"   /* CS  */
//         "pushl  0(%eax)     \n\t"   /* EIP */
//     );
//
//     __asm__ volatile("lldt %%ax" :: "a"(0x30):"cc", "memory");
//     __asm__ volatile("ltr %%ax" :: "a"(0x38):"cc", "memory");
//                                __asm__ volatile ("iret");
// }

/*!
 * @brief Kernel entry point and stage dispatcher.
 * This function is responsible for invoking different dispatchers to finish the boot sequence.
 * This function is directly jumped from stage 2 loader and should never ever return (no return address in stack frame)
 * @return None, and is marked with [[noreturn]], so no return code is generated for main()
 */
[[noreturn, gnu::section(".kernel_entry_point")]]
NO_PLEASE_DONT_OPTIMIZE
// __attribute__((section(".kernel_entry_point")))
void main(const int32_t argc, const int32_t *argv)
{
    install_irq();

    if (argc != 2 || argv == nullptr) {
        die("Invalid loader arguments");
    }

    if (memcmp(MAGIC, "Anivice", 7) != 0) {
        die("Kernel data corrupted");
    }

    enable_fpu();
    rtc_irq_init();
    __asm__ volatile ("sti" ::: "memory");

    uint32_t below_16MB = (uint32_t)argv[0] * 1024u;
    uint32_t beyond_16MB = (uint32_t)argv[1] * 64u * 1024u;
    bool memory_hole = (beyond_16MB != 0) &&
                       (below_16MB != 15u * 1024u * 1024u);
    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");
    printk("0x00000000 - 0x00100000: Kernel Cache\n");
    printk("0x00100000 - 0x00200000: Kernel Code\n");
    if (memory_hole)
    {
        printk("0x00200000 - 0x%x: Main memory\n", below_16MB);
        printk("0x%x - 0x%x: Main memory\n", below_16MB, beyond_16MB);
    } else {
        printk("0x200000 - 0x%x: Main memory\n", below_16MB + beyond_16MB + 1024u * 1024u);
    }
    printk("System has %u KB memory in total\n", (below_16MB + beyond_16MB) / 1024u + 1024u);

    if (memory_hole)
    {
        die("Memory hole in lower 16MB part");
    }

    while (rtc_get_uptime() < 3)
        __asm__ volatile ("hlt" ::: "memory");

    /////////////////////////////////////////////////////////////
    die("Unexpected reach of the end of kernel entry point");
}
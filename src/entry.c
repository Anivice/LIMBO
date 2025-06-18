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

#include "printk.h"
#include "rtc.h"
#include "types.h"
#include "irq.h"
#include "die.h"
#include "ide.h"
#include "syscall.h"

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
    __asm__ volatile ("ljmpl $0x10, $0x200000");

    /////////////////////////////////////////////////////////////
    die("Unexpected reach of the end of kernel entry point!");
}

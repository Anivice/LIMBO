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
#include "stdint.h"
#include "idt.h"

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

__attribute__((naked))
void iret_stub(void)
{
    __asm__ volatile ("iret");
}

static void install_irq(void)
{
    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t)&idt;

    __asm__ volatile (
        "   cli                                     \n\t"
        "   lidt        (%%eax)                     \n\t"
        : : "a"((uint32_t)&idt_descriptor) : "memory"
    );

    for (int i = 0; i < 256; i++)
    {
        idt[i].offset_low = ((uint32_t)(void*)iret_stub) & 0xFFFF;
        idt[i].offset_high = ((uint32_t)(void*)iret_stub) >> 16;
        idt[i].selector = 0x10; // #2, flat 4GB
        idt[i].zero = 0;
        idt[i].type_attr = 0x8E;
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
void main()
{
    enable_fpu();
    install_irq();
    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");
    uptime = 5521;
    printk("%d\n", uptime);
    while (true);
}

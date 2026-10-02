/*!
 * @file irq.c
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
 * @brief This file defines interrupt dummies for kernel, for debug purposes only
 **/

#include "irq.h"

static const char irq_message[] __attribute__((used)) =
    "Unhandled processor exception or interrupt";

__attribute__((naked))
static void irq_terminal()
{
    __asm__ (
        "cli                        \n\t"
        "cld                        \n\t"
        "mov    $0x08,      %ax     \n\t"
        "mov    %ax,        %ds     \n\t"
        "mov    %ax,        %es     \n\t"
        "xor    %ebp,       %ebp    \n\t"
        "and    $-16,       %esp    \n\t"
        "sub    $12,        %esp    \n\t"
        "push   $irq_message        \n\t"
        "call   die                 \n\t"
     "1: hlt                        \n\t"
        "jmp    1b                  \n\t"
    );
}

void *irq_dummy_table[256];

void irq_dummies_init()
{
    for (unsigned i = 0; i < 256; ++i) {
        irq_dummy_table[i] = irq_terminal;
    }
}
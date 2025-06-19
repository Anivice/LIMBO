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
#include "die.h"

__attribute__((naked)) void irq_dummy_0()           { die("INT 000"); }
__attribute__((naked)) void irq_dummy_1()           { die("INT 001"); }
__attribute__((naked)) void irq_dummy_2()           { die("INT 002"); }
__attribute__((naked)) void irq_dummy_3()           { die("INT 003"); }
__attribute__((naked)) void irq_dummy_4()           { die("INT 004"); }
__attribute__((naked)) void irq_dummy_5()           { die("INT 005"); }
__attribute__((naked)) void irq_dummy_6()           { die("INT 006"); }
__attribute__((naked)) void irq_dummy_7()           { die("INT 007"); }
__attribute__((naked)) void irq_dummy_8()           { die("INT 008"); }
__attribute__((naked)) void irq_dummy_9()           { die("INT 009"); }
__attribute__((naked)) void irq_dummy_10()          { die("INT 010"); }
__attribute__((naked)) void irq_dummy_11()          { die("INT 011"); }
__attribute__((naked)) void irq_dummy_12()          { die("INT 012"); }
__attribute__((naked)) void irq_dummy_13()          { die("INT 013"); }
__attribute__((naked)) void irq_dummy_14()          { die("INT 014"); }
__attribute__((naked)) void irq_dummy_15()          { die("INT 015"); }
__attribute__((naked)) void irq_dummy_16()          { die("INT 016"); }
__attribute__((naked)) void irq_dummy_17_to_31()    { __asm__("iret");   }
__attribute__((naked)) void irq_dummy_32_to_255()   { __asm__("iret");   }

void * irq_dummy_table[256];

void irq_dummies_init()
{
    irq_dummy_table[0] = irq_dummy_0;
    irq_dummy_table[1] = irq_dummy_1;
    irq_dummy_table[2] = irq_dummy_2;
    irq_dummy_table[3] = irq_dummy_3;
    irq_dummy_table[4] = irq_dummy_4;
    irq_dummy_table[5] = irq_dummy_5;
    irq_dummy_table[6] = irq_dummy_6;
    irq_dummy_table[7] = irq_dummy_7;
    irq_dummy_table[8] = irq_dummy_8;
    irq_dummy_table[9] = irq_dummy_9;
    irq_dummy_table[10] = irq_dummy_10;
    irq_dummy_table[11] = irq_dummy_11;
    irq_dummy_table[12] = irq_dummy_12;
    irq_dummy_table[13] = irq_dummy_13;
    irq_dummy_table[14] = irq_dummy_14;
    irq_dummy_table[15] = irq_dummy_15;
    irq_dummy_table[16] = irq_dummy_16;
    for (int i = 17; i <= 31; i++)
    {
        irq_dummy_table[i] = irq_dummy_17_to_31;
    }

    for (int i = 32; i <= 255; i++)
    {
        irq_dummy_table[i] = irq_dummy_32_to_255;
    }
}

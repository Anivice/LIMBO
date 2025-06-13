/*!
 * @file io.c
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
 * @brief This file defines C wrapper for instructions `in` and `out`
 **/

#include "io.h"

void out8(unsigned short port, unsigned char value)
{
    __asm__ volatile (
        "outb   %%al,   %%dx        \n\t"
        :
        : "d"(port), "a"(value)
        : "memory"
    );
}

void out16(unsigned short port, unsigned short value)
{
    __asm__ volatile (
        "outw   %%ax,   %%dx        \n\t"
        :
        : "d"(port), "a"(value)
        : "memory"
    );
}

void in8(unsigned short port, unsigned char *value)
{
    unsigned char result;
    __asm__ volatile (
        "xor    %%eax,  %%eax       \n\t"
        "inb    %%dx,   %%al        \n\t"
        : "=a"(result)
        : "d"(port), "0"(value)
        : "memory"
    );

    *value = result;
}

void in16(unsigned short port, unsigned short *value)
{
    unsigned short result;
    __asm__ volatile (
        "xor    %%eax,  %%eax       \n\t"
        "inw    %%dx,   %%ax        \n\t"
        : "=a"(result)
        : "d"(port), "0"(value)
        : "memory"
    );

    *value = result;
}

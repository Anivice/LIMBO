/*!
 * @file gpu.c
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
 * @brief This file defines GPU VGA video editor functions
 **/

#include "gpu.h"
#include "io.h"

#define GPU_REGISTER_INDEX (0x3d4)
#define GPU_CURSOR_H8_BIT  (0x0e)
#define GPU_CURSOR_L8_BIT  (0x0f)
#define GPU_INDEXED_REG_IO (0x3d5)

void write_to_video_memory(char c, unsigned loc, unsigned char attr)
{
    __asm__ volatile (
        "movb   %b0,(%1,%2,2)\n\t"
        :
        : "q"(c),                   /* operand 0: any low-8-bit reg (al, bl, cl, dl) */
          "r"((void*)0xB8000),      /* operand 1: base pointer in any GP reg */
          "r"(loc)                  /* operand 2: index in any GP reg */
        : "memory"                  /* clobber memory so store isn’t optimized away */
    );

    __asm__ volatile (
        "movb   %b0,(%1,%2,2)\n\t"
        :
        : "q"(attr), "r"((void*)0xB8001), "r"(loc)
        : "memory"
    );
}

unsigned short get_cursor_loc()
{
    unsigned short loc;
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_H8_BIT);
    in8(GPU_INDEXED_REG_IO, (unsigned char*)&loc + 1);
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_L8_BIT);
    in8(GPU_INDEXED_REG_IO, (unsigned char*)&loc);

    return loc;
}

void set_cursor_loc(unsigned short loc)
{
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_H8_BIT);
    out8(GPU_INDEXED_REG_IO, ((unsigned char*)&loc)[1]);
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_L8_BIT);
    out8(GPU_INDEXED_REG_IO, (unsigned char)loc);
}

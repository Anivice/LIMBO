/*!
 * @file backtracer.c
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
 * @brief This file defines a backtrace functionality for GCC C code
 **/

#include "../include/backtracer.h"
#include "types.h"

// Must compile with -fno-omit-frame-pointer.
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames)
{
    struct stackframe_t__ *frame;
    asm("movl %%ebp, %0" : "=r"(frame));

    uint32_t count = 0;
    while (frame && count < max_frames)
    {
        addrs[count++] = (uint32_t)(void*)frame->eip;
        frame = frame->ebp;
    }

    return count - 1;
}

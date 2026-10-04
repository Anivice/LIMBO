/*!
 * @file backtracer.c
 * @brief This file defines a backtrace functionality for GCC C code
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
 **/

#include "backtracer.h"
#include "types.h"
#include "marco.h"

NO_PLEASE_DONT_OPTIMIZE
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames)
{
    uint32_t address;
    __asm__ volatile ("movl %%ebp, %0" : "=r"(address));
    uint32_t count = 0;

    if (addrs == nullptr) return 0;
    while (count < max_frames)
    {
        if ((address & 3u) != 0 ||
            address < KERNEL_STACK_BOTTOM ||
            address > KERNEL_STACK_TOP - sizeof(stackframe_t))
        {
            break;
        }

        const stackframe_t *frame = (const stackframe_t *)address;
        uint32_t next = (uint32_t)frame->ebp;
        uint32_t ret = frame->eip;
        if (ret < 0x100000u || ret >= 0x140000u) break;
        addrs[count++] = ret;
        if (next <= address) break;
        address = next;
    }
    return count;
}
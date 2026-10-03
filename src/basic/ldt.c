/*!
 * @file ldt.c
 * @brief This file defines descriptor utilities
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

#include "ldt.h"
#include "types.h"

segment_descriptor_t make_descriptor(const uint32_t base,
                                     const uint32_t limit,   /* 20-bit   */
                                     const uint16_t access,  /* full 8-bit access
                                                                + 4 flag bits */
                                     const uint8_t  flags)   /* G | DB | L | AVL */
{
    segment_descriptor_t d;

    /* ----- low 4 bytes ----- */
    d.limit_0_15   =  limit & 0xFFFF;
    d.base_0_15    =  base  & 0xFFFF;
    d.base_16_23   = (base  >> 16) & 0xFF;

    /* ----- high 4 bytes ---- */
    d.access       =  access & 0xFF;
    d.limit_flags  = ((limit >> 16) & 0x0F) |   /* limit 19-16       */
                     (flags  & 0xF0);           /* | G/DB/L/AVL      */
    d.base_24_31   = (base  >> 24) & 0xFF;
    return d;
}
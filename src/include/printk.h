/*!
 * @file printk.h
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
 */

#ifndef PRINTK_H
#define PRINTK_H

#include "types.h"

/*!
 * @brief C-style printf-like message printer.\n
 * WARNING: it uses its own derivatives for color codes and numbers/strings:\n
 * %d   -> decimal integer\n
 * %D   -> 64-bit decimal integer\n
 * %u   -> unsigned decimal integer\n
 * %U   -> 64-bit unsigned decimal integer\n
 * %x   -> hexadecimal integer\n
 * %X   -> 64-bit hexadecimal integer\n
 * %s   -> string\n
 * %c   -> character\n
 * %f   -> float\n
 * %F   -> double\n
 * %p   -> change float precision\n
 * %N   -> hide cursor\n
 * %n   -> show cursor\n
 * %B   -> black background\n
 * %b   -> black foreground\n
 * %@   -> reset to default colors\n
 * %%   -> literal percent character, if default, prints next char\n
 *
 * @param fmt Print format
 * @param ... Attachments
 * @returns NOTHING
 */
void printk(const char * fmt, ...);

/*!
 * @brief Print a character with color attributes
 * @param c Character
 * @param attr Color attributes
 * @return NONE
 */
void put(char c, uint8_t attr);

/*!
 * @brief Translate escape code into meaningful actions
 * @param code Escape code
 * @return Action determined by provided code
 */
escape_actions_t escape(char code);

#endif //PRINTK_H

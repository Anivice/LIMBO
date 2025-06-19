/*!
 * @file string.h
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
 * @brief This file defines C style string helpers
 **/

#ifndef STRING_H
#define STRING_H

#include "stdint.h"

/*!
 * Set each byte with an initial value
 * @param dest Destination
 * @param val Value
 * @param size Buffer size
 */
void memset(void * dest, int val, uint32_t size);

/*!
 * Copy buffer from source to destination
 * @param dest Destinayion
 * @param src Source
 * @param size Size
 */
void memcpy(void * dest, const void * src, uint32_t size);

/*!
 *
 * @param s1 String 1
 * @param s2 String 2
 * @param n Size minimum of s1 and s2
 * @returns
 * The memcmp() function returns an integer less than, equal to, or greater than zero
 * if the first n bytes of s1 is found, respectively,
 * to be less than, to match, or be greater than the first n bytes of s2.
 * For a nonzero return value, the sign is determined by the sign of the difference between the first pair of bytes
 * (interpreted as un‐signed char) that differ in s1 and s2.
 * If n is zero, the return value is zero.
 */
int memcmp(const void * s1, const void * s2, uint32_t n);

/// Convert expression to C literal
#define xstr(a) str(a)

/// Convert expression to C literal
#define str(a)  #a

/*!
 * @brief C-style printf-like message printer
 * @param buffer Buffer
 * @param buffer_length Buffer length
 * @param fmt Print format
 * @param ... Attachments
 * @returns String len
 */
uint32_t sprintf(char *buffer, uint32_t buffer_length, const char * fmt, ...);

int strlen(const char * s);
int strnlen(const char * s, int maxlen);

#endif //STRING_H

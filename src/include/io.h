/*!
 * @file io.h
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
 * @brief This file define C wrapper for instructions `in` and `out`
 **/

#ifndef IO_H
#define IO_H

/*!
 * @brief output an 8 bit value to a port
 * @param port Port
 * @param value Value
 * @returns Nothing
 */
void out8(unsigned short port, unsigned char value);

/*!
 * @brief output a 16 bit value to a port
 * @param port Port
 * @param value Value
 * @returns Nothing
 */
void out16(unsigned short port, unsigned short value);

/*!
 * @brief input an 8 bit value to a port
 * @param port Port
 * @param value Value
 * @returns Nothing
 */
void in8(unsigned short port, unsigned char *value);

/*!
 * @brief input an 16 bit value to a port
 * @param port Port
 * @param value Value
 * @returns Nothing
 */
void in16(unsigned short port, unsigned short *value);

#endif //IO_H

/*!
 * @file die.h
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
 * @brief This file defines a kernel panic routine to completely halt kernel in case of a critical error
 **/

#ifndef DIE_H
#define DIE_H

/*!
 * Invoke a kernel panic
 * This will display an error message, show the update and current die time (UNIX timestamp of current time in RTC),
 * and display caller frame trace to indicate who called die().
 * Then, it will enter an endless indefinite halt and will never resume.
 * This is used to indicate an unrecoverable error happened in kernel code.
 * @param str Error message
 */
[[noreturn]] void die(const char * str);

#endif //DIE_H

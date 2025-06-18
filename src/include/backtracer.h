/*!
 * @file backtracer.h
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

#ifndef BACKTRACER_H
#define BACKTRACER_H

#include "stdint.h"

/*!
 * Backtrace stackframe
 * @param addrs Stackframe vector to store result
 * @param max_frames Max backtrace
 * @return Number of actually traced frames
 */
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames);

#endif //BACKTRACER_H

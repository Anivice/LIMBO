/*!
 * @file gpu.h
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

#ifndef GPU_H
#define GPU_H

#include "stdint.h"

/*!
 * @brief Get current cursor location
 * @return Current cursor location index [0-1999]
 */
[[nodiscard]] uint16_t get_cursor_loc();

/*!
 * @brief Set new cursor location
 * @param loc New cursor location
 * @returns Nothing
 */
void set_cursor_loc(uint16_t loc);

/*!
 * @brief Write directly to VGA video memory
 * @param c ASCII code
 * @param loc Cursor location offset
 * @param attr Color attributes
 * @returns Nothing
 */
void write_to_video_memory(char c, uint32_t loc, uint8_t attr);

/// Hide cursor
void cursor_hide();

/// Show cursor
void cursor_show();

#endif //GPU_H

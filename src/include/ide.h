/*!
 * @file ide.h
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
 * @brief This file defines IDE disk reader and writer
 **/

#ifndef IDE_H
#define IDE_H

#include "stdint.h"

/*!
 * @brief Read disk, buffer will need to be 512 aligned, 0 < count <= 255 (0 will cause the operation to be discarded)
 * @param buffer Destination buffer
 * @param sector Starting sector
 * @param count Sector count
 * @returns Error code, 0 means successful
 */
[[nodiscard]]
int disk_read(char * buffer, uint32_t sector, uint8_t count);

/*!
 * @brief Write disk, buffer will need to be 512 aligned, 0 < count <= 255 (0 will cause the operation to be discarded)
 * @param buffer Source buffer
 * @param sector Starting sector
 * @param count Sector count
 * @returns Error code, 0 means successful
 */
[[nodiscard]]
int disk_write(const char *buffer, uint32_t sector, uint8_t count);

#endif //IDE_H

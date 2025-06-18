/*!
 * @file irq.h
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
 * @brief This file defines IRQ dummies for kernel, for debug purposes only
 **/

#ifndef IRQ_DUMMIES_H
#define IRQ_DUMMIES_H

/// Dummy IRQ table
extern void * irq_dummy_table[256];

/// Initialize dummy IRQ service routines
void irq_dummies_init();

#endif //IRQ_DUMMIES_H

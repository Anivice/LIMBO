/*!
 * @file idt.h
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
 * @brief This file defines IDT interrupt helper
 **/

#ifndef LIMBO_IDT_H_
#define LIMBO_IDT_H_

#include "types.h"

/// IDT table
extern idt_entry_t idt[256];
/// IDT descriptor
extern idt_descriptor_t idt_descriptor;

/*!
 * Set new IDT interrupt service gate
 * @param vector IRQ interrupt service vector
 * @param handler_addr Address of the handler
 * @param selector Code segment selector, always 0x10 (#2)
 * @param flags Service routine flag
 */
void idt_set_gate(uint8_t vector, uint32_t handler_addr, uint16_t selector, uint8_t flags);

#endif /* LIMBO_IDT_H_ */

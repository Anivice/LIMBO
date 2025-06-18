/*!
 * @file idt.c
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

#include "idt.h"

idt_entry_t idt[256];
idt_descriptor_t idt_descriptor;

void idt_set_gate(const uint8_t vector, const uint32_t handler_addr, const uint16_t selector, const uint8_t flags)
{
    idt[vector].offset_low  = handler_addr & 0xFFFF;
    idt[vector].selector    = selector;
    idt[vector].zero        = 0;
    idt[vector].type_attr   = flags;
    idt[vector].offset_high = (handler_addr >> 16) & 0xFFFF;
}

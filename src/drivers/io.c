/*!
 * @file io.c
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
 * @brief This file defines C wrapper for instructions `in` and `out`
 **/

#include "io.h"

void out8(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %b0, %w1"
                      : : "a"(value), "Nd"(port) : "memory");
}

void out16(uint16_t port, uint16_t value)
{
    __asm__ volatile ("outw %w0, %w1"
                      : : "a"(value), "Nd"(port) : "memory");
}

void in8(uint16_t port, uint8_t *value)
{
    uint8_t result;
    __asm__ volatile ("inb %w1, %b0"
                      : "=a"(result) : "Nd"(port) : "memory");
    *value = result;
}

void in16(uint16_t port, uint16_t *value)
{
    uint16_t result;
    __asm__ volatile ("inw %w1, %w0"
                      : "=a"(result) : "Nd"(port) : "memory");
    *value = result;
}

uint8_t inb(const uint16_t port)
{
    uint8_t value;
    in8(port, &value);
    return value;
}

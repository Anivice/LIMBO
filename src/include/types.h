/*!
 * @file types.h
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
 * @brief This file defines multiple types
 **/

#ifndef TYPES_H
#define TYPES_H

#include "stdint.h"

/// IDT entry for 32-bit interrupt gates
typedef struct idt_entry_t__ {
    uint64_t offset_low:16;     // lower 16 bits of handler address
    uint64_t selector:16;       // code segment selector in GDT/LDT
    uint64_t zero:8;            // must be 0
    uint64_t type_attr:8;       // type and attributes (flags)
    uint64_t offset_high:16;    // upper 16 bits of handler address
} idt_entry_t;

/// IDT Register
typedef struct idt_descriptor_t__ {
    uint16_t limit;                 // IDT boundary
    uint32_t base;                  // IDT linear base
} __attribute__((packed)) idt_descriptor_t;

/// Stack frame
typedef struct stackframe_t__ {
    struct stackframe_t__ *ebp;     // saved EBP of caller
    uint32_t eip;                   // return address (saved EIP)
} stackframe_t;

/// Page pointer
typedef struct page_t__ {
    uint32_t P:1;               // Present
    uint32_t RW:1;              // Read/Write 0 means Read-only
    uint32_t US:1;              // User/Supervisor 0 means DPL=3 would be denied
    uint32_t PWT:1;             // Page-level Write-Through
    uint32_t PCD:1;             // Page-level Cache Disable
    uint32_t A:1;               // Accessed, set by CPU, used as indicator for swap
    uint32_t D:1;               // Dirty, set by CPU, means it wrote data to the page, used as async cache flush indicator
    uint32_t PAT:1;             // Page Attribute Table, for more complicated paging
    uint32_t G:1;               // Global, used in high speed cache. Global means page will always be inside high speed cache
    uint32_t AVL:3;             // Ignored by CPU, can be repurposed by programmer
    uint32_t page_base:20;      // Page base address
} page_t;

/// Page directory pointer
typedef struct page_dir_t__ {
    uint32_t P:1;               // Present
    uint32_t RW:1;              // Read/Write 0 means Read-only
    uint32_t US:1;              // User/Supervisor 0 means DPL=3 would be denied
    uint32_t PWT:1;             // Page-level Write-Through
    uint32_t PCD:1;             // Page-level Cache Disable
    uint32_t A:1;               // Accessed, set by CPU, used as indicator for swap
    uint32_t D:1;               // Dirty, set by CPU, means it wrote data to the page, used as async cache flush indicator
    uint32_t ___reserved_0__:1; // ignored, and always 0
    uint32_t G:1;               // Global, used in high speed cache. Global means page will always be inside high speed cache
    uint32_t AVL:3;             // Ignored by CPU, can be repurposed by programmer
    uint32_t page_dir_base:20;  // Page directory base address
} page_dir_t;

/*!
 * @brief Escape actions denoted by escape code '%'
 */
typedef enum escape_actions {
    PRINT_NEXT_CHARACTER,               // print character right after %
    PRINT_NUMBER_IN_BASE10,             // print signed number in base 10 (decimal)
    PRINT_UNSIGNED_NUMBER_IN_BASE10,    // print unsigned number in base 10 (decimal)
    PRINT_NUMBER_IN_BASE16,             // print unsigned number in base 16 (hexadecimal)
    PRINT_64BIT_NUMBER_IN_BASE10,       // print signed number in base 10 (decimal)
    PRINT_64BIT_UNSIGNED_NUMBER_IN_BASE10, // print unsigned number in base 10 (decimal)
    PRINT_64BIT_NUMBER_IN_BASE16,       // print unsigned number in base 16 (hexadecimal)
    PRINT_STRING,                       // print a const char * string
    PRINT_CHARACTER,                    // print a char
    PRINT_FLOAT,                        // print a float point
    PRINT_DOUBLE,                       // print a double float
    FLOAT_PRECISION_CHANGE,             // precision change

    CURSOR_HIDE,                        // cursor hide
    CURSOR_SHOW,                        // cursor show

    SET_FONT_COLOR_BLACK,               // set text color to be black
    SET_FONT_COLOR_BLUE,                // set text color to be blue
    SET_FONT_COLOR_GREEN,               // set text color to be green
    SET_FONT_COLOR_CYAN,                // set text color to be cyan
    SET_FONT_COLOR_RED,                 // set text color to be red
    SET_FONT_COLOR_MAGENTA,             // set text color to be magenta
    SET_FONT_COLOR_YELLOW,              // set text color to be yellow
    SET_FONT_COLOR_WHITE,               // set text color to be white

    SET_BACK_COLOR_BLACK,               // set background color to be black
    SET_BACK_COLOR_BLUE,                // set background color to be blue
    SET_BACK_COLOR_GREEN,               // set background color to be green
    SET_BACK_COLOR_CYAN,                // set background color to be cyan
    SET_BACK_COLOR_RED,                 // set background color to be red
    SET_BACK_COLOR_MAGENTA,             // set background color to be magenta
    SET_BACK_COLOR_YELLOW,              // set background color to be yellow
    SET_BACK_COLOR_WHITE,               // set background color to be white

    SET_TO_DEFAULT_COLOR,               // set background color to be black and text to be white
} escape_actions_t;

#endif //TYPES_H

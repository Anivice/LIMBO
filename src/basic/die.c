/*!
 * @file die.c
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

#include "die.h"
#include "string.h"
#include "rtc.h"
#include "printk.h"
#include "../include/backtracer.h"
#include "../include/marco.h"

/*!
 * Get the current symbol table entry, and move the entry pointer to the next symbol
 * @param cursor Current symbol map pointer
 * @param name Symbol literal buffer
 * @param capacity Symbol literal buffer size
 * @return Symbol address
 */
static uint32_t query_map(char **cursor, char *name, uint32_t capacity)
{
    const unsigned char *p = (const unsigned char *)*cursor;
    const unsigned char *end = (const unsigned char *)MAGIC;
    if (capacity != 0) name[0] = '\0';

    if (p < (const unsigned char *)SYSTEM_SYMBOL_MAP ||
        p > end || (uint32_t)(end - p) < 4u) {
        return 0;
        }

    const uint32_t address = (uint32_t)p[0] |
                       ((uint32_t)p[1] << 8) |
                       ((uint32_t)p[2] << 16) |
                       ((uint32_t)p[3] << 24);
    if (address == 0) return 0;
    p += 4;

    uint32_t used = 0;
    while (p < end && *p != '\n' && *p != '\0') {
        if (capacity != 0 && used < capacity - 1) {
            name[used++] = (char)*p;
        }
        ++p;
    }
    if (capacity != 0) name[used] = '\0';
    if (p == end || *p != '\n') return 0;

    *cursor = (char *)(p + 1);
    return address;
}

/*!
 * Interpret symbol by currently provided stackframe
 * @param ip Current stacktrace
 * @param sym_ptr Symbol entry buffer
 * @param sym_name Symbol name(literal) buffer
 * @param capacity Symbol name buffer size
 */
static void get_symbol(const uint32_t ip, uint32_t *sym_ptr, char *sym_name, const uint32_t capacity)
{
    char *cursor = (char *)SYSTEM_SYMBOL_MAP;
    char candidate[32];
    *sym_ptr = 0;
    if (capacity != 0) sym_name[0] = '\0';

    for (;;) {
        uint32_t address = query_map(&cursor, candidate, sizeof(candidate));
        if (address == 0 || address > ip) break;
        if (address < 0x100000u || address >= 0x178000u) continue;

        *sym_ptr = address;
        if (capacity != 0) {
            uint32_t i = 0;
            while (i < capacity - 1 && candidate[i] != '\0') {
                sym_name[i] = candidate[i];
                ++i;
            }
            sym_name[i] = '\0';
        }
    }
}

[[noreturn]]
void die(const char *reason)
{
    __asm__ volatile ("cli" ::: "memory");
    printk("\n\n%R%wKERNEL PANIC%@\n%rREASON > %s%@\n",
           reason ? reason : "(no reason)");

    uint32_t frames[64];
    uint32_t count = backtrace(frames, sizeof(frames) / sizeof(frames[0]));
    printk("TRACED %u FRAME(S):\n", count);

    for (uint32_t i = 0; i < count; ++i) {
        char name[32];
        uint32_t symbol;
        get_symbol(frames[i] - 1u, &symbol, name, sizeof(name));
        printk(" at 0x%x: %s (0x%x)\n", frames[i],
               symbol != 0 ? name : "<unknown>", symbol);
    }

    for (;;) {
        __asm__ volatile ("hlt" ::: "memory");
    }
}
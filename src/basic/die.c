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
 * @param sysmap_ptr Current symbol map pointer
 * @param symbol_literal Symbol literal buffer
 * @param symbol_max Symbol literal buffer size
 * @return Symbol address
 */
uint32_t query_map(char ** sysmap_ptr, char * symbol_literal, const uint32_t symbol_max)
{
    uint32_t literal_off = 0;
    const uint32_t *sysmap_symbol_ip = (uint32_t *)*sysmap_ptr;
    char * symbol = (*sysmap_ptr + 4);
    while (*symbol != 0x0a)
    {
        if (literal_off < symbol_max) {
            symbol_literal[literal_off++] = *symbol;
        }

        symbol++;
    }
    symbol++;
    *sysmap_ptr = symbol;
    return *sysmap_symbol_ip;
}

/*!
 * Interpret symbol by currently provided stackframe
 * @param frame Current stacktrace
 * @param sym_ptr Symbol entry buffer
 * @param sym_name Symbol name(literal) buffer
 * @param sym_name_max Symbol name buffer size
 */
void get_symbol(const uint32_t frame, uint32_t * sym_ptr, char * sym_name, const uint32_t sym_name_max)
{
    char buffer[32] = { };
    char symbol_literal[32] = { };
    uint32_t result;
    char * sysmap;
    *(uint32_t*)(&sysmap) = (uint32_t)SYSTEM_SYMBOL_MAP;
    uint32_t symbol = 0;
    do
    {
        result = symbol;
        memcpy(symbol_literal, buffer, sizeof(buffer));
        memset(buffer, 0, sizeof(buffer));
        symbol = query_map(&sysmap, buffer, sizeof(buffer));
    } while (symbol && symbol < frame);

    memcpy(sym_name, symbol_literal, MIN(sym_name_max, sizeof(symbol_literal)));
    *sym_ptr = result;
}

[[noreturn]]
void die(const char * str)
{
    char frame_trace_literal_buffer[256] = { };
    char name_buffer[32] = { };
    uint32_t symbol = 0;
    uint32_t stackframes[64];
    auto const frames = backtrace(stackframes, sizeof(stackframes) / sizeof(stackframes[0]));
    uint32_t offset = sprintf(frame_trace_literal_buffer, sizeof(frame_trace_literal_buffer), "TRACED %d FRAME(S):\n", frames);
    for (uint32_t i = 0; i < frames; i++)
    {
        offset += sprintf(frame_trace_literal_buffer + offset, sizeof(frame_trace_literal_buffer), " at 0x%x: ", stackframes[i]);
        memset(name_buffer, 0, sizeof(name_buffer));
        get_symbol(stackframes[i], &symbol, name_buffer, sizeof(name_buffer) - 1);
        offset += sprintf(frame_trace_literal_buffer + offset, sizeof(frame_trace_literal_buffer), "%s (0x%x)\n", name_buffer, symbol);
    }

    printk("\n\n"
        "%R%w--------------------------------- KERNEL PANIC ---------------------------------%@"
        "%aTIME: uptime: %Ds, UNIX timestamp: %U\n"
        "%rREASON > %s%@\n"
        "%mSTACKTRACE:\n"
        "%s%@"
        "%R%w--------------------------------------------------------------------------------%@",
        str, uptime, read_rtc(), frame_trace_literal_buffer);
    while (1)
    {
        __asm__ __volatile__("cli\n\thlt");
    }
}

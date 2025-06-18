/*!
 * @file printk.c
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
 * @brief This file defines the kernel side C-style printf-like function
 */

#include "printk.h"
#include "gpu.h"
#include "stdint.h"
#include "types.h"

/*!
 * @brief Scroll screen upwards one line
 * @return NONE
 */
static void scroll_one_line()
{
    __asm__ __volatile__(
        "push       %%edi                               \n\t"
        "pusha                                          \n\t"
        "mov        $0xB8000,               %%edi       \n\t" // destination
        "mov        $0xB8000+80*2,          %%esi       \n\t" // src: start of the second line
        "mov        $2000-80,               %%ecx       \n\t" // { 2000 (all the character on screen) - 80 (first line) } * 2
        // == all the data on screen except for the first line
        "cld                                            \n\t" // direction
        "rep movsw                                      \n\t" // move
        // now we need to clear all the characters at the bottom of the screen
        "mov        $0xB8000+1920*2,        %%edi       \n\t" // dest
        "mov        $80,                    %%ecx       \n\t" // count
        "scroll_one_line.clear_bottom:                  \n\t"
        "    movb   $' ',                   (%%edi)     \n\t"
        "    inc    %%edi                               \n\t"
        "    movb   $0x07,                  (%%edi)     \n\t"
        "    inc    %%edi                               \n\t"
        "loop scroll_one_line.clear_bottom              \n\t"
        "popa                                           \n\t"
        "pop        %%edi                               \n\t"
        :
        :
        : "memory", "cc"
        );
}

/*!
 * @brief Puc one ASCII character on screen and perform cursor moving and screen scrolling automatically
 * @param c ASCII code to pur on screen
 * @param attr Color attribute
 * @return NONE
 */
void putc(const char c, const uint8_t attr)
{
    uint16_t cursor_pos = get_cursor_loc();

    if (c == '\r')
    {
        set_cursor_loc(cursor_pos / 80 * 80);
        return;
    }

    if ((cursor_pos >= 1920 && c == '\n') || cursor_pos == 1999)
    {
        scroll_one_line();
        if (c == '\n') {
            set_cursor_loc(1920);
            return;
        }

        set_cursor_loc(1919);
        cursor_pos = 1919;
    }

    if (c == '\n')
    {
        // if (cursor_pos % 80 != 0) {
        const uint16_t new_index = (cursor_pos / 80) * 80 + 80;
        set_cursor_loc(new_index);
        // }

        return;
    }

    write_to_video_memory(c, cursor_pos, attr);
    set_cursor_loc(cursor_pos + 1);
}

void put(const char c)
{
    putc(c, 0x07);
}

/*!
 * @brief Print unsigned number on screen
 * @param num Unsigned number
 * @param attr Color attributes
 * @param base16 Is base16 mode active
 * @return NONE
 */
void print_num(uint64_t num, const uint8_t attr, const bool base16)
{
    uint32_t p = 0;
    int i = 0;
    int base = base16 ? 16 : 10;

    if (num == 0)
    {
        putc('0', attr);
        return;
    }

    while (num != 0)
    {
        p = num % base;
        __asm__ volatile("push %0" : : "r"(p) : "memory");
        num /= base;
        i++;
    }

    for (; i > 0; i--)
    {
        __asm__ volatile("pop %0" : "=r"(p) : "0"(p) : "memory");
        char out = (char)('0' + p);
        if (out > '9') {
            out += 'A' - '9' - 1; // skip other ASCII map directly to 'A' - 'Z' region
        }
        putc(out, attr);
    }
}

/*!
 * @brief Print signed number on screen
 * @param num Signed number
 * @param attr Color attributes
 * @return NONE
 */
void print_signed(int num, const uint8_t attr)
{
    uint32_t unsigned_num = *(uint32_t*)&num;
    if ((unsigned_num & 0x80000000) != 0) {
        putc('-', attr);
        unsigned_num = ~unsigned_num;
        unsigned_num++;
    }

    print_num(unsigned_num, attr, false);
}

void print_64bit_signed(int64_t num, const uint8_t attr)
{
    uint64_t unsigned_num = *(uint64_t*)&num;
    if ((unsigned_num & 0x8000000000000000) != 0) {
        putc('-', attr);
        unsigned_num = ~unsigned_num;
        unsigned_num++;
    }

    print_num(unsigned_num, attr, false);
}

/*!
 * @brief Print float-point
 * @param value Number
 * @param precision Precision (decimal count)
 * @param attr Color attributes
 * @return NONE
 */
void print_double(double value, const int precision, const uint8_t attr)
{
    uint64_t int_part = 0;
    double frac_part;
    uint64_t scale = 0;
    uint64_t frac_scaled = 0;
    uint64_t div = 0;

    // Deal with sign first.
    if (value < 0.0)
    {
        putc('-', attr); value = -value;
    }

    // Separate the integer and fractional parts.
    int_part = (uint64_t) value;
    frac_part = value - (double) int_part;

    // Print the integer part.
    print_num(int_part, attr, false);

    // Print fractional part, if requested.
    if (precision > 0)
    {
        putc('.', attr);

        // Scale fractional part to an integer with rounding.
        scale = 1ULL;
        for (int i = 0; i < precision; ++i) scale *= 10ULL;

        // Add 0.5 for correct rounding.
        frac_scaled = (uint64_t)(frac_part * (double)scale + 0.5);

        // Handle cases where rounding spills into the next integer.
        if (frac_scaled >= scale) {
            ++int_part;
            frac_scaled -= scale;
        }

        // Print leading zeros in the fractional part.
        div = scale / 10ULL;
        while (div) {
            putc( (char)('0' + (frac_scaled / div) % 10), attr);
            div /= 10ULL;
        }
    }
}

/*!
 * @brief Translate escape code into meaningful actions
 * @param code Escape code
 * @return Action determined by provided code
 */
escape_actions_t escape(const char code)
{
    switch (code) {
            case 'd': return PRINT_NUMBER_IN_BASE10;
            case 'D': return PRINT_64BIT_NUMBER_IN_BASE10;
            case 'u': return PRINT_UNSIGNED_NUMBER_IN_BASE10;
            case 'U': return PRINT_64BIT_UNSIGNED_NUMBER_IN_BASE10;
            case 'x': return PRINT_NUMBER_IN_BASE16;
            case 'X': return PRINT_64BIT_NUMBER_IN_BASE16;
            case 'S': case 's': return PRINT_STRING;
            case 'C': case 'c': return PRINT_CHARACTER;

            case 'f': return PRINT_FLOAT;
            case 'F': return PRINT_DOUBLE;
            case 'p': return FLOAT_PRECISION_CHANGE;

            case 'N': return CURSOR_HIDE;
            case 'n': return CURSOR_SHOW;

            case 'B': return SET_BACK_COLOR_BLACK;
            case 'b': return SET_FONT_COLOR_BLACK;

            case 'E': return SET_BACK_COLOR_BLUE;
            case 'e': return SET_FONT_COLOR_BLUE;

            case 'G': return SET_BACK_COLOR_GREEN;
            case 'g': return SET_FONT_COLOR_GREEN;

            case 'A': return SET_BACK_COLOR_CYAN;
            case 'a': return SET_FONT_COLOR_CYAN;

            case 'R': return SET_BACK_COLOR_RED;
            case 'r': return SET_FONT_COLOR_RED;

            case 'M': return SET_BACK_COLOR_MAGENTA;
            case 'm': return SET_FONT_COLOR_MAGENTA;

            case 'Y': return SET_BACK_COLOR_YELLOW;
            case 'y': return SET_FONT_COLOR_YELLOW;

            case 'W': return SET_BACK_COLOR_WHITE;
            case 'w': return SET_FONT_COLOR_WHITE;

            case '@': return SET_TO_DEFAULT_COLOR;
        default: return PRINT_NEXT_CHARACTER;
    }
}

/*!
 * @brief Print a null-terminated const char * string
 * @param str String to print
 * @param attr Color attributes
 * @return NOTHING
 */
void puts(const char *str, const uint8_t attr)
{
    while (*str) {
        putc(*str, attr);
        str++;
    }
}

void printk(const char * fmt, ...)
{
    if (!fmt) return;
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);

    uint32_t i = 0;
    bool this_is_escape = false;
    uint8_t attr = 0x07;
    int precision = 2;
    while (fmt[i] != '\0')
    {
        if (this_is_escape)
        {
            const escape_actions_t action = escape(fmt[i]);
            switch (action)
            {
                case PRINT_NUMBER_IN_BASE10: {
                    const int num = __builtin_va_arg(ap, int);
                    print_signed(num, attr);
                    break;
                }
                case PRINT_UNSIGNED_NUMBER_IN_BASE10:
                case PRINT_NUMBER_IN_BASE16:
                {
                    const uint32_t num = __builtin_va_arg(ap, uint32_t);
                    print_num(num, attr, action == PRINT_NUMBER_IN_BASE16);
                    break;
                }
                case PRINT_64BIT_NUMBER_IN_BASE10: {
                    const int64_t num = __builtin_va_arg(ap, int64_t);

                    print_64bit_signed(num, attr);
                    break;
                }
                case PRINT_64BIT_UNSIGNED_NUMBER_IN_BASE10:
                case PRINT_64BIT_NUMBER_IN_BASE16: {
                    const uint64_t num = __builtin_va_arg(ap, uint64_t);
                    print_num(num, attr, action == PRINT_64BIT_NUMBER_IN_BASE16);
                    break;
                }
                case PRINT_STRING: {
                    const char * str = __builtin_va_arg(ap, const char *);
                    puts(str, attr);
                    break;
                }
                case PRINT_CHARACTER: {
                    const int c = __builtin_va_arg(ap, int); // 'char' is promoted to 'int' when passed through '...'
                    putc((char)c, attr);
                    break;
                }
                case PRINT_FLOAT: // 'float' is promoted to 'double' when passed through '...'
                case PRINT_DOUBLE: {
                    const double d = __builtin_va_arg(ap, double);
                    print_double(d, precision, attr);
                    break;
                }
                case FLOAT_PRECISION_CHANGE: {
                    precision = __builtin_va_arg(ap, int);
                    break;
                }
                case CURSOR_HIDE: {
                    cursor_hide();
                    break;
                }
                case CURSOR_SHOW: {
                    cursor_show();
                    break;
                }
                case SET_FONT_COLOR_BLACK: { attr &= 0xF0; break; }
                case SET_FONT_COLOR_BLUE: {
                    attr &= 0xF0;
                    attr |= 0x01;
                    break;
                }
                case SET_FONT_COLOR_GREEN: {
                    attr &= 0xF0;
                    attr |= 0x02;
                    break;
                }
                case SET_FONT_COLOR_CYAN: {
                    attr &= 0xF0;
                    attr |= 0x03;
                    break;
                }
                case SET_FONT_COLOR_RED: {
                    attr &= 0xF0;
                    attr |= 0x04;
                    break;
                }
                case SET_FONT_COLOR_MAGENTA: {
                    attr &= 0xF0;
                    attr |= 0x05;
                    break;
                }
                case SET_FONT_COLOR_YELLOW: {
                    attr &= 0xF0;
                    attr |= 0x06;
                    break;
                }
                case SET_FONT_COLOR_WHITE: {
                    attr &= 0xF0;
                    attr |= 0x07;
                    break;
                }

                case SET_BACK_COLOR_BLACK: {
                    attr &= 0x0F;
                    attr |= 0x00;
                    break;
                }
                case SET_BACK_COLOR_BLUE: {
                    attr &= 0x0F;
                    attr |= 0x10;
                    break;
                }
                case SET_BACK_COLOR_GREEN: {
                    attr &= 0x0F;
                    attr |= 0x20;
                    break;
                }
                case SET_BACK_COLOR_CYAN: {
                    attr &= 0x0F;
                    attr |= 0x30;
                    break;
                }
                case SET_BACK_COLOR_RED: {
                    attr &= 0x0F;
                    attr |= 0x40;
                    break;
                }
                case SET_BACK_COLOR_MAGENTA: {
                    attr &= 0x0F;
                    attr |= 0x50;
                    break;
                }
                case SET_BACK_COLOR_YELLOW: {
                    attr &= 0x0F;
                    attr |= 0x60;
                    break;
                }
                case SET_BACK_COLOR_WHITE: {
                    attr &= 0x0F;
                    attr |= 0x70;
                    break;
                }

                case SET_TO_DEFAULT_COLOR: {
                    attr = 0x07;
                    break;
                }

                case PRINT_NEXT_CHARACTER:
                default: putc(fmt[i], attr); break;
            }

            this_is_escape = false;
        }
        else
        {
            if (fmt[i] == '%') {
                this_is_escape = true;
            } else {
                putc(fmt[i], attr);
            }
        }

        i++;
    }

    __builtin_va_end(ap);
}

#include "printk.h"
#include "gpu.h"

void scroll_one_line()
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
        : "memory"
        );
}

void putc(const char c, const unsigned char attr)
{
    unsigned short cursor_pos = get_cursor_loc();
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
        if (cursor_pos % 80 != 0) {
            const unsigned short new_index = (cursor_pos / 80) * 80 + 80;
            set_cursor_loc(new_index);
        }

        return;
    }

    write_to_video_memory(c, cursor_pos, attr);
    set_cursor_loc(cursor_pos + 1);
}

void print_num(unsigned int num, unsigned char attr, bool base16)
{
    unsigned int p = 0;
    int i = 0;
    unsigned int base = base16 ? 16 : 10;
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


typedef enum escape_actions {
    PRINT_NEXT_CHARACTER,
    PRINT_NUMBER_IN_BASE10,
    PRINT_UNSIGNED_NUMBER_IN_BASE10,
    PRINT_NUMBER_IN_BASE16,
    PRINT_STRING,
    PRINT_CHARACTER,

    SET_FONT_COLOR_BLACK,
    SET_FONT_COLOR_BLUE,
    SET_FONT_COLOR_GREEN,
    SET_FONT_COLOR_CYAN,
    SET_FONT_COLOR_RED,
    SET_FONT_COLOR_MAGENTA,
    SET_FONT_COLOR_YELLOW,
    SET_FONT_COLOR_WHITE,

    SET_BACK_COLOR_BLACK,
    SET_BACK_COLOR_BLUE,
    SET_BACK_COLOR_GREEN,
    SET_BACK_COLOR_CYAN,
    SET_BACK_COLOR_RED,
    SET_BACK_COLOR_MAGENTA,
    SET_BACK_COLOR_YELLOW,
    SET_BACK_COLOR_WHITE,

    SET_TO_DEFAULT_COLOR,
} escape_actions_t;

escape_actions_t escape(const char code)
{
    switch (code) {
            case 'D': case 'd': return PRINT_NUMBER_IN_BASE10;
            case 'U': case 'u': return PRINT_UNSIGNED_NUMBER_IN_BASE10;
            case 'X': case 'x': return PRINT_NUMBER_IN_BASE16;
            case 'S': case 's': return PRINT_STRING;
            case 'C': case 'c': return PRINT_CHARACTER;

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

void puts(const char *str, const unsigned char attr)
{
    while (*str) {
        putc(*str, attr);
        str++;
    }
}

void printk(const char * fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);

    unsigned int i = 0;
    bool this_is_escape = false;
    unsigned char attr = 0x07;
    while (fmt[i] != '\0')
    {
        if (this_is_escape)
        {
            const escape_actions_t action = escape(fmt[i]);
            switch (action)
            {
                case PRINT_NUMBER_IN_BASE10: {
                    const int num = __builtin_va_arg(ap, int);
                    print_num(num, attr, false);
                    break;
                }
                case PRINT_UNSIGNED_NUMBER_IN_BASE10:
                case PRINT_NUMBER_IN_BASE16:
                {
                    const unsigned int num = __builtin_va_arg(ap, unsigned int);
                    print_num(num, attr, action == PRINT_NUMBER_IN_BASE16);
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

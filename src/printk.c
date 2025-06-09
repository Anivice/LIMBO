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
            const unsigned short new_index = cursor_pos / 80 + 1;
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

void printk(const char * fmt, ...)
{
}

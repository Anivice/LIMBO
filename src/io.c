#include "io.h"

void out8(unsigned short port, unsigned char value)
{
    __asm__ volatile (
        "outb   %%al,   %%dx        \n\t"
        :
        : "d"(port), "a"(value)
        : "memory"
    );
}

void out16(unsigned short port, unsigned short value)
{
    __asm__ volatile (
        "outw   %%ax,   %%dx        \n\t"
        :
        : "d"(port), "a"(value)
        : "memory"
    );
}

void in8(unsigned short port, unsigned char *value)
{
    unsigned char result;
    __asm__ volatile (
        "xor    %%eax,  %%eax       \n\t"
        "inb    %%dx,   %%al        \n\t"
        : "=a"(result)
        : "d"(port), "0"(value)
        : "memory"
    );

    *value = result;
}

void in16(unsigned short port, unsigned short *value)
{
    unsigned short result;
    __asm__ volatile (
        "xor    %%eax,  %%eax       \n\t"
        "inw    %%dx,   %%ax        \n\t"
        : "=a"(result)
        : "d"(port), "0"(value)
        : "memory"
    );

    *value = result;
}

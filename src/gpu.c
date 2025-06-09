#include "gpu.h"

#include <io.h>

#define GPU_REGISTER_INDEX (0x3d4)
#define GPU_CURSOR_H8_BIT  (0x0e)
#define GPU_CURSOR_L8_BIT  (0x0f)
#define GPU_INDEXED_REG_IO (0x3d5)

void write_to_video_memory(char c, unsigned loc, unsigned char attr)
{
    __asm__ volatile (
        "movb   %b0,(%1,%2,2)\n\t"
        :
        : "q"(c),                   /* operand 0: any low-8-bit reg (al, bl, cl, dl) */
          "r"((void*)0xB8000),      /* operand 1: base pointer in any GP reg */
          "r"(loc)                  /* operand 2: index in any GP reg */
        : "memory"                  /* clobber memory so store isn’t optimized away */
    );

    __asm__ volatile (
        "movb   %b0,(%1,%2,2)\n\t"
        :
        : "q"(attr), "r"((void*)0xB8001), "r"(loc)
        : "memory"
    );
}

unsigned short get_cursor_loc()
{
    unsigned short loc;
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_H8_BIT);
    in8(GPU_INDEXED_REG_IO, (unsigned char*)&loc + 1);
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_L8_BIT);
    in8(GPU_INDEXED_REG_IO, (unsigned char*)&loc);

    return loc;
}

void set_cursor_loc(unsigned short loc)
{
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_H8_BIT);
    out8(GPU_INDEXED_REG_IO, ((unsigned char*)&loc)[1]);
    out8(GPU_REGISTER_INDEX, GPU_CURSOR_L8_BIT);
    out8(GPU_INDEXED_REG_IO, (unsigned char)loc);
}

// void printk(const char *format, ...);

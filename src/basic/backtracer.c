#include "../include/backtracer.h"
#include "types.h"

// Must compile with -fno-omit-frame-pointer.
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames)
{
    struct stackframe_t__ *frame;
    asm("movl %%ebp, %0" : "=r"(frame));

    uint32_t count = 0;
    while (frame && count < max_frames)
    {
        addrs[count++] = (uint32_t)(void*)frame->eip;
        frame = frame->ebp;
    }

    return count - 1;
}

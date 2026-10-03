#include "ldt.h"
#include "types.h"

segment_descriptor_t make_descriptor(const uint32_t base,
                                     const uint32_t limit,   /* 20-bit   */
                                     const uint16_t access,  /* full 8-bit access
                                                                + 4 flag bits */
                                     const uint8_t  flags)   /* G | DB | L | AVL */
{
    segment_descriptor_t d;

    /* ----- low 4 bytes ----- */
    d.limit_0_15   =  limit & 0xFFFF;
    d.base_0_15    =  base  & 0xFFFF;
    d.base_16_23   = (base  >> 16) & 0xFF;

    /* ----- high 4 bytes ---- */
    d.access       =  access & 0xFF;
    d.limit_flags  = ((limit >> 16) & 0x0F) |   /* limit 19-16       */
                     (flags  & 0xF0);           /* | G/DB/L/AVL      */
    d.base_24_31   = (base  >> 24) & 0xFF;
    return d;
}
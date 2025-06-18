#include "ldt.h"
#include "types.h"

segment_descriptor_t make_descriptor(const uint32_t base, const uint16_t limit, const uint16_t attr)
{
    segment_descriptor_t descriptor;
    descriptor.limit_0_15 = limit & 0xFFFF;
    descriptor.limit_16_19 = (limit >> 16) & 0xF;
    descriptor.base_0_15 = base & 0xFFFF;
    descriptor.base_16_23 = (base >> 16) & 0xFF;
    descriptor.base_24_31 = (base >> 24) & 0xFF;
    descriptor.type_attr = attr & 0x0F;
    descriptor.S = (attr >> 4) & 0x1;
    descriptor.DPL = (attr >> 5) & 0x3;
    descriptor.P = (attr >> 7) & 0x1;
    descriptor.AVL = (attr >> 8) & 0x1;
    descriptor.L = (attr >> 9) & 0x1;
    descriptor.DB = (attr >> 10) & 0x1;
    descriptor.G = (attr >> 11) & 0x1;
    return descriptor;
}

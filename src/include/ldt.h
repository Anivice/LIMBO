#ifndef LDT_H
#define LDT_H

#include "types.h"
segment_descriptor_t make_descriptor(uint32_t base, uint32_t limit, uint16_t access, uint8_t flags);

#endif //LDT_H

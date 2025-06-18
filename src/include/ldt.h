#ifndef LDT_H
#define LDT_H

#include "types.h"
segment_descriptor_t make_descriptor(const uint32_t base, const uint16_t limit, const uint16_t attr);

#endif //LDT_H

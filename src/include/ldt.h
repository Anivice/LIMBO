#ifndef LDT_H
#define LDT_H

#include "types.h"

/// @brief make a descriptor in easier to understand way
/// @param base Base address
/// @param limit segment limit (20 bits)
/// @param access permissions and flag bits (12 bits. 8 permission, 4 flags)
/// @param flags segment flags (G | DB | L | AVL)
/// @return segment_descriptor_t, CPU understandable
segment_descriptor_t make_descriptor(uint32_t base, uint32_t limit, uint16_t access, uint8_t flags);

#endif //LDT_H

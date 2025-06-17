#ifndef TYPES_H
#define TYPES_H

#include "stdint.h"

/* IDT entry for 32-bit interrupt gates */
typedef struct {
    uint64_t offset_low:16;     // lower 16 bits of handler address
    uint64_t selector:16;       // code segment selector in GDT/LDT
    uint64_t zero:8;            // must be 0
    uint64_t type_attr:8;       // type and attributes (flags)
    uint64_t offset_high:16;    // upper 16 bits of handler address
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_descriptor_t;

#endif //TYPES_H

#include "idt.h"

idt_entry_t idt[256];
idt_descriptor_t idt_descriptor;

void idt_set_gate(const uint8_t vector, const uint32_t handler_addr, const uint16_t selector, const uint8_t flags)
{
    idt[vector].offset_low  = handler_addr & 0xFFFF;
    idt[vector].selector    = selector;
    idt[vector].zero        = 0;
    idt[vector].type_attr   = flags;
    idt[vector].offset_high = (handler_addr >> 16) & 0xFFFF;
}

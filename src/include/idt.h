#ifndef LIMBO_IDT_H_
#define LIMBO_IDT_H_

#include "types.h"

extern idt_entry_t idt[256];  // IDT table
extern idt_descriptor_t idt_descriptor;
void idt_set_gate(uint8_t vector, uint32_t handler_addr, uint16_t selector, uint8_t flags);

#endif /* LIMBO_IDT_H_ */


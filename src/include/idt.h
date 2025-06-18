#ifndef LIMBO_IDT_H_
#define LIMBO_IDT_H_

#include "types.h"

/// IDT table
extern idt_entry_t idt[256];
/// IDT descriptor
extern idt_descriptor_t idt_descriptor;

/*!
 * Set new IDT interrupt service gate
 * @param vector IRQ interrupt service vector
 * @param handler_addr Address of the handler
 * @param selector Code segment selector, always 0x10 (#2)
 * @param flags Service routine flag
 */
void idt_set_gate(uint8_t vector, uint32_t handler_addr, uint16_t selector, uint8_t flags);

#endif /* LIMBO_IDT_H_ */

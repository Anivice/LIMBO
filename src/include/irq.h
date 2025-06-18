#ifndef IRQ_DUMMIES_H
#define IRQ_DUMMIES_H

/// Dummy IRQ table
extern void * irq_dummy_table[256];

/// Initialize dummy IRQ service routines
void irq_dummies_init();

#endif //IRQ_DUMMIES_H

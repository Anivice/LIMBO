#ifndef PAGE_H
#define PAGE_H

#include "stdint.h"

void page_init();
void page_enable();
void tlb_flush();
void page_entry_set_present(uint32_t vaddr, int p);

#endif //PAGE_H

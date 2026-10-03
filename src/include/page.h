#ifndef PAGE_H
#define PAGE_H

#include "types.h"

void page_init();
void page_enable();
void tlb_flush();
void page_entry_set_present(uint32_t vaddr, int p);

extern page_dir_t page_directory[1024];
extern page_t page_table[1024];

#endif //PAGE_H

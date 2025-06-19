#ifndef PAGE_H
#define PAGE_H

#include "types.h"

extern __attribute__((aligned(4096))) page_dir_t page_directory[1024];
extern __attribute__((aligned(4096))) page_t page_table[1024];

#endif //PAGE_H

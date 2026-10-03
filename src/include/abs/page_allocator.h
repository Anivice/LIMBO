#ifndef LIMBO_PAGE_ALLOCATOR_H
#define LIMBO_PAGE_ALLOCATOR_H

#include "bitmap.h"

#define page_alloc_bitmap_start     ((uint8_t*)(void*)(256u*1024))
#define page_alloc_bitmap_end       ((uint8_t*)(void*)(256u*1024 + 128*1024))
#define page_alloc_bitmap_size      ((uint32_t)(128*1024))
#define page_alloc_bitmap_particles ((uint32_t)(1024*1024*1024*4ull/4096))

#endif //LIMBO_PAGE_ALLOCATOR_H

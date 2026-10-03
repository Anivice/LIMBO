#ifndef LIMBO_PAGE_ALLOCATOR_H
#define LIMBO_PAGE_ALLOCATOR_H

#include "bitmap.h"

#define page_alloc_bitmap_start     ((uint8_t*)(void*)(256u*1024))
#define page_alloc_bitmap_end       ((uint8_t*)(void*)(256u*1024 + 128*1024))
#define page_alloc_bitmap_size      ((uint32_t)(128*1024))
#define page_alloc_bitmap_particles ((uint32_t)(1024*1024*1024*4ull/4096))

typedef struct page_alloc_bitmap_t {
    bitmap_t bitmap;
    uint32_t free_pages;
} page_alloc_bitmap_t;

/*!
 * Allocate a new page. The page will be set as present upon allocation, usable at ring 0.
 * @param this page allocator context
 * @return New page index
 */
[[nodiscard]] uint64_t allocate_page(page_alloc_bitmap_t * this);

#endif //LIMBO_PAGE_ALLOCATOR_H

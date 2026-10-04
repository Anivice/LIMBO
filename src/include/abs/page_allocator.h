#ifndef LIMBO_PAGE_ALLOCATOR_H
#define LIMBO_PAGE_ALLOCATOR_H

#include "bitmap.h"

/* Physical frames: [0, 2 MiB) permanently reserved; only E820 usable RAM
 * above it may fund allocations and page tables. Physical and virtual
 * allocation are separate: allocate_page returns a frame index, not a pointer.
 */
#define KERNEL_IDENTITY_END         0x200000u
#define KERNEL_HEAP_START           0x80000000u
#define KERNEL_HEAP_END             0xC0000000u
#define page_alloc_bitmap_start     ((uint8_t*)(void*)(256u*1024))
#define page_alloc_bitmap_end       ((uint8_t*)(void*)(256u*1024 + 128*1024))
#define page_alloc_bitmap_size      ((uint32_t)(128*1024))
#define page_alloc_bitmap_particles ((uint32_t)(1024*1024*1024*4ull/4096))

typedef struct page_alloc_bitmap_t {
    bitmap_t bitmap;
    uint32_t free_pages;
} page_alloc_bitmap_t;

/* After E820 reservations, before page_enable(). Context must outlive heap. */
void page_allocator_init(page_alloc_bitmap_t *context);

/* Raw physical frames, not automatically mapped. Only pass owned, unmapped
 * frames to free_page; never free malloc storage or paging structures here.
 * OOM panics. Single CPU: operations preserve IF and exclude IRQ reentry.
 */
[[nodiscard]] uint64_t allocate_page(page_alloc_bitmap_t *context);
void free_page(page_alloc_bitmap_t *context, uint64_t page);

/* After page_enable(): contiguous virtual storage backed by arbitrary frames.
 * 16-byte alignment/header, page-granular allocation. malloc(0) returns nullptr;
 * free(nullptr) is a no-op. Other allocation failures panic with OOM.
 * Only exact live pointers returned by malloc may be passed to free.
 */
[[nodiscard]] void *malloc(uint32_t size);
void free(void *pointer);

#endif

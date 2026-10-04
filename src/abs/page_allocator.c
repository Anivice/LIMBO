#include "abs/page_allocator.h"
#include "page.h"
#include "die.h"
#include "string.h"
#include "marco.h"

#define HEAP_PAGES ((KERNEL_HEAP_END - KERNEL_HEAP_START) / 4096u)
#define HEAP_FIRST_DIRECTORY (KERNEL_HEAP_START >> 22)
#define HEAP_DIRECTORIES ((KERNEL_HEAP_END - KERNEL_HEAP_START) >> 22)
#define TABLE_WINDOW 0xFFC00000u
#define TABLE_SCRATCH 0x003FF000u
#define HEAP_MAGIC 0x48454150u

static page_alloc_bitmap_t *heap_allocator;
static uint32_t next_frame = KERNEL_IDENTITY_END / 4096;
static uint8_t virtual_bits[HEAP_PAGES / 8];
static bitmap_t virtual_pages = {HEAP_PAGES, virtual_bits};
static uint16_t table_entries[HEAP_DIRECTORIES];

typedef struct heap_block
{
    struct heap_block *next;
    uint32_t pages;
    uint32_t requested;
    uint32_t magic;
} heap_block_t;
_Static_assert(sizeof(heap_block_t) == 16, "Heap header must preserve 16-byte alignment");
static heap_block_t *heap_blocks;

NO_PLEASE_DONT_OPTIMIZE
static uint32_t irq_save()
{
    uint32_t flags;
    __asm__ volatile ("pushfl; popl %0; cli" : "=r"(flags) :: "memory", "cc");
    return flags;
}

NO_PLEASE_DONT_OPTIMIZE
static void irq_restore(uint32_t flags)
{
    __asm__ volatile ("pushl %0; popfl" :: "r"(flags) : "memory", "cc");
}

void page_allocator_init(page_alloc_bitmap_t *context)
{
    const uint32_t flags = irq_save();
    if (heap_allocator || !context || context->bitmap.particles_ != page_alloc_bitmap_particles)
        die("Invalid page allocator initialization");
    heap_allocator = context;
    memset(virtual_bits, 0, sizeof(virtual_bits));
    irq_restore(flags);
}

uint64_t allocate_page(page_alloc_bitmap_t *context)
{
    const uint32_t flags = irq_save();
    if (context != heap_allocator || !heap_allocator) die("Page allocator not initialized");
    if (!context->free_pages) die("OOM");
    const uint32_t first = KERNEL_IDENTITY_END / 4096;
    for (uint32_t checked = first; checked < context->bitmap.particles_; ++checked) {
        const uint32_t frame = next_frame;
        if (++next_frame == context->bitmap.particles_) next_frame = first;
        if (!get_bit(&context->bitmap, frame)) {
            set_bit(&context->bitmap, frame, 1);
            --context->free_pages;
            irq_restore(flags);
            return frame;
        }
    }
    die("OOM");
}

void free_page(page_alloc_bitmap_t *context, uint64_t frame)
{
    const uint32_t flags = irq_save();
    if (context != heap_allocator || !heap_allocator) die("Page allocator not initialized");
    if (frame < KERNEL_IDENTITY_END / 4096 || frame >= context->bitmap.particles_ ||
        !get_bit(&context->bitmap, frame)) die("Invalid page release");
    set_bit(&context->bitmap, frame, 0);
    ++context->free_pages;
    irq_restore(flags);
}

/* Called with interrupts disabled. A temporary low virtual page lets us zero
 * a new table before publishing it. PDE[1023] then exposes every page table
 * through the recursive window; no physical contiguity or identity is needed.
 */
NO_PLEASE_DONT_OPTIMIZE
static void map_heap_page(uint32_t address, uint32_t frame)
{
    const uint32_t directory = address >> 22;
    const uint32_t index = (address >> 12) & 1023;
    if (!page_directory[directory].P) {
        const uint32_t table_frame = (uint32_t)allocate_page(heap_allocator);
        memset(&page_table[1023], 0, sizeof(page_t));
        page_table[1023].page_base = table_frame;
        page_table[1023].RW = 1;
        page_table[1023].P = 1;
        __asm__ volatile ("invlpg (%0)" :: "r"(TABLE_SCRATCH) : "memory");
        memset((void *)TABLE_SCRATCH, 0, 4096);
        page_table[1023].P = 0;
        __asm__ volatile ("invlpg (%0)" :: "r"(TABLE_SCRATCH) : "memory");

        memset(&page_directory[directory], 0, sizeof(page_dir_t));
        page_directory[directory].page_dir_base = table_frame;
        page_directory[directory].RW = 1;
        page_directory[directory].P = 1;
        __asm__ volatile ("invlpg (%0)" :: "r"(TABLE_WINDOW + directory * 4096) : "memory");
    }
    page_t *table = (page_t *)(TABLE_WINDOW + directory * 4096);
    if (table[index].P) die("Heap mapping collision");
    memset(&table[index], 0, sizeof(page_t));
    table[index].page_base = frame;
    table[index].RW = 1;
    table[index].P = 1;
    ++table_entries[directory - HEAP_FIRST_DIRECTORY];
    __asm__ volatile ("invlpg (%0)" :: "r"(address) : "memory");
}

NO_PLEASE_DONT_OPTIMIZE
static void unmap_heap_page(uint32_t address)
{
    const uint32_t directory = address >> 22;
    const uint32_t index = (address >> 12) & 1023;
    page_t *table = (page_t *)(TABLE_WINDOW + directory * 4096);
    if (!page_directory[directory].P || !table[index].P) die("Missing heap mapping");
    const uint32_t frame = table[index].page_base;
    memset(&table[index], 0, sizeof(page_t));
    __asm__ volatile ("invlpg (%0)" :: "r"(address) : "memory");
    free_page(heap_allocator, frame);
    if (--table_entries[directory - HEAP_FIRST_DIRECTORY] == 0) {
        const uint32_t table_frame = page_directory[directory].page_dir_base;
        memset(&page_directory[directory], 0, sizeof(page_dir_t));
        /* Flush the recursive alias and paging-structure caches before reuse. */
        tlb_flush();
        free_page(heap_allocator, table_frame);
    }
}

NO_PLEASE_DONT_OPTIMIZE
void *malloc(uint32_t size)
{
    if (!size) return nullptr;
    const uint64_t bytes = (uint64_t)size + sizeof(heap_block_t);
    if (bytes > KERNEL_HEAP_END - KERNEL_HEAP_START) die("OOM");
    const uint32_t pages = (uint32_t)((bytes + 4095) / 4096);
    const uint32_t flags = irq_save();
    uint32_t cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    if (!heap_allocator || !(cr0 & (1u << 31))) die("Heap not initialized");

    uint32_t run = 0, start = 0;
    for (uint32_t page = 0; page < HEAP_PAGES; ++page) {
        if (get_bit(&virtual_pages, page)) run = 0;
        else if (++run == pages) { start = page + 1 - pages; break; }
    }
    if (run != pages) die("OOM");
    const uint32_t address = KERNEL_HEAP_START + start * 4096;
    const uint32_t last_directory = (address + (pages - 1) * 4096) >> 22;
    uint32_t required = pages;
    for (uint32_t directory = address >> 22; directory <= last_directory; ++directory)
        if (!page_directory[directory].P) ++required;
    if (required > heap_allocator->free_pages) die("OOM");

    for (uint32_t offset = 0; offset < pages; ++offset) {
        const uint32_t frame = (uint32_t)allocate_page(heap_allocator);
        map_heap_page(address + offset * 4096, frame);
        set_bit(&virtual_pages, start + offset, 1);
    }
    heap_block_t *block = (heap_block_t *)address;
    block->pages = pages;
    block->requested = size;
    block->magic = HEAP_MAGIC;
    block->next = heap_blocks;
    heap_blocks = block;
    irq_restore(flags);
    return block + 1;
}

void free(void *pointer)
{
    if (!pointer) return;
    const uint32_t flags = irq_save();
    /* Only dereference live headers, not the caller's potentially bad pointer. */
    heap_block_t **link = &heap_blocks;
    while (*link && (void *)(*link + 1) != pointer) link = &(*link)->next;
    if (!*link || (*link)->magic != HEAP_MAGIC) die("Invalid free");
    heap_block_t *block = *link;
    const uint32_t pages = block->pages;
    const uint32_t address = (uint32_t)block;
    const uint32_t start = (address - KERNEL_HEAP_START) / 4096;
    *link = block->next;
    block->magic = 0;
    for (uint32_t offset = 0; offset < pages; ++offset) {
        unmap_heap_page(address + offset * 4096);
        set_bit(&virtual_pages, start + offset, 0);
    }
    irq_restore(flags);
}

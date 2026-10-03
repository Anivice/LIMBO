#include "page.h"
#include "string.h"
#include "types.h"
#include "marco.h"

static __attribute__((aligned(4096))) page_dir_t page_directory[1024];
static __attribute__((aligned(4096))) page_t page_table[1024];

void page_init()
{
    memset(page_directory, 0, sizeof(page_directory));
    memset(page_table, 0, sizeof(page_table));

    for (uint32_t i = 0; i < 1024; ++i) {
        page_table[i].P = 1;
        page_table[i].RW = 1;
        page_table[i].US = 0;
        page_table[i].page_base = i;
    }

    page_directory[0].P = 1;
    page_directory[0].RW = 1;
    page_directory[0].US = 0;
    page_directory[0].page_dir_base =
        ((uint32_t)page_table) >> 12;
}

NO_PLEASE_DONT_OPTIMIZE
void tlb_flush()
{
    __asm__ volatile ("mov %%cr3, %%eax; mov %%eax, %%cr3"
                      ::: "eax", "memory");
}

void page_entry_set_present(const uint32_t vaddr, const int p)
{
    const uint32_t pdi = vaddr >> 22;          /* which PDE (directory index) */
    const uint32_t pti = (vaddr >> 12) & 0x3FF;/* which PTE (table index)     */

    if (!page_directory[pdi].P)
        return;

    page_table[pti].P = p;
}

NO_PLEASE_DONT_OPTIMIZE
void page_enable()
{
    uint32_t cr0;
    uint32_t cr4;

    __asm__ volatile ("cli" ::: "memory");

    __asm__ volatile ("mov %%cr4, %0" : "=r"(cr4));
    cr4 &= ~((1u << 5) |   /* PAE: use ordinary 32-bit paging */
             (1u << 4) |   /* PSE: no 4 MiB pages */
             (1u << 7));   /* PGE: no global mappings */
    __asm__ volatile ("mov %0, %%cr4"
                      :: "r"(cr4) : "memory");

    /* Identity mapping makes this pointer equal its physical address. */
    __asm__ volatile ("mov %0, %%cr3"
                      :: "r"((uint32_t)page_directory) : "memory");

    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= (1u << 31) |    /* PG */
           (1u << 16);     /* WP */
    __asm__ volatile ("mov %0, %%cr0"
                      :: "r"(cr0) : "memory");
}
#include "page.h"
#include "string.h"
#include "types.h"

__attribute__((aligned(4096))) page_dir_t page_directory[1024];
__attribute__((aligned(4096))) page_t page_table[1024];

void page_init()
{
    for (int i = 0; i < 1024; i++)
    {
        page_dir_t* page_dir = &page_directory[i];
        memset(page_dir, 0, sizeof(page_dir_t));
        page_dir->RW = 1;
    }

    for (int i = 0; i < 1024; i++)
    {
        page_t* page = &page_table[i];
        memset(page, 0, sizeof(page_t));
        page->RW = 1;
        page->page_base = i * 4096;
    }
}

#include "abs/page_allocator.h"
#include "rtc.h"
#include "page.h"

static volatile uint64_t seed = 0;

uint64_t allocate_page(page_alloc_bitmap_t * this)
{
    if (this->free_pages == 0) return UINT64_MAX;

    do {
        if (!seed) seed = read_rtc() ^ (rtc_get_uptime() + 255);
        seed = 0x5851F42D4C957F2DULL * seed + 1ULL;
        seed = 0xDEADBF03 * (seed + 1);
        seed = (seed >> 13) | (seed << 19);
        seed %= this->bitmap.particles_ + 1;
    } while (!get_bit(&this->bitmap, seed));

    --this->free_pages;
    page_entry_set_present(seed * 4096, 1);
    set_bit(&this->bitmap, seed, 1);
    return seed;
}
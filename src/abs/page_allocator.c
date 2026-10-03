#include "abs/page_allocator.h"
#include "rtc.h"
#include "page.h"

static volatile uint64_t seed = 0;

uint64_t allocate_page(page_alloc_bitmap_t * this)
{
    if (this->free_pages == 0) return UINT64_MAX;

    if (this->bitmap.particles_ == 0) return UINT64_MAX;

    if (!seed) seed = read_rtc() ^ (rtc_get_uptime() + 255);
    seed = 0x5851F42D4C957F2DULL * seed + 1ULL;
    seed = 0xDEADBF03 * (seed + 1);
    seed = (seed >> 13) | (seed << 19);
    seed %= this->bitmap.particles_;

    for (uint32_t checked = 0; checked < this->bitmap.particles_; ++checked)
    {
        if (!get_bit(&this->bitmap, seed)) {
            set_bit(&this->bitmap, seed, 1);
            --this->free_pages;
            page_entry_set_present(seed * 4096, 1);
            return seed;
        }
        seed = (seed + 1) % this->bitmap.particles_;
    }

    return UINT64_MAX;
}

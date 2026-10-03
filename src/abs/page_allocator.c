#include "abs/page_allocator.h"
#include "rtc.h"
#include "page.h"
#include "abs/random.h"
#include "die.h"

static int alloc(const uint64_t page, page_alloc_bitmap_t * this)
{
    if (!get_bit(&this->bitmap, page)) {
        set_bit(&this->bitmap, page, 1);
        --this->free_pages;
        page_entry_set_present(page * 4096, 1);
        return 1; // alloc finished
    }

    return 0; // alloc failed
}

uint64_t allocate_page(page_alloc_bitmap_t * this)
{
    if (this->bitmap.particles_ == 0)
        die("OOM"); // WTF
    uint32_t checked = 0;
    do
    {
        // first, random allocation, max this->bitmap.particles_ tries
        const uint32_t seed = genrand_int32() % this->bitmap.particles_;
        if (alloc(seed, this)) {
            return seed;
        }
        ++checked;
    } while (checked <= this->bitmap.particles_);

    // apparently after this->bitmap.particles_ tries, no hit, going through the list again, fully
    for (uint32_t i = 0; i < this->bitmap.particles_; i++)
    {
        if (alloc(i, this)) {
            return i;
        }
    }

    // nah, just OOM
    die("OOM");
}

void free_page(page_alloc_bitmap_t * this, const uint64_t page)
{
    if (get_bit(&this->bitmap, page))
    {
        set_bit(&this->bitmap, page, 0);
        ++this->free_pages;
        page_entry_set_present(page * 4096, 0);
    }
}
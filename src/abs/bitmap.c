#include "abs/bitmap.h"
#include "assert.h"

int get_bit(const bitmap_t * this, const uint64_t index)
{
    LIMBO_ASSERT(index < this->particles_);
    const uint64_t q = index >> 3;
    const uint64_t r = index & 7; // div by 8
    uint8_t c = 0;
    c = this->data_array_[q];
    c >>= r;
    c &= 0x01;
    return c;
}

void set_bit(const bitmap_t * this, const uint64_t index, const int new_bit)
{
    LIMBO_ASSERT(index < this->particles_);
    const uint64_t q = index >> 3;
    const uint64_t r = index & 7; // div by 8
    uint8_t c = 0x01;
    c <<= r;
    if (new_bit) // set to true
    {
        this->data_array_[q] |= c;
    }
    else // clear bit
    {
        this->data_array_[q] &= ~c;
    }
}
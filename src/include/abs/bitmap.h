#ifndef LIMBO_BITMAP_H
#define LIMBO_BITMAP_H

#include "../stdint.h"

typedef struct bitmap_t {
    uint32_t particles_;
    uint8_t * data_array_;
} bitmap_t;

int get_bit(const bitmap_t * this, uint64_t index);
void set_bit(const bitmap_t * this, uint64_t index, int new_bit);

#endif //LIMBO_BITMAP_H
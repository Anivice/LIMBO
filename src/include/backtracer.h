#ifndef BACKTRACER_H
#define BACKTRACER_H

#include "stdint.h"
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames);

#endif //BACKTRACER_H

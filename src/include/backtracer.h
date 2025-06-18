#ifndef BACKTRACER_H
#define BACKTRACER_H

#include "stdint.h"

/*!
 * Backtrace stackframe
 * @param addrs Stackframe vector to store result
 * @param max_frames Max backtrace
 * @return Number of actually traced frames
 */
uint32_t backtrace(uint32_t *addrs, uint32_t max_frames);

#endif //BACKTRACER_H

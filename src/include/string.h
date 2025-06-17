#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void memset(void * dest, int val, uint32_t size);
void memcpy(void * dest, const void * src, uint32_t size);
int memcmp(const void * s1, const void * s2, uint32_t n);

#define xstr(a) str(a)
#define str(a)  #a

#endif //STRING_H

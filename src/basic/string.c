#include "string.h"

void memset(void * dest, int val, unsigned int size)
{
    __asm__ __volatile__(
    "pushl %%eax               \n\t"
    "pushl %%ebx               \n\t"
    "pushl %%ecx               \n\t"

    "movl %1, %%ecx            \n\t"
    "movl %0, %%eax            \n\t"
    "movl %2, %%ebx            \n\t"
    "memset.loop:              \n\t"
    "    movb %%bl, (%%eax)    \n\t"
    "    inc  %%eax            \n\t"
    "loop memset.loop          \n\t"

    "popl %%ecx                \n\t"
    "popl %%ebx                \n\t"
    "popl %%eax                \n\t"
    : : "r" (dest), "r" (size), "r" (val) : "memory");
}

void memcpy(void * dest, const void * src, unsigned int size);
int memcmp(const void * s1, const void * s2, unsigned int n);

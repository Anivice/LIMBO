#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void memset(void * dest, int val, uint32_t size);
void memcpy(void * dest, const void * src, uint32_t size);
int memcmp(const void * s1, const void * s2, uint32_t n);

#define xstr(a) str(a)
#define str(a)  #a

/*!
 * @brief C-style printf-like message printer
 * @param buffer Buffer
 * @param buffer_length Buffer length
 * @param fmt Print format
 * @param ... Attachments
 * @returns String len
 */
uint32_t sprintf(char *buffer, uint32_t buffer_length, const char * fmt, ...);

#endif //STRING_H

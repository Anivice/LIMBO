#ifndef IO_H
#define IO_H

void out8(unsigned short port, unsigned char value);
void out16(unsigned short port, unsigned short value);
void in8(unsigned short port, unsigned char *value);
void in16(unsigned short port, unsigned short *value);

#endif //IO_H

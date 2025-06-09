#ifndef PRINTK_H
#define PRINTK_H

void printk(const char * fmt, ...);
void putc(char c, unsigned char attr);
void print_num(unsigned int num, unsigned char attr, bool base16);

#endif //PRINTK_H

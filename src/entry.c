__asm__("jmp main");

#include "printk.h"

[[noreturn]]
int main()
{
    printk("%s-\n", "Hello, world!");
    while (true);
}

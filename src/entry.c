__asm__("jmp main");

#include "printk.h"

[[noreturn]]
int main()
{
    printk("Hello, world!\n");
    while (true);
}

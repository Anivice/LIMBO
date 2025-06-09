__asm__("jmp main");

#include "printk.h"

[[noreturn]]
int main()
{
    printk("LIMBO kernel version %s, process starting...\n", LIMBO_VERSION);
    while (true);
}

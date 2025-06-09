__asm__("jmp main");

#include "printk.h"

[[noreturn]]
int main()
{
    while (1) {
        print_num(1145141919, 0x07, true);
    }
    while (true);
}

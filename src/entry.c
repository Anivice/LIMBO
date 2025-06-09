__asm__("jmp main");

#include "printk.h"

[[noreturn]]
int main()
{
    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");
    printk("%d", -1234);
    while (true);
}

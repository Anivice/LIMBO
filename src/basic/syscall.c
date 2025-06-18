#include "syscall.h"
#include "printk.h"
#include "types.h"
#include "idt.h"

__attribute__((naked))
void isr_0x80 (void)
{
    __asm__ __volatile__ (
        "push       %ebp                    \n\t"
        "push       %esi                    \n\t"
        "push       %edi                    \n\t"
        "push       %edx                    \n\t"
        "push       %ecx                    \n\t"
        "push       %ebx                    \n\t"

        // call dispatcher
        "push       %ebp                    \n\t"
        "push       %esi                    \n\t"
        "push       %edi                    \n\t"
        "push       %edx                    \n\t"
        "push       %ecx                    \n\t"
        "push       %ebx                    \n\t"
        "push       %eax                    \n\t"
        "call       syscall_req_dispatcher  \n\t"

        // clean up
        "add        $28,        %esp        \n\t"
        "pop        %ebx                    \n\t"
        "pop        %ecx                    \n\t"
        "pop        %edx                    \n\t"
        "pop        %edi                    \n\t"
        "pop        %esi                    \n\t"
        "pop        %ebp                    \n\t"
        "iret                               \n\t"
    );
}

int32_t syscall_req_dispatcher(
    const uint32_t entry  /* eax */,
    const uint32_t param1 /* ebx */,
    const uint32_t param2 /* ecx */,
    const uint32_t param3 /* edx */,
    const uint32_t param4 /* edi */,
    const uint32_t param5 /* esi */,
    const uint32_t param6 /* ebp */)
{
    switch (entry)
    {
        case 0x01:
            put((char)param1);
            return 0;

        default:
            return -1;
    }
}

void init_syscall (void)
{
    idt_set_gate(0x80, (uint32_t)(void*)isr_0x80, 0x10, 0x8E);
}

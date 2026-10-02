#ifndef SYSCALL_H
#define SYSCALL_H

#include "types.h"

enum syscall_table_t : uint32_t {
    SYS_FORK = 0x01,
    SYS_PUT_FRAME_TO_CONSOLE_WITH_ATTR = 0x20,
};

void init_syscall();

#endif //SYSCALL_H

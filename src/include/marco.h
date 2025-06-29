#ifndef MARCO_H
#define MARCO_H

#define LOCAL_DESCRIPTOR_TABLE         ((void*)(0x29F80))
#define LOCAL_DESCRIPTOR_TABLE_LIMIT   (127)
#define TASK_STATE_SEGMENT             ((void*)(0x29F10))
#define TASK_STATE_LIMIT               (103)
#define SYSTEM_SYMBOL_MAP              ((void*)(0x18E000))
#define MIN(a, b)                      (((a) < (b)) ? (a) : (b))
#define MAGIC                          ((const char*)0x1939F9)

#endif //MARCO_H

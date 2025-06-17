#include "die.h"
#include "string.h"
#include "rtc.h"
#include "printk.h"
#include "backtracer.h"

uint32_t backtrace(uint32_t *addrs, uint32_t max_frames);

uint32_t query_map(char ** sysmap_ptr, char * symbol_literal, uint32_t symbol_max)
{
    int literal_off = 0;
    uint32_t *sysmap_symbol_ip = (uint32_t *)*sysmap_ptr;
    char * symbol = (*sysmap_ptr + 4);
    while (*symbol != 0x0a)
    {
        if (literal_off < symbol_max) {
            symbol_literal[literal_off++] = *symbol;
        }

        symbol++;
    }

    *sysmap_ptr = symbol;
    return *sysmap_symbol_ip;
}

void get_symbol()
{

}

[[noreturn]]
void die(const char * str)
{
    char frame_trace_literal_buffer[256] = { };
    uint32_t stackframes[64];
    auto const frames = backtrace(stackframes, sizeof(stackframes) / sizeof(stackframes[0]));
    uint32_t offset = sprintf(frame_trace_literal_buffer, sizeof(frame_trace_literal_buffer), "Traced %d frames:\n", frames);
    for (uint32_t i = 0; i < frames; i++)
    {
        for (uint32_t j = 0; j < i + 1; j++)
        {
            offset += sprintf(frame_trace_literal_buffer + offset, sizeof(frame_trace_literal_buffer), " ");
        }

        offset += sprintf(frame_trace_literal_buffer + offset, sizeof(frame_trace_literal_buffer), "0x%x\n", stackframes[i]);
    }

    char buffer[32];
    char * sysmap;
    *(uint32_t*)(&sysmap) = 0x18DE00;
    uint32_t symbol_loc = query_map(&sysmap, buffer, sizeof(buffer));

    printk(
        "--------------------------------- Kernel panic ---------------------------------\n"
        "> %s\n"
        "TIME: uptime: %Ds, UNIX timestamp: %U\n"
        "STACK FRAME BACKTRACK:\n"
        "%s\n"
        "%x %s"
        "--------------------------------------------------------------------------------\n",
        str, uptime, read_rtc(), frame_trace_literal_buffer, symbol_loc, buffer);
    while (1)
    {
        __asm__ __volatile__("hlt");
    }
}

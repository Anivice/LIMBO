/*!
 * @file entry.c
 *
 * @copyright
 * Copyright 2025 Anivice Ives
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * @brief This file defines entry point from assembly second stage loader
 **/

#include "string.h"
#include "printk.h"
#include "rtc.h"
#include "irq.h"
#include "die.h"
#include "marco.h"
#include "page.h"

/*!
 * @brief Enable FPU
 */
static NO_PLEASE_DONT_OPTIMIZE
void enable_fpu()
{
    uint32_t cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1UL << 2);   /* clear EM */
    cr0 &= ~(1UL << 3);   /* clear TS */
    cr0 |=  (1UL << 5);   /* set NE: report FP errors via #MF */
    __asm__ volatile ("mov %0, %%cr0" :: "r"(cr0));
    __asm__ volatile ("fninit");     /* initialise x87 state */
}

static const char * value_to_human(
    char * buffer, const uint32_t buffer_size,
    const uint64_t value)
{
    static const char * size_values[] = {"B", "KB", "MB", "GB", "TB", "PB"};
    constexpr uint32_t size_values_size = sizeof(size_values) / sizeof(size_values[0]);
    uint32_t level = 0;
    double human_value;

    if (value == 0) {
        sprintf(buffer, buffer_size, "0 %s", size_values[0]);
        return buffer;
    }

    human_value = (double)value;

    while (level + 1 < size_values_size && human_value >= 1024.0) {
        human_value /= 1024.0;
        ++level;
    }

    sprintf(buffer, buffer_size, "%F %s", human_value, size_values[level]);
    return buffer;
}

typedef struct e820_entry_t {
    uint64_t base;      // offset 0:  starting physical address
    uint64_t length;    // offset 8:  size of the range in bytes
    uint32_t type;      // offset 16: 1=usable RAM, 2=reserved, 3=ACPI reclaimable, 4=ACPI NVS
} __attribute__((packed)) e820_entry_t;

_Static_assert(sizeof(e820_entry_t) == 20, "e820_entry_t must be 20 bytes");

/*!
 * @brief Kernel entry point and stage dispatcher.
 * This function is responsible for invoking different dispatchers to finish the boot sequence.
 * This function is directly jumped from stage 2 loader and should never ever return (no return address in stack frame)
 * @return None, and is marked with [[noreturn]], so no return code is generated for main()
 */
[[noreturn, gnu::section(".kernel_entry_point")]]
NO_PLEASE_DONT_OPTIMIZE
// __attribute__((section(".kernel_entry_point")))
void main(const int32_t argc, const uint8_t *argv)
{
    if (memcmp(MAGIC, "Anivice", 7) != 0) {
        die("Kernel data corrupted");
    }

    install_irq();
    enable_fpu();
    page_init();

    // get memory info, loader gives it to us from the BIOS
    int entries = argc / (int)sizeof(e820_entry_t);
    if (argc % (int)sizeof(e820_entry_t) != 0)
        die("Loader gives unaligned entries"); // FUCK

    char buff [32];
    printk("Memory layout:\n");
    uint64_t celling = 0;
    for (int i = 0; i < entries; i++)
    {
        e820_entry_t entry;
        memcpy(&entry, argv + sizeof(e820_entry_t) * i, sizeof(entry));
        celling = entry.base + entry.length;
        printk("Range: [0x%X, 0x%X), %s, type: ", entry.base, entry.base + entry.length,
            value_to_human(buff, sizeof(buff), entry.length));
        switch (entry.type) { //  1=usable RAM, 2=reserved, 3=ACPI reclaimable, 4=ACPI NVS
            case 1: printk("usable"); break;
            case 2: { // evict reserved entries
                printk("reserved");
                auto const length = entry.length / 4096 + (entry.length % 4096 == 0 ? 0 : 1);
                for (uint64_t j = 0; j < length; j++) {
                    page_entry_set_present(entry.base + j * 4096, 0);
                }
            }
            break;
            case 3: printk("ACPI reclaimable"); break;
            case 4: printk("ACPI NVS"); break;
            default: printk("%u", entry.type); break;
        }
        printk("\n");
    }

    printk("Range: [0x90000, 0x9FC00): kernel stacks.\n");
    printk("Range: [0x100000, 0x178000): Kernel code slot: 480 KiB.\n");
    printk("Range: [0x178000, 0x18E000): Kernel data slot: 88 KiB, containing .rodata, .data, .bss, and COMMON.\n");
    printk("Range: [0x18E000, 0x195DF9): Symbol-map storage and padding.\n");
    printk("Range: [0x195DF9, 0x195E00): \"Anivice\".\n");
    page_entry_set_present(0xB8000, 1); // VRAM
    for (uint32_t i = 0x90000; i < 0x9FC00; i += 4096) {
        page_entry_set_present(i, 1); // Kernel stacks
    }

    // evict common address spaces:
    for (uint32_t i = 0; i < 0x90000; i += 4096) {
        page_entry_set_present(i, 0);
    }
    for (uint64_t i = 0x197000; i < celling; i += 4096) {
        page_entry_set_present(i, 0);
    }

    // Set GDT page as present
    struct {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) gdtr;

    __asm__ volatile ("sgdt %0" : "=m"(gdtr));
    const uint64_t gdt_end = (uint64_t)gdtr.base + gdtr.limit + 1u;
    for (uint64_t addr = (uint64_t)gdtr.base & ~0xFFFULL;
         addr < gdt_end;
         addr += 4096)
    {
        page_entry_set_present((uint32_t)addr, 1);
    }

    page_enable();
    rtc_irq_init();
    __asm__ volatile ("sti" ::: "memory");

    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");

    // int a = 12 / 0;
    *(int*)(1024 * 1024 * 24) = 12;

    while (rtc_get_uptime() < 3)
        __asm__ volatile ("hlt" ::: "memory");

    /////////////////////////////////////////////////////////////
    die("Unexpected reach of the end of kernel entry point");
}
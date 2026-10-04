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
#include "abs/bitmap.h"
#include "abs/page_allocator.h"

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

    // We need to setup a usable memory model here:

    // 1. get memory info, loader gives it to us from the BIOS
    int entries = argc / (int)sizeof(e820_entry_t);
    if (argc % (int)sizeof(e820_entry_t) != 0)
        die("Loader gives unaligned entries"); // FUCK

    // entire 128KB -> 4GB map
    bitmap_t page_alloc_bitmap = {
        .particles_ = page_alloc_bitmap_particles,
        .data_array_ = page_alloc_bitmap_start
    };
    /* Unknown addresses are unavailable until E820 explicitly supplies RAM. */
    memset(page_alloc_bitmap_start, 0xFF, page_alloc_bitmap_size);

    char buff [32];
    printk("Memory layout:\n");
    for (int i = 0; i < entries; i++)
    {
        e820_entry_t entry;
        memcpy(&entry, argv + sizeof(e820_entry_t) * i, sizeof(entry));
        printk("Range: [0x%X, 0x%X), %s, type: ", entry.base, entry.base + entry.length,
            value_to_human(buff, sizeof(buff), entry.length));
        switch (entry.type) { //  1=usable RAM, 2=reserved, 3=ACPI reclaimable, 4=ACPI NVS
            case 1: {
                printk("usable");
                const uint64_t limit = 1ULL << 32;
                if (entry.base < limit && entry.length != 0) {
                    const uint64_t bytes = MIN(entry.length, limit - entry.base);
                    const uint64_t end = (entry.base + bytes) & ~0xFFFULL;
                    /* Only whole pages contained in usable RAM are free. */
                    for (uint64_t addr = (entry.base + 0xFFFULL) & ~0xFFFULL;
                         addr < end; addr += 4096) {
                        set_bit(&page_alloc_bitmap, addr / 4096, 0);
                    }
                }
                break;
            }
            case 2: printk("reserved"); break;
            case 3: printk("ACPI reclaimable"); break;
            case 4: printk("ACPI NVS"); break;
            default: printk("%u", entry.type); break;
        }
        printk("\n");
    }

    /* Non-RAM wins over overlapping usable entries, regardless of order.
     * Keep ACPI reclaimable/NVS and unknown types unavailable as well.
     */
    for (int i = 0; i < entries; ++i) {
        e820_entry_t entry;
        memcpy(&entry, argv + sizeof(entry) * i, sizeof(entry));
        const uint64_t limit = 1ULL << 32;
        if (entry.type == 1 || entry.length == 0 || entry.base >= limit)
            continue;
        const uint64_t bytes = MIN(entry.length, limit - entry.base);
        const uint64_t end = entry.base + bytes;
        for (uint64_t addr = entry.base & ~0xFFFULL;
             addr < end; addr += 4096) {
            set_bit(&page_alloc_bitmap, addr / 4096, 1);
        }
    }

    /* The fixed bitmap storage must be usable RAM, not firmware storage. */
    for (uint32_t addr = (uint32_t)page_alloc_bitmap_start;
         addr < (uint32_t)page_alloc_bitmap_end; addr += 4096) {
        if (get_bit(&page_alloc_bitmap, addr / 4096))
            die("Page allocator bitmap is not backed by usable RAM");
    }

    /* Retain low memory for the loader/firmware/stack and reserve the entire
     * first 2 MiB, including the kernel, paging structures and symbol map.
     * Mapping a page and owning a physical frame are separate decisions.
     */
    for (uint32_t addr = 0;
         addr < KERNEL_IDENTITY_END;
         addr += 4096) {
        set_bit(&page_alloc_bitmap, addr / 4096, 1);
    }

    _Static_assert(0x100000u + KERNEL_IMAGE_BYTES <= KERNEL_IDENTITY_END,
                   "Kernel must fit in the bootstrap identity map");
    printk("Range: [0, 0x200000): reserved bootstrap identity map.\n");

    static page_alloc_bitmap_t page_alloc_object;
    page_alloc_object.bitmap = page_alloc_bitmap;
    for (uint32_t page = 0; page < page_alloc_bitmap_particles; ++page) {
        if (!get_bit(&page_alloc_bitmap, page)) ++page_alloc_object.free_pages;
    }
    printk("Usable physical frames above 2 MiB: %u\n", page_alloc_object.free_pages);
    page_allocator_init(&page_alloc_object);

    page_enable();
    rtc_irq_init();
    __asm__ volatile ("sti" ::: "memory");

    printk("%rL%gITTLE %rI%g386 %rM%gICROKERNEL %rB%gAREMETAL %rO%gS " LIMBO_VERSION "\n");

    /* Demonstrate allocation, writable memory, and release. */
    uint32_t *sample = malloc(8192);
    sample[0] = 0x12345678;
    sample[2047] = 0x87654321;
    printk("malloc(8192) -> 0x%x, first=0x%x last=0x%x\n",
           (uint32_t)sample, sample[0], sample[2047]);
    free(sample);

    // uint64_t counter = 0;
    // while (true) {
        // printk("malloc(1) -> 0x%x, count=%U\n", malloc(1), ++counter);
    // }

    /////////////////////////////////////////////////////////////
    die("Unexpected reach of the end of kernel entry point");
}
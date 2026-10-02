/*!
 * @file rtc.c
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
 * @brief This file defines RTC interrupt routines and helpers
 **/

#include "rtc.h"
#include "io.h"
#include "idt.h"
#include "string.h"
#include "marco.h"

#define RTC_REGISTER_INDEX      (0x70)
#define RTC_REGISTER_IO         (0x71)
#define RTC_REGISTER_A          (0x0A)
#define RTC_REGISTER_B          (0x0B)
#define RTC_REGISTER_C          (0x0C)
#define RTC_REGISTER_D          (0x0D)
#define RTC_REGISTER_SEC        (0x00)
#define RTC_REGISTER_MIN        (0x02)
#define RTC_REGISTER_HUR        (0x04)
#define RTC_REGISTER_WEK        (0x06)
#define RTC_REGISTER_DAY        (0x07)
#define RTC_REGISTER_MON        (0x08)
#define RTC_REGISTER_YER        (0x09)
#define I8259_IMR               (0xA1)
#define MASTER_8259             (0x20)
#define SLAVE_8259              (0xA0)
#define EOI                     (0x20)

/// CPU uptime determined by RTC interrupt counter
static volatile uint64_t uptime __attribute__((used));

NO_PLEASE_DONT_OPTIMIZE
static uint32_t rtc_irq_save()
{
    uint32_t flags;
    __asm__ volatile ("pushfl; popl %0; cli"
                      : "=r"(flags) : : "memory", "cc");
    return flags;
}

NO_PLEASE_DONT_OPTIMIZE
static void rtc_irq_restore(uint32_t flags)
{
    __asm__ volatile ("pushl %0; popfl"
                      : : "r"(flags) : "memory", "cc");
}

NO_PLEASE_DONT_OPTIMIZE
uint64_t rtc_get_uptime()
{
    const uint32_t flags = rtc_irq_save();
    const uint64_t value = uptime;
    rtc_irq_restore(flags);
    return value;
}

__attribute__((naked, NO_OPTIMIZATION))
static void rtc_irq_handler()
{
    __asm__ volatile (
        "pushal                 \n\t"
        "push   %ds             \n\t"
        "mov    $0x08,  %ax     \n\t"
        "mov    %ax,    %ds     \n\t"
        "mov    $0x0c,  %al     \n\t"
        "out    %al,    $0x70   \n\t"
        "in     $0x71,  %al     \n\t"
        "test   $0x10,  %al     \n\t"
        "jz     1f              \n\t"
        "addl   $1,     uptime  \n\t"
        "adcl   $0,     uptime+4\n\t"
     "1: mov    $0x20,  %al     \n\t"
        "out    %al,    $0xa0   \n\t"
        "out    %al,    $0x20   \n\t"
        "pop    %ds             \n\t"
        "popal                  \n\t"
        "iret                   \n\t"
    );
}

NO_PLEASE_DONT_OPTIMIZE
void rtc_irq_init()
{
    uptime = 0;
    const uint32_t flags = rtc_irq_save();
    idt_set_gate(0x70, (uint32_t)rtc_irq_handler, 0x10, 0x8E);

    outb(0x70, RTC_REGISTER_B);
    const uint8_t b = inb(0x71);
    outb(0x70, RTC_REGISTER_B);
    outb(0x71, (b & 0x0F) | 0x10);

    outb(0x70, RTC_REGISTER_C);
    (void)inb(0x71);

    outb(0xA1, inb(0xA1) & 0xFE);
    outb(0x21, inb(0x21) & 0xFB);
    rtc_irq_restore(flags);
}

/*!
 * @brief Read RTC from index
 * @param index Register index,
 * can be RTC_REGISTER_SEC, RTC_REGISTER_MIN, RTC_REGISTER_HUR,
 * RTC_REGISTER_DAY, RTC_REGISTER_MON and RTC_REGISTER_YER
 * @return Data from register
 */
[[nodiscard]]
static uint8_t read_rtc_register(const uint16_t index)
{
    const uint32_t flags = rtc_irq_save();
    out8(RTC_REGISTER_INDEX, (uint8_t)(index & 0x7F));
    const uint8_t data = inb(RTC_REGISTER_IO);
    rtc_irq_restore(flags);
    return data;
}

/*!
 * Convert BCD to binary numeric
 * @param data Packed BCD
 * @return Binary numeric
 */
[[nodiscard]]
static uint8_t bcd_to_numeric(const uint8_t data)
{
    uint8_t numeric = 0;
    uint32_t bcd = data;
    bcd <<= 4;
    ((char*)&bcd)[0] >>= 4;
    ((char*)&bcd)[0] &= 0x0F;
    numeric = ((char*)(&bcd))[0];
    numeric += ((char*)(&bcd))[1] * 10;
    return numeric;
}

/*!
 * Convert YYYY-MM-DD:mm:hh:ss to UNIX Timestamp
 * @param year Year
 * @param month Month
 * @param day Day
 * @param hour Hour
 * @param minute Minute
 * @param second Second
 * @return UNIX Timestamp
 */
static uint64_t unix_timestamp(const uint32_t year, const uint32_t month, const uint32_t day,
                        const uint32_t hour, const uint32_t minute, const uint32_t second)
{
    // Days in each month for a non-leap year
    static const uint32_t mdays[12] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    uint64_t days = 0ULL;
    const uint64_t y = (uint64_t)year - 1ULL;   // year-1 for leap year calculation

    // Add days for all years from 1970 up to the year before the given year
    days += (uint64_t)(year - 1970) * 365ULL;
    days += (y / 4ULL) - (y / 100ULL) + (y / 400ULL)                // leap days up to year-1
          - (1969ULL / 4ULL - 1969ULL / 100ULL + 1969ULL / 400ULL); // leap days up to 1969

    // Add days for all months in the given year before the given month
    for (uint32_t m = 1; m < month; ++m) {
        days += mdays[m - 1];
    }
    // If leap year and date is after February, add one extra day for Feb 29
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        if (month > 2) {
            days += 1ULL;
        }
    }

    // Add days in the current month (day-1, since day=1 means zero full days passed in that month)
    days += (uint64_t)(day - 1);

    // Convert total days to seconds and add hours, minutes, seconds of the current day
    const uint64_t seconds = days * 86400ULL
                               + (uint64_t)hour * 3600ULL
                               + (uint64_t)minute * 60ULL
                               + (uint64_t)second;
    return seconds;
}

uint64_t read_rtc()
{
    static const uint8_t indices[] = {0, 2, 4, 7, 8, 9, 0x0B};
    uint8_t a[7], b[7];

    for (unsigned attempt = 0; attempt < 1024; ++attempt) {
        uint32_t flags = rtc_irq_save();

        if (read_rtc_register(RTC_REGISTER_A) & 0x80) {
            rtc_irq_restore(flags);
            continue;
        }

        for (unsigned i = 0; i < 7; ++i)
            a[i] = read_rtc_register(indices[i]);
        for (unsigned i = 0; i < 7; ++i)
            b[i] = read_rtc_register(indices[i]);

        uint8_t status_a = read_rtc_register(RTC_REGISTER_A);
        rtc_irq_restore(flags);

        if ((status_a & 0x80) || memcmp(a, b, sizeof(a)) != 0)
            continue;
        if (b[6] & 0x80)
            return UINT64_MAX;

        bool pm = (b[2] & 0x80) != 0;
        b[2] &= 0x7F;

        if (!(b[6] & 0x04)) {
            for (unsigned i = 0; i < 6; ++i) {
                if ((b[i] & 0x0F) > 9 || (b[i] >> 4) > 9)
                    return UINT64_MAX;
                b[i] = bcd_to_numeric(b[i]);
            }
        }

        if (!(b[6] & 0x02)) {
            if (b[2] < 1 || b[2] > 12)
                return UINT64_MAX;
            b[2] = b[2] % 12 + (pm ? 12 : 0);
        }

        unsigned year = 2000u + b[5];
        static const uint8_t mdays[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (b[0] > 59 || b[1] > 59 || b[2] > 23 ||
            b[4] < 1 || b[4] > 12 || b[5] > 99)
            return UINT64_MAX;

        unsigned days = mdays[b[4] - 1];
        if (b[4] == 2 && year % 4 == 0 &&
            (year % 100 != 0 || year % 400 == 0))
            ++days;

        if (b[3] < 1 || b[3] > days)
            return UINT64_MAX;

        return unix_timestamp(year, b[4], b[3],
                              b[2], b[1], b[0]);
    }

    return UINT64_MAX;
}
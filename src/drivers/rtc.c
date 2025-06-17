#include "rtc.h"
#include "io.h"
#include "string.h"

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

volatile uint64_t uptime;

__attribute__((naked))
void rtc_irq_handler(void)
{
    __asm__ volatile(
        "   pusha                                           \n\t"
        "   mov     $0x0C,              %al                 \n\t"
        "   out     %al,                $0x70               \n\t"
        "   in      $0x71,              %al                 \n\t"

        "   xor     %eax,               %eax                \n\t"
        "   mov     "str(uptime)",      %eax                \n\t"
        "   inc     %eax                                    \n\t"
        "   mov     %eax,               "str(uptime)"       \n\t"

        "   movb    $0x20,              %al                 \n\t"
        "   out     %al,                $0xA0               \n\t"
        "   out     %al,                $0x20               \n\t"
        "   popa                                            \n\t"
        "   iret                                            \n\t"
    );
}

void idt_set_gate(uint8_t vector, uint32_t handler_addr, uint16_t selector, uint8_t flags);

void rtc_irq_init(void)
{
    __asm__ volatile("cli");
    idt_set_gate(0x70, (uint32_t)(void*)rtc_irq_handler, 0x10, 0x8E);
    outb(0x70, 0x8B);
    outb(0x71, 0x12);
    outb(0x70, 0x0C);
    inb(0x71);
    outb(0xa1, 0xFE);
    outb(0x21, 0xFB);
    __asm__ volatile("sti");
}

/*!
 * @brief Read RTC from index
 * @param index Register index,
 * can be RTC_REGISTER_SEC, RTC_REGISTER_MIN, RTC_REGISTER_HUR,
 * RTC_REGISTER_DAY, RTC_REGISTER_MON and RTC_REGISTER_YER
 * @return Data from register
 */
[[nodiscard]]
uint8_t read_rtc_register(uint16_t index)
{
    uint8_t data;
    index |= 0x80;
    out8(RTC_REGISTER_INDEX, (uint8_t)index);
    in8(RTC_REGISTER_IO, &data);
    return data;
}

[[nodiscard]]
uint8_t bcd_to_numeric(const uint8_t data)
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

uint64_t unix_timestamp(const uint32_t year, const uint32_t month, const uint32_t day,
                                  const uint32_t hour, const uint32_t minute, const uint32_t second)
{
    // Days in each month for a non-leap year
    static const uint32_t mdays[12] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    uint64_t days = 0ULL;
    uint64_t y = (uint64_t)year - 1ULL;  // year-1 for leap year calculation

    // Add days for all years from 1970 up to the year before the given year
    days += (uint64_t)(year - 1970) * 365ULL;
    days += (y / 4ULL) - (y / 100ULL) + (y / 400ULL)      // leap days up to year-1
          - (1969ULL / 4ULL - 1969ULL / 100ULL + 1969ULL / 400ULL);  // leap days up to 1969

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
    const int second = bcd_to_numeric(read_rtc_register(RTC_REGISTER_SEC));
    const int minute = bcd_to_numeric(read_rtc_register(RTC_REGISTER_MIN));
    const int hour = bcd_to_numeric(read_rtc_register(RTC_REGISTER_HUR));
    const int day = bcd_to_numeric(read_rtc_register(RTC_REGISTER_DAY));
    const int month = bcd_to_numeric(read_rtc_register(RTC_REGISTER_MON));
    const int year = bcd_to_numeric(read_rtc_register(RTC_REGISTER_YER)) + 2000;
    return unix_timestamp(year, month, day, hour, minute, second);
}

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

void rtc_irq_handler(void);

void rtc_irq_init(void)
{
    /* 1. Mask IRQ 8 while we fiddle: set bit 0 of the slave mask. */
    uint8_t pic2_mask;
    in8(I8259_IMR, &pic2_mask);
    out8(I8259_IMR, pic2_mask | 0x01);

    /* 2. Disable NMI (bit 7) and select register B, then set UIE. */
    out8(RTC_REGISTER_INDEX, 0x80 | 0x0B);              /* NMI off, index = 0x0B */
    uint8_t prevB;
    in8(RTC_REGISTER_IO, &prevB);
    out8(RTC_REGISTER_INDEX, 0x80 | 0x0B);              /* need to re-set index after read */
    out8(RTC_REGISTER_IO, (prevB | 0x20) & ~0x40);      /* UIE=1, PIE=0, keep others */

    /* 3. Acknowledge any pending old RTC interrupt by reading reg C. */
    out8(RTC_REGISTER_INDEX, 0x0C);                     /* NMI already clear */
    uint8_t dummy;
    in8(RTC_REGISTER_IO, &dummy);                           /* throw away result */

    /* 4. Unmask IRQ 8 again. */
    out8(I8259_IMR, pic2_mask & ~0x01);
}

// /*!
//  * @brief Read RTC from index
//  * @param index Register index,
//  * can be RTC_REGISTER_SEC, RTC_REGISTER_MIN, RTC_REGISTER_HUR,
//  * RTC_REGISTER_DAY, RTC_REGISTER_MON and RTC_REGISTER_YER
//  * @return Data from register
//  */
// [[nodiscard]]
// unsigned char read_rtc_register(unsigned short index)
// {
//     unsigned char data;
//     index |= 0x80;
//     out8(RTC_REGISTER_INDEX, (unsigned char)index);
//     in8(RTC_REGISTER_IO, &data);
//     return data;
// }
//
// [[nodiscard]]
// unsigned char bcd_to_numeric(const unsigned char data)
// {
//     unsigned char numeric = 0;
//     unsigned int bcd = data;
//     bcd <<= 4;
//     ((char*)&bcd)[0] >>= 4;
//     numeric = ((char*)(&bcd))[0];
//     numeric += ((char*)(&bcd))[1];
//     return numeric;
// }
//
// unsigned long long unix_timestamp(const unsigned int year, const unsigned int month, const unsigned int day,
//                                   const unsigned int hour, const unsigned int minute, const unsigned int second)
// {
//     // Days in each month for a non-leap year
//     static const unsigned int mdays[12] = {
//         31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
//     };
//
//     unsigned long long days = 0ULL;
//     unsigned long long y = (unsigned long long)year - 1ULL;  // year-1 for leap year calculation
//
//     // Add days for all years from 1970 up to the year before the given year
//     days += (unsigned long long)(year - 1970) * 365ULL;
//     days += (y / 4ULL) - (y / 100ULL) + (y / 400ULL)      // leap days up to year-1
//           - (1969ULL / 4ULL - 1969ULL / 100ULL + 1969ULL / 400ULL);  // leap days up to 1969
//
//     // Add days for all months in the given year before the given month
//     for (unsigned int m = 1; m < month; ++m) {
//         days += mdays[m - 1];
//     }
//     // If leap year and date is after February, add one extra day for Feb 29
//     if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
//         if (month > 2) {
//             days += 1ULL;
//         }
//     }
//
//     // Add days in the current month (day-1, since day=1 means zero full days passed in that month)
//     days += (unsigned long long)(day - 1);
//
//     // Convert total days to seconds and add hours, minutes, seconds of the current day
//     unsigned long long seconds = days * 86400ULL
//                                + (unsigned long long)hour * 3600ULL
//                                + (unsigned long long)minute * 60ULL
//                                + (unsigned long long)second;
//     return seconds;
// }
//
// unsigned long long int read_rtc()
// {
//     const unsigned char second = bcd_to_numeric(read_rtc_register(RTC_REGISTER_SEC));
//     const unsigned char minute = bcd_to_numeric(read_rtc_register(RTC_REGISTER_MIN));
//     const unsigned char hour = bcd_to_numeric(read_rtc_register(RTC_REGISTER_HUR));
//     const unsigned char day = bcd_to_numeric(read_rtc_register(RTC_REGISTER_DAY));
//     const unsigned char month = bcd_to_numeric(read_rtc_register(RTC_REGISTER_MON));
//     const unsigned char year = bcd_to_numeric(read_rtc_register(RTC_REGISTER_YER)) + 2000;
//     return unix_timestamp(year, month, day, hour, minute, second);
// }

volatile uint64_t uptime;

[[noreturn]]
__attribute__((naked))
void rtc_irq_handler(void)
{
    __asm__ volatile(
        "   pusha                                           \n\t"
        "   mov     $0x0C,              %al                 \n\t"
        "   out     %al,                $0x70               \n\t"
        "   in      $0x71,              %al                 \n\t"
        "   movb    $0x20,              %al                 \n\t"
        "   out     %al,                $0xA0               \n\t"
        "   out     %al,                $0x20               \n\t"
        "   xor     %eax,               %eax                \n\t"
        "   mov     "str(uptime)",      %eax                \n\t"
        "   inc     %eax                                    \n\t"
        "   mov     %eax,               "str(uptime)"       \n\t"
        "   popa                                            \n\t"
        "   iret                                            \n\t"
    );
}

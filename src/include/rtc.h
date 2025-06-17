#ifndef RTC_H
#define RTC_H

#include <stdint.h>

extern volatile uint64_t uptime;
void rtc_irq_init(void);

#endif //RTC_H

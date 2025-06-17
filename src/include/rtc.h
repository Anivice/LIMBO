#ifndef RTC_H
#define RTC_H

#include "stdint.h"
#include "idt.h"

extern volatile uint64_t uptime;
void rtc_irq_init(void);
uint64_t read_rtc();

#endif //RTC_H

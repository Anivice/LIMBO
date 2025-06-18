#ifndef RTC_H
#define RTC_H

#include "stdint.h"
#include "idt.h"

/// CPU uptime determined by RTC interrupt counter
extern volatile uint64_t uptime;

/// initialize RTC
/// @return NONE
void rtc_irq_init(void);

/// Reads current timestamp in RTC
/// @returns NONE
uint64_t read_rtc();

#endif //RTC_H

/*!
 * @file rtc.h
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

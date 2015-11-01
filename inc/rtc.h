/*
 * rtc.h
 *
 * Copyright 2015  Felix Horn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#ifndef RTC_H_
#define RTC_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>

#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  #include "stm32f4xx_hal.h"
#elif defined(USE_HAL_DRIVER) & defined(STM32F1xx)
  #include "stm32f1xx_hal.h"
#elif defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  #include "stm32f10x.h"
#endif

/* Exported constants --------------------------------------------------------*/
/* Choose the clock source for RTC, uncomment this line */
//#define RTC_USE_LSE
#define RTC_USE_HSE

/* Exported variables --------------------------------------------------------*/
volatile uint_fast8_t Flag_NewSecond;

/* Exported types ------------------------------------------------------------*/
#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

/* Exported macro ------------------------------------------------------------*/
#define SET_FLAG(Variable)          Variable = 1
#define RESET_FLAG(Variable)        Variable = 0
#define CHECK_FLAG_SET(Variable)    Variable == 1
#define CHECK_FLAG_RESET(Variable)  Variable == 0

/* Exported functions --------------------------------------------------------*/
void RTC_Config(void);
void RTC_IRQHandler(void);
void RTC_SetTime(uint_least8_t *TimeData);

#if defined(RTC_USE_LSE) & defined(RTC_USE_HSE)
#error "Choose only one clock source for RTC"
#endif

#endif /* RTC_H_ */

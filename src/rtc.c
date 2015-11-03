/*
 * rtc.c
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


/* Includes ------------------------------------------------------------------*/

#include <rtc.h>
#include <stdint-gcc.h>
#include <stm32f407xx.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_cortex.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_rcc_ex.h>
#include <stm32f4xx_hal_rtc.h>
#include <stm32f4xx_hal_rtc_ex.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  /* Definition for RTC clock resources */
  #define RTC_CLK_ENABLE()                RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE)
  #define RTC_BKP_CLK_ENABLE()            RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE)

  /* Definition for RTC NVIC */
  #define RTC_IRQ_PRE_PRIORITY            12
  #define RTC_IRQ_SUB_PRIORITY            12
#endif

#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  /* Definition for RTC clock resources */
  #define RTC_CLK_ENABLE()                __HAL_RCC_RTC_ENABLE()
  #define RTC_ASYNCH_PREDIV               124
  #define RTC_SYNCH_PREDIV                7999

  /* Definition for RTC NVIC */
  #define RTC_IRQn                        RTC_WKUP_IRQn
  #define RTC_IRQ_PRE_PRIORITY            12
  #define RTC_IRQ_SUB_PRIORITY            12
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  RTC_HandleTypeDef RtcHandle;
#endif
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Config(void) {
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  /* Enable RTC clock */
  RTC_CLK_ENABLE();

  /* Enable BKP clock */
  RTC_BKP_CLK_ENABLE();

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

#ifdef RTC_USE_LSE
  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#elif defined(RTC_USE_HSE)
  /* Select HSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
#else
#error "No clock source for RTC defined"
#endif

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
#ifdef RTC_USE_LSE
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#elif defined(RTC_USE_HSE)
  RTC_SetPrescaler(HSE_VALUE / 128 + 1);
#endif

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
#endif

#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
#ifdef RTC_USE_LSE
  /* Configue LSE as RTC clock soucre */
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
#elif defined(RTC_USE_HSE)
  /* Configue HSE as RTC clock soucre */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV8;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
#else
#error "No clock source for RTC defined"
#endif
  /* Enable RTC clock */
  RTC_CLK_ENABLE();

  /* Configure RTC prescaler and RTC data registers */
  /* RTC configured as follow:
      - Hour Format    = Format 24
      - Asynch Prediv  = Value according to source clock
      - Synch Prediv   = Value according to source clock
      - OutPut         = Output Disable
      - OutPutPolarity = High Polarity
      - OutPutType     = Open Drain */
  RtcHandle.Instance = RTC;
  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

  HAL_RTC_Init(&RtcHandle);
#endif

  /* Configure NVIC */
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = RTC_IRQ_PRE_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = RTC_IRQ_SUB_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
#endif
#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)

#if 0
  HAL_NVIC_SetPriority(RTC_IRQn, RTC_IRQ_PRE_PRIORITY, RTC_IRQ_SUB_PRIORITY);
  HAL_NVIC_EnableIRQ(RTC_IRQn);
  HAL_RTCEx_SetWakeUpTimer_IT(&RtcHandle, 1, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
#endif /* 0 */

  #endif
}

/**
  * @brief  This function handles RTC second interrupt request.
  * @param  None
  * @retval None
  */
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
void RTC_IRQHandler(void) {

  if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);

    /* Enable time update */
    SET_FLAG(Flag_NewSecond);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }
}
#elif defined(USE_HAL_DRIVER) & defined(STM32F407xx)
void RTC_WKUP_IRQHandler(void){
  HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
  /* Enable time update */
  SET_FLAG(Flag_NewSecond);
  HAL_RTC_GetState(hrtc);
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}
#endif

/**
  * @brief  This function set time in rtc from a time message.
  * @param  TimeData: Pointer of the hour byte from a time message.
  * @retval None
  */
void RTC_SetTime(uint_least8_t *TimeData) {
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  /* Convert TimeData into second value */
  uint32_t seconds = (uint32_t)(*TimeData) * 3600;
  TimeData++;
  seconds += (uint32_t)(*TimeData) * 60;
  TimeData++;
  seconds += *TimeData;

  if (RTC_GetCounter() != seconds ) {
    RTC_SetCounter(seconds);
  }

#elif defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  sDate.Year = *TimeData;
  TimeData++;
  sDate.Month = *TimeData;
  TimeData++;
  sDate.Date = *TimeData;
  TimeData++;
  sDate.WeekDay = *TimeData;
  TimeData++;
  sTime.Hours = *TimeData;
  TimeData++;
  sTime.Minutes = *TimeData;
  TimeData++;
  sTime.Seconds = *TimeData;

  sTime.TimeFormat = RTC_HOURFORMAT12_AM;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;

  HAL_RTC_SetTime(&RtcHandle, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_SetDate(&RtcHandle, &sDate, RTC_FORMAT_BIN);
#endif
}
/**
  * @brief  This function set time in rtc from a time message.
  * @param  TimeData: Pointer of the hour byte from a time message.
  * @retval None
  */
uint32_t RTC_GetUnixTime(void) {
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  return RTC_GetCounter();
#elif defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  struct tm time;
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  HAL_RTC_GetTime(&RtcHandle, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&RtcHandle, &sDate, RTC_FORMAT_BIN);

  time.tm_sec = sTime.Seconds;
  time.tm_min = sTime.Minutes;
  time.tm_hour = sTime.Hours;
  time.tm_mday = sDate.Date;
  time.tm_mon = sDate.Month;
  time.tm_year = sDate.Year + 100;
  time.tm_wday = sDate.WeekDay;

  return (uint32_t)mktime(&time);
#endif
}

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
#include "rtc.h"

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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Config(void) {
  /* Enable PWR and BKP clocks */
  RTC_CLK_ENABLE();
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
  /* Select LSE as RTC Clock Source */
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

  /* Configure NVIC */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = RTC_IRQ_PRE_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = RTC_IRQ_SUB_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
}

/**
  * @brief  This function handles RTC second interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void) {
#if defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);

    /* Enable time update */
    SET_FLAG(Flag_NewSecond);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }
}
/*#elif defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  HAL_RTC_IRQHandler();*/
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
#endif
}

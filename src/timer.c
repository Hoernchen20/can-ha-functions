/*
 * @file    timer.c
 * @author  Felix Horn
 * @version 0.1
 * @date    12-Dec-2015
 * @brief   This file contains functions for a weekly timer.
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


/* Includes ----------------------------------------------------------*/
#include "timer.h"

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
struct {
    uint_least16_t Minute;
    uint_least8_t  OnDays;
    void *         Function;
    bool           WorkThrough;
    bool           FunctionComplete;
} TimerData[TIMER_ENTRIES];
uint_least16_t Minutes;

/* Private function prototypes ---------------------------------------*/
/* Private functions -------------------------------------------------*/

/**
  * @brief  Initialize data struct of timer and set minute variable.
  * @param  Minutes: Actual time in minutes.
  * @retval None
  */
void InitTimer(uint_least16_t Minutes) {
    SetTimerMinutes(Minutes);
}


/**
  * @brief  Handles Timer. Should start every minute.
  * @param  None
  * @retval None
  */
void HandleTimer(void) {
}


/**
  * @brief  Set global minute variable to actual time.
  * @param  Minutes: Actual time in minutes.
  * @retval None
  */
void SetTimerMinutes(uint_least16_t Minutes) {

}


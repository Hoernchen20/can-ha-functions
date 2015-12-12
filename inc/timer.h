/**
 * @file    timer.h
 * @author  Felix Horn
 * @version 0.1
 * @date    12-Dec-2015
 * @brief   This file contains defines and functions prototypes for
 *          heating, ventilation and air condition.
 *
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


#ifndef TIMER_H_
#define TIMER_H_

/* Includes ----------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported constants ------------------------------------------------*/
#define TIMER_ENTRIES 10

/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
/* Exported macro ----------------------------------------------------*/
#define CALC_MINUTES(h, m) h * 60 + m

/* Exported functions ------------------------------------------------*/
void InitTimer(uint_least16_t Minutes);
void HandleTimer(void);
void SetTimerMinutes(uint_least16_t Minutes);

#endif /* TIMER_H_ */

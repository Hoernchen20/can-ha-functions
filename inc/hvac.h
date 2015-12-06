﻿/**
 * @file    hvac.h
 * @author  Felix Horn
 * @version 0.1
 * @date    03-Nov-2015
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


#ifndef HVAC_H_
#define HVAC_H_

/**********************************************************************/
/**                                                                  **/
/**                             General                              **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/

/**********************************************************************/
/**                                                                  **/
/**                             Heating                              **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
/* Exported constants ------------------------------------------------*/
#define LIFETIME_ACTUAL_VALUE   300   /** in seconds */
#define BLOCKING_TIME_WINDOW    300   /** in seconds */
#define HYSTERESE               20    /** fix point 10,00°C = 1000) */
#define FREEZING_LEVEL          1000  /** fix point 10,00°C = 1000) */

/* Channel 1 */
#define CH1_STD_ACTUALVALUE         2000
#define CH1_STD_SETPOINT            2000
#define CH1_STD_CALCULATESETPOINT   1500

/* Exported types ----------------------------------------------------*/
typedef enum {
    Channel1,

    /* Don't remove this */
    NumberHeatingChannels
}HeatingChannel;

/* Exported variables ------------------------------------------------*/
extern volatile int16_t OutsideTemperature;

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
void Heating_Init(void);
void Heating_Handler(void);
void Heating_Put_ActualValue(HeatingChannel Channel, int_least16_t Value);
void Heating_Put_SetPoint(HeatingChannel Channel, int_least16_t Value);
void Heating_Put_WindowContact(HeatingChannel Channel, bool State);
int_least16_t Heating_GetCalculateSetPoint(HeatingChannel Channel);

/**********************************************************************/
/**                                                                  **/
/**                           Ventilation                            **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/

/**********************************************************************/
/**                                                                  **/
/**                          Air Condition                           **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/

#endif /* HVAC_H_ */

/**
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
#include "rtc.h"
/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/

/**********************************************************************/
/**                                                                  **/
/**                             Heating                              **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
/* Exported constants ------------------------------------------------*/
#define NUM_HEATING_CHANNELS    1
#define LIFETIME_MEASURED_VALUE 300   /** in seconds */
#define BLOCKING_TIME_WINDOW    300   /** in seconds */
#define HYSTERESE               20    /** fix point 10,00°C = 1000) */
#define FREEZING_LEVEL          1000  /** fix point 10,00°C = 1000) */

/* Exported types ----------------------------------------------------*/
typedef struct {
    /* Input */
    int_least16_t   ActualValue; /** fix point 10,00°C = 1000) */
    int_least16_t   SetPoint;    /** fix point 10,00°C = 1000) */
    bool            WindowContact; /** FALSE = window is closed */

    /* Output */
    bool            Heating;
    bool            ActualValue_IsOld;
    bool            Heating_FreezingLevel; /* Heating dispite the window
                                            * is open and the temprature
                                            * is unter the freezing
                                            * level */
    int_least16_t   CalculateSetPoint;

    /* Config */
    
    /* Private */
    uint_least16_t  Lifetime_ActualValue;
    uint_least16_t  BlockingTime_WindowContact;
} Heating_HandleTypeDef;

/* Exported variables ------------------------------------------------*/
extern int16_t OutsideTemperature;
extern Heating_HandleTypeDef hHeating[NUM_HEATING_CHANNELS];

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
void Heating_Handler(void);
void Heating_Put_ActualValue(Heating_HandleTypeDef *hhtd, int_least16_t Value);
void Heating_Put_SetPoint(Heating_HandleTypeDef *hhtd, int_least16_t Value);
void Heating_Put_WindowContact(Heating_HandleTypeDef *hhtd, bool State);

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

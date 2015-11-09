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
#define MAX_AGE_MEASURED_VALUE  1800  /** in seconds */
#define HYSTERESE               20    /** fix point 10,00°C = 1000) */
#define FREEZING_LEVEL          1000  /** fix point 10,00°C = 1000) */

/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
typedef struct {
    /* Input */
    int_least16_t   ActualValue; /** fix point 10,00°C = 1000) */
    int_least16_t   SetPoint;    /** fix point 10,00°C = 1000) */
    bool            WindowContact;

    /* Output */
    bool            Heating;
    bool            ActuealValue_IsToOld;
    bool            Heating_FreezingLevel; /* Heating dispite the window
                                           * is open and the temprature
                                           * is unter the freezing
                                           * level */

    /* Config */
    
    /* Private */
    uint32_t  Timestamp_ActualValue_IsToOld; /* After this time
                                                    * the actual value
                                                    * is to old */
} Heating_HandleTypeDef;

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
void Heating_Handler(void);
void Heating_Put_ActualValue(Heating_HandleTypeDef *hhtd, int_least16_t Value);
void Heating_Put_SetPoint(Heating_HandleTypeDef *hhtd, int_least16_t Value);

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

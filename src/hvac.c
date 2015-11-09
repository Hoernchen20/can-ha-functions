/*
 * @file    hvac.c
 * @author  Felix Horn
 * @version 0.1
 * @date    03-Nov-2015
 * @brief   This file contains functions for heating, ventilation
 *          and air condition.
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


/**********************************************************************/
/**                                                                  **/
/**                             General                              **/
/**                                                                  **/
/**********************************************************************/
/* Includes ----------------------------------------------------------*/
#include "../inc/hvac.h"
#include <stdint.h>

/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
/* Private functions -------------------------------------------------*/
/**
  * @brief  None.
  * @param  None
  * @retval None
  */

/**********************************************************************/
/**                                                                  **/
/**                             Heating                              **/
/**                                                                  **/
/**********************************************************************/
/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
Heating_HandleTypeDef hHeating[NUM_HEATING_CHANNELS];

/* Private function prototypes ---------------------------------------*/
static void Heating_Function(Heating_HandleTypeDef *p);

/* Private functions -------------------------------------------------*/
/**
  * @brief  Handles all heating channels.
  * @param  None
  * @retval None
  */
void Heating_Handler(void) {
    for ( uint_fast8_t i = 0; i < NUM_HEATING_CHANNELS; i++) {
        Heating_Function(&hHeating[i]);
    }
}

/**
  * @brief  Handles single heating channel.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @retval None
  */
static void Heating_Function(Heating_HandleTypeDef *p) {
    
}

/**
  * @brief  Write the measured actual value into heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  Value: Actual value (fix point 10,00°C = 1000).
  * @retval None
  */
void Heating_Put_ActualValue(Heating_HandleTypeDef *hhtd, int_least16_t Value) {
    hhtd->ActualValue = Value;
    hhtd->Timestamp_ActualValue_IsToOld = RTC_GetUnixTime + MAX_AGE_MEASURED_VALUE;
}

/**
  * @brief  Write the setpoint into heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  Value: Setpoint (fix point 10,00°C = 1000).
  * @retval None
  */
void Heating_Put_SetPoint(Heating_HandleTypeDef *hhtd, int_least16_t Value) {
    hhtd->SetPoint = Value;
}

/**********************************************************************/
/**                                                                  **/
/**                           Ventilation                            **/
/**                                                                  **/
/**********************************************************************/
/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
/* Private functions -------------------------------------------------*/

/**
  * @brief  None.
  * @param  None
  * @retval None
  */

/**********************************************************************/
/**                                                                  **/
/**                          Air Condition                           **/
/**                                                                  **/
/**********************************************************************/
/* Private typedef ---------------------------------------------------*/
/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
/* Private function prototypes ---------------------------------------*/
/* Private functions -------------------------------------------------*/

/**
  * @brief  None.
  * @param  None
  * @retval None
  */

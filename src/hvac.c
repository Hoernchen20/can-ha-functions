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
uint32_t Timestamp_OldHandling;
int16_t OutsideTemperature;
Heating_HandleTypeDef hHeating[NUM_HEATING_CHANNELS];

/* Private function prototypes ---------------------------------------*/
static void Heating_Function(Heating_HandleTypeDef *hhtd);

/* Private functions -------------------------------------------------*/
/**
  * @brief  Handles all heating channels.
  * @param  None
  * @retval None
  */
void Heating_Handler(void) {
    uint32_t tmp_time = RTC_GetUnixTime();
    
    /* Work only every second */
    if (tmp_time > Timestamp_OldHandling ) {
        
        /* Work off every channel */
        for ( uint_fast8_t i = 0; i < NUM_HEATING_CHANNELS; i++) {
            Heating_Function(&hHeating[i]);
        }
        
        /* Save old working time */
        Timestamp_OldHandling = tmp_time;
    }
}

/**
  * @brief  Handles single heating channel.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @retval None
  */
static void Heating_Function(Heating_HandleTypeDef *hhtd) {
    /* Decrease time values */
    Lifetime_ActualValue--;
    BlockingTime_WindowContact--;
    
    /* Manipulate set point with outside temperature */
    if (OutsideTemperature > 1000) {
        hhtd->CalculateSetPoint =
            hhtd->SetPoint - (OutsideTemperature - 1000) / 4;
    }
    
    
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
    hhtd->Lifetime_ActualValue = LIFETIME_MEASURED_VALUE;
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

/**
  * @brief  Set or unset the window contact int heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  State: State of window contact (0 = window is open).
  * @retval None
  */
void Heating_Put_WindowContact(Heating_HandleTypeDef *hhtd, bool State) {
    hhtd->WindowContact = State;
    if (State) {
        hhtd->BlockingTime_WindowContact = BLOCKING_TIME_WINDOW;
    }
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

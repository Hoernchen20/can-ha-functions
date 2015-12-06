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
#include "hvac.h"

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
struct {
    /* Input */
    int_least16_t   ActualValue; /** fix point 10,00°C = 1000) */
    int_least16_t   SetPoint;    /** fix point 10,00°C = 1000) */
    int_least16_t   CalculateSetPoint;
    bool            WindowContact; /** false = window is closed */

    /* Output */
    bool            Heating;
    bool            ActualValue_IsOld;
    bool            Heating_FreezingLevel; /* Heating dispite the window
                                            * is open and the temprature
                                            * is unter the freezing
                                            * level */


    /* Config */

    /* Private */
    uint_least16_t  Lifetime_ActualValue;
    uint_least16_t  BlockingTime_WindowContact;
} hHeating[NumberHeatingChannels];

/* Private define ----------------------------------------------------*/
/* Private macro -----------------------------------------------------*/
/* Private variables -------------------------------------------------*/
int16_t OutsideTemperature = 1500;

/* Private function prototypes ---------------------------------------*/
static void Heating_Function(HeatingChannel Channel);

/* Private functions -------------------------------------------------*/
void Heating_Init(void) {
    for(uint_fast8_t i = 0; i < NumberHeatingChannels; i++) {
        hHeating[i].ActualValue = CH1_STD_ACTUALVALUE;
        hHeating[i].SetPoint = CH1_STD_SETPOINT;
        hHeating[i].CalculateSetPoint = CH1_STD_CALCULATESETPOINT;
        hHeating[i].WindowContact = false;
        hHeating[i].Heating = false;
        hHeating[i].ActualValue_IsOld = false;
        hHeating[i].Heating_FreezingLevel = false;
        hHeating[i].Lifetime_ActualValue = LIFETIME_ACTUAL_VALUE;
        hHeating[i].BlockingTime_WindowContact = 0;
    }
}

/**
  * @brief  Handles all heating channels.
  * @param  None
  * @retval None
  */
void Heating_Handler(void) {
    /* Work off every channel */
    for ( uint_fast8_t i = 0; i < NumberHeatingChannels; i++) {
        Heating_Function(i);
    }
}

/**
  * @brief  Handles single heating channel.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @retval None
  */
static void Heating_Function(HeatingChannel Channel) {
    bool HeatingState;

    /* Manipulate set point with outside temperature */
    if (OutsideTemperature > 1000) {
        hHeating[Channel].CalculateSetPoint = (int_least16_t)(
                hHeating[Channel].SetPoint - (OutsideTemperature - 1000) / 4); /* check if division with shift right is smaller */
    } else {
        hHeating[Channel].CalculateSetPoint = hHeating[Channel].SetPoint;
    }
    
    /* Decrease time values and check blocking time of window contact */
    if (hHeating[Channel].Lifetime_ActualValue > 0) {
        hHeating[Channel].Lifetime_ActualValue--;
    }
    
    if (hHeating[Channel].BlockingTime_WindowContact > 0) {
        hHeating[Channel].BlockingTime_WindowContact--;
        HeatingState = false;
    } else {
        if (hHeating[Channel].WindowContact) {
            /* check if temperature is under freezing level then heat */
            if (hHeating[Channel].ActualValue < FREEZING_LEVEL) {
                HeatingState = true;
                hHeating[Channel].Heating_FreezingLevel = true;
            }
            if (hHeating[Channel].ActualValue > FREEZING_LEVEL + HYSTERESE){
                HeatingState = false;
                hHeating[Channel].Heating_FreezingLevel = false;
            }
        } else {
            /* heat if temperature is to low */
            if (hHeating[Channel].ActualValue < (hHeating[Channel].CalculateSetPoint - HYSTERESE)) {
                HeatingState = true;
            }
            if (hHeating[Channel].ActualValue > (hHeating[Channel].CalculateSetPoint + HYSTERESE)){
                HeatingState = false;
            }
        }
    }
    
    /* Save temporary state */
    hHeating[Channel].Heating = HeatingState;
}

/**
  * @brief  Write the measured actual value into heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  Value: Actual value (fix point 10,00°C = 1000).
  * @retval None
  */
void Heating_Put_ActualValue(HeatingChannel Channel, int_least16_t Value) {
    hHeating[Channel].ActualValue = Value;
    hHeating[Channel].Lifetime_ActualValue = LIFETIME_ACTUAL_VALUE;
}

/**
  * @brief  Write the setpoint into heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  Value: Setpoint (fix point 10,00°C = 1000).
  * @retval None
  */
void Heating_Put_SetPoint(HeatingChannel Channel, int_least16_t Value) {
    hHeating[Channel].SetPoint = Value;
}

/**
  * @brief  Set or unset the window contact in heating struct.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @param  State: State of window contact (false = window is closed).
  * @retval None
  */
void Heating_Put_WindowContact(HeatingChannel Channel, bool State) {
    hHeating[Channel].WindowContact = State;
    if (State) {
        hHeating[Channel].BlockingTime_WindowContact = 0;
    } else {
        hHeating[Channel].BlockingTime_WindowContact = BLOCKING_TIME_WINDOW;
    }
}

int_least16_t Heating_GetCalculateSetPoint(HeatingChannel Channel) {
    return hHeating[Channel].CalculateSetPoint;
}

bool Heating_GetHeatingState(HeatingChannel Channel) {
    return hHeating[Channel].Heating;
}

bool Heating_IsActualValueOld(HeatingChannel Channel) {
    return hHeating[Channel].ActualValue_IsOld;
}

bool Heating_GetWindowContact(HeatingChannel Channel) {
    return hHeating[Channel].WindowContact;
}

bool Heating_GetHeating_FreezingLevel(HeatingChannel Channel) {
    return hHeating[Channel].Heating_FreezingLevel;
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

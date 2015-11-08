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
Heating_TypeDef hHeating[NUM_HEATING_CHANNELS];

/* Private function prototypes ---------------------------------------*/
static void Heating_Function(Heating_TypeDef *p);

/* Private functions -------------------------------------------------*/
/**
  * @brief  Handles all heating channels.
  * @param  None
  * @retval None
  */
void Heating_Handler(void) {
    for ( uint_fast8_t i = 0; i < NUM_HEATING_CHANNELS; i++) {
        Heating_Function(hHeating[i-1]);
    }
}

/**
  * @brief  Handles single heating channel.
  * @param  hhtd: Pointer to the handle struct of the specific heating 
  *               channel.
  * @retval None
  */
static void Heating_Function(Heating_TypeDef *p) {
    
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

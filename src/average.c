/*
 * @file    average.c
 * @author  Felix Horn
 * @version 0.1
 * @date    24-Jan-2016
 * @brief   This file contains functions for an average calculation.
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
#include "average.h"

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
int_least16_t AverageIntLeast16(AverageIntLeast16_TypeDef *Instance, int_least16_t NewValue) {
    /* remove oldest value frum sum */
    Instance->Sum -= Instance->LastValues[Instance->ValuePtr];
    
    /* save new value into buffer and add it to sum */
    Instance->LastValues[Instance->ValuePtr] = NewValue;
    Instance->Sum += NewValue;
    
    /* increase buffer pointer */
    Instance->ValuePtr++;
    Instance->ValuePtr %= Instance->NumOfLastValues;
    
    /* calculate average */
    Instance->Average = (int_least16_t)(Instance->Sum / Instance->NumOfLastValues);
    return Instance->Average;
}

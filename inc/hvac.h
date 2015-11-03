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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#if defined(USE_HAL_DRIVER) & defined(STM32F407xx)
  #include "stm32f4xx_hal.h"
#elif defined(USE_HAL_DRIVER) & defined(STM32F1xx)
  #include "stm32f1xx_hal.h"
#elif defined(USE_STDPERIPH_DRIVER) & defined(STM32F10X_CL)
  #include "stm32f10x.h"
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#endif /* HVAC_H_ */

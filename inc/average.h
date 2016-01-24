/**
 * @file    average.h
 * @author  Felix Horn
 * @version 0.1
 * @date    24-Jan_2016
 * @brief   This file contains defines and functions prototypes for
 *          an average calculation.
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


#ifndef AVERAGE_H_
#define AVERAGE_H_

/* Includes ----------------------------------------------------------*/
#include <stdint.h>

/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
typedef struct {
    const uint_least16_t  NumOfLastValues;
    uint_least16_t  ValuePtr;
    int_least32_t   Sum;
    int_least16_t   Average;
    int_least16_t   LastValues[8];
} AverageIntLeast16_TypeDef;

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
int_least16_t AverageIntLeast16(AverageIntLeast16_TypeDef *Instance, int_least16_t NewValue);

#endif /* AVERAGE_H_ */

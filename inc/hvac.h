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
/* Exported constants ------------------------------------------------*/
/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
#ifndef BOOL
#define BOOL
typedef enum { FALSE, TRUE }bool;
#endif

<<<<<<< HEAD
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

/* Exported variables ------------------------------------------------*/
/* Exported types ----------------------------------------------------*/
typedef struct {
    int_least16_t   MeasuredValue;
    int_least16_t   ActualValue;
    uint_least32_t  Timestamp_ActualValue;
    bool            WindowContact;
    bool            Heating;
    //heizen trotz fenster auf
    bool            AblaufIstwert //translate
} Heating_HandleTypeDef;

/* Exported macro ----------------------------------------------------*/
/* Exported functions ------------------------------------------------*/
void Heating_Handler(Heating_TypeDef *hhtd);

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

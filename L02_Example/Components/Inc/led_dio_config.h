/**
  ******************************************************************************
  * @file		  : led_dio_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.2
   * @date    : Oct 9, 2025
  * @brief    : Digital output LED components configuration file
  *
  ******************************************************************************
  */
#ifndef INC_LED_DIO_CONFIG_H_
#define INC_LED_DIO_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "led_dio.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#define LED_GET_ID(hld) (hld == &hld1 ? 1 : \
                         hld == &hld2 ? 2 : \
                         hld == &hld3 ? 3 : 0)

/* Public variables ----------------------------------------------------------*/
extern LED_DIO_Handle_TypeDef hld1;
extern LED_DIO_Handle_TypeDef hld2;
extern LED_DIO_Handle_TypeDef hld3;

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_LED_DIO_CONFIG_H_ */

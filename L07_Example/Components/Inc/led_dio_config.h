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

/* Public variables ----------------------------------------------------------*/
extern LED_DIO_Handle_TypeDef hld1;
extern LED_DIO_Handle_TypeDef hld2;
extern LED_DIO_Handle_TypeDef hld3;

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Writes to LD1-3 as to LED line with 4 values
 *        (LD1 is least significant, LD3 most significant)
 * @param[in] n : Input value: 0, 1, 2 or 3.
 * retval None.
 */
void LED_DIO_Line_WriteValue(unsigned int n);

#endif /* INC_LED_DIO_CONFIG_H_ */

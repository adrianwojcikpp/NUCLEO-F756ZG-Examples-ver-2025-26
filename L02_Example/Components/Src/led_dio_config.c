/**
  ******************************************************************************
  * @file		  : led_dio_config.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.2
  * @date     : Oct 9, 2025
  * @brief   	: Digital output LED components configuration file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led_dio.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LED_DIO_Handle_TypeDef hld1 = LED_DIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld2 = LED_DIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld3 = LED_DIO_INIT_HANDLE(LD3, LED_ON_HIGH);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

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

/* Public variables ----------------------------------------------------------*/
LED_DIO_Handle_TypeDef hld1 = LED_DIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld2 = LED_DIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld3 = LED_DIO_INIT_HANDLE(LD3, LED_ON_HIGH);

/* Private variables ---------------------------------------------------------*/
LED_DIO_Handle_TypeDef *hld[] = { &hld1, &hld2, &hld3 };

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Writes to LD1-3 as to LED line with 4 values
 *        (LD1 is least significant, LD3 most significant)
 * @param[in] n : Input value: 0, 1, 2 or 3.
 * retval None.
 */
void LED_DIO_Line_WriteValue(unsigned int n)
{
  for(unsigned int i = 0; i < (sizeof(hld)/sizeof(hld[0])); i++)
    LED_DIO_Write(hld[i], n > i);
}

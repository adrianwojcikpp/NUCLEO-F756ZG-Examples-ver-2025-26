/**
  ******************************************************************************
  * @file     : led_pwm.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.5.0
  * @date     : Nov 20, 2024
  * @brief    : LED components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led_pwm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Initialize PWM LED control
  * @param[in] hled   : LED PWM handler
  * @retval None
  */
void LED_PWM_Init(LED_PWM_Handle_TypeDef* hled)
{
  hled->Output.Duty = (hled->ActiveState == LED_ON_HIGH) ? (hled->Output.Duty) : (100.0f - hled->Output.Duty);
  PWM_Init(&(hled->Output));
}

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hled   : LED PWM handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void LED_PWM_WriteDuty(LED_PWM_Handle_TypeDef* hled, float duty)
{
  hled->Output.Duty = (hled->ActiveState == LED_ON_HIGH) ? (duty) : (100.0f - duty);
  PWM_WriteDuty(&(hled->Output), hled->Output.Duty);
}

/**
  * @brief Read PWM duty cycle
  * @param[in] hled   : LED PWM handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float LED_PWM_ReadDuty(const LED_PWM_Handle_TypeDef* hled)
{
  return (hled->ActiveState == LED_ON_HIGH) ? (hled->Output.Duty) : (100.0f - hled->Output.Duty);
}

/**
  * @brief Initialize PWM LED RGB control
  * @param[in/out] hled   : LED RGB PWM handler
  * @retval None
  */
void LED_RGB_PWM_Init(LED_RGB_PWM_Handle_TypeDef* hled)
{
  LED_PWM_Init(hled->R);
  LED_PWM_Init(hled->G);
  LED_PWM_Init(hled->B);
}

/**
  * @brief Write LED color
  * @param[in/out] hled   : LED PWM handler
  * @param[in]     color  : 24 bit RGB color
  * @retval None
  */
void LED_RGB_PWM_WriteColor(LED_RGB_PWM_Handle_TypeDef* hled, unsigned int color)
{
  LED_PWM_WriteDuty(hled->R, 100*((0x00FF0000 & color) >> 16) / 255.0f);
  LED_PWM_WriteDuty(hled->G, 100*((0x0000FF00 & color) >>  8) / 255.0f);
  LED_PWM_WriteDuty(hled->B, 100*((0x000000FF & color) >>  0) / 255.0f);
}

/**
  * @brief Read LED color
  * @param[in] hled   : LED RGB PWM handler
  * @retval 24 bit RGB color
  */
unsigned int LED_RGB_PWM_ReadColor(const LED_RGB_PWM_Handle_TypeDef* hled)
{
  unsigned int r = 255*LED_PWM_ReadDuty(hled->R) / 100.0f;
  unsigned int g = 255*LED_PWM_ReadDuty(hled->G) / 100.0f;
  unsigned int b = 255*LED_PWM_ReadDuty(hled->B) / 100.0f;
  return (r << 16) | (g << 8) | (b << 0);
}

/**
  ******************************************************************************
  * @file     : pwm.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Pulse Width Modulation outputs components driver.
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "pwm.h"

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
  * @brief Initialize PWM output
  * @param[in/out] hpwm   : PWM output handle
  * @retval None
  */
void PWM_Init(PWM_Handle_TypeDef* hpwm)
{
  PWM_WriteDuty(hpwm, hpwm->Duty);
  HAL_TIM_PWM_Start(hpwm->Timer, hpwm->Channel);
}

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hpwm   : PWM output handle
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void PWM_WriteDuty(PWM_Handle_TypeDef* hpwm, float duty)
{
  // Saturate duty cycle value
    // TODO
  // Write duty to handle field
    // TODO
  // Compute Capture/Compare Register value
    // TODO
  // Write value to register
    // TODO
}

/**
  * @brief Set PWM duty cycle
  * @param[in]     hpwm   : PWM output handle
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float PWM_ReadDuty(const PWM_Handle_TypeDef* hpwm)
{
  return hpwm->Duty;
}

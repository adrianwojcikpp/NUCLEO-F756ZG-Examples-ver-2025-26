/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "led_dio_config.h"
#include "jsmn.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */
/**
 * @brief  Low-level implementation of the _write system call.
 *
 * This function redirects standard output (e.g., printf) to UART3.
 * It transmits data from the provided buffer over the UART interface.
 *
 * @param[in]  file File descriptor (ignored in this implementation).
 * @param[in]  ptr  Pointer to the data buffer to be transmitted.
 * @param[in]  len  Number of bytes to transmit.
 *
 * @retval Number of bytes transmitted on success.
 * @retval -1 on transmission error.
 *
 * @note This function is typically used when retargeting printf() to UART.
 *       It blocks until all bytes are sent (uses HAL_MAX_DELAY).
 */
int _write(int file, char *ptr, int len)
{
  return (HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, HAL_MAX_DELAY) == HAL_OK) ? len : -1;
}

/**
 * @brief  Low-level implementation of the _read system call.
 *
 * This function redirects standard input (e.g., scanf) to UART3.
 * It receives data into the provided buffer from the UART interface.
 *
 * @param[in]  file File descriptor (ignored in this implementation).
 * @param[out] ptr  Pointer to the data buffer where received bytes will be stored.
 * @param[in]  len  Maximum number of bytes to read.
 *
 * @retval Number of bytes received on success.
 * @retval -1 on reception error.
 *
 * @note This function blocks until the specified number of bytes is received.
 *       It is typically used when retargeting scanf() to UART.
 */
int _read(int file, char *ptr, int len)
{
  return (HAL_UART_Receive(&huart3, (uint8_t*)ptr, len, HAL_MAX_DELAY) == HAL_OK) ? len : -1;
}

/**
 * @brief Read and validate command in the format "LDxy"
 *
 * @param[in] str    : Input C-string (must be null-terminated)
 * @param[out] led   : Double pointer to LED_DIO_Handle_TypeDef
 * @param[out] state : Pointer to LED_DIO_State_TypeDef
 * @return true if valid format and values, false otherwise
 */
_Bool UART_ParseCmd(const char *json, LED_DIO_Handle_TypeDef **hled, LED_DIO_State_TypeDef *state)
{
  if(!json)
    return 0;

  jsmn_parser parser;
  jsmntok_t tokens[128]; // Adjust size depending on expected input complexity
  jsmn_init(&parser);

  int token_count = jsmn_parse(&parser, json, strlen(json), tokens, sizeof(tokens)/sizeof(tokens[0]));
  if(token_count < 1 || tokens[0].type != JSMN_ARRAY)
    return 0;

  size_t led_index = 0;

  // Iterate over array elements
  for(int i = 1; i < token_count && led_index < 3; )
  {
    if(tokens[i].type != JSMN_OBJECT)
    {
      i++;
      continue;
    }

    int object_size = tokens[i].size * 2; // Each key-value pair = 2 tokens
    int end = i + object_size + 1;

    int led_val = -1;
    _Bool state_val = 0;
    _Bool led_found = 0, state_found = 0;

    // Process each key-value pair
    for(int j = i + 1; j < end; j += 2)
    {
      jsmntok_t key = tokens[j];
      jsmntok_t val = tokens[j + 1];

      // Extract key string
      int key_len = key.end - key.start;
      const char *key_str = json + key.start;

      if(strncmp(key_str, "id", key_len) == 0 && val.type == JSMN_STRING)
      {
        if(strncmp(json + val.start, "LD", 2) == 0)
        {
          led_val = atoi(json + val.start + 2);
          if (led_val >= 1 && led_val <= 3)
            led_found = 1;
        }
      }
      else if(strncmp(key_str, "state", key_len) == 0 && val.type == JSMN_PRIMITIVE)
      {
        if(strncmp(json + val.start, "true", 4) == 0 || atoi(json + val.start) == 1)
          state_val = 1;
        else if (strncmp(json + val.start, "false", 5) == 0 || atoi(json + val.start) == 0)
          state_val = 0;
        else
          return 0; // Invalid value
        state_found = 1;
      }
    }

    if(led_found && state_found)
    {
      switch(led_val)
      {
      case 1:
        hled[led_index] = &hld1;
        break;
      case 2:
        hled[led_index] = &hld2;
        break;
      case 3:
        hled[led_index] = &hld3;
        break;
      default: break;
      }
      state[led_index] = state_val;
      led_index++;
    }
    i = end;
  }
  return 1;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  setvbuf(stdin, NULL, _IONBF, 0);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  puts("Hello, Nucleo!");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    char json_str[128];
    scanf("%s", json_str);
    LED_DIO_Handle_TypeDef *hled[3] = { NULL, };
    LED_DIO_State_TypeDef state[3];
    if(UART_ParseCmd(json_str, hled, state))
    {
      for(int i = 0; hled[i] != NULL && i < 3; i++)
      {
        LED_DIO_Write(hled[i], state[i]);
        printf("LD%i is %s\n", LED_GET_ID(hled[i]), LED_DIO_Read(hled[i]) ? "On" : "Off" );
      }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

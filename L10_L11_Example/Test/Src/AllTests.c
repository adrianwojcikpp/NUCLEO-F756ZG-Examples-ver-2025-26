/**
  ******************************************************************************
  * @file     : AllTests.c
  * @author   : Enno Rehling https://github.com/ennorehling
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test runner for CMSIS DSP RMSE test suite using CuTest.
  *
  *             This file initializes and executes all CuTest suites, collects
  *             the results, and transmits test output via UART for diagnostics.
  *
  * @see      : https://github.com/ennorehling/cutest/blob/master/AllTests.c
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "CuTest.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
//CuSuite* CuGet_Test_CMSIS_DSP_RMSE_Suite(void);
//CuSuite* CuGet_Test_CMSIS_MULT_Suite(void);
//CuSuite* CuGet_Test_CMSIS_DSP_FIR_Suite(void);
//CuSuite* CuGet_Test_CMSIS_DSP_IIR_Suite(void);
CuSuite* CuGet_Test_CMSIS_DSP_PID_Suite(void);

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
int RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	//CuSuiteAddSuite(suite, CuGet_Test_CMSIS_DSP_RMSE_Suite());
	//CuSuiteAddSuite(suite, CuGet_TestCmsisDsp_MAT_MULT_Suite());
	//CuSuiteAddSuite(suite, CuGet_Test_CMSIS_DSP_FIR_Suite());
	//CuSuiteAddSuite(suite, CuGet_Test_CMSIS_DSP_IIR_Suite());
	CuSuiteAddSuite(suite, CuGet_Test_CMSIS_DSP_PID_Suite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);

	HAL_UART_Transmit(&huart3, (uint8_t*)output->buffer, output->length, 0xffff);
	return suite->failCount;
}

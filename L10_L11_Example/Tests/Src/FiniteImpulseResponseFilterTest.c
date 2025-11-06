/**
  ******************************************************************************
  * @file     : FiniteImpulseResponseFilterTest.c.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test for CMSIS DSP FIR filter function.
  *
  *             This file defines and verifies FIR filter computation based on
  *             CMSIS DSP library routines. The test uses the CuTest
  *             framework for validation.
  *
  * @see      : https://arm-software.github.io/CMSIS-DSP/latest/group__FIR.html
  *
  ******************************************************************************
  */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Private includes ----------------------------------------------------------*/
#include "CuTest.h"
#include "arm_math.h"

#include "FIR1_fir.h"
#include "X1_vec.h"
#include "Y1_vec.h"
#include "Y1_REF_vec.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USE_SWV_FIR 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if USE_SWV_FIR
float32_t SWV_FIR1;
#endif

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Root mean square error
 * @param[in] yref : Reference vector
 * @param[in] y    : Input vector
 * @param[in] len  : Vectors length
 * @return Root mean square error: sqrt(sum( (yref - y)^2 ))
 */
float32_t RMSE(const float32_t* y, const float32_t* yref, const uint32_t len);

/* Private functions ---------------------------------------------------------*/

void Test_CMSIS_DSP_FIR(CuTest *tc)
{
  // Initialize FIR filter instance
  arm_fir_init_f32(&FIR1, FIR1_NUM_TAPS, FIR1_COEFFS, FIR1_STATE, FIR1_BLOCK_SIZE);

  // Filter test signal sample by sample
  for(uint32_t i = 0; i < X1_LEN; i++)
  {
    arm_fir_f32(&FIR1, &X1[i], &Y1[i], FIR1_BLOCK_SIZE);
    #if USE_SWV_FIR
    SWV_FIR1 = Y1[i];
    HAL_Delay(0);
    #endif
  }

  float32_t rmse = RMSE(Y1_REF, Y1, Y1_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-6f);
}

/* Public functions ----------------------------------------------------------*/
CuSuite* CuGet_Test_CMSIS_DSP_FIR_Suite(void)
{
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_CMSIS_DSP_FIR);
  return suite;
}

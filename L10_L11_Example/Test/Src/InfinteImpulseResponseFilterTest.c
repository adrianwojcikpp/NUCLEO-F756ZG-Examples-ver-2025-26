/**
  ******************************************************************************
  * @file     : InfiniteImpulseResponseFilterTest.c.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test for CMSIS DSP Biquad Cascade IIR filter function.
  *
  *             This file defines and verifies Biquad Cascade IIR filter
  *             computation based on CMSIS DSP library routines.
  *             The test uses the CuTest framework for validation.
  *
  * @see      : https://arm-software.github.io/CMSIS-DSP/main/group__BiquadCascadeDF2T.html
  *
  ******************************************************************************
  */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Private includes ----------------------------------------------------------*/
#include "CuTest.h"
#include "arm_math.h"

#include "IIR1_biquad_df1.h"
#include "X2_vec.h"
#include "Y2_vec.h"
#include "Y2_REF_vec.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USE_SWV_IIR 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if USE_SWV_IIR
float32_t SWV_IIR1;
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

void Test_CMSIS_DSP_IIR(CuTest *tc)
{
  // Initialize FIR filter instance
  arm_biquad_cascade_df1_init_f32(&IIR1, IIR1_NUM_STAGES, IIR1_COEFFS, IIR1_STATE);

  // Filter test signal sample by sample
  for(uint32_t i = 0; i < X2_LEN; i++)
  {
      arm_biquad_cascade_df1_f32(&IIR1, &X2[i], &Y2[i], IIR1_BLOCK_SIZE);
#if USE_SWV_IIR
      SWV_IIR1 = Y2[i];
      HAL_Delay(0);
#endif
   }

  float32_t rmse = RMSE(Y2_REF, Y2, Y2_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-4f);
}

/* Public functions ----------------------------------------------------------*/
CuSuite* CuGet_Test_CMSIS_DSP_IIR_Suite(void)
{
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_CMSIS_DSP_IIR);
  return suite;
}

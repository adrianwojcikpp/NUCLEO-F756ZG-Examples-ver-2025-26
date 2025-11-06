/**
  ******************************************************************************
  * @file     : RmseTest.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test for CMSIS DSP Root Mean Square Error (RMSE) function.
  *
  *             This file defines and verifies an RMSE computation based on
  *             CMSIS DSP library routines. The test uses the CuTest framework
  *             for validation.
  *
  * @see      : https://arm-software.github.io/CMSIS-DSP/main/group__RMS.html
  *
  ******************************************************************************
  */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Private includes ----------------------------------------------------------*/
#include "CuTest.h"
#include "arm_math.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

// ########## FUNCTION FOR UNIT TESTING BEGIN ############################### //

/**
 * @brief Root mean square error
 * @param[in] yref : Reference vector
 * @param[in] y    : Input vector
 * @param[in] len  : Vectors length
 * @return Root mean square error: sqrt(sum( (yref - y)^2 ))
 */
float32_t RMSE(const float32_t* y, const float32_t* yref, const uint32_t len)
{
  float32_t err[len];
  arm_sub_f32(yref, y, err, len);
  float32_t rmse;
  arm_rms_f32(err, len, &rmse);
  return rmse;
}

// ########## FUNCTION FOR UNIT TESTING END ################################# //

void Test_CMSIS_DSP_RMSE(CuTest *tc)
{
  const float32_t a[] = { 0.8150f, 0.9060f, 0.1270f };
  const float32_t b[] = { 0.9130f, 0.6320f, 0.0980f };
  const float32_t c_ref = -0.1688402f;

  // CMSIS DSP implementation of root mean square error
  float32_t c = RMSE(a, b, 3);

  CuAssertDblEquals(tc, c_ref, c, 1e-7f);
}

/* Public functions ----------------------------------------------------------*/
CuSuite* CuGet_Test_CMSIS_DSP_RMSE_Suite(void)
{
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_CMSIS_DSP_RMSE);
  return suite;
}

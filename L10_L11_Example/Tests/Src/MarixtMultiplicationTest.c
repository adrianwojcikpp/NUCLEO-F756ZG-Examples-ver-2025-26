/**
  ******************************************************************************
  * @file     : MarixtMultiplicationTest.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test for CMSIS DSP matrix multiplication function.
  *
  *             This file defines and verifies matrix multiplication computation
  *             based onCMSIS DSP library routines. The test uses the CuTest
  *             framework for validation.
  *
  * @see      : https://arm-software.github.io/CMSIS-DSP/main/group__MatrixMult.html
  *
  ******************************************************************************
  */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Private includes ----------------------------------------------------------*/
#include "CuTest.h"
#include "arm_math.h"

#include "A_mat.h"
#include "B_mat.h"
#include "C_mat.h"
#include "C_REF_mat.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

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

void TestCmsisDsp_MAT_MULT(CuTest *tc)
{
  // Initialize matrix instances
  arm_mat_init_f32(&A, A_ROWS, A_COLS, A_DATA);
  arm_mat_init_f32(&B, B_ROWS, B_COLS, B_DATA);
  arm_mat_init_f32(&C, C_ROWS, C_COLS, C_DATA);

  arm_status status = arm_mat_mult_f32(&A, &B, &C);

  CuAssertIntEquals(tc, ARM_MATH_SUCCESS, status);

  float32_t rmse = RMSE((float32_t*)C_REF_DATA, C.pData, C_ROWS*C_COLS);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-7f);
}

/* Public functions ----------------------------------------------------------*/
CuSuite* CuGet_TestCmsisDsp_MAT_MULT_Suite(void)
{
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestCmsisDsp_MAT_MULT);
  return suite;
}

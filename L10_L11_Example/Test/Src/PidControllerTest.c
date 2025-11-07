/**
  ******************************************************************************
  * @file     : PidControllerTest.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Nov 6, 2025
  * @brief    : Unit test for CMSIS DSP PID controller function.
  *
  *             This file defines and verifies PID controller computation based
  *             on CMSIS DSP library routines. The test uses the CuTest framework
  *             for validation.
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

#include "PID1_pid.h"
#include "X3_vec.h"
#include "Y3_vec.h"
#include "Y3_REF_vec.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USE_SWV_PID 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if USE_SWV_PID
float32_t SWV_PID1;
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


void Test_CMSIS_DSP_PID(CuTest *tc)
{
  // Set PID controller gains
  PID1.Kp = PID1_KP;
  PID1.Ki = PID1_KI;
  PID1.Kd = PID1_KD;

  // Initialize PID controller instance */
  /** This function computes the structure fields: A0, A1 A2
   *  using the proportional gain (Kp), integral gain (Ki)
   *  and derivative gain (Kd); also sets the state variables to zeros.
   */
  arm_pid_init_f32(&PID1, 1);

  /* Generate control signal sample by sample */
  for(uint32_t i = 0; i < X3_LEN; i++)
  {
    Y3[i] = arm_pid_f32(&PID1, X3[i]);
    #if USE_SWV_PID
    SWV_PID1 = Y3[i];
    HAL_Delay(0);
    #endif
  }

  float32_t rmse = RMSE(Y3_REF, Y3, Y3_LEN);

  CuAssertDblEquals(tc, 0.0f, rmse, 1e-10f);
}

/* Public functions ----------------------------------------------------------*/
CuSuite* CuGet_Test_CMSIS_DSP_PID_Suite(void)
{
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_CMSIS_DSP_PID);
  return suite;
}

/* MATLAB GENERATED SOURCE FILE: ADC_LPF_fir.c */
#include "ADC_LPF_fir.h"
// Filter state
uint32_t ADC_LPF_STATE_UINT[ADC_LPF_NUM_TAPS+ADC_LPF_BLOCK_SIZE-1] = {
  #include "ADC_LPF_state_init.csv"
};
float32_t *ADC_LPF_STATE = (float32_t*)ADC_LPF_STATE_UINT;
// Filter coefficients
uint32_t ADC_LPF_COEFFS_UINT[ADC_LPF_NUM_TAPS] = {
  #include "ADC_LPF_coeffs.csv"
};
float32_t *ADC_LPF_COEFFS = (float32_t*)ADC_LPF_COEFFS_UINT;
// Filter instance
arm_fir_instance_f32 ADC_LPF;

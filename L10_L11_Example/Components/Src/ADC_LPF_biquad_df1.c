/* MATLAB GENERATED SOURCE FILE: ADC_LPF_biquad_df1.c */
#include "ADC_LPF_biquad_df1.h"
// Filter state
uint32_t ADC_LPF_STATE_UINT[4*ADC_LPF_NUM_STAGES] = {
  #include "ADC_LPF_state_init.csv"
};
float32_t *ADC_LPF_STATE = (float32_t*)ADC_LPF_STATE_UINT;
// Filter coefficients
uint32_t ADC_LPF_COEFFS_UINT[5*ADC_LPF_NUM_STAGES] = {
  #include "ADC_LPF_coeffs.csv"
};
float32_t *ADC_LPF_COEFFS = (float32_t*)ADC_LPF_COEFFS_UINT;
// Filter instance
arm_biquad_casd_df1_inst_f32 ADC_LPF;

/* MATLAB GENERATED  HEADER FILE: ADC_LPF_biquad_df1.h */
#ifndef INC_ADC_LPF_H_
#define INC_ADC_LPF_H_

#include "arm_math.h"

#define ADC_LPF_NUM_STAGES  2
#define ADC_LPF_BLOCK_SIZE  1
// Filter state
extern float32_t *ADC_LPF_STATE;
// Filter coefficients
extern float32_t *ADC_LPF_COEFFS;
// Filter instance
extern arm_biquad_casd_df1_inst_f32 ADC_LPF;
#endif // INC_ADC_LPF_H_

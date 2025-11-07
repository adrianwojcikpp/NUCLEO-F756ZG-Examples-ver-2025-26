/* MATLAB GENERATED  HEADER FILE: ADC_LPF_fir.h */
#ifndef INC_ADC_LPF_H_
#define INC_ADC_LPF_H_

#include "arm_math.h"

#define ADC_LPF_NUM_TAPS  58
#define ADC_LPF_BLOCK_SIZE  1
// Filter state
extern float32_t *ADC_LPF_STATE;
// Filter coefficients
extern float32_t *ADC_LPF_COEFFS;
// Filter instance
extern arm_fir_instance_f32 ADC_LPF;

#endif // INC_ADC_LPF_H_


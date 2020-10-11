#ifndef AT103_11_H
#define AT103_11_H


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>


#define ADC_VREF       (3.30)               // Reference Voltage
#define ADC_RESOL_BIT  (10)                 // ADC resolution (bit)
#define ADC_RESOLUTION (1 << ADC_RESOL_BIT) // ADC resloution
#define ADC_MAX_VALUE  (ADC_RESOLUTION-1)   // ADC MAX
#define ADC_MIN_VALUE  (0)                  // ADC MIN
#define ADC_3_3V_VALUE (2703)               // 5.0V

#define THERM_VREF             (3.30)      // 
#define THERM_103AT_B_PARAM    (3435.0)    // SEMITEC 103AT-11
#define THERM_KELVIN_OF_25DEGC (298.0)     // 
#define THERM_DEGC_OF_ABS_ZERO (-273.0)    // 


extern void convert_analog2degc(uint16_t* analog, double* temp_degc);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // AT103_11_H

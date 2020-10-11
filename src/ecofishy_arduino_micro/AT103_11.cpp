/*************************************************************************//**
 * @file AT103_11.c
 * @author typeR
 * @brief 
 * @version 0.1
 * @date 2020-01-19
 * 
 * @copyright Copyright (c) 2020
 * 
 ****************************************************************************/

#include "AT103_11.h"
#include <stdint.h>
#include <math.h>

/*************************************************************************//**
 * @brief 
 * 
 * @param analog 
 * @param temp_degc 
 ****************************************************************************/
void convert_analog2degc(uint16_t* analog, double* temp_degc)
{
    *temp_degc = (THERM_103AT_B_PARAM / (log((double)*analog / ((double)ADC_RESOLUTION - (double)*analog)) + 
                 (THERM_103AT_B_PARAM / THERM_KELVIN_OF_25DEGC))) + THERM_DEGC_OF_ABS_ZERO;
}

/*
 * input_analog.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_INPUT_ANALOG_H_
#define INC_INPUT_ANALOG_H_

#include "adc.h"

#define ADC_TO_VOLTAGE(value)   ((float)(value) * 3.3f / 4095.0f)

void currentMeasureInit(void);
void currentMeasure(uint16_t * buffer);
void currentMeasureVolt(float *voltages);
uint32_t get_I_measured(void);

#endif /* INC_INPUT_ANALOG_H_ */

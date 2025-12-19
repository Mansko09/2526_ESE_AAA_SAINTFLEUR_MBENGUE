/*
 * input_encoder.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_ACQUISITION_INPUT_ENCODER_H_
#define INC_ACQUISITION_INPUT_ENCODER_H_

#include "tim.h"

void EncoderCallback(void);
void init_encodeur(void);
float getOmega(void);

#endif /* INC_ACQUISITION_INPUT_ENCODER_H_ */

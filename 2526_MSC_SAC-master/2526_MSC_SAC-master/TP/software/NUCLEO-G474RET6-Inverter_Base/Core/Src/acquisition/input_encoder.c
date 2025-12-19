/*
 * input_encoder.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "acquisition/input_encoder.h"

#define ENCODER_RESOLUTION 8192.0f
#define M_PI 3.14159265358979323846f
#define TS 0.005f


volatile int32_t encoder_cnt_prev = 0;
volatile float omega_rad_s = 0.0f;

void init_encodeur(void){
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1|TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim4);
}

void EncoderCallback(void)
{

	int32_t encoder_cnt = (int32_t)__HAL_TIM_GET_COUNTER(&htim3);
	int32_t delta_cnt = encoder_cnt - encoder_cnt_prev;

	// Correction débordement compteur 16 bits
	if(delta_cnt > 32767) delta_cnt -= 65536;
	if(delta_cnt < -32768) delta_cnt += 65536;

	encoder_cnt_prev = encoder_cnt;

	// Calcul vitesse angulaire
	omega_rad_s = (2.0f * M_PI / ENCODER_RESOLUTION) * ((float)delta_cnt / TS);
}

float getOmega(void){
	return omega_rad_s;
}

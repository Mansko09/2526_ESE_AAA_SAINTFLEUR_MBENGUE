/*
 * analog_input.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "acquisition/input_analog.h"
#include <stdint.h>
#include "stm32g4xx_hal.h"
#include "tim.h"

/* Taille du buffer = nombre d'échantillons × nombre de canaux */
#define ADC_BUF_SIZE  2

static volatile uint16_t adc_buffer[ADC_BUF_SIZE];

static uint32_t Imes = 0;

void currentMeasureInit(void)
{
    HAL_TIM_Base_Start(&htim1);

    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, ADC_BUF_SIZE) != HAL_OK)
    {
        Error_Handler();
    }
}

uint32_t get_I_measured(void){
	return Imes;
}

void currentMeasureVolt(float *voltages)
{
    *voltages = ADC_TO_VOLTAGE(Imes);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
    	HAL_GPIO_TogglePin(ADC_Conv_toogle_GPIO_Port, ADC_Conv_toogle_Pin);
        // Exemple : moyenne pour réduire le bruit
        Imes =  adc_buffer[1];
    }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        // adc_buffer[0] disponible immédiatement (valley)
        // Utile si vous voulez traiter très vite
        Imes = adc_buffer[0];
    }
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        Error_Handler();  // Overrun ou autre erreur DMA
    }
}


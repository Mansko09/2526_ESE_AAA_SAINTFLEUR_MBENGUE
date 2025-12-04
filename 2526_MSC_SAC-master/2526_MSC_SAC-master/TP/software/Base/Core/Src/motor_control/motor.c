/*
 * motor.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "motor_control/motor.h"
#include "stdlib.h"

#define PWM_MAX 4250
#define RAMP_STEP 100
#define TIME_STEP 500

// Variables globales
static int16_t current_speed = PWM_MAX/2;
static int16_t target_speed = 0;

void motor_init(){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

int shellMotor(struct h_shell_struct* h_shell, int argc, char** argv){
	int size;

	if(argc==2){
		int16_t value=atoi(argv[1]);
		// Met à jour la consigne cible, mais ne bloque pas !
		target_speed = value;

		size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "Nouveau rapport cyclique : %d\r\n", value);
	}
	else{
		size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "%s : no such command\r\n", argv[0]);
	}
	h_shell->drv.transmit(h_shell->print_buffer, size);
	return 0;
}

// Fonction à appeler dans la boucle principale
void motor_update(void)
{
    if(current_speed < target_speed)
    {
        current_speed += RAMP_STEP;
        if(current_speed > target_speed) current_speed = target_speed;
    }
    else if(current_speed > target_speed)
    {
        current_speed -= RAMP_STEP;
        if(current_speed < target_speed) current_speed = target_speed;
    }

    // Applique la valeur actuelle sur le PWM
    int pwm_cmd = (uint16_t)(((current_speed ) * PWM_MAX) / 1000);
    setAlpha(pwm_cmd);
}

int setAlpha(int16_t in)
{
	/* Saturation */
	if (in > PWM_MAX) in = PWM_MAX;
	if (in < 0) in = 0;

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, in);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX - in);
	return (int)in;

}

int setMotor(int16_t target)
{

	/* Saturation */
		if (target > 1000) target = 1000;
		if (target < 0) target = 0;

		target_speed = target;
    /* Rampe progressive */
    if (current_speed < target_speed)
    	current_speed += RAMP_STEP;
    else if (current_speed > target_speed)
    	current_speed -= RAMP_STEP;

    /* Empêche overshoot */
    if (abs(target_speed - current_speed) < RAMP_STEP)
        current_speed = target_speed;

    /* Applique la valeur sur le PWM */
    int pwm = setAlpha(current_speed);

    /* Petite pause pour réguler la rampe */
    HAL_Delay(TIME_STEP);

    return pwm;
}

/*
 * Frein actif :
 * - les deux PWMs deviennent 0
 * - les deux sorties sont mises au même niveau
 * - arrêt instantané du moteur
 */

void setMotorBrake(void)
{
	/* On met toutes les PWM à 0 */
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

	/* Petit délai pour éviter cross-conduction */
	HAL_Delay(1);

	/*
	 * Selon les drivers :
	 * - Soit il faut mettre les deux sorties à LOW (frein bas)
	 * - Soit il faut mettre les deux sorties à HIGH (frein haut)
	 *
	 * Sur IHM16M1 → frein LOW suffit
	 * (TIM inactive PWM = sortie maintenue LOW)
	 */
}

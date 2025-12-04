/*
 * motor.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_MOTOR_CONTROL_MOTOR_H_
#define INC_MOTOR_CONTROL_MOTOR_H_

#include <stdint.h>
#include "user_interface/shell.h"
#include "tim.h"
#include <stdio.h>


int setAlpha(int16_t pwm);
int setMotor(int16_t value);
int shellMotor(struct h_shell_struct* h_shell, int argc, char** argv);
void setMotorBrake(void);
void motor_init();
void motor_update(void);
#endif /* INC_MOTOR_CONTROL_MOTOR_H_ */

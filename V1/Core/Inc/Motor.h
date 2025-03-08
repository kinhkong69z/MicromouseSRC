/*
 * Motor.h
 *
 *  Created on: Feb 28, 2025
 *      Author: kinhz
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "Sensor.h"
#include "Timer.h"


#define L_PWM_F TIM1->CCR4
#define L_PWM_R TIM1->CCR3
#define R_PWM_F TIM1->CCR2
#define R_PWM_R TIM1->CCR1
#define WALL_L 2400
#define WALL_R 2000
#define WALL_FR 1200
#define WALL_FL 1700
#define bias 0.5
#define PULSE_TURN 840
#define PULSE_MM 0.0763

extern float SpeedL;
extern float SpeedR;
extern float xErrorLR;
extern float wErrorLR;
extern float leftEncoder5ms;
extern float rightEncoder5ms;

void R_Motor();
void L_Motor();
void Stop();
void Turn_L();
void Turn_R();
void Backward();
void Forward();
void SpeedStatus();
#endif /* INC_MOTOR_H_ */

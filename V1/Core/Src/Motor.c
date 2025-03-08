/*
 * Motor.c
 *
 *  Created on: Feb 28, 2025
 *      Author: kinhz
 */
#include "Motor.h"


float SpeedL = 0;
float SpeedR = 0;
float leftEncoder5ms = 0;
float rightEncoder5ms = 0;
float xErrorLR;
float wErrorLR;

void R_Motor()
{

}

void L_Motor()
{

}

void Stop()
{
	HAL_Delay(200);
	L_PWM_F = 0;
	L_PWM_R = 0;
	R_PWM_F = 0;
	R_PWM_R = 0;
}


void Forward()
{

}
void Backward()
{

	L_PWM_F = 0;
	L_PWM_R = 800;
	R_PWM_F = 0;
	R_PWM_R = 800;
	HAL_Delay(400);
	Stop();
}
void Turn_R()
{

}
void Turn_L()
{

}
void SpeedStatus()
{
	leftEncoder5ms += leftEncoderchange;
	rightEncoder5ms += rightEncoderchange;
	if(Millis - oldTime >= 200){
		SpeedL = leftEncoder5ms * PULSE_MM * 5;
		SpeedR = rightEncoder5ms * PULSE_MM * 5;
		oldTime = Millis;
		leftEncoder5ms = 0;
		rightEncoder5ms = 0;
	}
	xErrorLR = (SpeedL + SpeedR) / 2;
	wErrorLR = SpeedR - SpeedL;
}


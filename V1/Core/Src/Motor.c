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
float accX = 160; // mm/s/s
float decX = 160;
float accW;
float decW;
float curSpeedX;
float curSpeedW;
int PWM_L;
int PWM_R;

void R_Motor()
{

}

void L_Motor()
{

}

void Stop()
{
//	HAL_Delay(200);
	L_PWM_F = 0;
	L_PWM_R = 0;
	R_PWM_F = 0;
	R_PWM_R = 0;
}


void Forward()
{
	L_PWM_F = PWM_L;
	L_PWM_R = 0;
	R_PWM_F = PWM_R;
	R_PWM_R = 0;
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
	delay_us(20);
	resetEN();
	while((2 * en_value1) <= PULSE_TURN)
	{
		L_PWM_F = (PULSE_TURN - en_value1) * 4;
		R_PWM_R = (PULSE_TURN - (65535 - en_value2)) * 4;
	}
}
void Turn_L()
{

}
void SpeedStatus()
{
	leftEncoder5ms += leftEncoderchange;
	rightEncoder5ms += rightEncoderchange;
	if(Millis - oldTime >= 100){
		SpeedL = leftEncoder5ms * PULSE_MM * 10;
		SpeedR = rightEncoder5ms * PULSE_MM * 10;
		oldTime = Millis;
		leftEncoder5ms = 0;
		rightEncoder5ms = 0;
	}
	curSpeedX = (SpeedL + SpeedR) / 2;
	wErrorLR = SpeedR - SpeedL;
}
int counts_to_mm(float count)
{
	return count * PULSE_MM;
}
void updateSpeed()
{
	PID();
	PWM_L = 650 + (int)wPID;
	PWM_R = 635 - (int)wPID;

}

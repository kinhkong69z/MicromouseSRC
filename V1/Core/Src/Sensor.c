/*
 * Sensor.c
 *
 *  Created on: Feb 26, 2025
 *      Author: kinhz
 */
//front left : 3
//left: 2
//right: 1
//front right: 0
#include "Sensor.h"

float IR_FL;
float IR_FR;
float IR_LL;
float IR_RR;
uint32_t en_value1;
uint32_t en_value2;
uint32_t ADC_VAL[4];
int32_t leftEncoderchange;
int32_t rightEncoderchange;
int32_t encoderChange;
int32_t leftEncodercount;
int32_t rightEncodercount;
int32_t encoderCount;
int32_t distanceLeft;
int32_t leftEncoderOld;
int32_t rightEncoderOld;

void resetIR()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
}
void resetEN()
{
	HAL_Delay(100);
	en_value1 = 0;
	en_value2 = 0;
	TIM2->CNT = 0;
	TIM3->CNT = 0;
}
void EncoderStatus()
{
	en_value1 = (TIM2->CNT);
	en_value2 = (TIM3->CNT);
	if(en_value1 > leftEncoderOld) {leftEncoderchange = en_value1 - leftEncoderOld;}
	else {leftEncoderchange = -en_value1 + leftEncoderOld;}
	if(en_value2 > rightEncoderOld) {rightEncoderchange = en_value2 - rightEncoderOld;}
	else {rightEncoderchange = -en_value2 + rightEncoderOld;}

	encoderChange = (leftEncoderchange + rightEncoderchange) / 2;

	leftEncodercount += leftEncoderchange;
	rightEncodercount += rightEncoderchange;
	encoderCount = (leftEncodercount + rightEncodercount) / 2;

	distanceLeft -= encoderCount;
	leftEncoderOld = TIM2->CNT;
	rightEncoderOld = TIM3->CNT;
}

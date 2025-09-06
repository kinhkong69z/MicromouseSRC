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

int32_t IR_FL = 0;
int32_t IR_FR = 0;
int32_t IR_LL = 0;
int32_t IR_RR = 0;
int32_t IR_FL_raw = 0;
int32_t IR_FR_raw = 0;
int32_t IR_LL_raw = 0;
int32_t IR_RR_raw = 0;
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
int32_t sum = 0;
float IR_data[4];

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
	leftEncoderchange = 0;
	rightEncoderchange = 0;
	encoderChange = 0;
	leftEncodercount = 0;
	rightEncodercount = 0;
	encoderCount = 0;
	distanceLeft = 0;
	leftEncoderOld = 0;
	rightEncoderOld = 0;
}
void EncoderStatus()
{
	en_value1 = (TIM2->CNT);
	en_value2 = (TIM3->CNT);
	if(en_value1 >= leftEncoderOld) {leftEncoderchange = en_value1 - leftEncoderOld;}
	else {leftEncoderchange = en_value1;}
	if(en_value2 >= rightEncoderOld) {rightEncoderchange = en_value2 - rightEncoderOld;}
	else {rightEncoderchange = en_value2;}
	encoderChange = (leftEncoderchange + rightEncoderchange) / 2;

	//	leftEncodercount = leftEncoderchange;
	//	rightEncodercount = rightEncoderchange;
	encoderCount += (leftEncoderchange + rightEncoderchange) ;

	distanceLeft -= encoderChange;
	leftEncoderOld = TIM2->CNT;
	rightEncoderOld = TIM3->CNT;
}
void SensorStatus()
{
	if(IR_data[1] >= 100 && IR_data[2] < 100)
		wall_error = WALL_L - IR_data[2];
	else if(IR_data[2] >= 100 & IR_data[1] < 100)
		wall_error = IR_data[1] - WALL_R;
	else
		wall_error = 0;
}
void getIR()
{
	L_EM_OFF;
	R_EM_OFF;
	LF_EM_OFF;
	RF_EM_OFF;
	//	IR_FL = 0;
	//	IR_FR = 0;
	//	IR_LL = 0;
	//	IR_RR = 0;
	//	IR_FL_raw = 0;
	//	IR_FR_raw = 0;
	//	IR_LL_raw = 0;
	//	IR_RR_raw = 0;


	//Get IR front right
	sum = 0;
	for(int i = 0; i < 20; i++)
	{
		IR_FR_raw += ADC_VAL[0];
	}
	IR_FR_raw = IR_FR_raw / 20;
	RF_EM_ON;
	delay_s(1);
	sum = 0;
	for(int i = 0; i < 20; i++)
	{
		IR_FR += ADC_VAL[0];
	}

	IR_FR = IR_FR / 20;
	IR_FR = IR_FR - IR_FR_raw;

	if(IR_FR < 180) IR_data[0] = 200;
	else IR_data[0] = (1255.1 / (log10(IR_FR + 118.9))) - 329;
	RF_EM_OFF;
	if(IR_data[0] > 200) IR_data[0] = 200;
	delay_s(1);

	//Get IR front left
	for(int i = 0; i < 20; i++)
	{
		IR_FL_raw += ADC_VAL[0];
	}
	IR_FL_raw = IR_FL_raw / 20;
	LF_EM_ON;
	delay_s(1);
	for(int i = 0; i < 20; i++)
	{
		IR_FL += ADC_VAL[3];
	}

	IR_FL = IR_FL / 20;
	LF_EM_OFF;
	IR_FL -= IR_FL_raw;

	if(IR_FL < 150) IR_data[0] = 200;
	else IR_data[3] = (1338.7 / (log10(IR_FL + 116.5))) - 350.9;
	if(IR_data[3] > 200) IR_data[3] = 200;
	delay_s(1);

	//Get IR right
	for(int i = 0; i < 20; i++)
	{
		IR_RR_raw += ADC_VAL[1];
	}
	IR_RR_raw = IR_RR_raw / 20;
	R_EM_ON;
	delay_s(1);
	for(int i = 0; i < 20; i++)
	{
		IR_RR += ADC_VAL[1];
	}

	IR_RR = IR_RR / 20;
	R_EM_OFF;
	IR_RR -= IR_RR_raw;

	if(IR_RR < 180) IR_data[1] = 200;
	else IR_data[1] = (534.3 / (log10(IR_RR - 186.5))) - 139.2;
	if(IR_data[1] > 200) IR_data[1] = 200;
	delay_s(1);


	//Get IR left
	for(int i = 0; i < 20; i++)
	{
		IR_LL_raw += ADC_VAL[2];
	}
	IR_LL_raw = IR_LL_raw / 20;
	L_EM_ON;
	delay_s(1);
	for(int i = 0; i < 20; i++)
	{
		IR_LL += ADC_VAL[2];
	}

	IR_LL = IR_LL / 20;
	L_EM_OFF;
	IR_LL -= IR_LL_raw;

	if(IR_LL < 280) IR_data[2] = 200;
	else IR_data[2] = (1050 / (log10(IR_LL - 269.3))) - 273.7;
	if(IR_data[2] > 200) IR_data[2] = 200;
	delay_s(1);

	SensorStatus();
}

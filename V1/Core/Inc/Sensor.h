/*
 * Sensor.h
 *
 *  Created on: Feb 26, 2025
 *      Author: kinhz
 */
//1 vong 360 xung
#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "main.h"
#include "stm32f1xx_hal.h"

#define LF_EM_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#define L_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
#define R_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
#define RF_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

#define LF_EM_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
#define L_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
#define R_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
#define RF_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

extern float IR_FL;
extern float IR_FR;
extern float IR_LL;
extern float IR_RR;

extern uint32_t ADC_VAL[4];
extern uint32_t en_value1;
extern uint32_t en_value2;
extern int32_t leftEncoderchange;
extern int32_t rightEncoderchange;
extern int32_t encoderChange;
extern int32_t leftEncodercount;
extern int32_t rightEncodercount;
extern int32_t encoderCount;
extern int32_t distanceLeft;
extern int32_t leftEncoderOld;
extern int32_t rightEncoderOld;
//void readIR();
void resetIR(void);
void resetEN(void);
void EncoderStatus(void);
#endif /* INC_SENSOR_H_ */

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

#define LF_EM_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#define L_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
#define R_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
#define RF_EM_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

#define LF_EM_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
#define L_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
#define R_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
#define RF_EM_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

extern int16_t debug_sensor;
extern float alpha;

extern int32_t WALL_L;
extern int32_t WALL_R;
extern int32_t WALL_FR;
extern int32_t WALL_FL;

extern float IR_FL;
extern float IR_FR;
extern float IR_LL;
extern float IR_RR;

extern uint16_t IR_data[4];
extern uint8_t completeADC;
//void readIR();

typedef struct {
	ADC_HandleTypeDef *ADCx;
	uint8_t prev_ir_state_left;
	uint8_t prev_ir_state_right;
	uint8_t ir_state_left;
	uint8_t ir_state_right;
} IR_SENSOR;

void IR_init(ADC_HandleTypeDef *ADCx);
void read_ir_adc();
void ir_calibration();
int16_t wall_calibration();
void wall_front_calibration();

extern IR_SENSOR IR_sensor;

#endif /* INC_SENSOR_H_ */

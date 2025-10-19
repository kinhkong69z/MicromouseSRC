/*
 * Mode.c
 *
 *  Created on: Oct 2, 2025
 *      Author: kinhz
 */

#include "Mode.h"

uint16_t SPEED = 200;
uint8_t BTN_STATE1 = 0;
uint8_t BTN_STATE2 = 0;

void mode() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
	while(BTN_STATE1 < 1) {
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) {
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			wall_front_calibration();
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		}
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) {
			BTN_STATE1 = 1;
		}
	}
	delay_ms(2000);
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

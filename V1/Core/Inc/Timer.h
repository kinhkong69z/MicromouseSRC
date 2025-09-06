/*
 * Timer.h
 *
 *  Created on: Mar 5, 2025
 *      Author: kinhz
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "Sensor.h"

extern uint32_t Millis;
extern uint32_t oldTime;
extern uint32_t Millis2;

void delay_s(int32_t time);
void delay_us(int32_t time);

#endif /* INC_TIMER_H_ */

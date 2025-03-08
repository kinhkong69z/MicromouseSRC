/*
 * PID.h
 *
 *  Created on: Mar 7, 2025
 *      Author: kinhz
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "Sensor.h"
#include "Timer.h"

extern float xKp;
extern float xKd;
extern float wKp;
extern float wKd;

void PID_x();
void PID_w();
#endif /* INC_PID_H_ */

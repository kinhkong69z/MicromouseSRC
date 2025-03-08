/*
 * Timer.c
 *
 *  Created on: Mar 5, 2025
 *      Author: kinhz
 */

#include "Timer.h"

uint32_t Millis = 0;
uint32_t oldTime = 0;

void delay_s(int32_t time)
{
	Millis = 0;
	while(Millis < time){}
}

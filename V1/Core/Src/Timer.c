/*
 * Timer.c
 *
 *  Created on: Mar 5, 2025
 *      Author: kinhz
 */

#include "Timer.h"

uint32_t Millis = 0;
uint32_t oldTime = 0;
uint32_t Millis2 = 0;

void delay_s(int32_t time)
{
	Millis2 = 0;
	while(Millis2 < time){}
}

void delay_us(int32_t time)
{
	for(int i = 0; i < time; i++)
	{
		for(int j = 0; j < 64; j++){}
	}
}

/*
 * PID.c
 *
 *  Created on: Mar 7, 2025
 *      Author: kinhz
 */

#include "PID.h"

float xKp;
float xKd;
float wKp = 1.06;
float wKd = 0.9;
float wPID;
float oldErrorW = 0;
float wall_error = 0;
float Kp_wall = 2;

void PID()
{
	wPID = wErrorLR * wKp + (wErrorLR - oldErrorW) * wKd;
	wPID += wall_error * Kp_wall;
	oldErrorW = wErrorLR;

}


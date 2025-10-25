/*
 * Speed_profile.h
 *
 *  Created on: Oct 22, 2025
 *      Author: kinhz
 */

#ifndef INC_CALCULATION_H_
#define INC_CALCULATION_H_

#include "main.h"

#define perimeter 276.46
#define onecell 180

extern float SPEED_MAX;
extern float _SPEED;
extern float ACC;
extern float PREV_SPEED;
extern float OMEGA;
extern uint16_t cnt_cell;

void update_speed(uint32_t dt, uint8_t state);
float mm_to_cnt(float distance);
uint8_t check_state();
float cnt_to_omega(uint32_t cnt_left, uint32_t cnt_right);
float cnt_to_mm(uint32_t cnt);
void mouse_correction();

#endif /* INC_CALCULATION_H_ */

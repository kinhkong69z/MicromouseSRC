/*
 * Speed_profile.c
 *
 *  Created on: Oct 22, 2025
 *      Author: kinhz
 */

#include <Calculation.h>

float SPEED_MAX = 200; // mm/s
float _SPEED = 0;
float ACC = 1500; // mm/s/s
float PREV_SPEED = 0;
float OMEGA = 0;
uint16_t cnt_cell = 0;

void update_speed(uint32_t dt, uint8_t state) {
	if (state == 1) {
		_SPEED = ACC * dt / 1000000 + PREV_SPEED;
		if(_SPEED >= SPEED_MAX) _SPEED = SPEED_MAX;
		PREV_SPEED = _SPEED;
	}
	else if(state == 0){
		_SPEED = - ACC * dt / 1000000 + PREV_SPEED;
		if(_SPEED <= 0) _SPEED = 0;
		PREV_SPEED = _SPEED;
	}
}

uint8_t check_state() {
	if (get(&mouse_state, mouse_state.index + 1) == 1) {
		return 1;
	}
	else {
		if (mm_to_cnt(180) - encoder_cnt_left >= mm_to_cnt(20)) {
			return 0;
		}
		return 1;
	}
}

float cnt_to_omega(uint32_t cnt_left, uint32_t cnt_right) {
	uint32_t cnt_delta = cnt_left - cnt_right;
	return (cnt_delta / mm_to_cnt(perimeter) * 360);
}

float mm_to_cnt(float distance) {
	return distance * 815 / 106.81;
}

float cnt_to_mm(uint32_t cnt) {
	return cnt * 106.81 / 815;
}


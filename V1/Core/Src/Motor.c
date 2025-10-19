/*
 * Motor.c
 *
 *  Created on: Feb 28, 2025
 *      Author: kinhz
 */

#include "Motor.h"

Motor motor_left;
Motor motor_right;

uint8_t mouse_state = 0;
uint32_t prev_time_pid_forward = 0;
uint32_t prev_time_pid_rotation = 0;
int32_t debug_pwm = 0;

void Motor_Init(Motor *motor, TIM_HandleTypeDef *tim1, TIM_HandleTypeDef *tim2,
		uint16_t channel1, uint16_t channel2) {
	motor->M_TIM1 = tim1;
	motor->M_TIM2 = tim2;
	motor->m_channel1 = channel1;
	motor->m_channel2 = channel2;

	HAL_TIM_PWM_Start(tim1, channel1);
	HAL_TIM_PWM_Start(tim2, channel2);
}

void Set_Motor_speed(Motor *motor, int16_t speed) {
	if (speed > 0) {
		__HAL_TIM_SET_COMPARE(motor->M_TIM1, motor->m_channel1, 0);
		__HAL_TIM_SET_COMPARE(motor->M_TIM2, motor->m_channel2, speed);
	} else {
		__HAL_TIM_SET_COMPARE(motor->M_TIM1, motor->m_channel1, -speed);
		__HAL_TIM_SET_COMPARE(motor->M_TIM2, motor->m_channel2, 0);
	}
}

void Move_forward(float distance, float speed) { // distance in cm ,speed in mm/s
//	int16_t count = 0;
	reset_en();
//	if(mouse_state == 1) {
//		count = (COUNT90 + encoder_cnt_left) + (COUNT90 - encoder_cnt_right);
//		reset_en();
//		encoder_cnt_right += count;
//	}
//
//	else if(mouse_state == 2) {
//		count = (COUNT90 - encoder_cnt_left) + (COUNT90 + encoder_cnt_right);
//		reset_en();
//		encoder_cnt_left += count;
//	}
//	else {
//		reset_en();
//	}
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);
//	for(int i = 0; i < count; i ++ )
//	{
//		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//		delay_ms(1000);
//	}

	speed = (speed * 815) / 108;
	distance = (distance * 10) * 815 / 108;
	prev_time_pid_forward = Millis;
	prev_time_pid_rotation = Millis;
	read_ir_adc();
//	uint32_t curt = Micros;
	PID_reset(&pid_steering);
	PID_reset(&pid_wall_stable);
	PID_reset(&pid_forward_right);
	PID_reset(&pid_forward_left);
	while (((distance > encoder_cnt_left) || (distance > encoder_cnt_right))
			&& ((IR_FL < WALL_FL) || (IR_FR < WALL_FR))) {

		int16_t left_pwm = PID_calc(&pid_forward_left, speed, speed_left,
				Millis - prev_time_pid_forward);
//		debug_pid ++;
		int16_t right_pwm = PID_calc(&pid_forward_right, speed, speed_right,
				Millis - prev_time_pid_forward);
		prev_time_pid_forward = Millis;
		int16_t error_steering = PID_calc(&pid_steering, 0,
				encoder_cnt_left - encoder_cnt_right,
				Millis - prev_time_pid_rotation);
		int16_t error_wall = PID_calc(&pid_wall_stable, 0, wall_calibration(),
				Millis - prev_time_pid_rotation);
		debug_pid = error_wall;
		prev_time_pid_rotation = Millis;
//		error_wall = 0;
		left_pwm += error_steering + error_wall;
		right_pwm += -error_steering - error_wall;

		if (left_pwm > 10000)
			left_pwm = 10000;
		if (left_pwm < 0)
			left_pwm = 0;
		if (right_pwm > 10000)
			right_pwm = 10000;
		if (right_pwm < 0)
			right_pwm = 0;

		Set_Motor_speed(&motor_left, left_pwm);
		Set_Motor_speed(&motor_right, right_pwm);

//		elapseMillis(1000, curt);
//		curt = Micros;

		delay_ms(1);
//		read_ir_adc();
	}
	mouse_state = 0;
	Motor_stop();
}

void Turn_left90() {
	angle = 0;
	uint32_t prev_time = micros();
	uint32_t curt = Millis;
	PID_reset(&pid_forward_right);
	PID_reset(&pid_forward_left);
	while (fabs(80 - angle) > 4) {
		MPU6050_getAngle(MPU6050.I2Cx, micros() - prev_time);

		int16_t pwm_target = 25 * (80 - angle);
		int16_t left_pwm = PID_calc(&pid_forward_left, -pwm_target, speed_left,
				micros() - prev_time);
		int16_t right_pwm = PID_calc(&pid_forward_right, pwm_target, speed_right,
				micros() - prev_time);
		prev_time = micros();
		Set_Motor_speed(&motor_left, left_pwm);
		Set_Motor_speed(&motor_right, right_pwm);

		elapseMillis(2, curt);
		curt = Millis;
	}
	printf("%f\n", angle);
	Motor_stop();
//	delay_ms(20);
	mouse_state = 1;
}

void Turn_right90() {
	angle = 0;

	reset_en();
	uint32_t prev_time = micros();
//	uint32_t prev_time_check = Millis;
	uint32_t curt = Millis;
	PID_reset(&pid_forward_right);
	PID_reset(&pid_forward_left);
	while (fabs(80 + angle) > 4) {
		MPU6050_getAngle(MPU6050.I2Cx, micros() - prev_time);

		int16_t pwm_target = 25 * (80 + angle);
		int16_t left_pwm = PID_calc(&pid_forward_left, pwm_target, speed_left,
				micros() - prev_time);
		int16_t right_pwm = PID_calc(&pid_forward_right, -pwm_target, speed_right,
				micros() - prev_time);
		prev_time = micros();
		Set_Motor_speed(&motor_left, left_pwm);
		Set_Motor_speed(&motor_right, right_pwm);

		elapseMillis(2, curt);
		curt = Millis;
	}
	Motor_stop();
//	delay_ms(20);
	printf("%f\n", angle);
	mouse_state = 2;
}

void Motor_stop() {
	Set_Motor_speed(&motor_right, 0);
	Set_Motor_speed(&motor_left, 0);
}

void Adjuster() {
	int curt = Millis; //start to track time in order to make one adjust every 1000us
	read_ir_adc();
	Set_Motor_speed(&motor_left, (WALL_FL - IR_FL) * 10); //set left motor speed
	Set_Motor_speed(&motor_right, (WALL_FR - IR_FR) * 10); //set right motor speed
	elapseMicros(1, curt); //elapse 1000 micro seconds
}

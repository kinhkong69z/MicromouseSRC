#include "Sensor.h"

IR_SENSOR IR_sensor;

int16_t debug_sensor;
float alpha = 0.1;

int32_t WALL_L = 0;
int32_t WALL_R = 0;
int32_t WALL_FR = 0;
int32_t WALL_FL = 0;

float IR_FL = 0;
float IR_FR = 0;
float IR_LL = 0;
float IR_RR = 0;

uint16_t IR_data[4];
uint8_t completeADC = 0;

void IR_init(ADC_HandleTypeDef *ADCx) {
	IR_sensor.ADCx = ADCx;
	IR_sensor.prev_ir_state_left = 1;
	IR_sensor.prev_ir_state_right = 1;
	IR_sensor.ir_state_left = 1;
	IR_sensor.ir_state_right = 1;
	HAL_ADC_Start_DMA(IR_sensor.ADCx, (uint32_t*) IR_data, 4);
	RF_EM_ON;
	LF_EM_ON;
	L_EM_ON;
	R_EM_ON;
}

void read_ir_adc() {
	if(completeADC == 0) {
		uint32_t curt = Micros;
		RF_EM_ON;
		IR_FR = (float) IR_data[0] * alpha + (float) (1 - alpha) * IR_FR;
		elapseMicros(100, curt);
		RF_EM_OFF;
		elapseMicros(160,curt);

		LF_EM_ON;
		IR_FL = (float) IR_data[3] * alpha + (float) (1 - alpha) * IR_FL;
		elapseMicros(240,curt);
		LF_EM_OFF;
		elapseMicros(320,curt);

		L_EM_ON;
		R_EM_ON;
		IR_RR = (float) IR_data[1] * alpha + (float) (1 - alpha) * IR_RR;
		IR_LL = (float) IR_data[2] * alpha + (float) (1 - alpha) * IR_LL;
		elapseMicros(400,curt);
		L_EM_OFF;
		R_EM_OFF;
		elapseMicros(480, curt);

	}
	else {
		completeADC = 0;
		HAL_ADC_Start_DMA(IR_sensor.ADCx,(uint32_t*) IR_data, 4);
	}
//	delay_us(300);
}

void ir_calibration() {
	for (int i = 0; i < 4000; i++) {
		read_ir_adc();
		WALL_L += IR_LL;
		WALL_R += IR_RR;
	}
	WALL_L /= 4000;
	WALL_R /= 4000;
	IR_sensor.prev_ir_state_left = WALL_L;
	IR_sensor.prev_ir_state_right = WALL_R;
}

void wall_front_calibration() {
	for (int i = 0; i < 4000; i++) {
		read_ir_adc();
		WALL_FL += IR_FL;
		WALL_FR += IR_FR;
	}
	WALL_FL /= 4000;
	WALL_FR /= 4000;

}

int16_t wall_calibration() {
	read_ir_adc();
	int16_t error;
//	if (encoder_cnt_left - prev_distance >= COUNT18cm) {
//		prev_distance = encoder_cnt_left;
//		if (IR_RR < WALL_R - 50) {
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//			IR_sensor.ir_state_right = 0;
//		} else {
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//			IR_sensor.ir_state_right = 1;
//		}
//		if (IR_LL < WALL_L - 50) {
//			IR_sensor.ir_state_left = 0;
//		} else {
//			IR_sensor.ir_state_left = 1;
//		}
//	}
	/*
	 * When WALL_R - IR_RR > 0 that mean you want to go right mean that when set
	 * pwm you want - pwm_right and + pwm_left
	 *
	 * When WALL_L - IR_LL > 0 that mean go to left then set pwm + pwm right and - pwm left
	 *
	 * When IR_LL - IR_RR > 0 then go right. Set pwm + pwm_left and - pwm_right

	 */

	if (IR_LL > WALL_L && IR_RR < WALL_R) {
		error = WALL_L - IR_LL;
	}
	else if(IR_LL < WALL_L && IR_RR > WALL_R) {
		error = IR_RR - WALL_R;
	}
	else
		error = 0;
	return error;
}

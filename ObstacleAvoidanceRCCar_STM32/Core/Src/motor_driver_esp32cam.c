/*
 * motor_driver.c
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#include "motor_driver_esp32cam.h"

#define LEFT(n) m_htim->Instance->CCR1 = n * 10 - 1
#define RIGHT(n) m_htim->Instance->CCR2 = n * 10 - 1

static TIM_HandleTypeDef *m_htim;

uint8_t cur_dir = 'h'; // w = forward, s = back, a = turn_left, d = turn_right, h = halt
uint8_t cur_fl = 'F';  // ESP32-CAM FlashLight status
uint8_t cur_slp = 'F';  // ESP32-CAM Deep Sleep status

void motor_init(TIM_HandleTypeDef *htim) {
	m_htim = htim;
	drive(cur_dir);
}

void drive(uint8_t dir) {
	switch (dir) {
	case 'w':
		if (cur_dir == 's' || cur_dir == 'z' || cur_dir == 'c') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'w';
			forward();
		}
		break;

	case 's':
		if (cur_dir == 'w' || cur_dir == 'q' || cur_dir == 'e') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 's';
			backward();
		}
		break;

	case 'a':
		if (cur_dir == 'd') {
			cur_dir = 'h';
			stop();
		} else if (cur_dir == 'w') {
			cur_dir = 'q';
			forward_left();
		} else if (cur_dir == 's') {
			cur_dir = 'z';
			backward_left();
		} else {
			cur_dir = 'a';
			turn_left();
		}
		break;

	case 'd':
		if (cur_dir == 'a') {
			cur_dir = 'h';
			stop();
		} else if (cur_dir == 'w') {
			cur_dir = 'e';
			forward_right();
		} else if (cur_dir == 's') {
			cur_dir = 'c';
			backward_right();
		} else {
			cur_dir = 'd';
			turn_right();
		}
		break;

	case 'q':
		if (cur_dir == 's' || cur_dir == 'z' || cur_dir == 'c') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'q';
			forward_left();
		}
		break;

	case 'e':
		if (cur_dir == 's' || cur_dir == 'z' || cur_dir == 'c') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'e';
			forward_right();
		}
		break;

	case 'z':
		if (cur_dir == 'w' || cur_dir == 'q' || cur_dir == 'e') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'z';
			backward_left();
		}
		break;

	case 'c':
		if (cur_dir == 'w' || cur_dir == 'q' || cur_dir == 'e') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'c';
			backward_right();
		}
		break;

	case 'f':
		if (HAL_GPIO_ReadPin(PC0_ESP32_FL_GPIO_Port, PC0_ESP32_FL_Pin) == 0) {
			HAL_GPIO_WritePin(PC0_ESP32_FL_GPIO_Port, PC0_ESP32_FL_Pin, 1);
			cur_fl = 'T';
		} else {
			HAL_GPIO_WritePin(PC0_ESP32_FL_GPIO_Port, PC0_ESP32_FL_Pin, 0);
			cur_fl = 'F';
		}
		break;

	case 'p':
		if (cur_slp == 'F') {
			HAL_GPIO_WritePin(PC1_ESP32_SLP_GPIO_Port, PC1_ESP32_SLP_Pin, 1);
			HAL_Delay(1);
			HAL_GPIO_WritePin(PC1_ESP32_SLP_GPIO_Port, PC1_ESP32_SLP_Pin, 0);
			cur_slp = 'T';
		} else {
			HAL_GPIO_WritePin(PC2_ESP32_INT_GPIO_Port, PC2_ESP32_INT_Pin, 1);
			HAL_Delay(1);
			HAL_GPIO_WritePin(PC2_ESP32_INT_GPIO_Port, PC2_ESP32_INT_Pin, 0);
			cur_slp = 'F';
		}
		break;

	default:
		cur_dir = 'h';
		stop();
	}
}

void forward(void) {  // 'w'
	LEFT(35);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void backward(void) {  // 's'
	LEFT(35);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void turn_left(void) {  // 'a'
	LEFT(35);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void turn_right(void) {  // 'd'
	LEFT(35);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void forward_left(void) {  // 'q'
	LEFT(30);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void forward_right(void) {  // 'e'
	LEFT(35);
	RIGHT(30);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void backward_left(void) {  // 'z'
	LEFT(30);
	RIGHT(35);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void backward_right(void) {  // 'c'
	LEFT(35);
	RIGHT(30);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void stop(void) {  // 'h'
	LEFT(0);
	RIGHT(0);
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

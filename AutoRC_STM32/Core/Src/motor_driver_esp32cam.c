/*
 * motor_driver.c
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#include "motor_driver_esp32cam.h"

#define DUTY(n) n*10-1

static TIM_HandleTypeDef *m_htim;

uint8_t cur_dir = 'h'; // w = forward, s = back, a = turn_left, d = turn_right, h = halt
uint8_t cur_fl = 'F';  // ESP32-CAM FlashLight status
uint8_t cur_slp = 'F';  // ESP32-CAM Deep Sleep status

void motor_init(TIM_HandleTypeDef *htim) {
	m_htim = htim;
	drive(cur_dir);
}

void drive(uint8_t dir) {
	m_htim->Instance->CCR1 = DUTY(100); // left motor duty = 100%
	m_htim->Instance->CCR2 = DUTY(100); // right motor duty = 100%
	switch (dir) {
	case 'w':
		if (cur_dir == 's') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'w';
			forward();
		}
		break;

	case 's':
		if (cur_dir == 'w') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 's';
			back();
		}
		break;

	case 'a':
		if (cur_dir == 'd') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'a';
			turn_left();
		}
		break;

	case 'd':
		if (cur_dir == 'a') {
			cur_dir = 'h';
			stop();
		} else {
			cur_dir = 'd';
			turn_right();
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
		break;
	}
}

void forward(void) {
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void back(void) {
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void turn_left(void) {
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 0);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 0);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

void turn_right(void) {
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 0);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 0);
}

void stop(void) {
	m_htim->Instance->CCR1 = 0; // left motor duty = 0%
	m_htim->Instance->CCR2 = 0; // right motor duty = 0%
	HAL_GPIO_WritePin(PB5_MTR_IND_GPIO_Port, PB5_MTR_IND_Pin, 1);
	HAL_GPIO_WritePin(PB4_MTR_INC_GPIO_Port, PB4_MTR_INC_Pin, 1);
	HAL_GPIO_WritePin(PA8_MTR_INA_GPIO_Port, PA8_MTR_INA_Pin, 1);
	HAL_GPIO_WritePin(PB10_MTR_INB_GPIO_Port, PB10_MTR_INB_Pin, 1);
}

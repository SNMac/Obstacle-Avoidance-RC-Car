/*
 * ultrasonic_sensor.c
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#include "ultrasonic_sensor.h"

#define DIST_CALC(diff) diff*0.034/2  // diff * (34000cm / 1000000us) / 2 (Diff's unit is microsecond)
// Divide the round trip distance by 2 to calculate the one-way distance

static TIM_HandleTypeDef *m_htim;

uint32_t L_IC_Val[2] = { 0, };
uint32_t C_IC_Val[2] = { 0, };
uint32_t R_IC_Val[2] = { 0, };
uint32_t L_Diff = 0;
uint32_t C_Diff = 0;
uint32_t R_Diff = 0;
bool L_Is_First_Captured = 0;
bool C_Is_First_Captured = 0;
bool R_Is_First_Captured = 0;
uint8_t L_Dist = 0;
uint8_t C_Dist = 0;
uint8_t R_Dist = 0;

void ultrasonic_init(TIM_HandleTypeDef *htim) {
	m_htim = htim;
}

void delay_us(uint16_t time) {  // delay for microseconds
	__HAL_TIM_SET_COUNTER(m_htim, 0);
	while ((__HAL_TIM_GET_COUNTER(m_htim)) < time)
		;
}

void HCSR04_Read(void) {
	HAL_GPIO_WritePin(PC9_TRIG_GPIO_Port, PC9_TRIG_Pin, 1); // pull the TRIG pin HIGH
	delay_us(10);  // wait for 10 us
	HAL_GPIO_WritePin(PC9_TRIG_GPIO_Port, PC9_TRIG_Pin, 0); // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(m_htim, TIM_IT_CC1);
	__HAL_TIM_ENABLE_IT(m_htim, TIM_IT_CC2);
//	__HAL_TIM_ENABLE_IT(m_htim, TIM_IT_CC3);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == m_htim->Instance
			&& htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) { // if the interrupt source is channel 1
		if (L_Is_First_Captured == false) { // if the first value is not captured
			L_IC_Val[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			L_Is_First_Captured = true;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		} else if (L_Is_First_Captured == true) { // if the first is already captured
			L_IC_Val[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read second value

			if (L_IC_Val[1] > L_IC_Val[0]) {
				L_Diff = L_IC_Val[1] - L_IC_Val[0];
			} else if (L_IC_Val[0] > L_IC_Val[1]) { // if IC_Val[0] is overflowed value
				L_Diff = (0xffff - L_IC_Val[0]) + L_IC_Val[1];
			}

			L_Dist = DIST_CALC(L_Diff);
			L_Is_First_Captured = false;  // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(m_htim, TIM_IT_CC1);
		}
	} else if (htim->Instance == m_htim->Instance
			&& htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) { // if the interrupt source is channel 2
		if (C_Is_First_Captured == false) { // if the first value is not captured
			C_IC_Val[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
			C_Is_First_Captured = true;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		} else if (C_Is_First_Captured == true) { // if the first is already captured
			C_IC_Val[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read second value

			if (C_IC_Val[1] > C_IC_Val[0]) {
				C_Diff = C_IC_Val[1] - C_IC_Val[0];
			} else if (C_IC_Val[0] > C_IC_Val[1]) { // if IC_Val[0] is overflowed value
				C_Diff = (0xffff - C_IC_Val[0]) + C_IC_Val[1];
			}

			C_Dist = DIST_CALC(C_Diff);
			C_Is_First_Captured = false;  // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(m_htim, TIM_IT_CC2);
		}
	} else if (htim->Instance == m_htim->Instance
			&& htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) { // if the interrupt source is channel 2
		if (R_Is_First_Captured == false) { // if the first value is not captured
			R_IC_Val[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the first value
			R_Is_First_Captured = true;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_FALLING);
		} else if (R_Is_First_Captured == true) { // if the first is already captured
			R_IC_Val[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read second value

			if (R_IC_Val[1] > R_IC_Val[0]) {
				R_Diff = R_IC_Val[1] - R_IC_Val[0];
			} else if (R_IC_Val[0] > R_IC_Val[1]) { // if IC_Val[0] is overflowed value
				R_Diff = (0xffff - R_IC_Val[0]) + R_IC_Val[1];
			}

			R_Dist = DIST_CALC(R_Diff);
			R_Is_First_Captured = false;  // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3,
					TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(m_htim, TIM_IT_CC3);
		}
	}
}

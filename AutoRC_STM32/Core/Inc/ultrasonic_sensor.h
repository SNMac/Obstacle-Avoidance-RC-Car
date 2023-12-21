/*
 * ultrasonic_sensor.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#ifndef INC_ULTRASONIC_SENSOR_H_
#define INC_ULTRASONIC_SENSOR_H_

#include "main.h"

void ultrasonic_init(TIM_HandleTypeDef *htim);
void delay_us(uint16_t time);
void HCSR04_Read(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif /* INC_ULTRASONIC_SENSOR_H_ */

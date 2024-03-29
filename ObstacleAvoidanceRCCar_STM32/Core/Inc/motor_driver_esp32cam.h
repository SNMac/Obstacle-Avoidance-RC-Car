/*
 * motor_driver.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#ifndef INC_MOTOR_DRIVER_ESP32CAM_H_
#define INC_MOTOR_DRIVER_ESP32CAM_H_

#include "main.h"

void motor_init(TIM_HandleTypeDef *htim);
void drive(uint8_t dir);
void forward(void);
void backward(void);
void turn_left(void);
void turn_right(void);
void forward_left(void);
void forward_right(void);
void backward_left(void);
void backward_right(void);
void stop(void);

#endif /* INC_MOTOR_DRIVER_ESP32CAM_H_ */

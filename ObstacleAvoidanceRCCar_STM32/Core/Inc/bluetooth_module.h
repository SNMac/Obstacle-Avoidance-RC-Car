/*
 * bluetooth_module.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#ifndef INC_BLUETOOTH_MODULE_H_
#define INC_BLUETOOTH_MODULE_H_

#include <motor_driver_esp32cam.h>
#include "main.h"
#include <stdio.h>
#include <string.h>

void init_bt(UART_HandleTypeDef *huart);
void send_distance(uint8_t L_Dist, uint8_t C_Dist, uint8_t R_Dist);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_BLUETOOTH_MODULE_H_ */

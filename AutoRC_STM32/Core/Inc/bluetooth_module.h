/*
 * bluetooth_module.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#ifndef INC_BLUETOOTH_MODULE_H_
#define INC_BLUETOOTH_MODULE_H_

#include "main.h"
#include "motor_driver.h"
#include <stdio.h>
#include <string.h>

void init_bt(UART_HandleTypeDef *huart);
void send_distance(uint8_t L_Dist, uint8_t C_Dist);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_BLUETOOTH_MODULE_H_ */

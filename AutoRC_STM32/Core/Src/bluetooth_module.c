/*
 * bluetooth_module.c
 *
 *  Created on: Dec 22, 2023
 *      Author: Macmillan
 */

#include "bluetooth_module.h"

static UART_HandleTypeDef *m_huart;

uint8_t rx_c;
uint8_t tx_c[32];
uint8_t tx_dist[256];

extern uint8_t cur_dir;

void init_bt(UART_HandleTypeDef *huart) {
	m_huart = huart;
}

void send_distance(uint8_t L_Dist, uint8_t C_Dist) {
	sprintf((char*) tx_dist,
			"cur_dir : %c\r\nL_Dist : %d cm\r\nC_Dist : %d cm\r\nR_Dist : 0 cm\r\n==================\r\n",
			cur_dir, L_Dist, C_Dist);
	printf("%s", tx_dist);
	HAL_UART_Transmit(m_huart, tx_dist, strlen((char*) tx_dist), 100);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART1) {
		drive(rx_c);
		sprintf((char*) tx_c, "rx_c : %c\r\n", rx_c);
		printf("%s", tx_c);
		HAL_UART_Transmit(huart, tx_c, strlen((char*) tx_c), 10);
		HAL_UART_Receive_IT(huart, &rx_c, 1);
	}
}

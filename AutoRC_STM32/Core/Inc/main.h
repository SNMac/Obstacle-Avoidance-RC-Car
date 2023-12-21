/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PA0_TIM2_PWM_L_Pin GPIO_PIN_0
#define PA0_TIM2_PWM_L_GPIO_Port GPIOA
#define PA1_TIM2_PWM_R_Pin GPIO_PIN_1
#define PA1_TIM2_PWM_R_GPIO_Port GPIOA
#define PA6_TIM3_ECHO_L_Pin GPIO_PIN_6
#define PA6_TIM3_ECHO_L_GPIO_Port GPIOA
#define PA7_TIM3_ECHO_C_Pin GPIO_PIN_7
#define PA7_TIM3_ECHO_C_GPIO_Port GPIOA
#define PB0_TIM3_ECHO_R_Pin GPIO_PIN_0
#define PB0_TIM3_ECHO_R_GPIO_Port GPIOB
#define PB10_MTR_INB_Pin GPIO_PIN_10
#define PB10_MTR_INB_GPIO_Port GPIOB
#define PC9_TRIG_Pin GPIO_PIN_9
#define PC9_TRIG_GPIO_Port GPIOC
#define PA8_MTR_INA_Pin GPIO_PIN_8
#define PA8_MTR_INA_GPIO_Port GPIOA
#define PA9_BT_RX_Pin GPIO_PIN_9
#define PA9_BT_RX_GPIO_Port GPIOA
#define PA10_BT_TX_Pin GPIO_PIN_10
#define PA10_BT_TX_GPIO_Port GPIOA
#define PA11_BT_STATE_Pin GPIO_PIN_11
#define PA11_BT_STATE_GPIO_Port GPIOA
#define PB4_MTR_INC_Pin GPIO_PIN_4
#define PB4_MTR_INC_GPIO_Port GPIOB
#define PB5_MTR_IND_Pin GPIO_PIN_5
#define PB5_MTR_IND_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENSOR4_Pin GPIO_PIN_3
#define SENSOR4_GPIO_Port GPIOF
#define SENSOR5_Pin GPIO_PIN_5
#define SENSOR5_GPIO_Port GPIOF
#define SENSOR8_Pin GPIO_PIN_8
#define SENSOR8_GPIO_Port GPIOF
#define SENSOR6_Pin GPIO_PIN_10
#define SENSOR6_GPIO_Port GPIOF
#define SENSOR1_Pin GPIO_PIN_0
#define SENSOR1_GPIO_Port GPIOC
#define SENSOR3_Pin GPIO_PIN_3
#define SENSOR3_GPIO_Port GPIOC
#define OBS_DETECTOR_Pin GPIO_PIN_3
#define OBS_DETECTOR_GPIO_Port GPIOA
#define IN2_RIGHT_Pin GPIO_PIN_5
#define IN2_RIGHT_GPIO_Port GPIOA
#define IN1_LEFT_Pin GPIO_PIN_6
#define IN1_LEFT_GPIO_Port GPIOA
#define DEBUG_LGREEN_Pin GPIO_PIN_0
#define DEBUG_LGREEN_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOB
#define DEBUG_LRED_Pin GPIO_PIN_14
#define DEBUG_LRED_GPIO_Port GPIOB
#define BLUET_RX_Pin GPIO_PIN_15
#define BLUET_RX_GPIO_Port GPIOB
#define IN2_LEFT_Pin GPIO_PIN_14
#define IN2_LEFT_GPIO_Port GPIOD
#define PWM_LEFT_Pin GPIO_PIN_15
#define PWM_LEFT_GPIO_Port GPIOD
#define USER_BTN_Pin GPIO_PIN_8
#define USER_BTN_GPIO_Port GPIOC
#define SPI3_SDA_Pin GPIO_PIN_2
#define SPI3_SDA_GPIO_Port GPIOD
#define BLUET_TX_Pin GPIO_PIN_6
#define BLUET_TX_GPIO_Port GPIOB
#define DEBUG_LBLUE_Pin GPIO_PIN_7
#define DEBUG_LBLUE_GPIO_Port GPIOB
#define PWM_RIGHT_Pin GPIO_PIN_8
#define PWM_RIGHT_GPIO_Port GPIOB
#define IN1_RIGHT_Pin GPIO_PIN_9
#define IN1_RIGHT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

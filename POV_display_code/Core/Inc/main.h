/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

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
#define BAT_IN_Pin GPIO_PIN_0
#define BAT_IN_GPIO_Port GPIOA
#define IR_SIG_Pin GPIO_PIN_2
#define IR_SIG_GPIO_Port GPIOA
#define DBG_Pin GPIO_PIN_3
#define DBG_GPIO_Port GPIOA
#define RCLK_Pin GPIO_PIN_14
#define RCLK_GPIO_Port GPIOB
#define NOT_OE_Pin GPIO_PIN_11
#define NOT_OE_GPIO_Port GPIOA
#define NOT_CLEAR_Pin GPIO_PIN_12
#define NOT_CLEAR_GPIO_Port GPIOA
#define HAL_SIG_Pin GPIO_PIN_5
#define HAL_SIG_GPIO_Port GPIOB
#define HAL_SIG_EXTI_IRQn EXTI4_15_IRQn
#define BAT_EN_Pin GPIO_PIN_9
#define BAT_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

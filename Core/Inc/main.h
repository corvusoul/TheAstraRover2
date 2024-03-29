/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define steer_rl_ChannelA_Pin GPIO_PIN_2
#define steer_rl_ChannelA_GPIO_Port GPIOE
#define steer_rl_ChannelA_EXTI_IRQn EXTI2_IRQn
#define steer_rr_ChannelA_Pin GPIO_PIN_3
#define steer_rr_ChannelA_GPIO_Port GPIOE
#define steer_rr_ChannelA_EXTI_IRQn EXTI3_IRQn
#define RLDrive1_Pin GPIO_PIN_6
#define RLDrive1_GPIO_Port GPIOA
#define RLDrive2_Pin GPIO_PIN_7
#define RLDrive2_GPIO_Port GPIOA
#define RRDrive1_Pin GPIO_PIN_0
#define RRDrive1_GPIO_Port GPIOB
#define RRDrive2_Pin GPIO_PIN_1
#define RRDrive2_GPIO_Port GPIOB
#define FRDrive1_Pin GPIO_PIN_9
#define FRDrive1_GPIO_Port GPIOE
#define FRDrive2_Pin GPIO_PIN_11
#define FRDrive2_GPIO_Port GPIOE
#define FLDrive1_Pin GPIO_PIN_13
#define FLDrive1_GPIO_Port GPIOE
#define FLDrive2_Pin GPIO_PIN_14
#define FLDrive2_GPIO_Port GPIOE
#define FRSteer1_Pin GPIO_PIN_12
#define FRSteer1_GPIO_Port GPIOD
#define FRSteer2_Pin GPIO_PIN_13
#define FRSteer2_GPIO_Port GPIOD
#define FLSteer1_Pin GPIO_PIN_14
#define FLSteer1_GPIO_Port GPIOD
#define FLSteer2_Pin GPIO_PIN_15
#define FLSteer2_GPIO_Port GPIOD
#define RLSteer1_Pin GPIO_PIN_6
#define RLSteer1_GPIO_Port GPIOC
#define RLSteer2_Pin GPIO_PIN_7
#define RLSteer2_GPIO_Port GPIOC
#define RRSteer1_Pin GPIO_PIN_8
#define RRSteer1_GPIO_Port GPIOC
#define RRSteer2_Pin GPIO_PIN_9
#define RRSteer2_GPIO_Port GPIOC
#define steer_fr_ChannelB_Pin GPIO_PIN_0
#define steer_fr_ChannelB_GPIO_Port GPIOD
#define steer_fl_ChannelB_Pin GPIO_PIN_1
#define steer_fl_ChannelB_GPIO_Port GPIOD
#define steer_rl_ChannelB_Pin GPIO_PIN_2
#define steer_rl_ChannelB_GPIO_Port GPIOD
#define steer_rr_ChannelB_Pin GPIO_PIN_3
#define steer_rr_ChannelB_GPIO_Port GPIOD
#define steer_fr_ChannelA_Pin GPIO_PIN_0
#define steer_fr_ChannelA_GPIO_Port GPIOE
#define steer_fr_ChannelA_EXTI_IRQn EXTI0_IRQn
#define steer_fl_ChannelA_Pin GPIO_PIN_1
#define steer_fl_ChannelA_GPIO_Port GPIOE
#define steer_fl_ChannelA_EXTI_IRQn EXTI1_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

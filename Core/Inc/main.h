/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define onBoard_Button_Pin GPIO_PIN_13
#define onBoard_Button_GPIO_Port GPIOC
#define DHT11_data_Pin GPIO_PIN_0
#define DHT11_data_GPIO_Port GPIOF
#define onBoard_Green_LED_Pin GPIO_PIN_0
#define onBoard_Green_LED_GPIO_Port GPIOB
#define keypad_r1_Pin GPIO_PIN_1
#define keypad_r1_GPIO_Port GPIOB
#define keypad_r2_Pin GPIO_PIN_2
#define keypad_r2_GPIO_Port GPIOB
#define FND_D1_Pin GPIO_PIN_0
#define FND_D1_GPIO_Port GPIOG
#define FND_D2_Pin GPIO_PIN_1
#define FND_D2_GPIO_Port GPIOG
#define TIM1_PWM_Pin GPIO_PIN_14
#define TIM1_PWM_GPIO_Port GPIOE
#define keypad_c3_Pin GPIO_PIN_10
#define keypad_c3_GPIO_Port GPIOB
#define keypad_c4_Pin GPIO_PIN_11
#define keypad_c4_GPIO_Port GPIOB
#define onBoard_RED_LED_Pin GPIO_PIN_14
#define onBoard_RED_LED_GPIO_Port GPIOB
#define FND_D3_Pin GPIO_PIN_2
#define FND_D3_GPIO_Port GPIOG
#define FND_D4_Pin GPIO_PIN_3
#define FND_D4_GPIO_Port GPIOG
#define FND_A_Pin GPIO_PIN_0
#define FND_A_GPIO_Port GPIOD
#define FND_B_Pin GPIO_PIN_1
#define FND_B_GPIO_Port GPIOD
#define FND_C_Pin GPIO_PIN_2
#define FND_C_GPIO_Port GPIOD
#define FND_D_Pin GPIO_PIN_3
#define FND_D_GPIO_Port GPIOD
#define FND_E_Pin GPIO_PIN_4
#define FND_E_GPIO_Port GPIOD
#define FND_F_Pin GPIO_PIN_5
#define FND_F_GPIO_Port GPIOD
#define FND_G_Pin GPIO_PIN_6
#define FND_G_GPIO_Port GPIOD
#define FND_P_Pin GPIO_PIN_7
#define FND_P_GPIO_Port GPIOD
#define keypad_r3_Pin GPIO_PIN_3
#define keypad_r3_GPIO_Port GPIOB
#define keypad_r4_Pin GPIO_PIN_4
#define keypad_r4_GPIO_Port GPIOB
#define keypad_c1_Pin GPIO_PIN_5
#define keypad_c1_GPIO_Port GPIOB
#define keypad_c2_Pin GPIO_PIN_6
#define keypad_c2_GPIO_Port GPIOB
#define onBoard_Blue_LED_Pin GPIO_PIN_7
#define onBoard_Blue_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

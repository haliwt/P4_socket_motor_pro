/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

#include "stm32g0xx_ll_adc.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

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
#define LED_KEY_Pin LL_GPIO_PIN_15
#define LED_KEY_GPIO_Port GPIOC
//GPIO RELAY 
#define RELAY_CTL_Pin LL_GPIO_PIN_1
#define RELAY_CTL_GPIO_Port GPIOA
//GPIO PINCH WITH MOTOR
#define PINCH_Pin LL_GPIO_PIN_6
#define PINCH_GPIO_Port GPIOA
//GPIO MOTOR 
#define MOTOR_POS_UP_Pin LL_GPIO_PIN_7
#define MOTOR_POS_UP_GPIO_Port GPIOA
#define MOTOR_POS_DOWN_Pin LL_GPIO_PIN_0
#define MOTOR_POS_DOWN_GPIO_Port GPIOB
#define MOROT_RUN_CW_Pin LL_GPIO_PIN_2
#define MOROT_RUN_CW_GPIO_Port GPIOB
#define MOTOR_RUN_CCW_Pin LL_GPIO_PIN_10
#define MOTOR_RUN_CCW_GPIO_Port GPIOB
#define CHARGING_Pin LL_GPIO_PIN_11
#define CHARGING_GPIO_Port GPIOB
#define MUTE_SOUND_Pin LL_GPIO_PIN_12
#define MUTE_SOUND_GPIO_Port GPIOB
#define TM1639_STB_Pin LL_GPIO_PIN_13
#define TM1639_STB_GPIO_Port GPIOB
#define TM1639_SCLK_Pin LL_GPIO_PIN_14
#define TM1639_SCLK_GPIO_Port GPIOB
#define TM1639_DIO_Pin LL_GPIO_PIN_15
#define TM1639_DIO_GPIO_Port GPIOB
//USB ENABLE POWER 
#define USB_EN_Pin LL_GPIO_PIN_15
#define USB_EN_GPIO_Port GPIOA
//USB BE DETECTED HIGH CURRENT 
#define USB_OVERLOAD_Pin LL_GPIO_PIN_0
#define USB_OVERLOAD_GPIO_Port GPIOD
//INA219 IC I2C 
#define I2C_INA_SDA_Pin LL_GPIO_PIN_7
#define I2C_INA_SDA_GPIO_Port GPIOB
#define I2C_INA_SCL_Pin LL_GPIO_PIN_8
#define I2C_INA_SCL_GPIO_Port GPIOB
//EEPRO IC I2C 
#define I2C_EP_SCL_Pin LL_GPIO_PIN_4
#define I2C_EP_SCL_GPIO_Port GPIOA
#define I2C_EP_SDA_Pin LL_GPIO_PIN_5
#define I2C_EP_SDA_GPIO_Port GPIOA

//
#define KEY_Pin LL_GPIO_PIN_9
#define KEY_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

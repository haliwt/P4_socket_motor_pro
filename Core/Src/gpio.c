/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(LED_KEY_GPIO_Port, LED_KEY_Pin);

  /**/
  LL_GPIO_ResetOutputPin(RELAY_CTL_GPIO_Port, RELAY_CTL_Pin);

  /**/
  LL_GPIO_ResetOutputPin(I2C_EP_SCL_GPIO_Port, I2C_EP_SCL_Pin);

  /**/
  LL_GPIO_ResetOutputPin(I2C_EP_SDA_GPIO_Port, I2C_EP_SDA_Pin);

  /**/
  LL_GPIO_ResetOutputPin(MOROT_RUN_CW_GPIO_Port, MOROT_RUN_CW_Pin);

  /**/
  LL_GPIO_ResetOutputPin(MOTOR_RUN_CCW_GPIO_Port, MOTOR_RUN_CCW_Pin);

  /**/
  LL_GPIO_ResetOutputPin(MUTE_SOUND_GPIO_Port, MUTE_SOUND_Pin);

  /**/
  LL_GPIO_ResetOutputPin(TM1639_STB_GPIO_Port, TM1639_STB_Pin);

  /**/
  LL_GPIO_ResetOutputPin(TM1639_SCLK_GPIO_Port, TM1639_SCLK_Pin);

  /**/
  LL_GPIO_ResetOutputPin(TM1639_DIO_GPIO_Port, TM1639_DIO_Pin);

  /**/
  LL_GPIO_ResetOutputPin(USB_EN_GPIO_Port, USB_EN_Pin);

  /**/
  LL_GPIO_ResetOutputPin(I2C_INA_SDA_GPIO_Port, I2C_INA_SDA_Pin);

  /**/
  LL_GPIO_ResetOutputPin(I2C_INA_SCL_GPIO_Port, I2C_INA_SCL_Pin);

  /**/
  GPIO_InitStruct.Pin = LED_KEY_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(LED_KEY_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = RELAY_CTL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(RELAY_CTL_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = I2C_EP_SCL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(I2C_EP_SCL_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = I2C_EP_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(I2C_EP_SDA_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PINCH_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PINCH_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MOTOR_POS_UP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(MOTOR_POS_UP_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MOTOR_POS_DOWN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(MOTOR_POS_DOWN_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MOROT_RUN_CW_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(MOROT_RUN_CW_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MOTOR_RUN_CCW_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(MOTOR_RUN_CCW_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = CHARGING_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(CHARGING_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MUTE_SOUND_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(MUTE_SOUND_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TM1639_STB_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(TM1639_STB_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TM1639_SCLK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(TM1639_SCLK_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = TM1639_DIO_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(TM1639_DIO_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = USB_EN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(USB_EN_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = USB_OVERLOAD_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(USB_OVERLOAD_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = I2C_INA_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(I2C_INA_SDA_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = I2C_INA_SCL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(I2C_INA_SCL_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = KEY_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

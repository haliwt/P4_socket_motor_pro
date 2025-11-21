#ifndef __BSP_I2C_H
#define __BSP_I2C_H
#include "main.h"




#define SCL_H()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7)
#define SCL_L()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7)

#define SDA_H()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_9)
#define SDA_L()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_9)

#define SDA_READ()  (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_9))




void I2C_GPIO_Init(void);



void TM1650_Write(uint8_t addr, uint8_t data);



#endif 



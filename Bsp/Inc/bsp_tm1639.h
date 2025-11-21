#ifndef __BSP_TM1639_H
#define __BSP_TM1639_H
#include "main.h"


#define DisplayReg           0x40// to write display register 
 
#define AddrFixed 	         0x44// 
#define AddrAutoAdd          0x40 

  
 
#define OpenDispTM1639          0x88// 
#define CloseDispTM1639		    0x80// 


#define STB_HIGH()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13)
#define STB_LOW()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13)

#define SCLK_HIGH()  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_14)
#define SCLK_LOW()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_14)

#define DIO_HIGH()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_15)
#define DIO_LOW()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_15)


void TM1639_Init(void);

void TM1639_donotDisplay(void);

void TM1639_WriteData(uint8_t addr, uint8_t data);


#endif


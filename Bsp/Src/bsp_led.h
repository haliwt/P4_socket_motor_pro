#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"



#define LED_KEY_ON()       LL_GPIO_ResetOutputPin(LED_KEY_GPIO_Port,LED_KEY_Pin)
#define LED_KEY_OFF()      LL_GPIO_SetOutputPin(LED_KEY_GPIO_Port,LED_KEY_Pin)









#endif 


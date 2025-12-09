#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H
#include "main.h"


#define RELAY_CTL_ON()       LL_GPIO_SetOutputPin(RELAY_CTL_GPIO_Port,RELAY_CTL_Pin)
#define RELAY_CTL_OFF()      LL_GPIO_ResetOutputPin(RELAY_CTL_GPIO_Port,RELAY_CTL_Pin)





#endif 


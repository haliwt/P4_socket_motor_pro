#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"


#define LED_RUN_ON()      LL_GPIO_ResetOutputPin(LED_RUN_GPIO_Port,LED_RUN_Pin)
#define LED_RUN_OFF()     LL_GPIO_SetOutputPin(LED_RUN_GPIO_Port,LED_RUN_Pin)

#define LED_RUN_TOGGLE()     LL_GPIO_TogglePin(LED_RUN_GPIO_Port,LED_RUN_Pin)

#define LED_STOP_ON()      LL_GPIO_ResetOutputPin(LED_STOP_GPIO_Port,LED_STOP_Pin)
#define LED_STOP_OFF()     LL_GPIO_SetOutputPin(LED_STOP_GPIO_Port,LED_STOP_Pin)

#define LED_ERROR_ON()     LL_GPIO_ResetOutputPin(LED_NG_GPIO_Port,LED_NG_Pin)
#define LED_ERROR_OFF()     LL_GPIO_SetOutputPin(LED_NG_GPIO_Port,LED_NG_Pin)

#define LED_STEP_ON()     LL_GPIO_ResetOutputPin(LED_STEP_GPIO_Port,LED_STEP_Pin)
#define LED_STEP_OFF()     LL_GPIO_SetOutputPin(LED_STEP_GPIO_Port,LED_STEP_Pin)




#endif 


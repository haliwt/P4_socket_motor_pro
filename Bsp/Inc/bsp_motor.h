#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H
#include "main.h"


#define MOTOR_RUN_UP_SetHigh()    LL_GPIO_SetOutputPin(MOTOR_RUN_CCW_GPIO_Port,MOTOR_RUN_CCW_Pin)
#define MOTOR_RUN_UP_SetLow()     LL_GPIO_ResetOutputPin(MOTOR_RUN_CCW_GPIO_Port,MOTOR_RUN_CCW_Pin)

#define MOTOR_RUN_DOWN_SetHigh()    LL_GPIO_SetOutputPin(MOROT_RUN_CW_GPIO_Port,MOROT_RUN_CW_Pin)
#define MOTOR_RUN_DOWN_SetLow()     LL_GPIO_ResetOutputPin(MOROT_RUN_CW_GPIO_Port,MOROT_RUN_CW_Pin)

#define WIRELESS_CHARGING_VALUE()      LL_GPIO_IsInputPinSet(CHARGING_GPIO_Port,CHARGING_Pin)

#define MOTOR_POS_UP_VALUE()           LL_GPIO_IsInputPinSet(MOTOR_POS_UP_GPIO_Port,MOTOR_POS_UP_Pin)

#define MOTOR_POS_DOWN_VALUE()         LL_GPIO_IsInputPinSet(MOTOR_POS_DOWN_GPIO_Port,MOTOR_POS_DOWN_Pin)


#define MOTOR_PINCH_VALUE()            LL_GPIO_IsInputPinSet(PINCH_GPIO_Port,PINCH_Pin)          


void motor_run_up(void);
void motor_run_down(void);

void motor_stop(void);


#endif 

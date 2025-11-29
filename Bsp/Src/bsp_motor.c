#include "bsp.h"

void motor_run_up(void)
{
   MOTOR_RUN_UP_SetHigh();
   MOTOR_RUN_DOWN_SetLow();

}
void motor_run_down(void)
{
	MOTOR_RUN_DOWN_SetHigh();
	MOTOR_RUN_UP_SetLow();

}
void motor_stop(void)
{
   MOTOR_RUN_UP_SetLow();
   MOTOR_RUN_DOWN_SetLow();

}


#ifndef __BSP_POWER_H
#define __BSP_POWER_H
#include "main.h"

typedef enum{


  power_off,
  power_on

}power_state_t;

typedef enum{

  motor_id_up=1,
  motor_id_down,
  motor_id_stop,
  charging_state,
  

}motor_dir_state_t;


void main_process_handler(void);

#endif 


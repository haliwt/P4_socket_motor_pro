#ifndef __BSP_SMG_H
#define __BSP_SMG_H
#include "main.h"


typedef enum{

  smg_init,
  smg_voltage,
  smg_kw,
  smg_usb,

}glsmg_enum;

void smg_Init(void);

void works_disp_hanlder(void);





#endif 


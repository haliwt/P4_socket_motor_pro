#ifndef __BSP_SMG_H
#define __BSP_SMG_H
#include "main.h"

//Low Bit    
#define   seg_a  0x01      //SEG0   //seg_e = 0x10  
#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
#define   seg_c  0x04      //SEG2 , //seg_g = 0x40
#define   seg_d  0x08      //SEG3 , //seg_d = 0x08

//High BIT
#define   seg_e  0x10      //SEG4 , //seg_c = 0x04
#define   seg_f  0x20      //SEG5   //seg_a = 0x01
#define   seg_g  0x40      //SEG6   //seg_b = 0x02 
#define   seg_h  0x80      //SEG7 -> ":"



typedef enum{

  smg_init,
  smg_voltage,
  smg_kw,
  smg_usb,

}glsmg_enum;

void smg_Init(void);

void works_disp_hanlder(void);

void smg_power_off_ref(void);

void display_usb_kw_symbol(void);



#endif 


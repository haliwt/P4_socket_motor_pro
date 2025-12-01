#include "bsp.h"

const uint8_t segTab[10] = {
	  0x3F, // 0
	  0x06, // 1
	  0x5B, // 2
	  0x4F, // 3
	  0x66, // 4
	  0x6D, // 5
	  0x7D, // 6
	  0x07, // 7
	  0x7F, // 8
	  0x6F	// 9
};


typedef struct SMG_PROCESS{

    uint8_t smg_run_step;
	uint8_t read_kw_value;
	uint8_t read_usb_w_value;
    uint16_t read_ac_voltage;

}SMG_PROCESS_T;

SMG_PROCESS_T glsmg_t;

static void disp_voltage_3bit_value(uint16_t voltage);

static void disp_usb_capacity_2bit_value(uint8_t usb_value);


static void disp_capacity_2bit_kwvalue(uint8_t kwvalue,uint8_t decimal);



/*
	*@brief:// --- 示例：显示数字 ---
	*@note:
	*@param:
	*@retval:
*/

void smg_Init(void)
{
    if(gpro_t.gpower_flag == power_on){

           
	}
	else{


	}

}
/*
	*@brief:// --- 示例：显示数字 ---
	*@note:
	*@param:
	*@retval:
*/
//void TM1639_DisplayTest(void)
//{
//   for (uint8_t i = 0; i < 10; i++) {
//        TM1639_WriteData(i, segTab[i]);
//    }
//}
/*
	*@brief: smg main process from this run
	*@note:
	*@param:
	*@retval:
*/
void works_disp_hanlder(void)
{

     switch(glsmg_t.smg_run_step){

	 case smg_init:
	 LED_KEY_ON();	
     TM1639_Init();
	 glsmg_t.smg_run_step= smg_voltage;

	 break;

	 case smg_voltage:
      glsmg_t.read_ac_voltage= read_ac_voltage_value();
	  disp_voltage_3bit_value(glsmg_t.read_ac_voltage);
	  motor_detect_pinch(); 
	  display_usb_kw_symbol();
	  glsmg_t.smg_run_step = smg_kw;
    
	 break;

	 case smg_kw://2
//		glsmg_t.read_kw_value = read_total_kw_decade_value();
//		if(glsmg_t.read_kw_value > 0){

//             disp_capacity_2bit_kwvalue(glsmg_t.read_kw_value,1);
//		}
//		else{

//		   glsmg_t.read_kw_value = read_total_kw_uint_value();
//		    disp_capacity_2bit_kwvalue(glsmg_t.read_kw_value,0);

//		}
        disp_capacity_2bit_kwvalue(0,1);
        motor_detect_pinch();
	    display_usb_kw_symbol();
		glsmg_t.smg_run_step = smg_usb;
	 break;

	 case smg_usb:

	      glsmg_t.read_usb_w_value = read_usb_capacity_value(); 
		  disp_usb_capacity_2bit_value(glsmg_t.read_usb_w_value);
          motor_detect_pinch();
		  display_usb_kw_symbol();
		  glsmg_t.smg_run_step = smg_voltage;

	 break;

     }

  

}
/*
	*@brief: display address GRID_1,GRID_2,GRID_3
	*@note:
	*@param:
	*@retval:
*/
static void disp_voltage_3bit_value(uint16_t voltage)
{
  uint8_t vol_hundred,vol_decade,vol_unit;

  vol_hundred = voltage / 100 ;
  vol_decade =  (voltage  /10) %10;
  vol_unit =  voltage  %10;
  
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID1_H, TM1639_ADDR_GRID1_L, segTab[vol_hundred]);
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID2_H, TM1639_ADDR_GRID2_L, segTab[vol_decade]);
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID3_H, TM1639_ADDR_GRID3_L, segTab[vol_unit]);

  
}
/*
	*@brief: display kw of power capacity 
	*@note:
	*@param:
	*@retval:
*/
static void disp_capacity_2bit_kwvalue(uint8_t kwvalue,uint8_t decimal)
{
	
	 uint8_t kw_decade,kw_unit;

	 if(decimal > 0){ //integer 
	
	
	 kw_decade =  (kwvalue  /10) %10;
	 kw_unit =  kwvalue  %10;
	 
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID6_H, TM1639_ADDR_GRID7_L, segTab[kw_decade]);
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, segTab[kw_unit]);
	 
	 }
	 else{ //decimal 
       
        TM1639_Write_Digit_Full(TM1639_ADDR_GRID6_H, TM1639_ADDR_GRID7_L, segTab[0]+0x80);
	    TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, segTab[kw_unit]);


	 }

   
}
/*
	*@brief: display kw of power capacity 
	*@note:
	*@param:
	*@retval:
*/
static void disp_usb_capacity_2bit_value(uint8_t usb_value)
{
     uint8_t usb_decade,usb_unit;

     usb_decade =  (usb_value  /10) %10;
	 usb_unit =  usb_value %10;
	 
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID4_H, TM1639_ADDR_GRID4_L, segTab[usb_decade]);
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID5_H, TM1639_ADDR_GRID5_L, segTab[usb_unit]);
	 
	
}


void splitDigits(uint16_t number, uint8_t  *hundred, uint8_t *decade, uint8_t *unit) 
{
    *hundred = number / 100;
    *decade = (number % 100) / 10;
    *unit = number % 10;
}



void smg_power_off_ref(void)
{

	glsmg_t.smg_run_step= smg_init;
    LED_KEY_OFF();

}


void display_usb_kw_symbol(void)
{

  TM1639_Write_Digit_Full(TM1639_ADDR_GRID8_H, TM1639_ADDR_GRID8_L, seg_a|seg_b|seg_c|seg_d);
 

}

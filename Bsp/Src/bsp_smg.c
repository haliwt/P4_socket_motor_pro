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
/*
	*@brief:// --- 示例：显示数字 ---
	*@note:
	*@param:
	*@retval:
*/
void TM1639_DisplayTest(void)
{
   for (uint8_t i = 0; i < 10; i++) {
        TM1639_WriteData(i, segTab[i]);
    }
}
/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/
void works_disp_hanlder(void)
{
     

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

  vol_hundred = voltage / 100) ;
  vol_decade =  (voltage  /10) %10;
  vol_unit =  voltage  %10;
  
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID1_H, TM1639_ADDR_GRID1_L, TM1639_Number_Table[vol_hundred]);
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID2_H, TM1639_ADDR_GRID2_L, TM1639_Number_Table[vol_decade]);
  TM1639_Write_Digit_Full(TM1639_ADDR_GRID3_H, TM1639_ADDR_GRID3_L, TM1639_Number_Table[vol_unit]);


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
	 
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID6_H, TM1639_ADDR_GRID7_L, TM1639_Number_Table[kw_decade]);
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, TM1639_Number_Table[kw_unit]);
	 
	 }
	 else{ //decimal 
       
        TM1639_Write_Digit_Full(TM1639_ADDR_GRID6_H, TM1639_ADDR_GRID7_L, TM1639_Number_Table[0]+0x80);
	    TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, TM1639_Number_Table[kw_unit]);


	 }


}
/*
	*@brief: display kw of power capacity 
	*@note:
	*@param:
	*@retval:
*/
static void disp_usb_capacity_2bit_value(void)
{
     uint8_t usb_decade,usb_unit;


	
	 usb_decade =  (kwvalue  /10) %10;
	 kw_unit =  kwvalue  %10;
	 
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID4_H, TM1639_ADDR_GRID4_L, TM1639_Number_Table[kw_decade]);
	 TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, TM1639_Number_Table[kw_unit]);
	 
	

}


void splitDigits(uint16_t number, uint8_t  *hundred, uint8_t *decade, uint8_t *unit) 
{
    *hundred = number / 100;
    *decade = (number % 100) / 10;
    *unit = number % 10;
}


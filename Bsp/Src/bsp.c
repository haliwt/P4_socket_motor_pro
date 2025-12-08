#include "bsp.h"

process_t gpro_t;



/**********************************************************************
    *
    *Function Name:uint8_t bcc_check(const unsigned char *data, int len) 
    *Function: BCC????
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
uint8_t bcc_check(const unsigned char *data, int len) 
{
    unsigned char bcc = 0;
    for (int i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}
/**************************************************************************************
*
*Function Name:  void bsp_init(void)
*Function: initial of base reference 
*Input Ref:NO
*Return Ref:NO
*
**************************************************************************************/
  void bsp_init(void)
  {
  
   INA219_I2C_GPIO_Init();
   callback_register_fun();
  
   
   #if Enable_EventRecorder == 1  
	/* 0…60‹10‡80†40†30…4EventRecorder0…50„40†70„90‡40‹0 */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
	#endif
	
  
  }
  






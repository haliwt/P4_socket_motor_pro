#ifndef __BSP_H
#define __BSP_H
#include "main.h"

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//freeRTOS
#include "FreeRTOS.h"
#include "task.h"

//main board bsp files

#include "bsp_freertos.h"


#include "bsp_tm1639.h"

#include "bsp_delay.h"
#include "bsp_smg.h"
#include "bsp_led.h"

#include "bsp_power.h"

#include "bsp_key.h"
#include "bsp_motor.h"

#include "bsp_power_meter.h"
#include "bsp_usb_meter.h"
#include "bsp_eeprom.h"
#include "bsp_buzzer.h"
#include "bsp_adc.h"
#include "bsp_hlw8032.h"
#include "bsp_ina219.h"
#include "bsp_i2c.h"

#include "interrupt_manager.h"




#define Enable_EventRecorder  1

#define DEBUG_FLAG        Enable_EventRecorder //(Enable_EventRecorder? 1:0)


#define WIFI_RX_NUMBERS         1



#define  USE_FreeRTOS      1


#if USE_FreeRTOS == 1
	#include "FreeRTOS.h"
    #include "task.h"
    #include "cmsis_os.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ??????????l? */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* '???????? */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ????????? */
#endif

#if Enable_EventRecorder == 1
	#include "EventRecorder.h"
#endif


extern uint8_t wifi_rx_inputBuf[WIFI_RX_NUMBERS];
extern uint8_t inputBuf[1];









typedef struct PROCESS_T{

  uint8_t gpower_flag;
  
  uint8_t gTimer_smg_counter;
}process_t;

extern process_t gpro_t;

void bsp_init(void);


#endif 

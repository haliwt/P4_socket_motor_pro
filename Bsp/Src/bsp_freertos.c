#include "bsp.h"


#define BIT_0	(1 << 0)
#define BIT_1	(1 << 1)


/***********************************************************************************************************
											函数声明
***********************************************************************************************************/
//static void vTaskWifiPro(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);


/* 创建任务通信机制 */
//static void AppObjCreate(void);


/***********************************************************************************************************
											变量声明
***********************************************************************************************************/
//static TaskHandle_t xHandleTaskWifiPro = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;




#define LOWEST_PRIORITY   1  // ???????
#define HIGHEST_PRIORITY  2


typedef struct{

  uint8_t power_key_counter;
  uint8_t power_on_flag;
  uint8_t power_key_id ;
  uint8_t key_long_flag;


}freertos_run_t;

freertos_run_t glrun_t;


uint8_t power_on_sound_flag ;

/**********************************************************************************************************
*
*	Function Name:void freeRTOS_Handler(void)
*   Function :
*	
*  
**********************************************************************************************************/
void freeRTOS_Handler(void)
{
     /* 创建任务 */
	   AppTaskCreate();
	  
	  /* 创建任务通信机制 */
//	   AppObjCreate();
	  
	  /* 启动调度，开始执行任�?1�?7?1�?1�?7?7 */
	   vTaskStartScheduler();


}
/**
 * @brief  :  static void vTaskStart(void *pvParameters
 * @note    
 * @param   None
 * @retval  None
 */
static void vTaskMsgPro(void *pvParameters)
{
     BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(30); /* 设置最大等待时间为500ms */
	uint32_t ulValue;
	static uint8_t key_id_counter;
	while(1)
    {
       if(power_on_sound_flag==0){
            power_on_sound_flag ++;
            buzzer_sound();//buzzer_sound();
			

       }

	   xResult = xTaskNotifyWait(0x00000000,      
						          0xFFFFFFFF,      
						          &ulValue,        /* 保存ulNotifiedValue到变量ulValue中 */
						          xMaxBlockTime);  /* 最大允许延迟时间 */
		
	  if( xResult == pdPASS )
	  {

	     /* 接收到消息，检测那个位被按下 */
			if((ulValue & BIT_0) != 0)
			{
               glrun_t.power_key_counter=0;
			 //   glrun_t.key_long_flag = 0;
			   if(gpro_t.gpower_flag == power_off){
			     gpro_t.gpower_flag = power_on;
			   }
			   else{
			      gpro_t.gpower_flag = power_off;
				  
				  motor_pause();
                  
			   }
			  //printf("接收到K2按键按下消息, ulNotifiedValue = 0x%08x\r\n", ulValue);
		
			}
            else if((ulValue & BIT_1) != 0 && KEY_VALUE() ==KEY_UP && glrun_t.key_long_flag == 0)
			{
               glrun_t.power_key_counter=0;
			   buzzer_sound();
               key_id_counter = key_id_counter ^ 0x01;
			   if(key_id_counter == 1){
			   	 
			     glrun_t.power_key_id = 1;

				 motor_run_state();
			   }
			   else{

			     glrun_t.power_key_id = 2;
				 motor_pause();
                  
			   }
			  //printf("接收到K3按键按下消息, ulNotifiedValue = 0x%08x\r\n", ulValue);
			}
	  }
      else{
      main_process_handler();
	  if(gpro_t.gTimer_key_counter > 1 && glrun_t.key_long_flag ==1){
	     gpro_t.gTimer_key_counter =0;
	      glrun_t.key_long_flag=0;


	  }
	  vTaskDelay(pdMS_TO_TICKS(20));	
      }
 	}
}	

/**
 * @brief  :  static void vTaskStart(void *pvParameters)
 * @note   :  priority is higest
 * @param   None
 * @retval  None
 */
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
  
       
		if(KEY_VALUE() ==KEY_DOWN){

			glrun_t.power_key_counter++;
			if(glrun_t.power_key_counter > 35 && glrun_t.key_long_flag != 1){

			    glrun_t.power_key_counter =0;
				glrun_t.power_key_id = 1;
			    glrun_t.key_long_flag = 1;

				gpro_t.gTimer_key_counter=0;
			    buzzer_sound();
				xTaskNotify(xHandleTaskMsgPro, /* 目标任务 */
								BIT_0,         /* 设置目标任务事件标志位bit0  */
								eSetBits);     /* 将目标任务的事件标志位与BIT_0进行或操作， 
				                                      将结果赋值给事件标志位。*/

		    }
            if(glrun_t.power_key_counter < 34 &&  gpro_t.gpower_flag  == power_on && glrun_t.key_long_flag != 1){

			   xTaskNotify(xHandleTaskMsgPro, /* 目标任务 */
								BIT_1,        /* 设置目标任务事件标志位bit0  */
								eSetBits);    /* 将目标任务的事件标志位与BIT_0进行或操作， 
				                                      将结果赋值给事件标志位。*/
                

			}
			

		}

        vTaskDelay(pdMS_TO_TICKS(20));
	} 
}
 /**
 * @brief  :  void AppTaskCreate (void)
 * @note    
 * @param   None
 * @retval  None
 */
void AppTaskCreate (void)
{

	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务�?1�?7?1�?1�?7?7    */
                 256,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 1,              		/* 任务优先�?1�?7?1�?1�?7?7 数�1�?7�?1�?7越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskMsgPro);   /* 任务句柄  */


   xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务�?1�?7?1�?1�?7?7    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,              		/* 任务优先�?1�?7?1�?1�?7?7 数�1�?7�?1�?7越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskStart );   /* 任务句柄  */
}


/********************************************************************************
	**
	*Function Name:void freertos_set_prority(void)
	*Function :
	*Input Ref: 
	*Return Ref:NO
	*
*******************************************************************************/
void freertos_set_prority(void)
{
	
	vTaskPrioritySet(xHandleTaskStart, LOWEST_PRIORITY);  // ???????
	taskYIELD();  // ??????
	vTaskPrioritySet(xHandleTaskMsgPro,HIGHEST_PRIORITY);  // ???????

   
} 

//void freertos_decoder_isr_handler(void)
//{
//	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

//	xTaskNotifyFromISR(xHandleTaskMsgPro,  /* ???? */
//						DECODER_BIT_0,	   /* ???????????bit0  */
//						eSetBits,  /* ????????????BIT_0?????, ??????????? */
//						&xHigherPriorityTaskWoken);

//	/* ??xHigherPriorityTaskWoken = pdTRUE,???????????????????? */
//	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

//}

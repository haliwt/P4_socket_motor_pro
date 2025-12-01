#include "bsp.h"




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
  uint8_t key_long_flag;


}freertos_run_t;

freertos_run_t glrun_t;


uint8_t power_on_sound_flag ;
uint8_t key_value;
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
  
	while(1)
    {
       if(power_on_sound_flag==0){
            power_on_sound_flag ++;
            buzzer_sound();//buzzer_sound();
			

       }
      
      main_process_handler();
	  vTaskDelay(pdMS_TO_TICKS(10));		                                   
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
			if(glrun_t.power_key_counter > 65){

			    glrun_t.power_key_counter =0;
				glrun_t.key_long_flag = 1;

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

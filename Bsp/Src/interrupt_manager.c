#include "bsp.h"




static void tim17_isr_callback_handler(void);


// 定义 TIM17 回调函数类型
typedef void (*Tim17Callback)(void);

// 保存回调函数指针的全局变量
static Tim17Callback tim17_cb = NULL;   // 保存回调函数指针

// 注册回调函数
void tim17_register_callback(Tim17Callback cb) 
{
    tim17_cb = cb;  // 把传进来的函数指针保存到全局变量
}

// ISR 调用时触发
void tim17_invoke_callback(void) 
{
    if (tim17_cb) {
        tim17_cb();   // 调用用户注册的回调
    }
}

// 注册回调函数
void callback_register_fun(void)
{
  tim17_register_callback(tim17_isr_callback_handler);

}

/********************************************************************************
	**
	*Function Name:void tim17_isr_callback_handler(void)
	*Function : // 业务逻辑函数（回调实现）
	*Input Ref: 
	*Return Ref:NO
	*
*******************************************************************************/
static void tim17_isr_callback_handler(void)
{
   static  uint16_t tm0;
 

    tm0 ++ ;
      
     
	 if(tm0 > 999){//10ms *100 = 1000ms =1s
        tm0 =0;
	    gpro_t.gTimer_smg_counter++;
	
	
		    

        
		
	}
 }





 

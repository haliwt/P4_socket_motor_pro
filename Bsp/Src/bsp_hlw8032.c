#include "bsp.h"

uint8_t hlw8032_rxbuf[HLW8032_DMA_RX_BUFFER_SIZE]={0};

volatile uint8_t hlw8032_rx_tc_flag = 0;

typedef struct {
    uint32_t voltage;
    uint32_t current;
    uint32_t power;
	
} HLW8032_Data;

HLW8032_Data hlw_data;



typedef struct {
    uint32_t v_param, v_reg;
    uint32_t i_param, i_reg;
    uint32_t p_param, p_reg;
} hlw_regs_t;

typedef struct {
    float Kv;  // or alpha_V if using two-point
    float Ki;  // or alpha_I
    float Kp;  // or alpha_P
    float Vb;  // beta_V (optional)
    float Ib;  // beta_I (optional)
    float Pb;  // beta_P (optional)
} hlw_cal_t;



volatile uint8_t  hlw8032_rx_tc_flag ; //= 1;   // 一帧接收完成

/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/
#if 1
void HLW8032_StartDMA(void)
{
  // 禁用DMA
     LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);

	  memset(hlw8032_rxbuf, 0, HLW8032_FRAME_SIZE);

	  // 配置外设和内存地址
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4,
        LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_RECEIVE), // 外设地址
        (uint32_t)hlw8032_rxbuf,                                         // 内存地址
        LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    
    // 清除缓冲区
     
    
     // 设置数据长度（双缓冲总长度）
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4,HLW8032_FRAME_SIZE);
    
    // 使能DMA中断：半传输完成和传输完成
     // 6) Enable DMA IRQ if你要用 HT/TC 中断回调处理
    //LL_DMA_EnableIT_HT(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
    
    // 5. 使能USART1的DMA接收
   // LL_USART_EnableIT_IDLE(USART1);//空闲中断
    LL_USART_Enable(USART1);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);    // 关键：启用通道
    LL_USART_EnableDMAReq_RX(USART1);
   
}
#endif 
/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/
#if  0
void HLW8032_ParseFrame(uint8_t *buf)
{
    // 校验
    uint32_t sum = 0;
    for(int i=0; i<HLW8032_FRAME_LEN-1; i++) sum += buf[i];
    if((sum & 0xFF) != buf[HLW8032_FRAME_LEN-1]) return; // 校验失败

    // 电压寄存器 (示例：第 4~6 字节)
    hlw_data.voltage = ((uint32_t)buf[4] << 16) | ((uint32_t)buf[5] << 8) | buf[6];

    // 电流寄存器 (示例：第 10~12 字节)
    hlw_data.current = ((uint32_t)buf[10] << 16) | ((uint32_t)buf[11] << 8) | buf[12];

    // 功率寄存器 (示例：第 16~18 字节)
    hlw_data.power = ((uint32_t)buf[16] << 16) | ((uint32_t)buf[17] << 8) | buf[18];
}
#endif 

/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/
static uint32_t u24(const uint8_t *b) 
{
    return ((uint32_t)b[0] << 16) | ((uint32_t)b[1] << 8) | (uint32_t)b[2];
}
/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/
static float ratio(uint32_t reg, uint32_t param) 
{
    return (param != 0) ? ((float)reg / (float)param) : 0.0f;
}
/*
	*@brief: single-point convert
	*@note:
	*@param:
	*@retval:
*/
void hlw_convert_sp(const hlw_regs_t *r, const hlw_cal_t *c,float *V, float *I, float *P) 
{
    float rv = ratio(r->v_reg, r->v_param);
    float ri = ratio(r->i_reg, r->i_param);
    float rp = ratio(r->p_reg, r->p_param);
    *V = rv * c->Kv;
    *I = ri * c->Ki;
    *P = rp * c->Kp;
}
/*
	*@brief:  two-point convert (if you decided to use offsets)
	*@note:
	*@param:
	*@retval:
*/
void hlw_convert_tp(const hlw_regs_t *r, const hlw_cal_t *c,float *V, float *I, float *P) 
{
    float rv = ratio(r->v_reg, r->v_param);
    float ri = ratio(r->i_reg, r->i_param);
    float rp = ratio(r->p_reg, r->p_param);
    *V = c->Kv * rv + c->Vb;
    *I = c->Ki * ri + c->Ib;
    *P = c->Kp * rp + c->Pb;
}

/*
	*@brief:  
	*@note:
	*@param:
	*@retval:
*/
uint16_t read_ac_voltage_value(void)
{

    return (uint16_t)hlw_data.voltage;

}

uint8_t read_total_kw_decade_value(void)
{
  
   if(hlw_data.power > 0) return (uint8_t)hlw_data.power;
   else return 0;
   
}

uint8_t read_total_kw_uint_value(void)
{
  
   if(hlw_data.power == 0) return (uint8_t)hlw_data.power;
   
}

/*
	*@brief: IC HLW8032 handler
	*@note:
	*@param:
	*@retval:
*/
void hlw8032_run_process_handler(void)
{

    
	if(hlw8032_rx_tc_flag==1){
	
	   HLW8032_ParseData();
	   hlw8032_rx_tc_flag=0;
	   HLW8032_StartDMA();
	}


	if(gpro_t.gTimer_read_total_w >3){
	  gpro_t.gTimer_read_total_w=0;
	   hlw8032_output_value();
	}

}
/*
	*@brief: interrupt DMA callback
	*@note:
	*@param:
	*@retval:
*/




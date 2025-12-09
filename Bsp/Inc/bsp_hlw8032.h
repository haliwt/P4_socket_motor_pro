#ifndef __BSP_HLW8032_H
#define __BSP_HLW8032_H
#include "main.h"

// DMA缓冲区配置
#define HLW8032_DMA_RX_BUFFER_SIZE  48      // 双缓冲，每个24字节
#define HLW8032_FRAME_SIZE          24      // HLW8032单帧数据长度






extern uint8_t hlw8032_rxbuf[HLW8032_DMA_RX_BUFFER_SIZE];

extern volatile uint8_t  hlw8032_rx_half_flag;

//void USART1_DMA_RX_Init(void);

uint16_t read_ac_voltage_value(void);

uint8_t read_total_kw_decade_value(void);

uint8_t read_total_kw_uint_value(void);




#endif 



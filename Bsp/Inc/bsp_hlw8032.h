#ifndef __BSP_HLW8032_H
#define __BSP_HLW8032_H
#include "main.h"

// DMA缓冲区配置
#define HLW8032_DMA_RX_BUFFER_SIZE  48      // 双缓冲，每个24字节
#define HLW8032_FRAME_SIZE          24      // HLW8032单帧数据长度






extern uint8_t hlw8032_rxbuf[HLW8032_DMA_RX_BUFFER_SIZE];

extern volatile uint8_t  hlw8032_rx_tc_flag;

//void HLW8032_StartDMA(void);


void hlw8032_run_process_handler(void);



#endif 



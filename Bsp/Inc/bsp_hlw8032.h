#ifndef __BSP_HLW8032_H
#define __BSP_HLW8032_H
#include "main.h"


extern volatile uint8_t  hlw8032_rx_done;

void USART1_DMA_RX_Init(void);

uint16_t read_ac_voltage_value(void);

uint8_t read_total_kw_decade_value(void);

uint8_t read_total_kw_uint_value(void);




#endif 




#include "bsp.h"

//====================================================
// 数据结构体
// 在 HLW8032_Data_t 结构体中添加新字段
typedef struct {

    uint8_t status_reg;             // fram[0] 状态寄存器
    uint8_t check_reg;              // fram[1] 检测寄存器
    uint8_t voltage_param_rg[3];   // fram[3-5] 电压参数寄存器
    uint8_t voltage_reg[3];         // fram[6-8] 电压寄存器
    uint8_t current_param_reg[3];   // fram[9-11] 电流参数寄存器
    uint8_t current_reg[3];         // fram[12-14] 电流寄存器
    uint8_t power_param_reg[3];     // fram[15-17] 功率参数寄存器
    uint8_t power_reg[3];           // fram[18-20] 功率寄存器
    uint8_t data_update_reg;        // fram[21] 数据更新寄存器
    uint8_t pf[2];              // fram[22-23] PF寄存器
    uint8_t checksum;           // fram[24] 校验和
} HLW0803_DataFrame_t;



/* 解析后的工程值 */
typedef struct {
    float voltage_param_ref;      // 电压 (V)
    float voltage_ref;
    float  current_param_ref;      // 电流 (A)
    float current_ref;
    float  power_param_ref;        // 功率 (W)
    float  power_ref;
	float    voltage_v;
	float    current_a;
	float    power_w;
    float energy;       // 电能 (kWh)
               // 功率因数
    uint8_t status_ref;     // 状态
    uint8_t data_valid;    // 数据有效标志
    volatile uint8_t dma_tx_half_flag;
	float voltage_factor;
	float current_factor;
	float power_factor;
	
} HLW0803_Measure_t;


HLW0803_DataFrame_t hlw8032_frame_t;
HLW0803_Measure_t   hlw8032_measure_t;

uint8_t copy_hlw8032_buf[48];
uint8_t rx_frame_sum;

static uint8_t parse_hlw8032_frame(const uint8_t* frame,HLW0803_DataFrame_t *frame_out ,HLW0803_Measure_t *mease_out);
/**
  * @brief  开始校正电压,电流,功率系数
  * @param  使用100W,电压 220V ,电流 I= 0.455A,W=100W.
  * @param  
  * @retval
  */
void caliration_hlw8032_factor(void)
{
     
    hlw8032_measure_t.voltage_factor = (hlw8032_measure_t.voltage_param_ref/hlw8032_measure_t.voltage_ref)/220 ;//
    #if DEBUG_FLAG
     printf("votlage_k1 = %0.2f \n",hlw8032_measure_t.voltage_factor);
	#endif 
	hlw8032_measure_t.voltage_factor = (hlw8032_measure_t.current_param_ref/hlw8032_measure_t.current_ref)/0.455 ;//I= 0.455A
    #if DEBUG_FLAG
		printf("current_k2 = %0.2f \n",hlw8032_measure_t.current_factor);
   #endif 

	hlw8032_measure_t.power_factor = (hlw8032_measure_t.power_param_ref/hlw8032_measure_t.power_ref)/100;//100W
     #if DEBUG_FLAG
     printf("power_k3 = %0.2f \n",hlw8032_measure_t.power_factor);
	#endif 
}

/**
  * @brief  查找有效数据帧的起始位置
  * @param  buffer: 待搜索的缓冲区
  * @param  size: 缓冲区大小
  * @retval 有效帧起始索引，-1表示未找到
  */
static int find_frame_start(const uint8_t* buffer)
{
    // HLW8032帧头：stateREG =0x55 ---芯片误差修正正常, checkREG:0x5A --default is data
        uint16_t total_sum=0 ;
        uint8_t i, uint8_data ; 
	    for (i=2 ; i <23; i++)//for (int i = 0; i < size - HLW8032_FRAME_SIZE + 1; i++)
	    {
	         total_sum = buffer[i] + total_sum;
             if(i==22){

			   uint8_data = (uint8_t)total_sum;
			   if(uint8_data == buffer[23]){
			      return 1;

			   	}
			    else{

				   return -1;

				}

             }
				
        }
	    
    
	
    return -1;
}


/**
  * @brief   更快且安全的校验和计算（frame 长度 24，校验 sum = bytes[2..22]） 
  * @param  frame: 24字节数据帧指针
  * @param  data: 数据存储结构体
  * @retval true: 解析成功, false: 解析失败
  */
static  uint8_t hlw8032_calc_checksum(const uint8_t *frame)
{
    uint8_t sum = 0;
    const uint8_t *p = frame + 2;
    for (int i = 0; i < 21; ++i) { /* 2..22 共21字节 */
        sum += p[i];
    }
    return sum;
}

/**
  * @brief  解析HLW8032数据帧
  * @param  frame: 24字节数据帧指针
  * @param  data: 数据存储结构体
  * @retval true: 解析成功, false: 解析失败
  */
static uint8_t parse_hlw8032_frame(const uint8_t* frame,HLW0803_DataFrame_t *frame_out,HLW0803_Measure_t  *measure_out)
{

   
    
    // 4. 解析所有寄存器（小端格式）
    // 4.1 电压参数寄存器 (字节3-5)
    hlw8032_measure_t.voltage_param_ref = ((uint32_t)frame[5] << 16) |((uint32_t)frame[4] << 8)  |(uint32_t)frame[3];
    
    // 4.2 电压寄存器 (字节6-8)
    hlw8032_measure_t.voltage_ref = ((uint32_t)frame[8] << 16) |((uint32_t)frame[7] << 8)  |(uint32_t)frame[6];
    
    // 4.3 电流参数寄存器 (字节9-11)
    hlw8032_measure_t.current_param_ref = ((uint32_t)frame[11] << 16) |((uint32_t)frame[10] << 8) |(uint32_t)frame[9];
    
    // 4.4 电流寄存器 (字节12-14)
   hlw8032_measure_t.current_ref = ((uint32_t)frame[14] << 16) |((uint32_t)frame[13] << 8)  |(uint32_t)frame[12];
    
    // 4.5 功率参数寄存器 (字节15-17)
   hlw8032_measure_t.power_param_ref = ((uint32_t)frame[17] << 16) |((uint32_t)frame[16] << 8)  |(uint32_t)frame[15];

        
    // 4.5 功率寄存器 (字节18-20)
    hlw8032_measure_t.power_ref = ((uint32_t)frame[20] << 16) |((uint32_t)frame[19] << 8)  |(uint32_t)frame[18];
    
	
    
    // 5. 使用校准系数计算物理值
    // 注意：应该使用“参数寄存器”计算高精度的电压电流值
    if(hlw8032_measure_t.voltage_ref !=0){
       hlw8032_measure_t.voltage_v = ((float)hlw8032_measure_t.voltage_param_ref/(float)hlw8032_measure_t.voltage_ref )* HLW8032_VOLTAGE_COEFF;
    }
	else{
       hlw8032_measure_t.voltage_v = 0;
	   
	}

	if(hlw8032_measure_t.current_ref !=0){
    	hlw8032_measure_t.current_a = ((float)hlw8032_measure_t.current_param_ref /(float)hlw8032_measure_t.current_ref)* HLW8032_CURRENT_COEFF;
	}
	else{
        hlw8032_measure_t.current_a = 0;

	}

    if(hlw8032_measure_t.power_ref !=0){
	  hlw8032_measure_t.power_w   = ((float)hlw8032_measure_t.power_param_ref /(float)hlw8032_measure_t.power_ref)* HLW8032_POWER_COEFF;
	  
    }
	else{
      hlw8032_measure_t.power_w = 0 ;
	}
	#if 0
    // 6. 计算功率因数
    if (data->voltage_v > 10.0f && data->current_a > 0.001f) {
        float apparent_power = data->voltage_v * data->current_a;
        if (apparent_power > 0.1f) {
            data->power_factor = data->power_w / apparent_power;
            // 安全钳位 [-1, 1]
            if (data->power_factor > 1.0f) data->power_factor = 1.0f;
            if (data->power_factor < -1.0f) data->power_factor = -1.0f;
        } else {
            data->power_factor = 0.0f;
        }
    } else {
        data->power_factor = 0.0f;
    }
    #endif 
	#if 0
    // 7. 可选：使用“寄存器”值进行交叉验证或快速显示
    float voltage_fast = (float)data->voltage_reg * HLW8032_VOLTAGE_COEFF;
    float current_fast = (float)data->current_reg * HLW8032_CURRENT_COEFF;
    
    // 可以比较两者差异，如果差异过大可能是数据错误
    float voltage_diff = fabs(data->voltage_v - voltage_fast) / data->voltage_v;
    if (voltage_diff > 0.1f) { // 差异超过10%
        data->error_count++;
    }
    
    data->data_valid = true;
	#endif 
    return 1;
}


/**
  * @brief  处理接收到的数据
  * @param  data: 数据存储结构体指针
  * @retval true: 有新数据, false: 无新数据
  */
uint8_t HLW8032_ParseData(void)
{

        //current_buffer = &hlw8032_rxbuf[0];//1.STATE REG original is the "24"
	    //buffer_size = HLW8032_DMA_RX_BUFFER_SIZE ;
	    rx_frame_sum =   hlw8032_calc_checksum(hlw8032_rxbuf);
		 
	    if (rx_frame_sum == hlw8032_rxbuf[23])
	    {
	        // 解析数据帧
	        memcpy(copy_hlw8032_buf,hlw8032_rxbuf,sizeof(hlw8032_rxbuf));
			hlw8032_rxbuf[0]=0;
		    hlw8032_rxbuf[1]=0;
	        parse_hlw8032_frame(copy_hlw8032_buf, &hlw8032_frame_t,&hlw8032_measure_t);
	       
	    }
		else{
           return 2;
		   hlw8032_rx_tc_flag=0;//go on read AC 220 power value 

		   hlw8032_rxbuf[0]=0;
		   hlw8032_rxbuf[1]=0;
           HLW8032_StartDMA();
		}
       
       return 1;
}

/**
  * @brief  返回一个DMA USART TX HALF FLAG
  * @param  data: 数据存储结构体指针
  * @retval true: 有新数据, false: 无新数据
  */

 
#if 0
/**
  * @brief  重置数据接收
  */
void HLW8032_ResetReception(void)
{
    // 禁用DMA
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
    
    // 清除缓冲区
    memset(dma_rx_buffer, 0, HLW8032_DMA_RX_BUFFER_SIZE);
    
    // 重置DMA指针
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)dma_rx_buffer);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, HLW8032_DMA_RX_BUFFER_SIZE);
    
    // 重新使能DMA
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    
    // 重置状态
    active_buffer = 0;
    frame_ready = false;
    memset(&hlw8032_data, 0, sizeof(HLW8032_Data_t));
}
#endif 

/**
  * @brief  printf output voltage ,current ,powe value 
  * @param  data: 数据存储结构体指针
  * @retval true: 有新数据, false: 无新数据
  */
void hlw8032_output_value(void)
{ 
   #if DEBUG_FLAG
   printf("voltage = %0.2f\n",hlw8032_measure_t.voltage_v);
   printf("current = %0.2f\n",hlw8032_measure_t.current_a);
   printf("power_w = %0.2f\n",hlw8032_measure_t.power_w);
  #endif 
}


#if 0
/**
  * @brief 计算工程值
  * @note 这里需要根据HLW0803数据手册的换算公式进行转换
  *       以下为示例换算，实际公式请参考HLW0803手册
  */
void HLW0803_CalculateValues(void)
{
    uint32_t raw_value;
    float voltage_coef, current_coef, power_coef;
    
    /* 示例：将3字节数据转换为32位整数 */
    raw_value = ((uint32_t)hlw0803_raw_data.voltage[0] << 16) |
                ((uint32_t)hlw0803_raw_data.voltage[1] << 8) |
                hlw0803_raw_data.voltage[2];
    
    /* 示例：电压换算系数 (需要根据实际CT/PT变比调整) */
    voltage_coef = 1.0; // 默认系数，实际应用中应根据参数寄存器调整
    
    /* 使用功率参数寄存器进行校准 */
    if(hlw0803_raw_data.power_param[0] != 0)
    {
        /* 示例：假设参数寄存器存储的是标定系数 */
        power_coef = (float)((hlw0803_raw_data.power_param[0] << 16) |
                            (hlw0803_raw_data.power_param[1] << 8) |
                            hlw0803_raw_data.power_param[2]) / 10000.0;
    }
    else
    {
        power_coef = 1.0; // 默认值
    }
    
    /* 计算电压 (示例公式，请参考实际手册) */
    hlw0803_measure.voltage = (float)raw_value * voltage_coef;
    
    /* 计算电流 */
    raw_value = ((uint32_t)hlw0803_raw_data.current[0] << 16) |
                ((uint32_t)hlw0803_raw_data.current[1] << 8) |
                hlw0803_raw_data.current[2];
    
    /* 电流换算系数 (考虑CT变比) */
    current_coef = 1.0; // 默认系数
    hlw0803_measure.current = (float)raw_value * current_coef;
    
    /* 计算功率 (使用功率参数寄存器校准) */
    raw_value = ((uint32_t)hlw0803_raw_data.power[0] << 16) |
                ((uint32_t)hlw0803_raw_data.power[1] << 8) |
                hlw0803_raw_data.power[2];
    
    hlw0803_measure.power = (float)raw_value * power_coef;
    
    /* 计算功率因数 */
    if(hlw0803_raw_data.pf[0] != 0 || hlw0803_raw_data.pf[1] != 0)
    {
        uint16_t pf_raw = (hlw0803_raw_data.pf[0] << 8) | hlw0803_raw_data.pf[1];
        hlw0803_measure.pf = (float)pf_raw / 1000.0; // 假设PF值放大1000倍
    }
    else
    {
        hlw0803_measure.pf = 1.0;
    }
    
    /* 更新状态 */
    hlw0803_measure.status = hlw0803_raw_data.status;
    hlw0803_measure.data_valid = true;
}


/**
  * @brief  处理DMA半缓冲区
  **
  * @brief 计算工程值
  * @note 这里需要根据HLW0803数据手册的换算公式进行转换
  *       以下为示例换算，实际公式请参考HLW0803手册
  *
  */
static void Process_DMA_Half(uint32_t start, uint32_t end)
{
    for(uint32_t i = start; i < end; i++)
    {
        uint8_t byte = hlw8032_rxbuf[i];//dma_state.buffer[i];
       // memcpy(dma_state.buffer,hlw8032_rxbuf,24);
        
        /* 将字节存入帧缓存 */
        dma_state.frame_buffer[dma_state.frame_index++] = byte;
        
        /* 检查是否收到完整帧 */
        if(dma_state.frame_index >= HLW0803_FRAME_SIZE)
        {
            /* 验证帧有效性 */
            if(Validate_Frame(dma_state.frame_buffer))
            {
                /* 解析帧数据 */
                parse_hlw8032_frame(dma_state.frame_buffer);
                dma_state.frame_assembled = true;
            }
            
            /* 重置帧索引（注意：这里使用滑动窗口） */
            dma_state.frame_index = 0;
            
            /* 尝试从当前字节重新开始组帧 */
            if(i + 1 < end)
            {
                dma_state.frame_buffer[0] = dma_state.buffer[i + 1];
                dma_state.frame_index = 1;
            }
        }
    }
}

#endif 

#if 0
/**
  * @brief  添加到搜索缓冲区（处理跨缓冲区问题）
  */
static void Add_To_Search_Buffer(uint8_t *data, uint32_t length)
{
    /* 检查缓冲区是否足够 */
    if(frame_parser.search_index + length > sizeof(frame_parser.search_buffer))
    {
        /* 缓冲区满，保留最后可能包含不完整帧的部分 */
        uint32_t keep = HLW0803_FRAME_SIZE;
        if(frame_parser.search_index > keep)
        {
            memmove(frame_parser.search_buffer,
                   &frame_parser.search_buffer[frame_parser.search_index - keep],
                   keep);
            frame_parser.search_index = keep;
        }
    }
    
    /* 添加新数据 */
    memcpy(&frame_parser.search_buffer[frame_parser.search_index], data, length);
    frame_parser.search_index += length;
}


/**
  * @brief  处理搜索缓冲区中的帧
  */
static void Process_Search_Buffer(void)
{
    uint32_t i = 0;
    
    /* 在搜索缓冲区中滑动查找 */
    while(i <= frame_parser.search_index - HLW0803_FRAME_SIZE)
    {
        uint8_t *potential_frame = &frame_parser.search_buffer[i];
        
        /* 快速预检查 */
       
         /* 解析帧 */
          if(parse_hlw8032_frame(&hlw8032_rxbuf))
          {
                    /* 成功解析，标记帧就绪 */
                    hlw0803_frame_ready = true;
                    
                    /* 从缓冲区移除已处理的帧 */
                    uint32_t remaining = frame_parser.search_index - (i + HLW0803_FRAME_SIZE);
                    if(remaining > 0)
                    {
                        memmove(frame_parser.search_buffer,
                               &frame_parser.search_buffer[i + HLW0803_FRAME_SIZE],
                               remaining);
                    }
                    frame_parser.search_index = remaining;
                    
                    /* 重置索引，因为缓冲区内容改变了 */
                    i = 0;
                    continue;
           }
            
        /* 如果不是有效帧，移动到下一个字节 */
        i++;
    }
    
    /* 清理搜索缓冲区，保留最后可能的不完整帧 */
    if(frame_parser.search_index > HLW0803_FRAME_SIZE)
    {
        uint32_t keep = frame_parser.search_index;
        if(keep > HLW0803_FRAME_SIZE)
        {
            keep = HLW0803_FRAME_SIZE;
            memmove(frame_parser.search_buffer,
                   &frame_parser.search_buffer[frame_parser.search_index - keep],
                   keep);
            frame_parser.search_index = keep;
        }
    }
}


/**
  * @brief  处理新接收的DMA数据
  */
void Process_New_DMA_Data(uint32_t start, uint32_t end)
{
    uint32_t length = end - start;
    
    if(length == 0) return;
    
    /* 将新数据添加到搜索缓冲区 */
    Add_To_Search_Buffer(&hlw8032_rxbuf[start], length);
    
    /* 在搜索缓冲区中查找并处理完整帧 */
    Process_Search_Buffer();
}

#endif 

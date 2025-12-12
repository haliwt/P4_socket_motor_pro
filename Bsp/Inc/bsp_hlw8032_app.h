#ifndef __BSP_HLW8032_APP_H
#define __BSP_HLW8032_APP_H
#include "main.h"

#define HLW0803_FRAME_SIZE     24      // HLW0803数据帧长度
#define HLW0803_BUFFER_SIZE    (HLW0803_FRAME_SIZE * 2) // 双缓冲

// ===========================================
// 电流,电压,功率测量部分---电压系数,电流系数,功率系数
// ===========================================
// 需要你确认的电压分压参数
#define HLW8032_VOLTAGE_COEFF     1.14

#define HLW8032_CURRENT_COEFF     82.21

#define  HLW8032_POWER_COEFF      0.015

// 校准系数（必须根据实际硬件调整）
//extern float HLW8032_VOLTAGE_COEFF;    // 电压系数
//extern float HLW8032_CURRENT_COEFF;    // 电流系数
///extern float HLW8032_POWER_COEFF;      // 功率系数



///* 私有变量 */
//static volatile struct {
//    uint8_t buffer[HLW0803_BUFFER_SIZE];      // DMA双缓冲
//    uint32_t write_index;                      // DMA当前写入位置
//    uint8_t frame_buffer[HLW0803_FRAME_SIZE];  // 完整帧缓存
//    uint8_t frame_index;                       // 帧缓存索引
//    bool frame_assembled;                      // 帧组装完成标志
//} dma_state = {0};


///* 私有状态 */
//typedef enum {
//    FRAME_SEARCH,      // 搜索帧起始
//    FRAME_ASSEMBLING,  // 组帧中
//    FRAME_COMPLETE     // 帧完成
//} FrameState_t;

//static struct {
//    FrameState_t state;
//    uint8_t frame_buffer[HLW0803_FRAME_SIZE];
//    uint8_t frame_index;
//    uint32_t last_byte_time;
//    uint8_t search_buffer[HLW0803_FRAME_SIZE * 2];
//    uint16_t search_index;
//}frame_parser = {
//    .state = FRAME_SEARCH,
//    .frame_index = 0,
//    .search_index = 0
//  };



/* 外部变量声明 */
//extern volatile uint8_t hlw0803_rx_buffer[HLW0803_BUFFER_SIZE];
//extern volatile uint32_t hlw0803_rx_index;
//extern volatile bool hlw0803_frame_ready;
//extern HLW0803_DataFrame_t hlw0803_raw_data;
//extern HLW0803_Measure_t hlw0803_measure;


// ===========================================
// 函数声明
// ===========================================
/* 函数声明 */
//void HLW0803_Init(void);
//void HLW0803_StartReceive(void);
//bool HLW0803_ParseFrame(uint8_t *buffer);
//void HLW0803_CalculateValues(void);
//uint8_t HLW0803_CalculateChecksum(uint8_t *data, uint32_t len);

void caliration_hlw8032_factor(void);

void HLW8032_ParseData(void);

void hlw8032_output_value(void);

#endif 



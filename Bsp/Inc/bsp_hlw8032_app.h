#ifndef __BSP_HLW8032_APP_H
#define __BSP_HLW8032_APP_H
#include "main.h"

#define HLW0803_FRAME_SIZE     24      // HLW0803数据帧长度
#define HLW0803_BUFFER_SIZE    (HLW0803_FRAME_SIZE * 2) // 双缓冲

// ===========================================
// 电流,电压,功率测量部分---电压系数,电流系数,功率系数
// ===========================================
// 需要你确认的电压分压参数
#define VOLTAGE_COEFFICIENT        

#define CURRENT_COEFFICIENT  

#define POWER_COEFFICINET 

// 校准系数（必须根据实际硬件调整）
extern float HLW8032_VOLTAGE_COEFF;    // 电压系数
extern float HLW8032_CURRENT_COEFF;    // 电流系数
extern float HLW8032_POWER_COEFF;      // 功率系数
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
    uint32_t voltage_param_ref;      // 电压 (V)
    uint32_t voltage_ref;
    uint32_t  current_param_ref;      // 电流 (A)
    uint32_t current_ref;
    uint32_t  power_param_ref;        // 功率 (W)
    uint8_t  power_ref;
	float    voltage_v;
	float    current_a;
	float    power_w;
    float energy;       // 电能 (kWh)
               // 功率因数
    uint8_t status_ref;     // 状态
    bool data_valid;    // 数据有效标志
} HLW0803_Measure_t;


/* 私有变量 */
static volatile struct {
    uint8_t buffer[HLW0803_BUFFER_SIZE];      // DMA双缓冲
    uint32_t write_index;                      // DMA当前写入位置
    uint8_t frame_buffer[HLW0803_FRAME_SIZE];  // 完整帧缓存
    uint8_t frame_index;                       // 帧缓存索引
    bool frame_assembled;                      // 帧组装完成标志
} dma_state = {0};


/* 私有状态 */
typedef enum {
    FRAME_SEARCH,      // 搜索帧起始
    FRAME_ASSEMBLING,  // 组帧中
    FRAME_COMPLETE     // 帧完成
} FrameState_t;

static struct {
    FrameState_t state;
    uint8_t frame_buffer[HLW0803_FRAME_SIZE];
    uint8_t frame_index;
    uint32_t last_byte_time;
    uint8_t search_buffer[HLW0803_FRAME_SIZE * 2];
    uint16_t search_index;
}frame_parser = {
    .state = FRAME_SEARCH,
    .frame_index = 0,
    .search_index = 0
  };



/* 外部变量声明 */
extern volatile uint8_t hlw0803_rx_buffer[HLW0803_BUFFER_SIZE];
extern volatile uint32_t hlw0803_rx_index;
extern volatile bool hlw0803_frame_ready;
extern HLW0803_DataFrame_t hlw0803_raw_data;
extern HLW0803_Measure_t hlw0803_measure;


// ===========================================
// 函数声明
// ===========================================
/* 函数声明 */
//void HLW0803_Init(void);
//void HLW0803_StartReceive(void);
//bool HLW0803_ParseFrame(uint8_t *buffer);
//void HLW0803_CalculateValues(void);
//uint8_t HLW0803_CalculateChecksum(uint8_t *data, uint32_t len);
uint8_t HLW8032_ProcessData(HLW8032_Data_t* data)


void Process_New_DMA_Data(uint32_t start, uint32_t end);

uint8_t HLW8032_Read_DMARxHalf_Flag(void);
	
#endif 



#ifndef __BSP_INA219_H
#define __BSP_INA219_H
#include "main.h"

#define SCL_H()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_8)
#define SCL_L()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_8)

#define SDA_H()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7)
#define SDA_L()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7)

#define SDA_READ()  (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_7))


#define INA219_ADDR   0x40  
#define INA219_WRITE_ADDR      0xC0
#define INA219A_READ_ADDR      0x40


// INA219 I2C 地址（默认A0=A1=GND）
#define INA219_ADDRESS          0x40

// INA219 寄存器地址
#define INA219_REG_CONFIG       0x00
#define INA219_REG_SHUNTV       0x01
#define INA219_REG_BUSV         0x02
#define INA219_REG_POWER        0x03
#define INA219_REG_CURRENT      0x04
#define INA219_REG_CALIBRATION  0x05

// 系统参数
#define SHUNT_RESISTOR          0.01f     // 分流电阻 0.01Ω
#define MAX_CURRENT             4.0f      // 最大电流 4A
#define CURRENT_LSB             0.001f    // 电流分辨率 1mA/bit
#define CAL_VALUE               4096      // 计算得到的校准值

// 配置寄存器设置（BRNG=0(16V), PGA=±40mV, ADC=12位）
#define INA219_CONFIG           (0x2000 | 0x1800 | 0x07FF)
// 具体: 
// BRNG(13)=0: 16V范围
// PG(11-12)=11: ±40mV
// BADC(7-10)=1111: 12位
// SADC(3-6)=1111: 12位
// MODE(0-2)=111: 连续测量所有

// 配置寄存器值
//#define INA219_CONFIG_VALUE      0x399F    // ±40mV, 12位, 连续测量

// 错误代码
#define INA219_OK                0
#define INA219_ERROR             1
#define INA219_TIMEOUT           2


typedef struct {
    float bus_voltage;     // 总线电压 (V)
    float shunt_voltage;   // 分流电压 (mV)
    float current;         // 电流 (A)
    float power;           // 功率 (W)
    float load_voltage;    // 负载电压 (V) = 总线电压 - 分流电压
} INA219_Data;

// 函数声明
//uint8_t INA219_Init(I2C_HandleTypeDef *hi2c);
//uint8_t INA219_Calibrate(I2C_HandleTypeDef *hi2c);
//INA219_Data INA219_ReadAll(I2C_HandleTypeDef *hi2c);
//float INA219_GetBusVoltage(I2C_HandleTypeDef *hi2c);
//float INA219_GetShuntVoltage(I2C_HandleTypeDef *hi2c);
//float INA219_GetCurrent(I2C_HandleTypeDef *hi2c);
//float INA219_GetPower(I2C_HandleTypeDef *hi2c);
//void INA219_Reset(I2C_HandleTypeDef *hi2c);

void INA219_I2C_GPIO_Init(void);

uint8_t INA219_Init(void) ;

uint8_t INA219_Calibrate(void);


uint8_t INA219_TestConnection(void);

float INA219_GetPower(void) ;

float INA219_ReadPower_mW(void);

float INA219_GetCurrent(void) ;

float INA219_GetBusVoltage(void);

float INA219_GetShuntVoltage(void) ;
;


#endif 


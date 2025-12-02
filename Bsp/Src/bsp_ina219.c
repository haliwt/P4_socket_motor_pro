#include "bsp.h"




static uint8_t INA219_Calibrate(void) ;
static uint8_t INA219_WriteRegister(uint8_t reg, uint16_t value) ;
static void INA219_Reset(void) ;

/*
	*@brief
	*@note:
	*@param:
*/
void INA219_I2C_GPIO_Init(void)
{
    // 打开 GPIOB 时钟
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

    // 配置 PB7 (SCL) 和 PB9 (SDA) 为开漏输出，带上拉
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LL_GPIO_PIN_7 | LL_GPIO_PIN_8;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 默认拉高
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_8);
}


/*
	*@brief: I2C START 
	*@note:
	*@param:
	*@retval:
*/
void I2C_Start(void)
{
    SDA_H();
    SCL_H();
    delay_us(5);
    SDA_L();   // SDA 从高到低，SCL 保持高
    delay_us(5);
    SCL_L();  //时钟线拉低
}
/*
	*@brief: I2C STAOP 
	*@note:
	*@param:
*/
void I2C_Stop(void)
{
    SCL_L();
    SDA_L();
    delay_us(5);
    SCL_H();     //时钟线拉高
    delay_us(5);
    SDA_H();   // SDA 从低到高，SCL 保持高
    delay_us(5);
}

/*
	*@brief: read  I2C Acknowledge
	*@note:  Acknowledge is low is answer signal
	*@param:
	*@return : answer is "0" ,don't answer is "1"
*/

uint8_t I2C_WaitAck(void)
{
    uint8_t ack;

    SDA_H(); // 释放 SDA
    delay_us(2);
    SCL_H();
    delay_us(5);
    ack = SDA_READ(); // 0 = ACK, 1 = NACK, SDA input GPIO 
    SCL_L();
    return ack;
}

/*
	*@brief: I2C send one byte  
	*@note:  from MSB bit 7 the first 
	*@param:
*/
uint8_t I2C_WriteOneByte(uint8_t data)
{
    uint8_t i;
	for (i = 0; i < 8; i++) {
        if (data & 0x80) SDA_H();
		else SDA_L();
		
        delay_us(2);
        SCL_H(); //sclock is pull high write one bit 
        delay_us(5);
        SCL_L(); //sclock is pull low maybe changed for next bit prepare.
        delay_us(2);
        data <<= 1;//串口一位一位发送 . 从最高位开始.
    }

	return I2C_WaitAck();
}

/*
	*@brief: send I2C Acknowledge
	*@note:  Acknowledge is low is answer signal
	*@param: ack =1 isnot ack ,ack =0 is acknowledge signal
	*@return : 
*/
void I2C_SendAck(uint8_t ack)
{
    if(ack) SDA_H(); //Acknowledge is "0" 
	else SDA_L(); // ack=0 → ACK, ack=1 → NACK
    delay_us(2);
    SCL_H();
    delay_us(5);
    SCL_L();
    SDA_H(); // 释放 SDA
}

/*
	*@brief: read I2C one byte
	*@note:  Acknowledge is low is answer signal
	*@param: 
	*@return : receive data 
*/
uint8_t I2C_ReadOneByte(uint8_t ack)
{
    uint8_t data = 0,i;

    SDA_H(); // 释放 SDA，准备读
    for (i = 0; i < 8; i++) {
        data <<= 1; //left shift ->>this is the first recieve MSB .
        SCL_H();
        delay_us(5);
        if (SDA_READ()) data |= 0x01;
        SCL_L();
        delay_us(2);
    }

    I2C_SendAck(ack); // ack=0 → 发送 ACK，ack=1 → 发送 NACK
    return data;
}
/*
	*@brief: read I2C one byte
	*@note:// 向器件 addr 写入一个寄存器 reg，再读一个字节
	*@param: 
	*@return : receive data 
*/
uint8_t I2C_WriteRead(uint8_t addr, uint8_t reg)
{
    uint8_t data;

    I2C_Start();
    I2C_WriteOneByte(addr);//I2C_WriteOneByte(addr << 1);   // 发送器件地址 + 写位
    I2C_WaitAck();
    I2C_WriteOneByte(reg);         // 发送寄存器地址
    I2C_WaitAck();

    I2C_Start();
    I2C_WriteOneByte(addr);//I2C_WriteOneByte((addr << 1) | 0x01); // 发送器件地址 + 读位
    I2C_WaitAck();
    data = I2C_ReadOneByte(1);    // 读一个字节，最后发送 NACK
    I2C_Stop();

    return data;
}



/*
	*@brief: 
	*@note:
	*@param: 
	*@return :
*/
void I2C_WriteOneData(uint8_t addr, uint8_t data)
{
    I2C_Start();
    I2C_WriteOneByte(addr);   // TM1650 地址 + 写位
    I2C_WaitAck();
    I2C_WriteOneByte(data);
    I2C_WaitAck();
    I2C_Stop();
}
/*
	*@brief: // 写入多个字节
	*@note:
	*@param: 
	*@return :
*/
uint8_t I2C_WriteMoreData(uint8_t addr, uint8_t *data, uint8_t len) 
{
    uint8_t i;
    
    I2C_Start();//SoftI2C_Start(hi2c);
    
    // 发送设备地址（写模式）
    if (I2C_WriteOneByte(addr << 1)) {
        I2C_Stop();//SoftI2C_Stop(hi2c);
        return 0;
    }
    
    // 发送数据
    for (i = 0; i < len; i++) {
        if (I2C_WriteOneByte(data[i])) {
            I2C_Stop();//SoftI2C_Stop(hi2c);
            return 0;
        }
    }
    
    I2C_Stop();//SoftI2C_Stop(hi2c);
    return 1;
}


/*
	*@brief:  读取寄存器
	*@note:
	*@param: 
	*@return :
*/
uint8_t I2C_ReadRegister(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) 
{
    I2C_Start();//SoftI2C_Start(hi2c);
    
    // 发送设备地址（写模式）+ 寄存器地址
    if (I2C_WriteOneByte(addr << 1)) {
        I2C_Stop();//SoftI2C_Stop(hi2c);
        return 0;
    }
    
    // 发送要读取的寄存器地址
    if (I2C_WriteOneByte(reg)) {
        I2C_Stop();//SoftI2C_Stop(hi2c);
        return 0;
    }
    
    // 重新启动并读取数据
    I2C_Start(); //SoftI2C_Start(hi2c);
    
    // 发送设备地址（读模式）
    if (I2C_WriteOneByte((addr << 1) | 0x01)) {
        I2C_Stop();//SoftI2C_Stop(hi2c);
        return 0;
    }
    
    // 读取数据
    for (uint8_t i = 0; i < len; i++) {
        if (i == (len - 1)) {
            data[i] = I2C_ReadOneByte(0);  // 最后一个字节发送NACK
        } else {
            data[i] = I2C_ReadOneByte(1);  // 发送ACK
        }
    }
    
    I2C_Stop();//SoftI2C_Stop(hi2c);
    return 1;
}

//IC INA219 
/*
	*@brief: 写入16位寄存器
	*@note:
	*@param: 
	*@return :
*/
static uint8_t INA219_WriteRegister(uint8_t reg, uint16_t value) 
{
    uint8_t data[3];
    data[0] = reg;
    data[1] = (value >> 8) & 0xFF;  // 高字节
    data[2] = value & 0xFF;         // 低字节
    
  // if (HAL_I2C_Master_Transmit(ina219_hi2c, INA219_ADDRESS << 1, data, 3, 100) != HAL_OK) {
//        return 0;
//    }
    I2C_WriteMoreData(INA219_ADDRESS ,data,3);
    return 1;
}
/*
	*@brief: 读取16位寄存器
	*@note:
	*@param: 
	*@return :
*/
static uint16_t INA219_ReadRegister(uint8_t reg) 
{
    uint8_t data[2] = {0, 0};
    
    if(!I2C_ReadRegister(INA219_ADDRESS,reg,data,2)){
        return 0xFFFF;
	}
	return (data[0] << 8) | data[1];
}
/*
	*@brief: // 测试设备连接
	*@note:
	*@param: 
	*@return :
*/
uint8_t INA219_TestConnection(void) 
{
    
    uint16_t config = INA219_ReadRegister(INA219_REG_CONFIG);
    return (config != 0xFFFF);
}
/*
	*@brief:  初始化INA219
	*@note:
	*@param: 
	*@return :
*/
uint8_t INA219_Init(void) 
{
   
    
    // 1. 重置设备
    INA219_Reset();
    vTaskDelay(pdMS_TO_TICKS(10));//HAL_Delay(10);
    
    // 2. 配置寄存器
    if (!INA219_WriteRegister(INA219_REG_CONFIG, INA219_CONFIG)) {
        return 0;
    }
    vTaskDelay(pdMS_TO_TICKS(10));//HAL_Delay(10);
    
    // 3. 校准
    if (!INA219_Calibrate()) {
        return 0;
    }
    vTaskDelay(pdMS_TO_TICKS(10));//HAL_Delay(10);
    
    return 1;
}
/*
	*@brief:  校准INA219
	*@note:
	*@param: 
	*@return :
*/
static uint8_t INA219_Calibrate(void) 
{
  
   // 写入校准值
    if (!INA219_WriteRegister(INA219_REG_CALIBRATION, CAL_VALUE)) {
        return 0;
    }
    
    // 验证校准值
    uint16_t cal_read = INA219_ReadRegister(INA219_REG_CALIBRATION);
    if (cal_read == CAL_VALUE) {
        return 1;
    }
    
    return 0;
}
/*
	*@brief:  初始化INA219
	*@note:
	*@param: 
	*@return :
*/

// 重置INA219
static void INA219_Reset(void) 
{
   // 配置寄存器的最高位(RST)设为1进行重置
    INA219_WriteRegister(INA219_REG_CONFIG, 0x8000);
}
/*
	*@brief:  读取总线电压 (V)
	*@note:
	*@param: 
	*@return :
*/
float INA219_GetBusVoltage(void) 
{
   
    uint16_t value = INA219_ReadRegister(INA219_REG_BUSV);
    
    // 总线电压寄存器格式: D15-D3 = 电压值，D2=CNVR，D1=OVF，D0保留
    value = (value >> 3);  // 右移3位，丢弃状态位
    float voltage = value * 0.004f;  // 1 LSB = 4mV
    return voltage;
}
/*
	*@brief:  读取分流电压 (mV)
	*@note:
	*@param: 
	*@return :
*/
float INA219_GetShuntVoltage(void) 
{
   
    int16_t value = (int16_t)INA219_ReadRegister(INA219_REG_SHUNTV);
    float voltage = value * 0.01f;  // 1 LSB = 10μV = 0.01mV
    return voltage;  // 单位: mV
}
/*
	*@brief:  读取电流 (A)
	*@note:
	*@param: 
	*@return :
*/
float INA219_GetCurrent(void) 
{
   
    int16_t value = (int16_t)INA219_ReadRegister(INA219_REG_CURRENT);
    float current = value * CURRENT_LSB;  // 乘以电流LSB
    return current;  // 单位: A
}
/*
	*@brief:  读取功率 (W)
	*@note:
	*@param: 
	*@return :
*/
float INA219_GetPower(void) 
{
    
    uint16_t value = INA219_ReadRegister(INA219_REG_POWER);
    float power = value * 20 * CURRENT_LSB;  // Power_LSB = 20 * Current_LSB
    return power;  // 单位: W
}
/*
	*@brief: 读取所有数据
	*@note:
	*@param: 
	*@return : receive data 
*/
INA219_Data INA219_ReadAll(void) 
{
    INA219_Data data;
    
    // 读取各项数据
    data.bus_voltage = INA219_GetBusVoltage();
    data.shunt_voltage = INA219_GetShuntVoltage();
    data.current = INA219_GetCurrent();
    data.power = INA219_GetPower();
    
    // 计算负载电压（考虑分流电阻压降）
    // 注意：分流电压单位是mV，需要转换为V
    data.load_voltage = data.bus_voltage - (data.shunt_voltage / 1000.0f);
    
    return data;
}


float INA219_ReadPower_mW(void)
{
   return INA219_GetPower()*2.0f; //20mW/LSB 
}


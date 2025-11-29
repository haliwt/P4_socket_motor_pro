#include "bsp.h"


/*
	*@brief
	*@note:
	*@param:
*/
void I2C_GPIO_Init(void)
{
    // 打开 GPIOB 时钟
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

    // 配置 PB7 (SCL) 和 PB9 (SDA) 为开漏输出，带上拉
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LL_GPIO_PIN_7 | LL_GPIO_PIN_9;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 默认拉高
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_9);
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
	*@brief: I2C send one byte  
	*@note:  from MSB bit 7 the first 
	*@param:
*/
void I2C_SendByte(uint8_t data)
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
uint8_t I2C_ReadByte(uint8_t ack)
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
    I2C_SendByte(addr);//I2C_SendByte(addr << 1);   // 发送器件地址 + 写位
    I2C_WaitAck();
    I2C_SendByte(reg);         // 发送寄存器地址
    I2C_WaitAck();

    I2C_Start();
    I2C_SendByte(addr);//I2C_SendByte((addr << 1) | 0x01); // 发送器件地址 + 读位
    I2C_WaitAck();
    data = I2C_ReadByte(1);    // 读一个字节，最后发送 NACK
    I2C_Stop();

    return data;
}



/*
	*@brief: 
	*@note:
	*@param: 
	*@return :
*/
void TM1650_Write(uint8_t addr, uint8_t data)
{
    I2C_Start();
    I2C_SendByte(addr);   // TM1650 地址 + 写位
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
}



#include "bsp.h"


// --- 写一个字节到 TM1639 ---
void TM1639_WriteByte(uint8_t data)
{
   uint8_t i;

	for(i = 0; i < 8; i++) {
        SCLK_LOW();
        TM1639_Delay();

        if (data & 0x01) {
            DIO_HIGH();
        } else {
            DIO_LOW();
        }
        data >>= 1;

        TM1639_Delay();
        SCLK_HIGH();
        TM1639_Delay();
    }
}

// --- 发送命令 ---
void TM1639_SendCommand(uint8_t cmd)
{
    STB_LOW();
    TM1639_WriteByte(cmd);
    STB_HIGH();
}

// --- 写数据到某个地址 ---
void TM1639_WriteData(uint8_t addr, uint8_t data)
{
    STB_LOW();
    TM1639_WriteByte(0xC0 | addr); // 地址命令
    TM1639_WriteByte(data);
    STB_HIGH();
}

// --- 初始化 TM1639 ---
void TM1639_Init(void)
{
    //TM1639_GPIO_Init();

    // 设置显示模式：自动地址增加
    TM1639_SendCommand(0x40);

    // 设置显示开，亮度最大
    TM1639_SendCommand(0x8F);

    // 清屏
    for (uint8_t i = 0; i < 16; i++) {
        TM1639_WriteData(i, 0x00);
    }
}



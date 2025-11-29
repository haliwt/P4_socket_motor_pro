#include "bsp.h"

// 数码管段码表�?0-9的显示码
const uint8_t TM1639_Number_Table[] = {
    0xF3, // 0: 0011 1111 --0x3F  （h,g,f,e,d,c,b,a--0x3F
    0x60, // 1: 0000 0110 --0x06--写数据式从低位开始，向高位开始写
    0xB5, // 2: 0101 1011 --0x5B
    0xF4, // 3: 0100 1111 --0x4F
    0x66, // 4: 0110 0110 --0x66
    0xD6, // 5: 0110 1101 --0x6D
    0xD7, // 6: 0111 1101  --0x7D 
    0x70, // 7: 0000 0111  --0x07
    0xF7, // 8: 0111 1111  --0x7F
    0xF6  // 9: 0110 1111  --0x6F
};

// 字母和特殊字符显示码
static const uint8_t TM1639_Char_Table[] = {
    0x67, // H: 0111 0110 (h,g,f,e,d,c,b,a)
    0x36, // °: 0110 0011 (h,g,f,e,d,c,b,a)
    0x93, // C: 0011 1001 (h,g,f,e,d,c,b,a)
    0x05  // RH的H部分: 0101 0000 (e,g)
};

#define TM1639_CHAR_H 				TM1639_Char_Table[0]
#define TM1639_CHAR_DEGREE 			TM1639_Char_Table[1]
#define TM1639_CHAR_C 				TM1639_Char_Table[2]
#define TM1639_CHAR_RH 				TM1639_Char_Table[3]

#define TM1639_DOT 0x08 // 小数点段�?,from low position start

static void TM1639_Display_ON_OFF(uint8_t status);
static void TM1639_DISP_ALL_SMG_STATE(uint8_t data);



/**
 * @brief  TM1639写入�?个字�?
 * @param  byte: 要写入的字节
 * @retval None
 */
static void TM1639_Write_Byte(uint8_t byte)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        TM1639_CLK_SetLow();
        //delay_us(2); //is big error .DATA.2025.06.13
        
        if(byte & 0x01)
            TM1639_DIO_SetHigh(); //写入数据 �?1�?
        else
            TM1639_DIO_SetLow(); //写入数据 �?0�?
            
       // delay_us(2);//is big error .DATA.2025.06.13
        TM1639_CLK_SetHigh();
       // delay_us(2);//is big error .DATA.2025.06.13
        byte >>= 1;
    }
}

/**
 * @brief  TM1639�?始信�?
 * @param  None
 * @retval None
 */
static void TM1639_Start(void)
{
    TM1639_STB_SetHigh();
    delay_us(2);
    TM1639_CLK_SetHigh();
    delay_us(2);
    TM1639_STB_SetLow();
    delay_us(2);
}

/**
 * @brief  TM1639停止信号
 * @param  None
 * @retval None
 */
static void TM1639_Stop(void)
{
    TM1639_CLK_SetLow();
    delay_us(2);
    TM1639_DIO_SetLow();
    delay_us(2);
    TM1639_STB_SetHigh();
    delay_us(2);
}

/**
 * @brief  初始化TM1639
 * @param  None
 * @retval None
 */
void TM1639_Init(void)
{
    // 设置数据命令：自动地�?增加
    TM1639_Start();
    TM1639_Write_Byte(TM1639_CMD_DATA);
    TM1639_Stop();
    
    // 设置显示控制：显示开，最大亮�?
    //TM1639_Display_ON_OFF(1);
    //TM1639_Set_Brightness(TM1639_BRIGHTNESS_MAX);
    TM1639_DISP_ALL_SMG_STATE(1);
}

/**
 * @brief  设置显示亮度
 * @param  bright: 亮度级别(0-7)
 * @retval None
 */
void TM1639_Set_Brightness(uint8_t bright)
{
    if(bright > TM1639_BRIGHTNESS_MAX)
        bright = TM1639_BRIGHTNESS_MAX;
        
    TM1639_Start();
    TM1639_Write_Byte(TM1639_CMD_DISPLAY | TM1639_DISPLAY_ON | bright);
    TM1639_Stop();
}

/**
 * @brief  显示�?关控�?
 * @param  status: 1-�?显示�?0-关显�?
 * @retval None
 */
static void TM1639_Display_ON_OFF(uint8_t status)
{
    TM1639_Start();
    if(status)
        TM1639_Write_Byte(TM1639_CMD_DISPLAY | TM1639_BRIGHTNESS_MAX);
    else
        TM1639_Write_Byte(TM1639_DONOT_DISPLAY);
    TM1639_Stop();
}


/**
 * @brief  写入完整的一位数码管（包括高4位和�?4位）
 * @param  addr_h: �?4位地�?
 * @param  addr_l: �?4位地�?
 * @param  data: 要显示的段码数据
 * @retval None
 */
void TM1639_Write_Digit_Full(uint8_t addr_h, uint8_t addr_l, uint8_t data)
{
    // 先写入低4�?
    TM1639_Start();
    TM1639_Write_Byte(addr_l);
    TM1639_Write_Byte(data & 0x0F);  // �?4位数�?
    TM1639_Stop();
    
    // 再写入高4�?
    TM1639_Start();
    TM1639_Write_Byte(addr_h);
    TM1639_Write_Byte(data >> 4);  // �?4位数�?
    TM1639_Stop();
}

/**
 * @brief  关闭�?有显示（包括数码管和LED�?
 * @param  None
 * @retval None
 */
void TM1639_DISP_ALL_SMG_STATE(uint8_t data)
{
    // 关闭数码管显示（GRID1-GRID3�?
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID1_H, TM1639_ADDR_GRID1_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID2_H, TM1639_ADDR_GRID2_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID3_H, TM1639_ADDR_GRID3_L, 0x00);

    // 关闭LED显示（GRID4-GRID8�?
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID4_H, TM1639_ADDR_GRID4_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID5_H, TM1639_ADDR_GRID5_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID6_H, TM1639_ADDR_GRID6_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID7_H, TM1639_ADDR_GRID7_L, 0x00);
    TM1639_Write_Digit_Full(TM1639_ADDR_GRID8_H, TM1639_ADDR_GRID8_L, 0x00);

    // 关闭显示
    TM1639_Display_ON_OFF(data);
}



void TM1639_donotDisplay(void)
{

	TM1639_Start();
     TM1639_Write_Byte(TM1639_DONOT_DISPLAY);
    TM1639_Stop();


}



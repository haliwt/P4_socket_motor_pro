#ifndef __BSP_TM1639_H
#define __BSP_TM1639_H
#include "main.h"


#define DisplayReg           0x40// to write display register 
 
#define AddrFixed 	         0x44// 
#define AddrAutoAdd          0x40 

  
 
#define OpenDispTM1639          0x88// 
#define CloseDispTM1639		    0x80// 


#define TM1639_STB_SetHigh()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13)
#define TM1639_STB_SetLow()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13)

#define TM1639_CLK_SetHigh()  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_14)
#define TM1639_CLK_SetLow()   LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_14)

#define TM1639_DIO_SetHigh()   LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_15)
#define TM1639_DIO_SetLow()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_15)

// TM1639 显示模式
#define TM1639_DISPLAY_ON            0x08    // 显示�??
#define TM1639_DISPLAY_OFF           0x00    // 显示�??

// TM1639 亮度级别 (0-7)
#define TM1639_BRIGHTNESS_MAX        0x07    // �??大亮�?? //WT.EDIT 2025.04.23
#define TM1639_BRIGHTNESS_MIN        0x00    // �??小亮�??


// TM1639 命令定义
#define TM1639_CMD_DATA               0x40    // 数据命令
#define TM1639_CMD_DISPLAY            0x88    // 显示控制命令
#define TM1639_DONOT_DISPLAY          0x80    //  关闭显示

// TM1639 显示地址定义（每个数字需要高4位和�??4位两个地�??�??
// 8段位数码管（最左）-L -> H
#define TM1639_ADDR_GRID1_H           0xC1    // �??4位地�??
#define TM1639_ADDR_GRID1_L           0xC0    // �??4位地�??
// �??2位数码管（中间）
#define TM1639_ADDR_GRID2_H           0xC3    // �??4位地�??
#define TM1639_ADDR_GRID2_L           0xC2    // �??4位地�??
// �??3位数码管（最右）
#define TM1639_ADDR_GRID3_H           0xC5    //  �??4位地�??
#define TM1639_ADDR_GRID3_L           0xC4    // �??4位地�??

#define TM1639_ADDR_GRID4_H          0xC7
#define	TM1639_ADDR_GRID4_L 	     0xC6

#define TM1639_ADDR_GRID5_H      	0xC9
#define TM1639_ADDR_GRID5_L      	0xC8

#define TM1639_ADDR_GRID6_H			0xCB
#define TM1639_ADDR_GRID6_L			0xCA

#define TM1639_ADDR_GRID7_H			0xCD
#define TM1639_ADDR_GRID7_L			0xCC

#define TM1639_ADDR_GRID8_H			0xCF
#define TM1639_ADDR_GRID8_L			0xCE



// TM1639 显示模式
#define TM1639_DISPLAY_ON            0x08    // 显示�??
#define TM1639_DISPLAY_OFF           0x00    // 显示�??

// TM1639 亮度级别 (0-7)
#define TM1639_BRIGHTNESS_MAX        0x07    // �??大亮�?? //WT.EDIT 2025.04.23
#define TM1639_BRIGHTNESS_MIN        0x00    // �??小亮�??








void TM1639_Init(void);


void TM1639_Write_Digit_Full(uint8_t addr_h, uint8_t addr_l, uint8_t data);

void TM1639_donotDisplay(void);


#endif


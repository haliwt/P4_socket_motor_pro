#include "bsp.h"

const uint8_t segTab[10] = {
	  0x3F, // 0
	  0x06, // 1
	  0x5B, // 2
	  0x4F, // 3
	  0x66, // 4
	  0x6D, // 5
	  0x7D, // 6
	  0x07, // 7
	  0x7F, // 8
	  0x6F	// 9
};
/*
	*@brief:// --- 示例：显示数字 ---
	*@note:
	*@param:
	*@retval:
*/
void TM1639_DisplayTest(void)
{
   for (uint8_t i = 0; i < 10; i++) {
        TM1639_WriteData(i, segTab[i]);
    }
}
/*
	*@brief: 
	*@note:
	*@param:
	*@retval:
*/

void works_disp_hanlder(void)
{
     

}



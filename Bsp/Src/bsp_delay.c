#include "bsp.h"


// 假设已定义全局变量 HCLK_MHz (例如 64)
#define HCLK_MHZ 64

/**
 * @brief  微秒延时函数（非阻塞）
 * @param  us: 延时微秒数
 * @retval None
 */
void delay_us(uint32_t us)
{
    uint32_t ticks = us * HCLK_MHZ; // 需要计数的时钟周期数
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD; // 获取 SysTick 的重载值（通常是 1ms 的计数值）

    told = SysTick->VAL; // 记录初始值

    while (1)
    {
        tnow = SysTick->VAL; // 读取当前值
        
        // SysTick 是倒计时的，所以 tnow < told
        if (tnow < told) {
            tcnt += told - tnow; // 正常倒数，累加差值
        } else {
            // 发生溢出（从 reload 倒数到 0），一个溢出周期等于 reload+1 个时钟周期
            tcnt += reload - tnow + told; 
        }

        told = tnow; // 更新上次的值

        if (tcnt >= ticks) {
            break; // 达到目标延时
        }
    }
}


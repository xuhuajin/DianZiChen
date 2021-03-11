/**
 *********************************************************************************************************
 *
 *	模块名称 : 延时函数
 *	文件名称 : bsp_delay.c
 *	版    本 : V1.0
 *	说    明 : 基于SysTick定时器实现了us、ms级延时函数，不影响SysTick定时器的中断
 *	           STM32H750拥有480MHz主频，SYsTick定时器采用系统频率，一个Tick时钟节拍为1/480us，因而
 *	           如果要延时1us需要480个时钟节拍
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/25    Xuhuajin     编写发布
 *
 *********************************************************************************************************
 */

#include "bsp_delay.h"
static uint32_t fac_us=0;							//us延时倍乘数
/**
 * @brief 延时函数初始化
 * @param SYSCLK SysTick时钟频率，单位MHz
 * @retval None
 */
void bsp_DelayInit(void)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTick频率为HCLK
    SysTick_Config(SystemCoreClock / 1000); //1ms一中断
}

/**
 * @brief us延时函数，nus不要超过1000
 * @param nus 要延时的us数
 * @retval None
 */
void bsp_DelayUs(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload;
    reload = SysTick->LOAD; /* 重装载的值 */
    ticks = (nus>1000?1000:nus) * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */
    tcnt = 0;
    told = SysTick->VAL;             /* 刚进入时的计数器值 */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            /* SYSTICK是一个递减的计数器 */
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
                /* 重新装载递减 */
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;

            /* 时间超过/等于要延迟的时间,则退出 */
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * @brief ms延时函数
 * @param nms 要延时的ms数
 * @retval None
 */
void bsp_DelayMs(uint32_t nms)
{
    uint32_t i;
    for(i=0;i<nms;i++)
        bsp_DelayUs(1000);
}
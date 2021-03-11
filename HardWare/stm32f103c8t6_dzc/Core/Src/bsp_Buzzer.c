/**
 *********************************************************************************************************
 *
 *	模块名称 : 蜂鸣器驱动
 *	文件名称 : bsp_Buzzer.c
 *	版    本 : V1.0
 *	说    明 : 无源蜂鸣器驱动程序
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/5    Xuhuajin     编写发布
 *		
 *********************************************************************************************************
 */

#include "bsp_Buzzer.h"
#include "bsp_delay.h"

/**
 * @brief 蜂鸣器初始化
 * @retval None
 */
void bsp_BuzzerInit(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOB时钟

    //PB5初始化设置
    GPIO_Initure.Pin=GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_NOPULL;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //快速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

/**
 * @brief 蜂鸣器响一声
 * @retval None
 */
void bsp_BuzzerOneVocal(void)
{
    uint8_t i=0;
    for(i=0;i<200;i++)
    {
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
        bsp_DelayUs(666); //频率1.5Khz
    }
}
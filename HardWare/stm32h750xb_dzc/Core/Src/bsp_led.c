/**
 *********************************************************************************************************
 *
 *	模块名称 : LED驱动模块
 *	文件名称 : bsp_led.c
 *	版    本 : V1.0
 *	说    明 : 实现了对板载LED的操作函数
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/7    Xuhuajin     编写发布
 *		
 *********************************************************************************************************
 */



#include "bsp_led.h"
#include "bsp_delay.h"

/**
 * @brief LED红灯闪烁
 * @param time 闪烁次数
 * @param interval 闪烁时间间隔,单位ms
 */
void bsp_LedRFlicker(uint8_t time,uint32_t interval)
{
    uint8_t i;
    for(i=0;i<2*time;i++) {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        bsp_DelayMs(interval);
    }
}

/**
 * @brief LED蓝灯闪烁
 * @param time 闪烁次数
 * @param interval 闪烁时间间隔,单位ms
 */
void bsp_LedBFlicker(uint8_t time,uint32_t interval)
{
    uint8_t i;
    for(i=0;i<2*time;i++) {
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
        bsp_DelayMs(interval);
    }
}
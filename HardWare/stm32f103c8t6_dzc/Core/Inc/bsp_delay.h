/**
 *********************************************************************************************************
 *
 *	模块名称 : 延时函数
 *	文件名称 : bsp_delay.h
 *	版    本 : V1.0
 *	说    明 : bsp_delay.c的头文件
 *	           该文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/25    Xuhuajin     编写发布
 *
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_DELAY_H
#define NOW_CS_BSP_DELAY_H
#include "stm32f1xx_hal.h"

void bsp_DelayInit(void);
void bsp_DelayUs(uint32_t nus);
void bsp_DelayMs(uint32_t nms);

#endif //NOW_CS_BSP_DELAY_H

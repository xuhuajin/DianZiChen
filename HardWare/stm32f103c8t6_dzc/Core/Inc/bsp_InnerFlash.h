/**
 *********************************************************************************************************
 *
 *	模块名称 : 内部Flash
 *	文件名称 : bsp_InnerFlash.h
 *	版    本 : V1.0
 *	说    明 : bsp_InnerFlash.c的头文件
 *	           该文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/4    Xuhuajin     编写发布
 *		
 *********************************************************************************************************
 */

#ifndef STM32F103C8T6_ZHSX_BSP_INNERFLASH_H
#define STM32F103C8T6_ZHSX_BSP_INNERFLASH_H
#include "stm32f1xx_hal.h"

void bsp_InnerFlashWrite(uint8_t PageAddr,uint8_t NbPages,uint32_t Data);
uint32_t bsp_InnerFlashRead(uint32_t PageAddr);

#endif //STM32F103C8T6_ZHSX_BSP_INNERFLASH_H

/**
 *********************************************************************************************************
 *
 *	模块名称 : LED驱动
 *	文件名称 : bsp_led.h
 *	版    本 : V1.0
 *	说    明 : bsp_led.c的头文件
 *	           此文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/7    Xuhuajin      编写发布
 *		
 *********************************************************************************************************
 */

#ifndef DIANZICHEN_BSP_LED_H
#define DIANZICHEN_BSP_LED_H

#include "main.h"

#define LED_R_ON()  HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_RESET)
#define LED_R_OFF()  HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET)

#define LED_B_ON()  HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_RESET)
#define LED_B_OFF()  HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_SET)

#define LED_R_TG()  HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)
#define LED_B_TG()  HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

void bsp_LedRFlicker(uint8_t time,uint32_t interval);
void bsp_LedBFlicker(uint8_t time,uint32_t interval);

#endif //DIANZICHEN_BSP_LED_H

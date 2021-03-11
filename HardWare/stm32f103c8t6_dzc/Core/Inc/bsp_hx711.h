/**
 *********************************************************************************************************
 *
 *	模块名称 : hx711模块驱动
 *	文件名称 : bsp_hx711.h
 *	版    本 : V1.0
 *	说    明 : bsp_hx711.c的头文件
 *            该文件包含应用程序的公共定义及函数声明
 *
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/3    Xuhuajin      编写发布
 *		
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_HX711_H
#define NOW_CS_BSP_HX711_H

#include "stm32f1xx_hal.h"

#define HX711_DOUT_Pin  GPIO_PIN_12
#define HX711_SCK_Pin   GPIO_PIN_11

#define HX711_GPIO_PORT GPIOA

#define HX711_SCK(n)  (n?HAL_GPIO_WritePin(HX711_GPIO_PORT,HX711_SCK_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(HX711_GPIO_PORT,HX711_SCK_Pin,GPIO_PIN_RESET)) //SCK

typedef struct {
    uint8_t P_val;
    uint8_t B_val;
    uint8_t S_val;
    uint8_t G_val;
} HX711_DataStruct;

extern uint32_t CZ_H_FLAG;
extern uint32_t maopi_ad;
extern uint16_t Weight_Shiwu;
extern HX711_DataStruct HX711_Data;

void bsp_Hx711Init(void);
uint32_t bsp_Hx711Read(void);
void bsp_GetMaopi(void);
void Get_Weight(void);
#endif //NOW_CS_BSP_HX711_H

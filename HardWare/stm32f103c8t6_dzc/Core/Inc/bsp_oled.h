/**
 *********************************************************************************************************
 *
 *	模块名称 : ssd1306-oled屏驱动
 *	文件名称 : bsp_oled.h
 *	版    本 : V1.0
 *	说    明 : bsp_oled.c的头文件
 *	           该文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/25    Xuhuajin    编写发布
 *
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_OLED_H
#define NOW_CS_BSP_OLED_H
#include "stm32f1xx_hal.h"

#define OLED_W_ADDR         0x78
#define OLED_R_ADDR         0x79


void OledInit();
void OledSetPos(uint8_t x, uint8_t y);
void OledFill(uint8_t fill_Data);
void OledCls(void);
void OledON(void);
void OledOFF(void);
void OledShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);
void OledShowCN(uint8_t x, uint8_t y, uint8_t z_w, uint8_t z_h, uint8_t N,uint8_t F16x16[]);
void OledShowOneChar(uint8_t x,uint8_t y,uint8_t wide, uint8_t ch[]);
void OledDrawBMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[],uint8_t num);

void OledShowStartDH(void);
void Oled_ShowTitle();
void Oled_SetWin(void);
#endif //NOW_CS_BSP_OLED_H

/**
 *********************************************************************************************************
 *
 *	模块名称 : 调试模块
 *	文件名称 : bsp_dubug.h
 *	版    本 : V1.0
 *	说    明 : bsp_dubug.c的头文件
 *	           此文件包含引用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/6    Xuhuajin  
 *		
 *********************************************************************************************************
 */

#ifndef DIANZICHEN_BSP_DUBUG_H
#define DIANZICHEN_BSP_DUBUG_H

#include "main.h"

#define DUBUG_UART  huart4

void bsp_DBPrintf(const char *__format,...);
void bsp_U1Printf(const char *__format,...);
#endif //DIANZICHEN_BSP_DUBUG_H

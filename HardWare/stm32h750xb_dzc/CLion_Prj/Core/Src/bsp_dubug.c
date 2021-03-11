/**
 *********************************************************************************************************
 *
 *	模块名称 : 调试模块
 *	文件名称 : bsp_dubug.c
 *	版    本 : V1.0
 *	说    明 : 包含一些调试输出函数，对printf进行重写
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/6    Xuhuajin     编写发布
 *		
 *********************************************************************************************************
 */

#include "bsp_dubug.h"
#include "stdio.h"
#include <stdarg.h>
#include <string.h>

/**
  *@brief 调试专用打印函数
 */
void bsp_DBPrintf(const char *__format,...)
{
    char TxBuf[200];
    va_list ap;
    va_start(ap,__format);
    //清空发送缓冲区
    memset(TxBuf,0x0,200);
    //填充发送缓冲区
    vsnprintf((char*)TxBuf,200,(const char*)__format,ap);
    va_end(ap);
    uint32_t len = strlen((const char*)TxBuf);
    //往串口发送数据
    uint8_t i;
    for(i=0;i<len;i++)
    {
        HAL_UART_Transmit(&DUBUG_UART, &TxBuf[i], 1, 0xFFFF);
    }
}

/**
  *@brief 串口1专用打印函数
 */
void bsp_U1Printf(const char *__format,...)
{
    char TxBuf[200];
    va_list ap;
    va_start(ap,__format);
    //清空发送缓冲区
    memset(TxBuf,0x0,200);
    //填充发送缓冲区
    vsnprintf((char*)TxBuf,200,(const char*)__format,ap);
    va_end(ap);
    uint32_t len = strlen((const char*)TxBuf);
    //往串口发送数据
    uint8_t i;
    for(i=0;i<len;i++)
    {
        HAL_UART_Transmit(&huart1, &TxBuf[i], 1, 0xFFFF);
    }
}
/**
 *********************************************************************************************************
 *
 *	ģ������ : �ڲ�Flash
 *	�ļ����� : bsp_InnerFlash.h
 *	��    �� : V1.0
 *	˵    �� : bsp_InnerFlash.c��ͷ�ļ�
 *	           ���ļ�����Ӧ�ó���Ĺ������弰��������
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/3/4    Xuhuajin     ��д����
 *		
 *********************************************************************************************************
 */

#ifndef STM32F103C8T6_ZHSX_BSP_INNERFLASH_H
#define STM32F103C8T6_ZHSX_BSP_INNERFLASH_H
#include "stm32f1xx_hal.h"

void bsp_InnerFlashWrite(uint8_t PageAddr,uint8_t NbPages,uint32_t Data);
uint32_t bsp_InnerFlashRead(uint32_t PageAddr);

#endif //STM32F103C8T6_ZHSX_BSP_INNERFLASH_H

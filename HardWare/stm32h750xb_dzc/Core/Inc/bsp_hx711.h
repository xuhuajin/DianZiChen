/**
 *********************************************************************************************************
 *
 *	ģ������ : hx711ģ������
 *	�ļ����� : bsp_hx711.h
 *	��    �� : V1.0
 *	˵    �� : bsp_hx711.c��ͷ�ļ�
 *            ���ļ�����Ӧ�ó���Ĺ������弰��������
 *
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/3/3    Xuhuajin      ��д����
 *		
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_HX711_H
#define NOW_CS_BSP_HX711_H

#include "stm32H7xx_hal.h"

#define HX711_DOUT_Pin  GPIO_PIN_15
#define HX711_SCK_Pin   GPIO_PIN_13

#define HX711_GPIO_PORT GPIOH

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
void bsp_Hx711GetMaopi(void);
void bsp_Hx711GetWeight(void);
#endif //NOW_CS_BSP_HX711_H

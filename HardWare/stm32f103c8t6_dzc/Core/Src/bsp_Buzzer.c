/**
 *********************************************************************************************************
 *
 *	ģ������ : ����������
 *	�ļ����� : bsp_Buzzer.c
 *	��    �� : V1.0
 *	˵    �� : ��Դ��������������
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/3/5    Xuhuajin     ��д����
 *		
 *********************************************************************************************************
 */

#include "bsp_Buzzer.h"
#include "bsp_delay.h"

/**
 * @brief ��������ʼ��
 * @retval None
 */
void bsp_BuzzerInit(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOBʱ��

    //PB5��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_NOPULL;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

/**
 * @brief ��������һ��
 * @retval None
 */
void bsp_BuzzerOneVocal(void)
{
    uint8_t i=0;
    for(i=0;i<200;i++)
    {
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
        bsp_DelayUs(666); //Ƶ��1.5Khz
    }
}
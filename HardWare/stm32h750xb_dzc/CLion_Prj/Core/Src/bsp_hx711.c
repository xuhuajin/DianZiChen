/**
 *********************************************************************************************************
 *
 *	ģ������ : hx711ģ������
 *	�ļ����� : bsp_hx711.c
 *	��    �� : V1.0
 *	˵    �� : hx711��ר��Ϊ���ش�������ƵķŴ�ת��оƬ��24λ�߾���ADC
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/3/3    Xuhuajin  
 *		
 *********************************************************************************************************
 */

#include "bsp_hx711.h"
#include "bsp_delay.h"
//#include "bsp_InnerFlash.h"
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */


//uint32_t CZ_H_FLAG=0; //����ֵ
uint32_t maopi_ad=0;
uint16_t Weight_Shiwu=0;
HX711_DataStruct HX711_Data={0};
void bsp_Hx711Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO�˿�ʱ��ʹ�� */
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* ����SCK���� */
    GPIO_InitStruct.Pin = HX711_SCK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_GPIO_PORT, &GPIO_InitStruct);
    /* ����DOUT���� */
    GPIO_InitStruct.Pin = HX711_DOUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_GPIO_PORT, &GPIO_InitStruct);
    /* ����GPIO���ſ���״̬ */
    HAL_GPIO_WritePin(HX711_GPIO_PORT, HX711_SCK_Pin, GPIO_PIN_RESET);
    /*��ȡ���ر���ֵ*/
    /*CZ_H_FLAG = bsp_InnerFlashRead(126);
    if(CZ_H_FLAG<1||CZ_H_FLAG>5000)
        CZ_H_FLAG=1;*/
}

/**
 * @brief ��ȡHX711ADת��ֵ
 * @return HX711 ADת����ֵ
 */
uint32_t bsp_Hx711Read(void)
{
    uint32_t count;
    uint8_t i;
    HX711_SCK(0);
    count=0;
    while(HAL_GPIO_ReadPin(HX711_GPIO_PORT,HX711_DOUT_Pin));
    bsp_DelayUs(10);
    for(i=0;i<24;i++)
    {
        HX711_SCK(1);
        count=count<<1;
        bsp_DelayUs(1);
        HX711_SCK(0);
        if(HAL_GPIO_ReadPin(HX711_GPIO_PORT,HX711_DOUT_Pin))
            count++;
        bsp_DelayUs(1);
    }
    HX711_SCK(1);
    count=count^0x800000;//��25�������½�����ʱ��ת������
    bsp_DelayUs(1);
    HX711_SCK(0);
    return(count);
}

/**
 * @brief ��ȡë��
 * @return None
 */
void bsp_Hx711GetMaopi(void)
{
    maopi_ad = bsp_Hx711Read();
}

void bsp_Hx711GetWeight(void)
{
    uint32_t HX711_Buffer=0;
    uint32_t HX711_AD = 0;
    HX711_Buffer = bsp_Hx711Read();
    if(HX711_Buffer > maopi_ad)
    {
        HX711_AD = HX711_Buffer - maopi_ad;				//��ȡʵ���AD������ֵ��
        Weight_Shiwu = (uint16_t)((float)(HX711_AD/449.5)); 	//����ʵ���ʵ������
    } else
    {
        Weight_Shiwu=0;
    }
    HX711_Data.P_val=Weight_Shiwu/1000;
    HX711_Data.B_val=Weight_Shiwu%1000/100;
    HX711_Data.S_val=Weight_Shiwu%100/10;
    HX711_Data.G_val=Weight_Shiwu%10;
}
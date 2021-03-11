/**
 *********************************************************************************************************
 *
 *	ģ������ : ��ʱ����
 *	�ļ����� : bsp_delay.c
 *	��    �� : V1.0
 *	˵    �� : ����SysTick��ʱ��ʵ����us��ms����ʱ��������Ӱ��SysTick��ʱ�����ж�
 *	           STM32H750ӵ��480MHz��Ƶ��SYsTick��ʱ������ϵͳƵ�ʣ�һ��Tickʱ�ӽ���Ϊ1/480us�����
 *	           ���Ҫ��ʱ1us��Ҫ480��ʱ�ӽ���
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/1/25    Xuhuajin     ��д����
 *
 *********************************************************************************************************
 */

#include "bsp_delay.h"
static uint32_t fac_us=0;							//us��ʱ������
/**
 * @brief ��ʱ������ʼ��
 * @param SYSCLK SysTickʱ��Ƶ�ʣ���λMHz
 * @retval None
 */
void bsp_DelayInit(void)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
    SysTick_Config(SystemCoreClock / 1000); //1msһ�ж�
}

/**
 * @brief us��ʱ������nus��Ҫ����1000
 * @param nus Ҫ��ʱ��us��
 * @retval None
 */
void bsp_DelayUs(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload;
    reload = SysTick->LOAD; /* ��װ�ص�ֵ */
    ticks = (nus>1000?1000:nus) * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */
    tcnt = 0;
    told = SysTick->VAL;             /* �ս���ʱ�ļ�����ֵ */
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            /* SYSTICK��һ���ݼ��ļ����� */
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
                /* ����װ�صݼ� */
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;

            /* ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

/**
 * @brief ms��ʱ����
 * @param nms Ҫ��ʱ��ms��
 * @retval None
 */
void bsp_DelayMs(uint32_t nms)
{
    uint32_t i;
    for(i=0;i<nms;i++)
        bsp_DelayUs(1000);
}
/**
 *********************************************************************************************************
 *
 *	ģ������ : �ڲ�Flash
 *	�ļ����� : bsp_InnerFlash.c
 *	��    �� : V1.0
 *	˵    �� : ���ڲ�Flash���в���
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/3/4    Xuhuajin     ��д����
 *		
 *********************************************************************************************************
 */

#include "bsp_InnerFlash.h"

/**
 * @brief ���ڲ�flashд����
 * @param PageAddr ����һҳд 0~127
 * @param NbPages  д����ҳ
 * @param Data  Ҫд�������
 */
void bsp_InnerFlashWrite(uint8_t PageAddr,uint8_t NbPages,uint32_t Data)
{
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef InnerFlash;
    HAL_FLASH_Unlock();  //����Flash
    InnerFlash.NbPages = NbPages;  //Ҫ��������ҳ
    InnerFlash.PageAddress =  ((uint32_t)0x08000000+1024*PageAddr); //Ҫ�����ĵ�ַ
    InnerFlash.TypeErase = FLASH_TYPEERASE_PAGES; //ҳ��ֻ����
    HAL_FLASHEx_Erase(&InnerFlash,&PageError); //����Flash
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,InnerFlash.PageAddress,Data);
    HAL_FLASH_Lock(); //��Flash
}

/**
 * @brief ���ڲ�Flash
 * @param PageAddr ���ڼ�ҳ
 * @return ��ȡ������
 */
uint32_t bsp_InnerFlashRead(uint32_t PageAddr)
{
    return ((*(__IO uint32_t*)(uint32_t)(0x08000000+1024*PageAddr)));
}
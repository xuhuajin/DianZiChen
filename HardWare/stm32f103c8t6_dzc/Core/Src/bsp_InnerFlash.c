/**
 *********************************************************************************************************
 *
 *	模块名称 : 内部Flash
 *	文件名称 : bsp_InnerFlash.c
 *	版    本 : V1.0
 *	说    明 : 对内部Flash进行操作
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/3/4    Xuhuajin     编写发布
 *		
 *********************************************************************************************************
 */

#include "bsp_InnerFlash.h"

/**
 * @brief 向内部flash写数据
 * @param PageAddr 向那一页写 0~127
 * @param NbPages  写多少页
 * @param Data  要写入的数据
 */
void bsp_InnerFlashWrite(uint8_t PageAddr,uint8_t NbPages,uint32_t Data)
{
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef InnerFlash;
    HAL_FLASH_Unlock();  //解锁Flash
    InnerFlash.NbPages = NbPages;  //要擦除多少页
    InnerFlash.PageAddress =  ((uint32_t)0x08000000+1024*PageAddr); //要擦除的地址
    InnerFlash.TypeErase = FLASH_TYPEERASE_PAGES; //页面只擦除
    HAL_FLASHEx_Erase(&InnerFlash,&PageError); //擦除Flash
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,InnerFlash.PageAddress,Data);
    HAL_FLASH_Lock(); //锁Flash
}

/**
 * @brief 读内部Flash
 * @param PageAddr 读第几页
 * @return 读取的数据
 */
uint32_t bsp_InnerFlashRead(uint32_t PageAddr)
{
    return ((*(__IO uint32_t*)(uint32_t)(0x08000000+1024*PageAddr)));
}
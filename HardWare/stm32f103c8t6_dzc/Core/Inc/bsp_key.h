/**
 *********************************************************************************************************
 *
 *	模块名称 : 独立按键驱动模块 (外部输入IO)
 *	文件名称 : bsp_key.h
 *	版    本 : V1.3
 *	说    明 : bsp_key.c的头文件
 *	           该文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号  日期        作者     说明
 *		V1.0    2013-02-01 armfly  正式发布
 *		V1.1    2013-06-29 armfly  增加1个读指针，用于bsp_Idle() 函数读取系统控制组合键（截屏）
 *								   增加 K1 K2 组合键 和 K2 K3 组合键，用于系统控制
 *		V1.2	2016-01-25 armfly  针对P02工控板更改. 调整gpio定义方式，更加简洁
 *		V1.3	2018-11-26 armfly  s_tBtn结构赋初值0
 *
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_KEY_H
#define NOW_CS_BSP_KEY_H
#include "stm32f1xx_hal.h"

#define KEY_1_Pin       GPIO_PIN_0
#define KEY_1_GPIO_Port GPIOA

#define KEY_2_Pin       GPIO_PIN_1
#define KEY_2_GPIO_Port GPIOA

#define KEY_3_Pin       GPIO_PIN_2
#define KEY_3_GPIO_Port GPIOA

#define KEY_4_Pin       GPIO_PIN_3
#define KEY_4_GPIO_Port GPIOA

/* 根据应用程序的功能重命名按键宏 */
#define KEY_DOWN_K1		KEY_1_DOWN
#define KEY_UP_K1		KEY_1_UP
#define KEY_LONG_K1		KEY_1_LONG

#define KEY_DOWN_K2		KEY_2_DOWN
#define KEY_UP_K2		KEY_2_UP
#define KEY_LONG_K2		KEY_2_LONG

#define KEY_DOWN_K3		KEY_3_DOWN
#define KEY_UP_K3		KEY_3_UP
#define KEY_LONG_K3		KEY_3_LONG

#define KEY_DOWN_K4		KEY_4_DOWN
#define KEY_UP_K4		KEY_4_UP
#define KEY_LONG_K4		KEY_4_LONG

#define KEY_DOWN_K5		KEY_5_DOWN
#define KEY_UP_K5		KEY_5_UP
#define KEY_LONG_K5		KEY_5_LONG

/* 按键ID, 主要用于bsp_KeyState()函数的入口参数 */
typedef enum
{
    KID_K1 = 0,
    KID_K2,
    KID_K3,
    KID_K4,
}KEY_ID_E;

/*
	按键滤波时间50ms, 单位10ms。
	只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
	即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
*/
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     200			/* 单位10ms， 持续1秒，认为长按事件 */

/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
    /* 下面是一个函数指针，指向判断按键手否按下的函数 */
    uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

    uint8_t  Count;			/* 滤波器计数器 */
    uint16_t LongCount;		/* 长按计数器 */
    uint16_t LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
    uint8_t  State;			/* 按键当前状态（按下还是弹起） */
    uint8_t  RepeatSpeed;	/* 连续按键周期 */
    uint8_t  RepeatCount;	/* 连续按键计数器 */
}KEY_T;

/*
	定义键值代码, 必须按如下次序定时每个键的按下、弹起和长按事件

	推荐使用enum, 不用#define，原因：
	(1) 便于新增键值,方便调整顺序，使代码看起来舒服点
	(2) 编译器可帮我们避免键值重复。
*/
typedef enum
{
    KEY_NONE = 0,			/* 0 表示按键事件 */

    KEY_1_DOWN,				/* 1键按下 */
    KEY_1_UP,				/* 1键弹起 */
    KEY_1_LONG,				/* 1键长按 */

    KEY_2_DOWN,				/* 2键按下 */
    KEY_2_UP,				/* 2键弹起 */
    KEY_2_LONG,				/* 2键长按 */

    KEY_3_DOWN,				/* 3键按下 */
    KEY_3_UP,				/* 3键弹起 */
    KEY_3_LONG,				/* 3键长按 */

    KEY_4_DOWN,				/* 组合键12按下 */
    KEY_4_UP,				/* 组合键12弹起 */
    KEY_4_LONG,				/* 组合键12长按 */

}KEY_ENUM;

/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE	6
typedef struct
{
    uint8_t Buf[KEY_FIFO_SIZE];		/* 键值缓冲区 */
    uint8_t Read;					/* 缓冲区读指针1 */
    uint8_t Write;					/* 缓冲区写指针 */
    uint8_t Read2;					/* 缓冲区读指针2 */
}KEY_FIFO_T;

/* 供外部调用的函数声明 */
void bsp_InitKey(void);
void bsp_KeyScan10ms(void);
void bsp_KeyScan1ms(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed);
void bsp_ClearKey(void);


#endif //NOW_CS_BSP_KEY_H

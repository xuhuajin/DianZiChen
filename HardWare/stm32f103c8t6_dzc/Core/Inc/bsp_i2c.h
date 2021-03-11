/**
 *********************************************************************************************************
 *
 *	模块名称 : 软件I2C驱动
 *	文件名称 : bsp_i2c.h
 *	版    本 : V1.0
 *	说    明 : bsp_i2c.c的头文件
 *	           该文件包含应用程序的公共定义及函数声明
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/24    Xuhuajin     编写发布
 *
 *********************************************************************************************************
 */

#ifndef NOW_CS_BSP_I2C_H
#define NOW_CS_BSP_I2C_H
#include "stm32f1xx_hal.h"

/* 软件I2C硬件接口 */
#define SOFTWAREI2C_PORT_CLK_EN()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define SOFTWAREI2C_PIN_SCL              GPIO_PIN_6
#define SOFTWAREI2C_PIN_SDA              GPIO_PIN_7
#define SOFTWAREI2C_PORT                 GPIOB

/* IO方向设置 */
//#define SDA_IN()  {SOFTWAREI2C_PORT->MODER&=~(3<<(12*2));SOFTWAREI2C_PORT->MODER|=0<<12*2;}	//PH5输入模式
//#define SDA_OUT() {SOFTWAREI2C_PORT->MODER&=~(3<<(12*2));SOFTWAREI2C_PORT->MODER|=1<<12*2;} //PH5输出模式
#define SDA_IN()    do{ GPIO_InitTypeDef GPIO_Initure;                              \
                        GPIO_Initure.Pin=SOFTWAREI2C_PIN_SDA;                       \
                        GPIO_Initure.Mode=GPIO_MODE_INPUT;                          \
                        GPIO_Initure.Pull=GPIO_PULLUP;                              \
                        GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;               \
                        HAL_GPIO_Init(SOFTWAREI2C_PORT,&GPIO_Initure);              \
                        }while(0)
#define SDA_OUT()    do{ GPIO_InitTypeDef GPIO_Initure;                             \
                        GPIO_Initure.Pin=SOFTWAREI2C_PIN_SDA;                       \
                        GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;                      \
                        GPIO_Initure.Pull=GPIO_PULLUP;                              \
                        GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;               \
                        HAL_GPIO_Init(SOFTWAREI2C_PORT,&GPIO_Initure);              \
                        }while(0)
/* IO操作 */
#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(SOFTWAREI2C_PORT,SOFTWAREI2C_PIN_SCL,GPIO_PIN_SET):HAL_GPIO_WritePin(SOFTWAREI2C_PORT,SOFTWAREI2C_PIN_SCL,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(SOFTWAREI2C_PORT,SOFTWAREI2C_PIN_SDA,GPIO_PIN_SET):HAL_GPIO_WritePin(SOFTWAREI2C_PORT,SOFTWAREI2C_PIN_SDA,GPIO_PIN_RESET)) //SDA
#define READ_SDA    HAL_GPIO_ReadPin(SOFTWAREI2C_PORT,SOFTWAREI2C_PIN_SDA)  //输入SDA

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);
#endif //NOW_CS_BSP_I2C_H

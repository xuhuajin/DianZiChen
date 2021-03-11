/**
 *********************************************************************************************************
 *
 *	模块名称 : 软件I2C驱动
 *	文件名称 : bsp_i2c.c
 *	版    本 : V1.0
 *	说    明 : 软件I2C代码实现，可随意更换GPIO引脚
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/24    Xuhuajin     编写发布
 *
 *********************************************************************************************************
 */

#include "bsp_i2c.h"
#include "bsp_delay.h"

/**
 * @brief IIC初始化
 */
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    SOFTWAREI2C_PORT_CLK_EN();   //使能GPIOH时钟

    //PH4,5初始化设置
    GPIO_Initure.Pin=SOFTWAREI2C_PIN_SCL|SOFTWAREI2C_PIN_SDA;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //快速
    HAL_GPIO_Init(SOFTWAREI2C_PORT,&GPIO_Initure);
    IIC_SDA(1);
    IIC_SCL(1);
}

/**
 * @brief 产生IIC起始信号
 */
void IIC_Start(void)
{
    SDA_OUT();     //sda线输出
    IIC_SDA(1);
    IIC_SCL(1);
    IIC_SDA(0);//START:when CLK is high,DATA change form high to low
    bsp_DelayUs(4);
    IIC_SCL(0);//钳住I2C总线，准备发送或接收数据
}

/**
 * @brief 产生IIC停止信号
 */
void IIC_Stop(void)
{
    SDA_OUT();//sda线输出
    IIC_SCL(0);
    IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
    bsp_DelayUs(4);
    IIC_SCL(1);
    bsp_DelayUs(4);
    IIC_SDA(1);//发送I2C总线结束信号
    bsp_DelayUs(4);
}

/**
 * @brief 等待应答信号到来
 * @retval 1，接收应答失败
 *         0，接收应答成功
 */
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    SDA_IN();      //SDA设置为输入
    IIC_SDA(1);bsp_DelayUs(1);
    IIC_SCL(1);bsp_DelayUs(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL(0);//时钟输出0
    return 0;
}

/**
 * @brief 产生ACK应答
 */
void IIC_Ack(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(0);
    bsp_DelayUs(2);
    IIC_SCL(1);
    bsp_DelayUs(2);
    IIC_SCL(0);
}

/**
 * @brief 不产生ACK应答
 */
void IIC_NAck(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(1);
    bsp_DelayUs(2);
    IIC_SCL(1);
    bsp_DelayUs(2);
    IIC_SCL(0);
}

/**
 * @brief IIC发送一个字节
 * @param txd 要发送的字节数据
 */
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        IIC_SDA((txd&0x80)>>7);
        txd<<=1;
        bsp_DelayUs(2);   //对TEA5767这三个延时都是必须的
        IIC_SCL(1);
        bsp_DelayUs(2);
        IIC_SCL(0);
        bsp_DelayUs(2);
    }
}

/**
 * @brief 读1个字节
 * @param ack 1，发送ACK
 *            0，发送nACK
 * @retval 读取到的字节数据
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        IIC_SCL(0);
        bsp_DelayUs(2);
        IIC_SCL(1);
        receive<<=1;
        if(READ_SDA)receive++;
        bsp_DelayUs(1);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}
/**
 *********************************************************************************************************
 *
 *	模块名称 : ssd1306-oled屏驱动
 *	文件名称 : bsp_oled.c
 *	版    本 : V1.0
 *	说    明 : SSD1306_0.96英寸OLED屏驱动
 *********************************************************************************************************
 *	修改记录 :
 *		版本号   日期         作者         说明
 *		V1.0    2021/1/25    Xuhuajin    编写发布
 *
 *********************************************************************************************************
 */

#include "bsp_oled.h"
#include "bsp_i2c.h"
#include "bsp_delay.h"
#include "codetab.h"
#include "bsp_hx711.h"
#include "bsp_key.h"
#include "bsp_InnerFlash.h"

/**
 * @drief 向OLED发送一个字节数据
 * @param addr OLED寄存器地址
 * @param data 需要向OLED寄存器写入的数据
 */
static void OledWriteByte(uint8_t addr,uint8_t data)
{
    //发送起始信号
    IIC_Start();
    //发送OLED地址并设置为发送器模式
    IIC_Send_Byte(OLED_W_ADDR);
    IIC_Wait_Ack();
    //发送OLED寄存器地址
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    //向OLED发送数据
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    //发送结束信号
    IIC_Stop();
    bsp_DelayUs(3);
}

/**
 * @brief 向OLED发送命令字节
 * @param OLED_CMD  OLED指令字节
 * @retval None
 */
static void OledWriteCmd(uint8_t OLED_CMD)
{
    OledWriteByte(0x00,OLED_CMD);
}

/**
 * @brief 向OLED写数据
 * @param OLED_DATA 要写入的数据
 */
static void OledWriteData(uint8_t OLED_DATA)
{
    OledWriteByte(0x40,OLED_DATA);
}

/**
 * @brief OLED初始化函数
 */
void OledInit()
{
    bsp_DelayMs(100);
    OledWriteCmd(0xAE); //display off
    OledWriteCmd(0x20);	//设置内存寻址模式
    OledWriteCmd(0x10);	//00,水平的寻址模式;01,垂直的寻址模式;10,页面寻址模式(重置);11,无效
    OledWriteCmd(0xb0);	//设置页面寻址模式的页面开始地址，0-7
    OledWriteCmd(0xc8);	//设置COM输出扫描方向
    OledWriteCmd(0x00); //---设置低列地址
    OledWriteCmd(0x10); //---设置高列地址
    OledWriteCmd(0x40); //--设定起始行地址
    OledWriteCmd(0x81); //--设置对比度控制寄存器
    OledWriteCmd(0xff); //亮度调节 0x00~0xff
    OledWriteCmd(0xa1); //--设置段重映射0到127
    OledWriteCmd(0xa6); //--设置正常显示
    OledWriteCmd(0xa8); //--设置多路复用比(1比64)
    OledWriteCmd(0x3F); //
    OledWriteCmd(0xa4); //0xa4，输出遵循RAM内容;0xa5，输出忽略RAM内容
    OledWriteCmd(0xd3); //-设置显示抵消
    OledWriteCmd(0x00); //-不抵消
    OledWriteCmd(0xd5); //--设置显示时钟分频比/振荡频率
    OledWriteCmd(0xf0); //--设置分率
    OledWriteCmd(0xd9); //--set pre-charge period
    OledWriteCmd(0x22); //
    OledWriteCmd(0xda); //--设置com引脚硬件配置
    OledWriteCmd(0x12);
    OledWriteCmd(0xdb); //--set vcomh
    OledWriteCmd(0x20); //0x20,0.77xVcc
    OledWriteCmd(0x8d); //--set DC-DC enable
    OledWriteCmd(0x14); //
    OledWriteCmd(0xaf); //--开启oled面板
    OledCls();
}

/**
 * @brief 设置起始点坐标
 * @param x x坐标
 * @param y y坐标
 */
void OledSetPos(uint8_t x, uint8_t y)
{
    OledWriteCmd(0xb0+y);
    OledWriteCmd(((x&0xf0)>>4)|0x10);
    OledWriteCmd((x&0x0f)|0x01);
}

/**
 * @brief 全屏填充
 * @param fill_Data fill_Data坐标
 */
void OledFill(uint8_t fill_Data)
{
    uint8_t m,n;
    for(m=0;m<8;m++)
    {
        OledWriteCmd(0xb0+m);	//page0-page1
        OledWriteCmd(0x00);		//低列起始地址
        OledWriteCmd(0x10);		//高列起始地址
        for(n=0;n<132;n++)
        {
            OledWriteData(fill_Data);
        }
    }
}

/**
 * @brief 清屏
 */
void OledCls(void)
{
    OledFill(0x00);
}

/**
 * @brief 将OLED从休眠中唤醒
 */
void OledON(void)
{
    OledWriteCmd(0X8D);  //设置电荷泵
    OledWriteCmd(0X14);  //开启电荷泵
    OledWriteCmd(0XAF);  //OLED唤醒
}

/**
 * @brief 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
 */
void OledOFF(void)
{
    OledWriteCmd(0X8D);  //设置电荷泵
    OledWriteCmd(0X10);  //关闭电荷泵
    OledWriteCmd(0XAE);  //OLED休眠
}

/**
 * @brief 显示codetab.h中的ASCII字符,有6*8和8*16可选择
 * @param x x坐标
 * @param y y坐标
 * @param ch[] 要显示的字符串
 * @param TextSize 字符大小(1:6*8 ; 2:8*16)
 */
void OledShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
{
    uint8_t c = 0,i = 0,j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 132)
                {
                    x = 0;
                    y++;
                }
                OledSetPos(x,y);
                for(i=0;i<6;i++)
                    OledWriteData(F6x8[c][i]);
                x += 6;
                j++;
            }
        }break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 128)
                {
                    x = 0;
                    y++;
                }
                OledSetPos(x,y);
                for(i=0;i<8;i++)
                    OledWriteData(F8X16[c*16+i]);
                OledSetPos(x,y+1);
                for(i=0;i<8;i++)
                    OledWriteData(F8X16[c*16+i+8]);
                x += 8;
                j++;
            }
        }break;
    }
}

/**
 * @brief 显示codetab.h中的汉字,16*16点阵
 * @param x 起始点坐标
 * @param y 起始点坐标
 * @param N 汉字在codetab.h中的索引
 */
void OledShowCN(uint8_t x, uint8_t y, uint8_t z_w, uint8_t z_h, uint8_t N,uint8_t F16x16[])
{
    uint8_t wm=0,h=0;
    uint16_t  adder=z_h*z_w/8*N;
    OledSetPos(x , y);
    for (h = 0;h < z_h/8;h++)
    {
        for(wm = 0;wm < z_w;wm++)
        {
            OledWriteData(F16x16[adder]);
            adder += 1;
        }
        y += 1;
        OledSetPos(x , y);
    }
}

/**
 * @brief 显示一个字符
 * @param x 起始点坐标
 * @param y 起始点坐标
 * @param wide 字符数
 * @param ch 字符数组
 */
void OledShowOneChar(uint8_t x,uint8_t y,uint8_t wide, uint8_t ch[])
{
    uint8_t i;
    OledSetPos(x,y);
    for(i=0;i<wide;i++)
        OledWriteData(ch[i]);
}

 /**
  * @brief 显示BMP位图
  * @param x0 x轴起点
  * @param y0 y轴起点
  * @param x1 x终点
  * @param y1 y终点
  * @param BMP 存放BNP位图的数组
  * @param num BMP位图幅数
  */
void OledDrawBMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[],uint8_t num)
{
    uint32_t j=0;
    uint8_t x,y,i;
    for(i=0;i<num;i++)
    {
        if(y1%8==0)
            y = y1/8;
        else
            y = y1/8 + 1;
        for(y=y0;y<y1;y++)
        {
            OledSetPos(x0,y);
            for(x=x0;x<x1;x++)
            {
                OledWriteData(BMP[j++]);
            }
        }
        bsp_DelayMs(10);
    }
}

/**
 * @brief 显示BMP位图动画
 */
void OledShowStartDH(void)
{
    uint8_t i;
    for(i=0;i<2;i++)
    {
        OledDrawBMP(31,0,95,8,(uint8_t*)COOL_BMP,28);
        //	Oled_DrawBMP(31,0,95,8,SL_BMP,28);
    }
    OledCls();
}

/**
 * @brief 电子秤主界面显示
 */
void Oled_ShowTitle(void)
{
    uint8_t i;
    uint8_t w=26;
    for(i=0;i<3;i++)
    {
        OledShowCN(40+(i*16), 0,16,16, i, (uint8_t *) DZC16X16);
    }
    OledShowCN(w,3,16,32,HX711_Data.P_val,(uint8_t*)NUM16X32);
    OledShowCN(16+w,3,16,32,HX711_Data.B_val,(uint8_t*)NUM16X32);
    OledShowCN(16*2+w,3,16,32,HX711_Data.S_val,(uint8_t*)NUM16X32);
    OledShowCN(16*3+w,3,16,32,HX711_Data.G_val,(uint8_t*)NUM16X32);
    OledShowStr(17*4+w,5,"g",2);
}

void Oled_SetWin(void)
{
    uint8_t i;
    uint8_t flat=1;
    uint8_t w=26;
    static uint8_t B=1;
    while(flat)
    {
        for(i=0;i<3;i++)
        {
            OledShowCN(40+(i*16), 0,16,16, i, (uint8_t *) CZZ16X16);
        }
        OledShowCN(w,3,16,32,CZ_H_FLAG/1000,(uint8_t*)NUM16X32);
        OledShowCN(16+w,3,16,32,CZ_H_FLAG%1000/100,(uint8_t*)NUM16X32);
        OledShowCN(16*2+w,3,16,32,CZ_H_FLAG%100/10,(uint8_t*)NUM16X32);
        OledShowCN(16*3+w,3,16,32,CZ_H_FLAG%10,(uint8_t*)NUM16X32);
        OledShowStr(17*4+w,5,"g",2);
        uint8_t ucKeyCode=0;
        ucKeyCode = bsp_GetKey();
        if (ucKeyCode != KEY_NONE)
        {
            switch (ucKeyCode)
            {
                case KEY_DOWN_K1:				 //K1按下
                    CZ_H_FLAG += 1*B;
                    if(CZ_H_FLAG>5000)
                        CZ_H_FLAG=1;
                    break;
                case KEY_UP_K1:
                    B=1;
                    break;
                case KEY_LONG_K1:
                    B=20;
                    break;
                case KEY_DOWN_K2:				 //K1按下
                    CZ_H_FLAG -= 1*B;
                    if(CZ_H_FLAG<1)
                        CZ_H_FLAG=5000;
                    break;
                case KEY_UP_K2:
                    B=1;
                    break;
                case KEY_LONG_K2:
                    B=20;
                    break;
                case KEY_LONG_K4:               //K1K2按下
                    bsp_InnerFlashWrite(126,1,CZ_H_FLAG);
                    flat=0;
                    break;
            }
        }
    }
    //bsp_DelayMs(5);
}

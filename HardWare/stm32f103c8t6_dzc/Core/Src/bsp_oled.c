/**
 *********************************************************************************************************
 *
 *	ģ������ : ssd1306-oled������
 *	�ļ����� : bsp_oled.c
 *	��    �� : V1.0
 *	˵    �� : SSD1306_0.96Ӣ��OLED������
 *********************************************************************************************************
 *	�޸ļ�¼ :
 *		�汾��   ����         ����         ˵��
 *		V1.0    2021/1/25    Xuhuajin    ��д����
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
 * @drief ��OLED����һ���ֽ�����
 * @param addr OLED�Ĵ�����ַ
 * @param data ��Ҫ��OLED�Ĵ���д�������
 */
static void OledWriteByte(uint8_t addr,uint8_t data)
{
    //������ʼ�ź�
    IIC_Start();
    //����OLED��ַ������Ϊ������ģʽ
    IIC_Send_Byte(OLED_W_ADDR);
    IIC_Wait_Ack();
    //����OLED�Ĵ�����ַ
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    //��OLED��������
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    //���ͽ����ź�
    IIC_Stop();
    bsp_DelayUs(3);
}

/**
 * @brief ��OLED���������ֽ�
 * @param OLED_CMD  OLEDָ���ֽ�
 * @retval None
 */
static void OledWriteCmd(uint8_t OLED_CMD)
{
    OledWriteByte(0x00,OLED_CMD);
}

/**
 * @brief ��OLEDд����
 * @param OLED_DATA Ҫд�������
 */
static void OledWriteData(uint8_t OLED_DATA)
{
    OledWriteByte(0x40,OLED_DATA);
}

/**
 * @brief OLED��ʼ������
 */
void OledInit()
{
    bsp_DelayMs(100);
    OledWriteCmd(0xAE); //display off
    OledWriteCmd(0x20);	//�����ڴ�Ѱַģʽ
    OledWriteCmd(0x10);	//00,ˮƽ��Ѱַģʽ;01,��ֱ��Ѱַģʽ;10,ҳ��Ѱַģʽ(����);11,��Ч
    OledWriteCmd(0xb0);	//����ҳ��Ѱַģʽ��ҳ�濪ʼ��ַ��0-7
    OledWriteCmd(0xc8);	//����COM���ɨ�跽��
    OledWriteCmd(0x00); //---���õ��е�ַ
    OledWriteCmd(0x10); //---���ø��е�ַ
    OledWriteCmd(0x40); //--�趨��ʼ�е�ַ
    OledWriteCmd(0x81); //--���öԱȶȿ��ƼĴ���
    OledWriteCmd(0xff); //���ȵ��� 0x00~0xff
    OledWriteCmd(0xa1); //--���ö���ӳ��0��127
    OledWriteCmd(0xa6); //--����������ʾ
    OledWriteCmd(0xa8); //--���ö�·���ñ�(1��64)
    OledWriteCmd(0x3F); //
    OledWriteCmd(0xa4); //0xa4�������ѭRAM����;0xa5���������RAM����
    OledWriteCmd(0xd3); //-������ʾ����
    OledWriteCmd(0x00); //-������
    OledWriteCmd(0xd5); //--������ʾʱ�ӷ�Ƶ��/��Ƶ��
    OledWriteCmd(0xf0); //--���÷���
    OledWriteCmd(0xd9); //--set pre-charge period
    OledWriteCmd(0x22); //
    OledWriteCmd(0xda); //--����com����Ӳ������
    OledWriteCmd(0x12);
    OledWriteCmd(0xdb); //--set vcomh
    OledWriteCmd(0x20); //0x20,0.77xVcc
    OledWriteCmd(0x8d); //--set DC-DC enable
    OledWriteCmd(0x14); //
    OledWriteCmd(0xaf); //--����oled���
    OledCls();
}

/**
 * @brief ������ʼ������
 * @param x x����
 * @param y y����
 */
void OledSetPos(uint8_t x, uint8_t y)
{
    OledWriteCmd(0xb0+y);
    OledWriteCmd(((x&0xf0)>>4)|0x10);
    OledWriteCmd((x&0x0f)|0x01);
}

/**
 * @brief ȫ�����
 * @param fill_Data fill_Data����
 */
void OledFill(uint8_t fill_Data)
{
    uint8_t m,n;
    for(m=0;m<8;m++)
    {
        OledWriteCmd(0xb0+m);	//page0-page1
        OledWriteCmd(0x00);		//������ʼ��ַ
        OledWriteCmd(0x10);		//������ʼ��ַ
        for(n=0;n<132;n++)
        {
            OledWriteData(fill_Data);
        }
    }
}

/**
 * @brief ����
 */
void OledCls(void)
{
    OledFill(0x00);
}

/**
 * @brief ��OLED�������л���
 */
void OledON(void)
{
    OledWriteCmd(0X8D);  //���õ�ɱ�
    OledWriteCmd(0X14);  //������ɱ�
    OledWriteCmd(0XAF);  //OLED����
}

/**
 * @brief ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
 */
void OledOFF(void)
{
    OledWriteCmd(0X8D);  //���õ�ɱ�
    OledWriteCmd(0X10);  //�رյ�ɱ�
    OledWriteCmd(0XAE);  //OLED����
}

/**
 * @brief ��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
 * @param x x����
 * @param y y����
 * @param ch[] Ҫ��ʾ���ַ���
 * @param TextSize �ַ���С(1:6*8 ; 2:8*16)
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
 * @brief ��ʾcodetab.h�еĺ���,16*16����
 * @param x ��ʼ������
 * @param y ��ʼ������
 * @param N ������codetab.h�е�����
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
 * @brief ��ʾһ���ַ�
 * @param x ��ʼ������
 * @param y ��ʼ������
 * @param wide �ַ���
 * @param ch �ַ�����
 */
void OledShowOneChar(uint8_t x,uint8_t y,uint8_t wide, uint8_t ch[])
{
    uint8_t i;
    OledSetPos(x,y);
    for(i=0;i<wide;i++)
        OledWriteData(ch[i]);
}

 /**
  * @brief ��ʾBMPλͼ
  * @param x0 x�����
  * @param y0 y�����
  * @param x1 x�յ�
  * @param y1 y�յ�
  * @param BMP ���BNPλͼ������
  * @param num BMPλͼ����
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
 * @brief ��ʾBMPλͼ����
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
 * @brief ���ӳ���������ʾ
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
                case KEY_DOWN_K1:				 //K1����
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
                case KEY_DOWN_K2:				 //K1����
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
                case KEY_LONG_K4:               //K1K2����
                    bsp_InnerFlashWrite(126,1,CZ_H_FLAG);
                    flat=0;
                    break;
            }
        }
    }
    //bsp_DelayMs(5);
}

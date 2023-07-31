#include "driverlib.h"
#include "oled.h"
#include "oled_font.h"

void IIC_Start()
{
    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

void IIC_Stop()
{
    OLED_SCLK_Set();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();
}

void IIC_waitAck()
{
    OLED_SCLK_Set();
    OLED_SCLK_Clr();
}

void IIC_writeByte(uint8_t IIC_Byte)
{
    uint8_t i;
    uint8_t m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0;i<8;i++)
    {
        m=da;
        m=m&0x80;
        if(m==0x80)
            OLED_SDIN_Set();
        else
            OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
        }
}

void IIC_writeCommand(uint8_t IIC_Command)
{
    IIC_Start();
    IIC_writeByte(0x78);            //Slave address,SA0=0
    IIC_waitAck();
    IIC_writeByte(0x00);            //write command
    IIC_waitAck();
    IIC_writeByte(IIC_Command);
    IIC_waitAck();
    IIC_Stop();
}

void IIC_writeData(uint8_t IIC_Data)
{
    IIC_Start();
    IIC_writeByte(0x78);            //D/C#=0; R/W#=0
    IIC_waitAck();
    IIC_writeByte(0x40);            //write data
    IIC_waitAck();
    IIC_writeByte(IIC_Data);
    IIC_waitAck();
    IIC_Stop();
}

void Delay_1ms(uint32_t Del_1ms)
{
    uint8_t j;
    while(Del_1ms--)
    {
        for(j=0;j<123;j++);
    }
}

void OLED_WR_Byte(uint32_t dat,uint32_t cmd)
{
    if(cmd)
        IIC_writeData(dat);
    else
        IIC_writeCommand(dat);
}

void OLED_Set_Pos(uint8_t x, uint8_t y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

void OLED_On(void)
{
    uint8_t i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

uint32_t oled_pow(uint8_t m,uint8_t n)
{
    uint32_t result=1;
    while(n--)result*=m;
    return result;
}

void OLED_init(void)
{
    GPIO_setAsOutputPin(SCL_PORT, SCL_PIN);
    GPIO_setAsOutputPin(SDA_PORT, SDA_PIN);
    Delay_1ms(200);
    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//
    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//
    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//
    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//
    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//
    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//
    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
    OLED_clear();
}

void OLED_clear(void)
{
    uint8_t i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    }
}

void OLED_showChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{
    unsigned char c=0,i=0;
    c=chr-' ';
    if(x>Max_Column-1){x=0;y=y+2;}
    if(Char_Size ==16)
    {
    OLED_Set_Pos(x,y);
    for(i=0;i<8;i++)
    OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
    OLED_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
    OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else {
    OLED_Set_Pos(x,y);
    for(i=0;i<6;i++)
    OLED_WR_Byte(F6x8[c][i],OLED_DATA);
    }
}

void OLED_showNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size2)
{
    unsigned char t,temp;
        unsigned char enshow=0;
        for(t=0;t<len;t++)
        {
            temp=(num/oled_pow(10,len-t-1))%10;
            if(enshow==0&&t<(len-1))
            {
                if(temp==0)
                {
                    OLED_showChar(x+(size2/2)*t,y,' ',size2);
                    continue;
                }else enshow=1;

            }
            OLED_showChar(x+(size2/2)*t,y,temp+'0',size2);
        }
}

void OLED_showSignNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t size2)
{
    unsigned char t,temp;
    unsigned char enshow=0;

    if(num<0)
    {
        num=-num;
        OLED_showChar(x,y,'-',size2);
        x+=8;
    }
    else
    {
        OLED_showChar(x,y,' ',size2);
        x+=8;
    }

    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_showChar(x+(size2/2)*t,y,' ',size2);
                continue;
            }
            else enshow=1;
        }

    OLED_showChar(x+(size2/2)*t,y,temp+'0',size2);
    }
}

void OLED_showString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
    uint8_t j=0;
    while (chr[j]!='\0')
    {       OLED_showChar(x,y,chr[j],Char_Size);
            x+=8;
        if(x>120){x=0;y+=2;}
            j++;
    }
}

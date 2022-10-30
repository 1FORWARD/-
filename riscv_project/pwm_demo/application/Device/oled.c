#include <stdio.h>
#include "oled.h"
#include "oledfont.h"
#include "sf1_eval.h"

#define OLED_ADD 0x78 
static uint32_t IIC_CLORK[] = {SOC_I2C_SCK_GPIO_MASK,SOC_I2C_SDA_GPIO_MASK};

#define IIC_SCK_1       gpio_write(GPIO,IIC_CLORK[0],1)
#define IIC_SCK_0 		gpio_write(GPIO,IIC_CLORK[0],0)
#define IIC_SDA_1 		gpio_write(GPIO,IIC_CLORK[1],1)
#define IIC_SDA_0 		gpio_write(GPIO,IIC_CLORK[1],0)



void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
  }
}

void delay_ms(unsigned int _ms_time)
{
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
}

void IIC_write(unsigned char date)
{
	unsigned char i, temp;
	temp = date;
			
	for(i=0; i<8; i++)
	{
		IIC_SCK_0; // @suppress("Statement has no effect")
		
        if ((temp&0x80)==0)
            IIC_SDA_0;

        else IIC_SDA_1;
		temp = temp << 1;
		delay_us(1);			  
		IIC_SCK_1;
		delay_us(1);
		
	}
	IIC_SCK_0;
	delay_us(1);
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
//								����ҪӦ��
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
}
//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //���в��������ͷ�SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
    IIC_write(0x78);
        
}

//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
void IIC_stop()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
}


void WriteCmd(uint8_t  I2C_Command)
{
	 
	IIC_start();
    IIC_write(0x00); 
    IIC_write(I2C_Command);
    IIC_stop();
}

void WriteDat(uint8_t  I2C_Data)
{
	IIC_start();
    IIC_write(0x40);
    IIC_write(I2C_Data);
    IIC_stop();
}

void OLED_Set_Pos(uint8_t x,uint8_t  y)
{
	 WriteCmd(0xb0+y);
	 WriteCmd(((x&0xf0)>>4)|0x10);
	 WriteCmd((x&0x0f)|0x01); 
}

void OLED_Fill(uint8_t fill_Data)//��?����0xff ��??e0x00
{
	uint8_t m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		 WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}

void OLED_Init(void)
{ 	
	delay_ms(100);
	
	WriteCmd(0xAE);//--display off
	WriteCmd(0x00);//---set low column address
	WriteCmd(0x10);//---set high column address
	WriteCmd(0x40);//--set start line address  
	WriteCmd(0xB0);//--set page address
	WriteCmd(0x81); // contract control
	WriteCmd(0xFF);//--128   
	WriteCmd(0xA1);//set segment remap 
	WriteCmd(0xA6);//--normal / reverse
	WriteCmd(0xA8);//--set multiplex ratio(1 to 64)
    WriteCmd(0x3F);//--1/32 duty
	WriteCmd(0xC8);//Com scan direction
	WriteCmd(0xD3);//-set display offset
	WriteCmd(0x00);//
	WriteCmd(0xD5);//set osc division
    WriteCmd(0x80);//
	WriteCmd(0xD8);//set area color mode off
	WriteCmd(0x05);//
	
	WriteCmd(0xD9);//Set Pre-Charge Period
	WriteCmd(0xF1);//
	
	WriteCmd(0xDA);//set com pin configuartion
	WriteCmd(0x12);//
	
	WriteCmd(0xDB);//set Vcomh
	WriteCmd(0x30);//
	
	WriteCmd(0x8D);//set charge pump enable
	WriteCmd(0x14);//
	WriteCmd(0xAF);//--turn on oled panel
	
	WriteCmd(0x00);
}
 
void OLED_display_char(uint8_t  x,uint8_t  y,uint8_t chr,uint8_t Char_Size)
{
		unsigned char c=0,i=0;	
		c=chr-' ';//		
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i+8]);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				WriteDat(F6x8[c][i]);
				
			}
}
	
void OLED_ShowString(uint8_t  x,uint8_t  y,uint8_t ch[],uint8_t  Char_Size)
{
	uint8_t c=0,i=0,j=0;
	switch(Char_Size)
	{
		case 1:
		{
			while(ch[j]!='\0')
			{
				c=ch[j]-32;
				if(x>126)
				{
					x=0;
					y++;
				}
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x+=6;
				j++;
			}
		}break;
	  case 2:
		{
			while(ch[j]!='\0')
			{
				c=ch[j]-32;
				if(x>120)
				{
					x=0;
					y++;
				}
				OLED_Set_Pos(x,y);
			 for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x+=8;
			 j++;
			}
		}break;
   }
}

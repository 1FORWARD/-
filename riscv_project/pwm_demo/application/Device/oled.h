#include <stdio.h>
#include "sf1_eval.h"

#ifndef _OLED_H_
#define _OLED_H_


void delay_us(unsigned int _us_time);
void delay_ms(unsigned int _ms_time);
void IIC_write(unsigned char date);
void IIC_start(void);
void IIC_stop(void);
	
void WriteCmd(uint8_t  I2C_Command);
void WriteDat(uint8_t  I2C_Data);
void OLED_Init(void);
void OLED_Fill(uint8_t fill_Data);
void OLED_Set_Pos(uint8_t x,uint8_t  y);
void OLED_ShowString(uint8_t  x,uint8_t  y,uint8_t ch[],uint8_t  Char_Size);
void OLED_display_char(uint8_t  x,uint8_t  y,uint8_t chr,uint8_t Char_Size);

#endif  

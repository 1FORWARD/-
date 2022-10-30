#include <stdio.h>
#include "pwm.h"
#include "control.h"
#include "k210.h"
#include "oled.h"
#include "line_walking.h"
#include "../../../../SoC/anlogic/Board/sf1_eval/Include/nuclei_sdk_hal.h"

#define LEDn  3
static uint32_t LED_CLORK[] = {SOC_LED_RED_GPIO_MASK, SOC_LED_GREEN_GPIO_MASK,SOC_LED_BLUE_GPIO_MASK};
static uint32_t IIC_CLORK[] = {SOC_I2C_SCK_GPIO_MASK,SOC_I2C_SDA_GPIO_MASK};

uint16_t temp;
uint16_t x,y,w,h;
uint8_t OLED_BUF[30];


void led_config(void)
{
    for(int i=0; i<LEDn; i++)
    {
        gpio_enable_output(GPIO,LED_CLORK[i]);
        gpio_write(GPIO,LED_CLORK[i],1);
    }
}

void oled_config(void)
{
    for(int i=0; i<2; i++)
    {
        gpio_enable_output(GPIO,IIC_CLORK[i]);
        gpio_write(GPIO,IIC_CLORK[i],1);
    }
}

void uart0_handler(void)
{
    if(uart_get_flag_rxip(UART0)==2)
    {
    	temp=uart_read(UART0);
    	Receive_Data(temp);
		uart_clean_fifo(UART0);
    }
}

void back(void)
{
	setpwm(5,9,200000,14222); // 转向舵机
	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2

	// 右轮
	setpwm(2,1,50000,30000); // BIN1
	setpwm(3,1,50000,45000); // BIN2

	delay_1ms(3500);

	/* 左转 */
	setpwm(5,9,200000,14222 + 5555);
	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2
	// 右轮
	setpwm(2,1,50000,20000); // BIN1
	setpwm(3,1,50000,45000); // BIN2

	delay_1ms(2000);

	/* 后退 */
	setpwm(5,9,200000,14222);
	// 左轮
	setpwm(0,1,50000,30000); // AIN1
	setpwm(1,1,50000,45000); // AIN2
	// 右轮
	setpwm(2,1,50000,45000); // BIN1
	setpwm(3,1,50000,30000); // BIN2

	delay_1ms(5000);

	/* 左转 */
	setpwm(5,9,200000,14222 + 5555);
	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2
	// 右轮
	setpwm(2,1,50000,20000); // BIN1
	setpwm(3,1,50000,45000); // BIN2

	delay_1ms(2000);

	/* 摆正车身 */
	setpwm(5,9,200000,14222);
	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2
	// 右轮
	setpwm(2,1,50000,30000); // BIN1
	setpwm(3,1,50000,45000); // BIN2

	delay_1ms(500);
}

void Catch_it(void)
{
	Stop();
	delay_1ms(2000);
	Capture_set(14500);
	delay_1ms(2000);

	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2

	// 右轮
	setpwm(2,1,50000,30000); // BIN1
	setpwm(3,1,50000,45000); // BIN2
}

void Release_it(void)
{
	setpwm(5,9,200000,14222); // 转向舵机
	delay_1ms(2000);
	Stop();
	delay_1ms(2000);
	Capture_set(20000);
	while(1);
}


int main(void)
{
	led_config();
	oled_config();

	__enable_irq();
	ECLIC_Register_IRQ(UART0_IRQn, ECLIC_NON_VECTOR_INTERRUPT,
	                                    ECLIC_LEVEL_TRIGGER, 1, 1,
	                                    uart0_handler);

	uart_init(UART0, 115200,UART_BIT_LENGTH_8);
	uart_config_stopbit(UART0,UART_STOP_BIT_2);

	uart_set_rx_watermark(UART0,0);
	uart_enable_rxint(UART0);

	// 等待语音识别模块和K210完成通信
	delay_1ms(3000);

	// 左轮
	setpwm(0,1,50000,45000); // AIN1
	setpwm(1,1,50000,30000); // AIN2

	// 右轮
	setpwm(2,1,50000,30000); // BIN1
	setpwm(3,1,50000,45000); // BIN2

	setpwm(4,9,200000,20000);// 夹子
	setpwm(5,9,200000,14222); // 转向舵机
	//delay_1ms(6000);

	OLED_Init();
	OLED_Fill(0x00);

	uint8_t i=0,j=0,q=0;

    while(1)
    {
    	 delay_1ms(100);
    	 j++;
		 sprintf((unsigned char *)OLED_BUF,"x:%d, y:%d ",x,y);
		 OLED_ShowString(1,1,OLED_BUF,1);
		 sprintf((unsigned char *)OLED_BUF,"w:%d, h:%d ",w,h);
		 OLED_ShowString(1,1+10,OLED_BUF,1);

		 /* 循迹 */
		 P_control(x);

		 /* 夹子工作 */
//		 if(j>60 && j<70)
		 if(j>55)
		 {
			 if(w>50)
			 {
				 if(q==0)
				 {
//
					 delay_1ms(1650);
					 Catch_it();
					 q=1;
				 }

			 }
		 }

		 // 返回起点
		 if(h<10 && w<50)
		 {
			 if(i==0)
			 {
				 back();
				 goto adc;
			 }
			 if(i==1)
			 {
				 Release_it();
			 }
			 adc: i=1;
		 }

    }
}


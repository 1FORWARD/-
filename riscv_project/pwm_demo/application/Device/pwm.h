/*
 * pwm.h
 *
 *  Created on: 2022年9月19日
 *      Author: zhang
 */
#include <stdio.h>
#include "nuclei.h"

#ifndef APPLICATION_DEVICE_PWM_H_
#define APPLICATION_DEVICE_PWM_H_

typedef struct {
	uint16_t PWM_CH;
	uint32_t PWM_Period;
	uint32_t PWM_Duty;
}PWM_InitTypeDef;

#define ENABLE  1
#define DISABLE 0

#define REGP(x) ((volatile unsigned int*)(x))
#define REG(x) (*((volatile unsigned int*)(x)))
#define REGP_8(x) (((volatile uint8_t*)(x)))

#define AHB_REGISTER_BASE_ADDR 0x40000000

#define PWM_EN	  	    AHB_REGISTER_BASE_ADDR + 0x0
#define PWM_DIV     	AHB_REGISTER_BASE_ADDR + 0x4

#define PWM_PERIOD0	    AHB_REGISTER_BASE_ADDR + 0x8
#define PWM_PERIOD1     AHB_REGISTER_BASE_ADDR + 0xC
#define PWM_PERIOD2     AHB_REGISTER_BASE_ADDR + 0x10
#define PWM_PERIOD3     AHB_REGISTER_BASE_ADDR + 0x14
#define PWM_PERIOD4     AHB_REGISTER_BASE_ADDR + 0x18
#define PWM_PERIOD5     AHB_REGISTER_BASE_ADDR + 0x1C
#define PWM_PERIOD6     AHB_REGISTER_BASE_ADDR + 0x20
#define PWM_PERIOD7     AHB_REGISTER_BASE_ADDR + 0x24

#define PWM_DUTY0       AHB_REGISTER_BASE_ADDR + 0x28
#define PWM_DUTY1       AHB_REGISTER_BASE_ADDR + 0x2C
#define PWM_DUTY2       AHB_REGISTER_BASE_ADDR + 0x30
#define PWM_DUTY3       AHB_REGISTER_BASE_ADDR + 0x34
#define PWM_DUTY4       AHB_REGISTER_BASE_ADDR + 0x38
#define PWM_DUTY5       AHB_REGISTER_BASE_ADDR + 0x3C
#define PWM_DUTY6       AHB_REGISTER_BASE_ADDR + 0x40
#define PWM_DUTY7       AHB_REGISTER_BASE_ADDR + 0x44



#define pwm_en 		REG(PWM_EN)
#define pwm_div     REG(PWM_DIV)

#define pwm_period0 REG(PWM_PERIOD0)
#define pwm_period1 REG(PWM_PERIOD1)
#define pwm_period2 REG(PWM_PERIOD2)
#define pwm_period3 REG(PWM_PERIOD3)
#define pwm_period4 REG(PWM_PERIOD4)
#define pwm_period5 REG(PWM_PERIOD5)
#define pwm_period6 REG(PWM_PERIOD6)
#define pwm_period7 REG(PWM_PERIOD7)

#define pwm_duty0	REG(PWM_DUTY0)
#define pwm_duty1	REG(PWM_DUTY1)
#define pwm_duty2	REG(PWM_DUTY2)
#define pwm_duty3	REG(PWM_DUTY3)
#define pwm_duty4	REG(PWM_DUTY4)
#define pwm_duty5	REG(PWM_DUTY5)
#define pwm_duty6	REG(PWM_DUTY6)
#define pwm_duty7	REG(PWM_DUTY7)

void pwm_cmd(uint8_t ch , uint8_t status);

void set_pwm_clkdiv(uint8_t ch , uint8_t div);
void set_pwm_period(uint8_t ch , uint32_t period);
void set_pwm_duty(uint8_t ch , uint32_t duty);

uint32_t get_pwm_period(uint8_t ch);
uint32_t get_pwm_duty(uint8_t ch);

#endif /* APPLICATION_DEVICE_PWM_H_ */

/*
 * pwm.c
 *
 *  Created on: 2022年9月19日
 *      Author: zhang
 */

#include <stdio.h>
#include "pwm.h"

void pwm_cmd(uint8_t ch , uint8_t status){
	if (status) {
		pwm_en |= 1<<ch;
	}
	else
	{
		pwm_en &= ~(1<<ch);
	}
}

void set_pwm_clkdiv(uint8_t ch , uint8_t div){
	pwm_div |= div<<(ch*4);
}

void set_pwm_period(uint8_t ch , uint32_t period){
	switch (ch) {
		case 0:
			pwm_period0 = period;
			break;
		case 1:
			pwm_period1 = period;
			break;
		case 2:
			pwm_period2 = period;
			break;
		case 3:
			pwm_period3 = period;
			break;
		case 4:
			pwm_period4 = period;
			break;
		case 5:
			pwm_period5 = period;
			break;
		case 6:
			pwm_period6 = period;
			break;
		case 7:
			pwm_period7 = period;
			break;
		default:
			break;
	}
}

void set_pwm_duty(uint8_t ch , uint32_t duty){
	switch (ch) {
		case 0:
			pwm_duty0 = duty;
			break;
		case 1:
			pwm_duty1 = duty;
			break;
		case 2:
			pwm_duty2 = duty;
			break;
		case 3:
			pwm_duty3 = duty;
			break;
		case 4:
			pwm_duty4 = duty;
			break;
		case 5:
			pwm_duty5 = duty;
			break;
		case 6:
			pwm_duty6 = duty;
			break;
		case 7:
			pwm_duty7 = duty;
			break;
		default:
			break;
	}
}


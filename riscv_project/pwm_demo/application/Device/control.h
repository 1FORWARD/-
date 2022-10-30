#include <stdio.h>
#include "pwm.h"

#ifndef APPLICATION_DEVICE_CONTROL_H_
#define APPLICATION_DEVICE_CONTROL_H_

void setpwm(uint8_t ch1, uint8_t div1, uint32_t period1, uint32_t duty1);

void Go_Forward(uint32_t PWM);
void Back_Forward(uint32_t PWM);
void Go_Right_Forward(uint32_t PWM);
void Go_Left_Forward(uint32_t PWM);
void Capture_set(uint32_t PWM);
void Stop(void);



#endif /* APPLICATION_DEVICE_PWM_H_ */

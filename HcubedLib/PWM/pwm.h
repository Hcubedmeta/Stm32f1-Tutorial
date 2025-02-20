#ifndef ___PWM_H___
#define ___PWM_H___

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void setup_CHx(void);
void timer_PWM(void);
//void Delay_ms(uint16_t _time);
void pwm_Init(void);
void pin_pwm_Init(void);

#endif

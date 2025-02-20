#ifndef ____DELAY_H___
#define ____DELAY_H___

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

void timer_config(void);
void Delay1Ms(void);
void DelayUs(uint32_t delay);
void DelayMs(uint32_t u32DelayInMs);

#endif
#include "delay.h"
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM



void timer_config(void)
{
	TIM_TimeBaseInitTypeDef timer_init;
//	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	timer_init.TIM_CounterMode = TIM_CounterMode_Up;
	timer_init.TIM_Period = 0xFFFF;
	timer_init.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2,&timer_init);
	
	TIM_Cmd(TIM2,ENABLE);
}
void Delay1Ms(void)
{
	
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
}

void DelayUs(uint32_t delay)
{
	
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < delay) {
	}
}

void DelayMs(uint32_t u32DelayInMs)
{
	
	while (u32DelayInMs) {
		Delay1Ms();
		--u32DelayInMs;
	}
}
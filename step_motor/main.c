#include "stm32f10x.h"                  // Device header
#include "pwm.h"
void Delay_ms(uint16_t _time);

int main(void){
	GPIO_InitTypeDef pin;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	pin.GPIO_Mode = GPIO_Mode_Out_PP;
	pin.GPIO_Pin = GPIO_Pin_9;
	pin.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&pin);
	pin_pwm_Init();
	pwm_Init();
	while(1)
	{

		
		GPIO_SetBits(GPIOA,GPIO_Pin_9);
		TIM1 ->CCR1 = 1000;
		Delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);
		TIM1->CCR1 = 1000;
		Delay_ms(1000); 

	}
}
void Delay_ms(uint16_t _time){
	uint16_t i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2AFF; j++);
	}
}

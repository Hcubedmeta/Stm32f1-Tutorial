#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
/*******************************************/
char ma_led[]={0x00c0,0x00f9,0x00a4,0x00b0,0x0099, 
0x0092,0x0082,0x00f8,0x0080,0x0090}; 

/*********************************************/
int main(void)
{
	GPIOx_Init(GPIOA, GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |
	GPIO_Pin_5 |GPIO_Pin_6 ,OUTPUT,Speed_50MHz);
	while(1)
	{
		for(int i =0; i < 10; i++)
		{
			GPIOA->ODR = ma_led[i];
			delay(200);
		}
	}
}
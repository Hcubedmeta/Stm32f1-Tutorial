#include "stm32f10x.h"                  // Device header
void delay (int time);
void shiftout(int data);
void Hienthi(int t);
char ma_led[]={0x0c0,0x0f9,0x00a4,0x0b0,0x099, 
0x092,0x082,0x0f8,0x080,0x090}; 
int main(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOC ->CRL &= 0x0FFFFFFF; // clear all bits PC 7
	GPIOC ->CRL |= 0x30000000; // configure for pc 7
	
	GPIOC ->CRH &= 0xFFF0FFFF; // clear all bits pc12
	GPIOC ->CRH |= 0x00030000; // configure for pc 12
	
	GPIOA ->CRL &= 0xFFFFFFF0; // clear all bits pa0
	GPIOA ->CRL |= 0x00000003; // configure for pa0
	
	GPIOA ->CRL &= 0xFFFFFF0F; // clear all bits pa1
	GPIOA ->CRL |= 0x00000030; // configure for pa1
	
	GPIOA ->CRL &= 0xFFFFF0FF; // clear all bits pa2
	GPIOA ->CRL |= 0x00000300; // configure for pa2
	while(1)
	{
		for(int t =0;t < 100;t++)
		{ 
			Hienthi(t);
//			GPIOC ->ODR ^= 0x0080; //  toggle 
//			GPIOC ->ODR ^= 0x1000;
			delay(100);
		}
	}
}
void delay (int time)
{
	int i,j;
	for( i =0; i < time; i++)
	{
		for(j =0; j < 0x2aff; j ++);
	}
}
void shiftout(int data)
{
	for(int i =0; i< 8;i++)
	{ /* serial data input*/
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,data << i &0x80);
		/*shiftclock*/
//		GPIOA -> ODR |= 0x0002;
//		GPIOA -> ODR &=~ 0x0002;
//		GPIOA -> ODR |= 0x0004;
//		GPIOA -> ODR &=~ 0x0004;
		GPIOA -> BSRR = 0x00000002;
		GPIOA -> BRR = 0x00000002;
		GPIOA -> BSRR = 0x00000004;
		GPIOA -> BRR =  0x00000004;
	}
}
void Hienthi(int led)
{
	shiftout(ma_led[led % 10]);
	shiftout(ma_led[led / 10]);
}
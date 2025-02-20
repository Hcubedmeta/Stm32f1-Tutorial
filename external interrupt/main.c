11#include "stm32f10x.h"                  // Device header

uint16_t signal =0;
void delay(int time);
void EXTI1_IRQHandler(void) ;
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOC -> CRL &= 0x0FFFFFFF; // pc7
	GPIOC -> CRL |= 0x30000000;
	GPIOC -> CRH &= 0xFFF0FFFF; // pc12
	GPIOC -> CRH |= 0x00030000;
	
	GPIOA -> CRL &= 0xFFFFFFF0; // pa0
	GPIOA -> CRL |= 0x00000008;
	__disable_irq();
	AFIO->EXTICR[0] &= ~(0xF << 0); // Clear all bits for EXTI0 (PA0)
	AFIO->EXTICR[0] |= (0x0 << 0);  // Configure EXTI0 to be triggered by PA0
	EXTI->IMR |= EXTI_IMR_MR0;      // Unmask EXTI0 interrupt
	EXTI->RTSR |= EXTI_RTSR_TR0;    // Enable rising edge trigger for EXTI0
	NVIC_EnableIRQ(EXTI0_IRQn);     // Enable EXTI0 interrupt in NVIC
	__enable_irq();
		
//	GPIOA -> CRL &= 0xFFFFFF0F; // pa1
//	GPIOA -> CRL |= 0x00000080;
//	__disable_irq();
//	AFIO->EXTICR[0] &= ~(0xF << 4); // clear all bits exti1
//	AFIO->EXTICR[0] |= (0x0 << 4); // configure exti1
//	EXTI->IMR |= EXTI_IMR_MR1;
//	EXTI->RTSR |= EXTI_RTSR_TR1;
//	NVIC_EnableIRQ(EXTI1_IRQn);
//	__enable_irq();
	
	
	while(1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_7,signal);
		if(signal)
		{
			delay(20);
			GPIOC -> ODR ^= 0x1000; // pc12
//			GPIOC -> ODR ^= 0x0080; // pc7
			delay(200);
		}
		else
		{
			GPIOC -> BSRR = 0x00001000; // pc12
//			GPIOC -> BSRR = 0x00000080; // pc7
		}
	}
}
void delay(int time)
{
	int i,j;
	for(i =0; i < time; i ++)
	{
		for(j = 0; j< 0x2aff; j++);
	}
}
void EXTI0_IRQHandler(void) 
{
	if(EXTI -> PR & EXTI_PR_PR0) // check the flag exti0
	{
	EXTI -> PR |= EXTI_PR_PR0; // delete the flag extio
	if(signal)
	{
		(signal) =0;
	}
	else
	{
		(signal) =1;
	}
}
}
#include "stm32f10x.h"                  // Device header
#include "GPIO_Drive.h"
#include "Delay_sys.h"
//char ma_led[]={0x0c0,0x0f9,0x00a4,0x0b0,0x099, 
//0x092,0x082,0x0f8,0x080,0x090};

void SysTick_Handler(void);
int main(void)
{
	systick_init();
	init_GPIO(PA,1,IN,Input_pp);
	init_GPIO(PC,12,O_50MHz,Output_pp);
	init_GPIO(PC,7,O_50MHz,Output_pp);
	__disable_irq();
	SysTick ->CTRL =0;
	SysTick ->LOAD = 7200000-1; // delay = Load value / clock Systick (72MHz) 0.1 seconds
	SysTick ->VAL =0;
	SysTick ->CTRL =7;
	__enable_irq();
	while(1)
	{
	}
}
void SysTick_Handler(void)
{
	if(R_GPIO(PA,1) == 1)
		{
			Toggle_GPIO(PC,7);
			Delay_Ms(1000);
			
		}
		else 
		{
			Toggle_GPIO(PC,12);
			Delay_Ms(1000);
		}
}

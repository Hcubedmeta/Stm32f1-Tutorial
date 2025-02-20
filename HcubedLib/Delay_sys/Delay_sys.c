#include "Delay_sys.h"

void systick_init(void)
{
	SysTick ->CTRL = 0;
	SysTick ->LOAD = 0x00FFFFFF;
	SysTick ->VAL = 0;
	SysTick ->CTRL |= 5;
}
void Delaymilis(void)
{
	SysTick ->LOAD = 72000-1;
	SysTick ->VAL = 0;
	while((SysTick ->CTRL & 0x00010000) == 0);
}
void Delay_Ms(unsigned long t)
{
	for(;t > 0;t --)
	{
		Delaymilis();
	}
}
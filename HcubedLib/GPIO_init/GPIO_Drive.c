#include "GPIO_Drive.h"

void init_GPIO(unsigned short port,unsigned short pin,unsigned short dir,unsigned short opt)
{
	volatile unsigned long * CR;
	unsigned short tPIN = pin;
	unsigned short offset = 0x00; // address the control resister low
	
	if(pin > 7)
	{
		tPIN -= 8;
		offset = 0x01;
	}
	if(port == 1)
	{
		RCC_APB2ENR |= 4; // enabling port A
		CR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if(port == 2)
	{
		RCC_APB2ENR |= 8; // enabling port B
		CR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else if(port == 3)
	{
		RCC_APB2ENR |= 0x10; // enabling port C (or address 16)
		CR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	else if(port == 4)
	{
		RCC_APB2ENR |= 0x20; // enabling port D ( or address 20)
		CR = (volatile unsigned long *)(&GPIO_D + offset);
	}
	*CR &= ~(unsigned long)(0xf <<(tPIN)*4); // reset the target pin
	*CR |= (unsigned long)((dir <<(tPIN*4)) | (opt <<(tPIN*4+2)));
}
int R_GPIO(unsigned short port,unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned short offset = 0x02;
	int state;
	if(port == 1)
	{
		IDR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if(port == 2)
	{
		IDR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else if(port == 3)
	{
		IDR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	else if(port == 4)
	{
		IDR = (volatile unsigned long *)(&GPIO_D + offset);
	}
	state = ((*IDR & (1<<pin)) >> pin);
	return state;
}
void W_GPIO(unsigned short port,unsigned short pin,unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned short offset = 0x03;
	if(port == 1)
	{
		ODR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if(port == 2)
	{
		ODR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else if(port == 3)
	{
		ODR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	else if(port == 4)
	{
		ODR = (volatile unsigned long *)(&GPIO_D + offset);
	}
	state ? (* ODR |= (state << pin)) : (*ODR &= ~(1<<pin));
}

void Toggle_GPIO(unsigned short port,unsigned short pin)
{
	if(R_GPIO(port,pin))
	{
		W_GPIO(port,pin,0);
	}
	else 
	{
		W_GPIO(port,pin,1);
	}
}

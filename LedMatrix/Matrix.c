#include "stm32f10x.h"                  // Device header
#include "GPIO.h"

int main(void)
{
	/* cau hinh chan A */
	GPIOx_Init(GPIOA,GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7,OUTPUT,Speed_50MHz);
	/* cau hinh chan B */
	GPIOx_Init(GPIOB,GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15,OUTPUT,Speed_50MHz);
	
	/* mang cot */
	unsigned char cot[] ={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	unsigned int hang[] ={0xffff,0x80ff,0x77ff,0x77ff,0x77ff,0x77ff,0x80ff,0xffff};
	while(1)
	{
		for(int i =0; i<8; i++)
		{
			GPIOB->ODR = hang[i];
			GPIOA->ODR = cot[i];
			delay(1);
		}
	}
}


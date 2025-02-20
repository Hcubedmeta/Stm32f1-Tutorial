#include "SPI_Drive.h"

void SPI_init(unsigned short Spi)
{
	if(Spi == 1)
	{
		RCC->APB2ENR |= 1; // enable clocks AFIO
		RCC->APB2ENR |= 0x1000; // enable clocks SPI1
		init_GPIO(PA,4,O_50MHz,Output_pp);
		init_GPIO(PA,5,O_50MHz,Output_alternate_pp);
		init_GPIO(PA,6,IN,Input_pp);
		init_GPIO(PA,7,O_50MHz,Output_alternate_pp);
		SPI1->CR1 |= 0x4; // master mode
		SPI1->CR1 |= 0x31; // fPCLK/128
		SPI1->CR2 |= 0x4; // SS ouput enable
		SPI1->CR1 |= 0x40; // SPI periperal
		W_GPIO(PA,4,HIGH);
	}
	else if(Spi == 2)
	{
		RCC->APB2ENR |= 1; // enable clocks AFIO
		RCC->APB1ENR |= 0x4000; // enable clocks SPI1
		init_GPIO(PB,12,O_50MHz,Output_pp);
		init_GPIO(PB,13,O_50MHz,Output_alternate_pp);
		init_GPIO(PB,14,IN,Input_pp);
		init_GPIO(PB,15,O_50MHz,Output_alternate_pp);
		SPI2->CR1 |= 0x4; // master mode
		SPI2->CR1 |= 0x31; // fPCLK/128
		SPI2->CR2 |= 0x4; // SS ouput enable
		SPI2->CR1 |= 0x40; // SPI periperal
		W_GPIO(PB,12,HIGH);
	}
}
void SPI_Tx(unsigned short Spi,char var)
{
	if(Spi == 1)
	{
		W_GPIO(PA,4,LOW);
		SPI1->DR |= var;
		while(SPI1->SR & 0x80){}
		W_GPIO(PA,4,HIGH);
	}
	else if(Spi == 2)
	{
		W_GPIO(PB,12,LOW);
		SPI2->DR |= var;
		while(SPI2->SR & 0x80){}
		W_GPIO(PB,12,HIGH);
	}
}
void SPI_Tx_array(unsigned short Spi,char arr[])
{
	int i = 0;
	if(Spi == 1)
	{
		W_GPIO(PA,4,LOW);
		while(arr[i])
		{
			SPI1->DR |= arr[i];
			while(SPI1->SR & 0x80){}
			i++;
		}
		W_GPIO(PA,4,HIGH);
	}
	else if(Spi == 2)
	{
		W_GPIO(PB,12,LOW);
		while(arr[i])
		{
			SPI2->DR |= arr[i];
			while(SPI2->SR & 0x80){}
			i++;
		}
		W_GPIO(PB,12,HIGH);
	}
}

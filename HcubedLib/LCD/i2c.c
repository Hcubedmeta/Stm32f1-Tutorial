#include "i2c.h"


/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA

*/


// configure 2 channel i2c
void i2c_init(char i2c,unsigned short speed_mode)
{
	RCC->APB2ENR |= 1; 
	
	if(i2c==1)
	{
		RCC->APB1ENR |= 0x200000;
		// Pin enable 
		init_GPIO(PB,6,O_50MHz,Output_alternate_op);
		init_GPIO(PB,7,O_50MHz,Output_alternate_op);
		I2C1->CR1 |= 0x8000; //   SWRST: Software reset
		I2C1->CR1 &= ~0x8000; // clear
		I2C1->CR2 =0x8; // PCLK1 = 8MHz // recepi : ccr = PLCK1 / (I2c speed x 2) i2c speed chuan la 100kHz vaf fast mode la 400khz, 
		I2C1->CCR = speed_mode; // CCR lan luot la 40 va 7 tuy mode
		I2C1->TRISE = 0x9; // PCLK1 + 1
		I2C1->CR1 |= 1; // kich hoat chuc nang giao tiep
	}
	else if(i2c==2)
	{
		RCC->APB1ENR |= 0x400000;
		// Pin enable 
		init_GPIO(PB,10,O_50MHz,Output_alternate_op);
		init_GPIO(PB,11,O_50MHz,Output_alternate_op);
		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		I2C2->CR2 =0x8;
		I2C2->CCR = speed_mode;
		I2C2->TRISE = 0x9;
		I2C2->CR1 |= 1;
	}

}

// Start step
void i2c_start(char i2c)
{
	if(i2c==1)
	{
		I2C1->CR1 |= 0x100; // start
		while (!(I2C1->SR1 & 1)){}; // vong lap kiem tra trang thai SB cua SR1 co dc dua len 1 hay ko
	}
	else if(i2c==2)
	{
		I2C2->CR1 |= 0x100;
		while (!(I2C2->SR1 & 1)){};
	}
}
// Sending the address + R or Write	
void i2c_add(char i2c, char address,char RW)
{
	volatile int tmp;
	if(i2c==1)
	{
		I2C1->DR = (address|RW); // truy xuat den address cua PCF8574
		while((I2C1->SR1 & 2)==0){}; // luu giu co trang thai cua i2c(ADDR)
		while((I2C1->SR1 & 2)){
			tmp = I2C1->SR1; // cho cac co bao hieu cuar i2c
			tmp = I2C1->SR2; // clear cac co loi va cung cap them ve tinh trang i2c
			if((I2C1->SR1 & 2)==0)
			{
				break;
			}
		}
	}
	else if(i2c==2)
	{
		I2C2->DR = (address|RW);
		while((I2C2->SR1 & 2)==0){};
		while((I2C2->SR1 & 2)){
			tmp = I2C2->SR1;
			tmp = I2C2->SR2;
			if((I2C2->SR1 & 2)==0)
			{
				break;
			}
		}
	}

}
// Sending data step
void i2c_data(char i2c,char data)
{
	if(i2c==1)
	{
		while((I2C1->SR1 & 0x80) == 0){} // truyen du lieu
			I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0){}
	}
	else if(i2c==2)
	{
		while((I2C2->SR1 & 0x80) == 0){}
			I2C2->DR = data;
		while((I2C2->SR1 & 0x80) == 0){}
	}
}
// Stop step
void i2c_stop(char i2c)
{
	volatile int tmp;
	if(i2c==1)
	{
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}
	else if(i2c==2)
	{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}
// i2c_write()
void i2c_write(char i2c, char address,char data[])
{
	int i = 0;
	
	i2c_start(i2c);
	
	i2c_add(i2c, address,0);
	
	while(data[i])
		{
			i2c_data(i2c,data[i]);
			i++;
		}
	i2c_stop(i2c);
}

// Receiving data
char i2c_rx(char i2c, char ACK_NACK)
{
	char temp;
	if(i2c==1)
	{
		I2C1->CR1 |= 0x0400;
		while((I2C1->SR1 & 0x40)==0){}
			temp = I2C1->DR;
		if(ACK_NACK)
		{
			I2C1->CR1 &= ~0x0400;
		}
		
	}
	else if(i2c==2)
	{
		I2C2->CR1 |= 0x0400;
		while((I2C2->SR1 & 0x40)==0){}
			temp = I2C2->DR;
		if(ACK_NACK)
		{
			I2C2->CR1 &= ~0x0400;
		}
		
	}
	return temp;
}

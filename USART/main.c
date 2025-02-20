#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART

#include "string.h"
void USART_Config();
void GPIO();
void delay(int time);
/******************giao tiep usart: gui ki tu 'B' -> den chan PC13 blink
*********************************** gui ki tu 'T' -> den chan PA0 blink
*********************************************toc do baud =9600********/

int main(void)
{
	char data;
	char Arr[] = "HA HUY HOANG\n";
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//  bat led pc13
	GPIO_SetBits(GPIOA,GPIO_Pin_0); // bat led pa0
	USART_Config();
	GPIO();
	while(1)
	{
		data = USART_ReceiveData(USART1);
		if (data == 'B')
		{
			USART_SendData(USART1,'A'); 
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			delay(100);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			delay(100);
		}
		else if (data == 'T')
		{
				USART_SendData(USART1,'C');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);
				delay(100);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				delay(100);
		}
		else if( data == 'H')
		{
		for(int i =0; i <strlen(Arr); i++)
		{
			USART_SendData(USART1,Arr[i]);
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			delay(100);
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			delay(100);
		}
	}
	}
}
void USART_Config()
{/*** Tx la truyen , RX la nhan***********/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef usart;
	usart.USART_BaudRate =9600;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Tx |USART_Mode_Rx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits =  USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&usart);
	USART_Cmd(USART1,ENABLE);
	
}

void GPIO()
{
	/********** cau hinh chan Rx-PA9***************/
	/********** cau hinh chan Tx-PA10***************/
	/********** cau hinh chan PC13 ***********/
	/********** cau hinh chan PA0 ***********/
//	init_GPIO(PA,9,O_AF_PP,O_50MHz);
//	init_GPIO(PA,10,IN,O_50MHz);
//	init_GPIO(PC,13,O_GP_PP,O_50MHz);
//	init_GPIO(PA,0,O_GP_PP,O_50MHz);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_struc;
	GPIO_struc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_struc.GPIO_Pin = GPIO_Pin_0;
	GPIO_struc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_struc);
	
	GPIO_struc.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_struc.GPIO_Pin = GPIO_Pin_13;
	GPIO_struc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_struc);
	
	GPIO_struc.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_struc.GPIO_Pin = GPIO_Pin_10;
	GPIO_struc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_struc);
	
	GPIO_struc.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_struc.GPIO_Pin = GPIO_Pin_9;
	GPIO_struc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_struc);
}
void delay(int time)
{
	int i,j;
	for(i =0; i< time; i++)
	for(j =0; j <0x2aff; j++)
	{
	}
}

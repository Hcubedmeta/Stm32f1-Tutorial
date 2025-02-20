#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "systick.h"
#include "pwm.h"

int dem = 0;
unsigned char data1;
unsigned char data2;
unsigned char data3;
unsigned char data;
/*-------------------setup GPIO---------------------*/
void setup_GPIO(void)
{
	/*----------------port A------------------*/
	GPIOx_Init(GPIOA,GPIO_Pin_4,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOA,GPIO_Pin_5,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOA,GPIO_Pin_6,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOA,GPIO_Pin_7,OUTPUT,Speed_50MHz);
//	/*----------------port B------------------*/
	GPIOx_Init(GPIOB,GPIO_Pin_0,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_1,INPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_3,INPUT,Speed_50MHz); // change the rc into line
	GPIOx_Init(GPIOB,GPIO_Pin_10,INPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_11,INPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_12,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_13,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_14,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOB,GPIO_Pin_15,OUTPUT,Speed_50MHz);
	/*----------------port C------------------*/
//	GPIOx_Init(GPIOC,GPIO_Pin_13,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOC,GPIO_Pin_14,OUTPUT,Speed_50MHz);
	GPIOx_Init(GPIOC,GPIO_Pin_15,OUTPUT,Speed_50MHz);
}
/*-------------------setup UART---------------------*/
void setup_UART(void)
{
	/********** cau hinh chan Rx-PA9***************/
	GPIOx_Init(GPIOA,GPIO_Pin_9,AF_PP,Speed_50MHz);
	/********** cau hinh chan Tx-PA10***************/
	GPIOx_Init(GPIOA,GPIO_Pin_10,INPUT,Speed_50MHz);
	
}
/*-------------------USART_config---------------------*/
int USART_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef usart;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	usart.USART_BaudRate =9600;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Tx |USART_Mode_Rx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits =  USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	
	/*-------------------on/off RXNE---------------------*/
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    
	NVIC_Init(&NVIC_InitStruct);
	USART_Init(USART1,&usart);
	
	USART_Cmd(USART1,ENABLE);
}


int main(void)
{
	USART_Config();
	setup_GPIO();
	setup_UART();
	setup_CHx();
	timer_PWM();
	
	while(1)
	{
		if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  {
				while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) { }
		}
		data = USART_ReceiveData(USART1);
		if (data == '0')
		{ // duty 10%
			TIM2-> CCR1= 0;
			TIM2-> CCR2= 0;
			TIM2-> CCR3= 0;
			TIM2-> CCR4= 0;
		}
		if (data == '1')
		{ // duty 10%
			TIM2-> CCR1= 99;
			TIM2-> CCR2= 99;
			TIM2-> CCR3= 99;
			TIM2-> CCR4= 99;
		}
		if (data == '2')
		{ // duty 20%
			TIM2-> CCR1= 199;
			TIM2-> CCR2= 199;
			TIM2-> CCR3= 199;
			TIM2-> CCR4= 199;
		}
		if (data == '3')
		{ // duty 30%
			TIM2-> CCR1= 299;
			TIM2-> CCR2= 299;
			TIM2-> CCR3= 299;
			TIM2-> CCR4= 299;
		}
		if (data == '4')
		{ // duty 40%
			TIM2-> CCR1= 399;
			TIM2-> CCR2= 399;
			TIM2-> CCR3= 399;
			TIM2-> CCR4= 399;
		}
		if (data == '5')
		{ // duty 50%
			TIM2-> CCR1= 499;
			TIM2-> CCR2= 499;
			TIM2-> CCR3= 499;
			TIM2-> CCR4= 499;
		}
		if (data == '6')
		{ // duty 60%
			TIM2-> CCR1= 599;
			TIM2-> CCR2= 599;
			TIM2-> CCR3= 599;
			TIM2-> CCR4= 599;
		}
		if (data == '7')
		{ // duty 70%
			TIM2-> CCR1= 699;
			TIM2-> CCR2= 699;
			TIM2-> CCR3= 699;
			TIM2-> CCR4= 699;
		}
		if (data == '8')
		{ // duty 80%
			TIM2-> CCR1= 799;
			TIM2-> CCR2= 799;
			TIM2-> CCR3= 799;
			TIM2-> CCR4= 799;
		}
		if (data == '9')
		{ // duty 109%
			TIM2-> CCR1= 899;
			TIM2-> CCR2= 899;
			TIM2-> CCR3= 899;
			TIM2-> CCR4= 899;
		}
		if (data == 'q')
		{ // duty 100%
			TIM2-> CCR1= 0xFFFF;
			TIM2-> CCR2= 0xFFFF;
			TIM2-> CCR3= 0xFFFF;
			TIM2-> CCR4= 0xFFFF;
		}
		if (data == 'B')
		{
			USART_SendData(USART1,'B'); 
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOA,GPIO_Pin_4 |GPIO_Pin_6);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15);
			delay(50);
			GPIO_SetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14);
			delay(50);
		}
		else if (data == 'F')
		{
				USART_SendData(USART1,'F');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7);
				GPIO_ResetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14);
				delay(50);
				GPIO_SetBits(GPIOA,GPIO_Pin_4 |GPIO_Pin_6);
				GPIO_SetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15);
				delay(50);
		}
		else if (data == 'L')
		{
				USART_SendData(USART1,'L');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7|GPIO_Pin_4 );
				GPIO_ResetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14 |GPIO_Pin_13 );
				delay(50);
				GPIO_SetBits(GPIOA,GPIO_Pin_6 );
				GPIO_SetBits(GPIOB,GPIO_Pin_15);
				delay(50);
		}
		else if (data == 'R')
		{
				USART_SendData(USART1,'R');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7|GPIO_Pin_6 );
				GPIO_ResetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14  |GPIO_Pin_15);
				delay(50);
				GPIO_SetBits(GPIOA,GPIO_Pin_4 );
				GPIO_SetBits(GPIOB,GPIO_Pin_13);
				delay(50);
		}
		else if (data == 'H')
		{
				USART_SendData(USART1,'H');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_4|GPIO_Pin_6 );
				GPIO_ResetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15);
				delay(50);
				GPIO_SetBits(GPIOA,GPIO_Pin_7 );
				GPIO_SetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14);
				delay(50);
		}
		else if (data == 'J')
		{
				USART_SendData(USART1,'J');
				USART_ClearFlag(USART1,USART_FLAG_TXE);
				GPIO_ResetBits(GPIOA,GPIO_Pin_6 |GPIO_Pin_7|GPIO_Pin_4 );
				GPIO_ResetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15);
				delay(50);
				GPIO_SetBits(GPIOA,GPIO_Pin_5 );
				GPIO_SetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14);
				delay(50);
		}
		else if (data == 'G')
		{
			USART_SendData(USART1,'G'); 
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12 |GPIO_Pin_14 |GPIO_Pin_13);
			delay(50);
			GPIO_SetBits(GPIOA,GPIO_Pin_4 |GPIO_Pin_6);
			GPIO_SetBits(GPIOB,GPIO_Pin_15 );
			delay(50);
		}
		else if (data == 'I')
		{
			USART_SendData(USART1,'I'); 
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5 |GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_14 |GPIO_Pin_15 |GPIO_Pin_12);
			delay(50);
			GPIO_SetBits(GPIOA,GPIO_Pin_4 |GPIO_Pin_6);
			GPIO_SetBits(GPIOB,GPIO_Pin_13 );
			delay(50);
		}
		else if (data == 'S')
		{
			USART_SendData(USART1,'S'); 
			USART_ClearFlag(USART1,USART_FLAG_TXE);
			GPIO_ResetBits(GPIOA,GPIO_Pin_4 |GPIO_Pin_6 | GPIO_Pin_5 |GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15 |GPIO_Pin_14 |GPIO_Pin_12);
		}
		else if(data == 'W')
	{
		USART_SendData(USART1,'W');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	}
	else if(data == 'w')
	{
		USART_SendData(USART1,'w');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
	else if(data == 'U')
	{
		USART_SendData(USART1,'U');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	}
	else if(data == 'u')
	{
		USART_SendData(USART1,'u');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
	}
	else if(data == 'V')
	{
		USART_SendData(USART1,'V');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);
	}
	else if(data == 'v')
	{
		USART_SendData(USART1,'v');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_SetBits(GPIOC,GPIO_Pin_14);
	}
	else if(data == 'X')
	{
		USART_SendData(USART1,'X');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
	}
	else if(data == 'x')
	{
		USART_SendData(USART1,'x');
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
		
}
	


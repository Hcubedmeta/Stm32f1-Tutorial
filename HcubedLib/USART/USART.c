#include <USART.h>

#define MAX 100

char vrc_Getc; // bien kieu char, dung de nhan du lieu Tu PC gui xuong
int vri_Stt; // bien danh dau trang thai
int vri_Count = 0; // bien dem
char vrc_Res[MAX];// Mang kieu char vrc_Res[MAX]: mang luu tru tam thoi

void usart1_Init(void)
{
	GPIO_InitTypeDef gpio_typedef;
	USART_InitTypeDef usart_typedef;
	/*** enable clock****/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/********** cau hinh chan Rx-PA9***************/
	gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_typedef.GPIO_Pin = GPIO_Pin_9;
	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_typedef);
	/********** cau hinh chan Tx-PA10***************/
	gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_typedef.GPIO_Pin = GPIO_Pin_10;
	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_typedef);
		/******USART configure********/
	usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart_typedef);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); // bat ngat USART chi dinh
	/**********Enable USART1 global interupt **************/
	NVIC_EnableIRQ(USART1_IRQn);
	USART_Cmd(USART1,ENABLE);
	}
void uart_Sendchar(char _chr)
{
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
void uart_SendStr(char *str)
{
	while(*str != NULL)
	{
		uart_Sendchar(*str++);
	}
}
/*************printf trong C***********/
struct _FILE
{
	int dummy;
};
FILE __stdout;

int fputc(int _chr, FILE *f)
{
	uart_Sendchar(_chr);
	
	return _chr;
}

uint16_t UARTx_Getc(USART_TypeDef* USARTx)
{
	return USART_ReceiveData(USARTx);
}
/********************NVIC_EnableIRQ(USART1_IRQn)************/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		vrc_Getc = UARTx_Getc(USART1);
		if(vrc_Getc == '!') // 13: enter; bao hieu ket noi chuoi
		{
			vri_Stt =1;// dieu kien kiem tra de thuc hien cac chuong trinh theo yeu cau
			vrc_Res[vri_Count] = NULL;
			vri_Count = 0;
		}
		else{
			vrc_Res[vri_Count] = vrc_Getc;
			// uart_sendchar(vrc_Getc);
			vri_Count++;
		}
	}
}

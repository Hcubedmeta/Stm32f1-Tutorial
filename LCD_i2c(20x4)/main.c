#include "stm32f10x.h"                  // Device header
#include <i2c.h>
#include <i2c_lcd.h>
#include <USART.h>
#include <stdio.h>
static volatile char data;
static volatile char data_send[20];

char Arr[] = "Ha Huy Hoang";
//char array[20]  ;
//char array1[20] ;
int main(void)
{
	usart1_Init();
	timer_config();
	lcd_i2c_init(2);
	lcd_i2c_msg(2,1, 0,"hello, my name is");
	
	
	while(1)
	{
		if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  {
			while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) { }
		}
		data = USART_ReceiveData(USART1);
		if((data) == 'H')
		{	for(int i = 0; i < strlen(Arr); i++)
			{
			sprintf(data_send, "%c",Arr[i]);
			lcd_i2c_msg(2,2,i,data_send);
			lcd_i2c_msg(2,3,0,"i'm from HaTinh");
			lcd_i2c_msg(2,4,5,"^-^");
			}
		}
		else if(data == 'C')
		{
			lcd_blank_1234(2);
			lcd_i2c_msg(2,2,5,"-*-^-^*-");
			lcd_i2c_msg(2,3,3,"thanks,see u");
			lcd_i2c_msg(2,4,7,"soon");
		}

	}
}
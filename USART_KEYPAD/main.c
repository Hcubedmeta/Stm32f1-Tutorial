#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "USART.h"
#include "Keypad.h"
/*-----------------------------------------------------*/
char vruc_key, vruc_check;
char Press_key(void){
	do{	
		vruc_key = keypad_Press();
		if(vruc_key != 0xFF){
			Delay_ms(20);
			vruc_check = vruc_key;
			printf("  %c",vruc_check);		
			while(vruc_key != 0xFF){vruc_key = keypad_Press();}		
			Delay_ms(20);
		}
	}while(vruc_key != 0xFF);
	return vruc_check;
}
/*__________________________________________________________*/





 
int main(){
	usart1_Init();
	keypad_Init();
//	GPIOx_Init(GPIOB,GPIO_Pin_0,OUTPUT,Speed_50MHz);
	while(1){
		
		Press_key();
	}
}






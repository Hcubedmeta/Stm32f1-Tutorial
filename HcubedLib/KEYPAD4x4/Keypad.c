//#include "Keypad.h"
//#include "stm32f10x_gpio.h"
//#include "string.h"

//#define SCAN_COL_0			0xEF
//#define SCAN_COL_1			0xDF
//#define SCAN_COL_2			0xBF
//#define SCAN_COL_3			0x7F
//#define STOP						0xFF

//#define PIN_ROW_0				GPIO_Pin_0
//#define PIN_ROW_1 			GPIO_Pin_1
//#define PIN_ROW_2 			GPIO_Pin_2
//#define PIN_ROW_3 			GPIO_Pin_3

//#define PIN_COL_0 			GPIO_Pin_4
//#define PIN_COL_1 			GPIO_Pin_5
//#define PIN_COL_2 			GPIO_Pin_6
//#define PIN_COL_3 			GPIO_Pin_7

//#define PORT_KEYPAD 		GPIOA

//#define RCC_APB2_PROT_KEYPAD RCC_APB2Periph_GPIOA

//uint16_t Row[]={PIN_ROW_0,PIN_ROW_1,PIN_ROW_2,PIN_ROW_3};
//uint16_t Column[]={PIN_COL_0,PIN_COL_1,PIN_COL_2,PIN_COL_3};

//GPIO_InitTypeDef GPIO_KEYPAD;


//void keypad_Init(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2_PROT_KEYPAD, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	// cau hinh cot
//	GPIO_KEYPAD.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_KEYPAD.GPIO_Pin = PIN_COL_0|PIN_COL_1|PIN_COL_2|PIN_COL_3;
//	GPIO_KEYPAD.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PORT_KEYPAD,&GPIO_KEYPAD);
//	// cau hinh hang
//	GPIO_KEYPAD.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_KEYPAD.GPIO_Pin = PIN_ROW_0|PIN_ROW_1|PIN_ROW_2|PIN_ROW_3;
//	GPIO_KEYPAD.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PORT_KEYPAD,&GPIO_KEYPAD);
//}

//char keypad_Press(void){
//	GPIO_Write(PORT_KEYPAD,SCAN_COL_0);
//	if(!GPIO_ReadOutputDataBit(PORT_KEYPAD,PIN_COL_0)){
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_0)){return '1';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_1)){return '4';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_2)){return '7';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_3)){return '*';}
//	}
//	
//	GPIO_Write(PORT_KEYPAD,SCAN_COL_1);
//	if(!GPIO_ReadOutputDataBit(PORT_KEYPAD,PIN_COL_1)){
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_0)){return '2';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_1)){return '5';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_2)){return '8';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_3)){return '0';}
//	}
//	GPIO_Write(PORT_KEYPAD,SCAN_COL_2);
//	if(!GPIO_ReadOutputDataBit(PORT_KEYPAD,PIN_COL_2)){
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_0)){return '3';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_1)){return '6';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_2)){return '9';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_3)){return '#';}
//	}
//	GPIO_Write(PORT_KEYPAD,SCAN_COL_3);
//	if(!GPIO_ReadOutputDataBit(PORT_KEYPAD,PIN_COL_3)){
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_0)){return 'A';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_1)){return 'B';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_2)){return 'C';}
//		if(!GPIO_ReadInputDataBit(PORT_KEYPAD,PIN_ROW_3)){return 'D';}
//	}
//	Delay(5);
//	return 0xFF;
//}

//void Delay(int time)
//{
//	int i,j;
//	for(i =0; i < time; i++)
//	{
//		for(j = 0; j <0x2aff; j++);
//	}
//}
////uint8_t CheckPass(char *Str1, char *Str2){
////	if(strlen(Str1) == strlen(Str2)){
////		if(strstr(Str1,Str2)!=NULL){ 
////			return 1;
////		}
////	}
////	return 0;
////}
#include "Keypad.h"
#include "delay.h"

void Key_Init(void)
{
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	gpioInit.GPIO_Mode = GPIO_Mode_IPU;
	gpioInit.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
}

uint32_t Key_Scan(void)
{
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	Delay_Ms(1);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
		return 1;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
		return 2;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) {
		return 3;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) {
		return 4;
	}
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
	Delay_Ms(1);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
		return 5;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
		return 6;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) {
		return 7;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) {
		return 8;
	}
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
	Delay_Ms(1);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
		return 9;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
		return 10;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) {
		return 11;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) {
		return 12;
	}
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	Delay_Ms(1);
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
		return 13;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
		return 14;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) {
		return 15;
	}
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)) {
		return 16;
	}
	
	return 0;
}

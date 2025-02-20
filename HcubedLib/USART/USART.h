#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"   
#include "string.h"
#include "stdio.h"
#define MAX 100

extern char vrc_Getc; // bien kieu char, dung de nhan du lieu Tu PC gui xuong
extern int vri_Stt; // bien danh dau trang thai
extern int vri_Count; // bien dem
extern char vrc_Res[MAX];// Mang kieu char vrc_Res[MAX]: mang luu tru tam thoi


void usart1_Init(void);
void uart_Sendchar(char _chr);
void uart_SendStr(char *str);
#endif

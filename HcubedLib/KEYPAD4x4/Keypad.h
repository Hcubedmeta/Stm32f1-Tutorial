//#ifndef _KEYPAD_H
//#define _KEYPAD_H

//#include "stm32f10x.h"

//char keypad_Press(void);
//void keypad_Init(void);
//void Delay(int time);

////uint8_t CheckPass(char *Str1, char *Str2);

//#endif
#ifndef KEY_H_
#define KEY_H_

#include "stm32f10x.h"

void Key_Init(void);
uint32_t Key_Scan(void);

#endif

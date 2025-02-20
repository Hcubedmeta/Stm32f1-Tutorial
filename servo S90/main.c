#include "stm32f10x.h"
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO


void delay(int time);
void Speed_Motor(uint16_t speed_motor1, uint16_t speed_motor2);
void forward_motor(void);
void MOTOR_PWM(void);
void ARMROBOT_PWM(void);
void TIM1_UP_IRQHandler(void);
void TIM3_IRQHandler(void);
void NVIC_Configuration(void);

int main() {
		MOTOR_PWM();
    ARMROBOT_PWM();
		NVIC_Configuration();
		RCC-> APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
    while (1) 
		{
			
			
    }
}

void ARMROBOT_PWM(void)
{
	 // Khai báo các c?u trúc c?u hình cho Timer, PWM, và GPIO
    TIM_TimeBaseInitTypeDef timer_init;
    TIM_OCInitTypeDef pwm_init;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Kích ho?t xung clock cho TIM1, GPIOA và ch?c nang AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // C?u hình GPIO cho các chân PA8, PA9, PA10, PA11 làm d?u ra PWM
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // C?u hình Timer cho PWM v?i t?n s? 1 kHz
    timer_init.TIM_Period = 20000 - 1;   // Ð?t chu k? 20,000 (1 kHz)
    timer_init.TIM_Prescaler = 71;       // Chia t?n s? xung nh?p
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_ClockDivision = 0;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &timer_init);
    
    // C?u hình PWM cho các kênh CH1, CH2, CH3, CH4 v?i giá tr? xung 1500 (7.5% duty cycle)
    pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
    pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
    pwm_init.TIM_OutputState = TIM_OutputState_Enable;
    pwm_init.TIM_Pulse = 1500;

    TIM_OC1Init(TIM1, &pwm_init);  // Kênh CH1
    TIM_OC2Init(TIM1, &pwm_init);  // Kênh CH2
    TIM_OC3Init(TIM1, &pwm_init);  // Kênh CH3
    TIM_OC4Init(TIM1, &pwm_init);  // Kênh CH4
    
    // Kích ho?t xu?t tín hi?u PWM và kh?i d?ng Timer
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // Kích ho?t ng?t Update c?a TIM1
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}
void MOTOR_PWM(void)
{
	 // Khai báo các c?u trúc c?u hình cho Timer, PWM, và GPIO
    TIM_TimeBaseInitTypeDef timer_init;
    TIM_OCInitTypeDef pwm_init;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Kích ho?t xung clock cho TIM1, GPIOA và ch?c nang AFIO
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // C?u hình GPIO cho các chân PA8, PA9, PA10, PA11 làm d?u ra PWM
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // C?u hình Timer cho PWM v?i t?n s? 1 kHz
    timer_init.TIM_Period = 100 - 1;   // Ð?t chu k? 20,000 (1 kHz)
    timer_init.TIM_Prescaler = 71;       // Chia t?n s? xung nh?p
    timer_init.TIM_CounterMode = TIM_CounterMode_Up;
    timer_init.TIM_ClockDivision = 0;
    timer_init.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timer_init);
    
    // C?u hình PWM cho các kênh CH1, CH2, CH3, CH4 v?i giá tr? xung 1500 (7.5% duty cycle)
    pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
    pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
    pwm_init.TIM_OutputState = TIM_OutputState_Enable;
    pwm_init.TIM_Pulse = 1500;

    TIM_OC1Init(TIM3, &pwm_init);  // Kênh CH1
    TIM_OC2Init(TIM3, &pwm_init);  // Kênh CH2
    TIM_OC3Init(TIM3, &pwm_init);  // Kênh CH3
    TIM_OC4Init(TIM3, &pwm_init);  // Kênh CH4
    
    // Kích ho?t xu?t tín hi?u PWM và kh?i d?ng Timer
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // Kích ho?t ng?t Update c?a TIM1
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}
void NVIC_Configuration(void) {
    NVIC_InitTypeDef NVIC_InitStructure;

    // C?u hình NVIC cho TIM1 Update Interrupt (TIM1_UP_IRQn)
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; // Kênh ng?t cho TIM1 Update
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // M?c uu tiên cho phép ng?t
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // M?c uu tiên ph?
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Kích ho?t ng?t
    NVIC_Init(&NVIC_InitStructure);

    // C?u hình NVIC cho TIM3 Interrupt (TIM3_IRQn)
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; // Kênh ng?t cho TIM3
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // M?c uu tiên cho phép ng?t
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // M?c uu tiên ph?
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Kích ho?t ng?t
    NVIC_Init(&NVIC_InitStructure);
}
// Hàm ISR cho TIM1
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        // Update each channel's CCR value
      TIM1 ->CCR1 = 800;
			delay(100);
			TIM1 ->CCR1 = 500;
			delay(100);
			TIM1 ->CCR1 = 1000;
			delay(100);
			TIM1 ->CCR1 = 1500;
			delay(100);
			TIM1 ->CCR1 = 1700;	
			delay(100);
			TIM1 ->CCR2 = 2300;
			delay(100); 
			TIM1 ->CCR2 = 1200;
			delay(100); 
			TIM1 -> CCR3 = 2000;
			delay(100);
			TIM1 ->CCR2 = 500;
			delay(100); 
			TIM1 ->CCR1 = 1900;
			delay(100);
			TIM1 -> CCR3 = 700;
			delay(500);
			TIM1 ->CCR1 = 700;
			delay(100);
			TIM1 -> CCR4 = 500;
			delay(100);
			TIM1 ->CCR1 = 800;
			delay(100);
			TIM1 ->CCR1 = 500;
			delay(100);
			TIM1 ->CCR1 = 1000;
			delay(100);
			TIM1 ->CCR1 = 1500;
			delay(100);
			TIM1 ->CCR1 = 1700;	
			delay(100);
			TIM1 ->CCR2 = 2300;
			delay(100); 
			TIM1 ->CCR2 = 1200;
			delay(100); 
			TIM1 -> CCR3 = 2000;
			delay(100);
			TIM1 ->CCR2 = 500;
			delay(100); 
			TIM1 ->CCR1 = 1900;	
			delay(100);
			TIM1 -> CCR3 = 700;
			delay(500);
			TIM1 ->CCR1 = 700;
			delay(100);
			TIM1 -> CCR4 = 2500;
			delay(100);
        
        // Clear the update interrupt flag
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
			forward_motor();
			Speed_Motor(70,70);
			        // Clear the update interrupt flag
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
void forward_motor(void)
{

	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_2);
	GPIO_SetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_3);
}
void Speed_Motor(uint16_t speed_motor1, uint16_t speed_motor2)
{
	TIM3 ->CCR1 = speed_motor1;
	TIM3 ->CCR2 = speed_motor2;
}
	void delay(int time)
{
	int i,j;
	for(i =0; i < time; i ++)
	{
		for(j = 0; j< 0x2aff; j++);
	}
}

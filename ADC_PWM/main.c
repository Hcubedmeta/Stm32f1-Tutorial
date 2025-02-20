#include "stm32f10x.h"
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

void PWM_Update(uint16_t pulse1, uint16_t pulse2, uint16_t pulse3, uint16_t pulse4);
void ADC1_Init(void);
void PWM_Init(void);


uint16_t ADC_Read(uint8_t channel);

// Kh?i t?o ADC
void ADC1_Init(void) {
    // B?t clock cho ADC1, GPIOA v? GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA   , ENABLE);

    // C?u h?nh GPIO cho PA4 (ADC1_IN4)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    // C?u h?nh GPIO cho PA5 (ADC1_IN5)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

		// C?u h?nh GPIO cho PA6 (ADC1_IN6)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		// C?u h?nh GPIO cho PA7 (ADC1_IN7)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		
    // C?u h?nh ADC1
    ADC_InitTypeDef ADC_InitStructure; 
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; // ENABLE d? qu?t nhi?u k?nh
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1; // S? lu?ng k?nh
    ADC_Init(ADC1, &ADC_InitStructure);

    // C?u h?nh k?nh 4 (PA4)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
    // C?u h?nh k?nh 5 (PB5)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
    // C?u h?nh k?nh 6 (PA6)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
    // C?u h?nh k?nh 7 (PA7)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_55Cycles5);
		
    // K?ch ho?t ADC1
    ADC_Cmd(ADC1, ENABLE);

    // Kh?i d?ng hi?u chu?n ADC1
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

    // B?t d?u chuy?n d?i ph?n m?m
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// ??c gi? tr? t? ADC
// ??c gi? tr? t? ADC
uint16_t ADC_Read(uint8_t channel) {
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}


// Kh?i t?o PWM
void PWM_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // PA0 - TIM2_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // PA1 - TIM2_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // PA2 - TIM2_CH3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // PA3 - TIM2_CH4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1; // 20ms (50Hz)
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 1MHz (1us)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure; 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
		
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
		
    TIM_Cmd(TIM2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
}


// C?p nh?t d? r?ng xung PWM
void PWM_Update(uint16_t pulse1, uint16_t pulse2, uint16_t pulse3, uint16_t pulse4) {
    TIM_SetCompare1(TIM2, pulse1);
    TIM_SetCompare2(TIM2, pulse2);
		TIM_SetCompare3(TIM2, pulse3);
    TIM_SetCompare4(TIM2, pulse4);
		
}

int main() {
    ADC1_Init();
    PWM_Init();
		

    while (1) {
        uint16_t adc_value1 = ADC_Read(ADC_Channel_4);
        uint16_t adc_value2 = ADC_Read(ADC_Channel_5);
				uint16_t adc_value3 = ADC_Read(ADC_Channel_6);
        uint16_t adc_value4 = ADC_Read(ADC_Channel_7);
				
        uint16_t pwm_pulse1 = (adc_value1 * 2000 / 4096) + 500; 
        uint16_t pwm_pulse2 = (adc_value2 * 2000 / 4096) + 500;
				uint16_t pwm_pulse3 = (adc_value3 * 2000 / 4096) + 500; 
        uint16_t pwm_pulse4 = (adc_value4 * 2000 / 4096) + 500;
			
				PWM_Update(pwm_pulse1, pwm_pulse2, pwm_pulse3, pwm_pulse4);
    }
}

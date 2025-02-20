#include "pwm.h"
void pin_pwm_Init(void){
	GPIO_InitTypeDef pin_pwm;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	/* TIM1 - Channel_1 - PA8 */
	pin_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pin_pwm.GPIO_Pin = GPIO_Pin_8;
	pin_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&pin_pwm);	
}
//void Delay_ms(uint16_t _time){
//	uint16_t i,j;
//	for(i = 0; i < _time; i++){
//		for(j = 0; j < 0x2AFF; j++);
//	}
//}
void pwm_Init(void){
	
	TIM_TimeBaseInitTypeDef timer_init;
	TIM_OCInitTypeDef				pwm_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	pin_pwm_Init();
	
	timer_init.TIM_Period				 		= 2000;
	timer_init.TIM_Prescaler 		 		= 71;
	timer_init.TIM_CounterMode 	 		= TIM_CounterMode_Up;
	timer_init.TIM_ClockDivision 		= 0;
	timer_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&timer_init);
	
	
	/*chon che do hoat dong cho chuc nang Ouput Compare*/
	pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
	/*lenh cau hinh muc tich cuc cua Output Compare doi voi cac chan CHx*/
	pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
	/*lenh cho phep hoac khong cho phep Output Compare xuat tin hieu ra chan CHx*/
	pwm_init.TIM_OutputState = TIM_OutputState_Enable;
	/*lenh cau hinh gia tri so sanh cho Output Compare*/
	pwm_init.TIM_Pulse = 0;

	TIM_OC1Init(TIM1,&pwm_init);
	/*cho phep xuat tin hieu o tim4.*/
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM1,ENABLE);
}
void timer_PWM(void)
{
	TIM_TimeBaseInitTypeDef timer_init;
	TIM_OCInitTypeDef				pwm_init;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	

	
	timer_init.TIM_Period				 		= 999; //T= 1ms or F = 1Khz
	timer_init.TIM_Prescaler 		 		= 71;
	timer_init.TIM_CounterMode 	 		= TIM_CounterMode_Up;
	timer_init.TIM_ClockDivision 		= 0;
	timer_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&timer_init);
	
	
	/*chon che do hoat dong cho chuc nang Ouput Compare*/
	pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
	/*lenh cau hinh muc tich cuc cua Output Compare doi voi cac chan CHx*/
	pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
	/*lenh cho phep hoac khong cho phep Output Compare xuat tin hieu ra chan CHx*/
	pwm_init.TIM_OutputState = TIM_OutputState_Enable;
	/*lenh cau hinh gia tri so sanh cho Output Compare*/
	pwm_init.TIM_Pulse = 0;
	TIM_OC4Init(TIM2,&pwm_init);
	
	/*chon che do hoat dong cho chuc nang Ouput Compare*/
	pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
	/*lenh cau hinh muc tich cuc cua Output Compare doi voi cac chan CHx*/
	pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
	/*lenh cho phep hoac khong cho phep Output Compare xuat tin hieu ra chan CHx*/
	pwm_init.TIM_OutputState = TIM_OutputState_Enable;
	/*lenh cau hinh gia tri so sanh cho Output Compare*/
	pwm_init.TIM_Pulse = 0;
	TIM_OC3Init(TIM2,&pwm_init);
	
	/*chon che do hoat dong cho chuc nang Ouput Compare*/
	pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
	/*lenh cau hinh muc tich cuc cua Output Compare doi voi cac chan CHx*/
	pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
	/*lenh cho phep hoac khong cho phep Output Compare xuat tin hieu ra chan CHx*/
	pwm_init.TIM_OutputState = TIM_OutputState_Enable;
	/*lenh cau hinh gia tri so sanh cho Output Compare*/
	pwm_init.TIM_Pulse = 0;
	TIM_OC2Init(TIM2,&pwm_init);
	
	/*chon che do hoat dong cho chuc nang Ouput Compare*/
	pwm_init.TIM_OCMode = TIM_OCMode_PWM1;
	/*lenh cau hinh muc tich cuc cua Output Compare doi voi cac chan CHx*/
	pwm_init.TIM_OCPolarity = TIM_OCPolarity_High;
	/*lenh cho phep hoac khong cho phep Output Compare xuat tin hieu ra chan CHx*/
	pwm_init.TIM_OutputState = TIM_OutputState_Enable;
	/*lenh cau hinh gia tri so sanh cho Output Compare*/
	pwm_init.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&pwm_init);
	
	/*cho phep xuat tin hieu o tim4.*/
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}
void setup_CHx(void)
{
	GPIO_InitTypeDef pin_pwm;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	/* TIM2 - Channel_4 - PA3 */
	pin_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pin_pwm.GPIO_Pin = GPIO_Pin_3;
	pin_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pin_pwm);
	/* TIM2 - Channel_3 - PA2 */
	pin_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pin_pwm.GPIO_Pin = GPIO_Pin_2;
	pin_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pin_pwm);
	/* TIM2 - Channel_2 - PA1 */
	pin_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pin_pwm.GPIO_Pin = GPIO_Pin_1;
	pin_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pin_pwm);
	/* TIM2 - Channel_1 - PA0 */
	pin_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pin_pwm.GPIO_Pin = GPIO_Pin_0;
	pin_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&pin_pwm);	
}
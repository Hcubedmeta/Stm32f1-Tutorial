#include "stm32f10x.h"                  // Device header


void SystemClock_Config(void);

int main(void) {
    // B?t clock cho GPIOA v� TIM2
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // B?t clock GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;    // B?t clock TIM2

    // C?u h�nh PA0 ? ch? d? Alternate Function Push-Pull
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0); // X�a c?u h�nh cu
    GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0;  // Output 50MHz, AF Push-Pull

    // C?u h�nh TIM2
    TIM2->PSC = 71;  // Chia t?n s? (8MHz / (71+1) = 1MHz)
    TIM2->ARR = 5000; // Chu k? Timer (1MHz / 20000 = 50Hz)
    TIM2->CCR1 = 1000; // �? r?ng xung ban d?u (1000�s)
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM Mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Cho ph�p preload
    TIM2->CCER |= TIM_CCER_CC1E;    // K�ch ho?t k�nh 1
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Auto-reload v� b?t Timer

    while (1) {
        // �i?u ch?nh d? r?ng xung PWM
        for (int pulse = 1000; pulse <= 2000; pulse += 10) {
            TIM2->CCR1 = pulse;
            for (volatile int i = 0; i < 100000; i++); // Delay
        }
    }
}

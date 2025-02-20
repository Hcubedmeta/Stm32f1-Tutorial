#include "math.h"
#include "stm32f10x.h"                  // Device header
#include "GPIO_Drive.h"
#include "mpu6050.h"
#include <stdio.h>
#include "Delay_sys.h"
#include "H_pid.h"
/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA

*/


#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define ACCEL_YOUT_H_REG 0x3D
#define ACCEL_ZOUT_H_REG 0x3F
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43
#define GYRO_YOUT_H_REG 0x45
#define GYRO_ZOUT_H_REG 0x47
#define config				0x1A
#define Level_int			55
#define interrupts		56

// Setup MPU6050
#define MPU6050_ADDR 0x68
void PWM_Init(void); 

int main(void)
{
	i2c_init(1,0x2d);
	Sendata(MPU6050_ADDR, SMPLRT_DIV_REG, 7);  // Ð?t t?n s? l?y m?u kho?ng 125 Hz
	Sendata(MPU6050_ADDR,config, 0x06);             // bat b? l?c thông th?p (DLPF_CFG = 0) d? gi?m d? tr?
	Sendata(MPU6050_ADDR, GYRO_CONFIG_REG, 0x00);  // C?u hình con quay h?i chuy?n v?i ph?m vi ±250 d?/giây
	Sendata(MPU6050_ADDR, ACCEL_CONFIG_REG, 0x00); // C?u hình gia t?c k? v?i ph?m vi ±2g
	Sendata(MPU6050_ADDR, PWR_MGMT_1_REG, 0x00);  // C?u hình  ho?t d?ng lien tuc c?a MPU6050
	Sendata(MPU6050_ADDR, Level_int, 0x80);  // C?u hình ng?t (n?u c?n)
	Sendata(MPU6050_ADDR, interrupts, 1u);  // C?u hình ng?t (n?u c?n)

	PWM_Init();
	systick_init();

	while(1)
	{

	}
}

void PWM_Init(void) {
    // B?t clock cho GPIOA và TIM2
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // B?t clock GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;    // B?t clock TIM2

    // C?u hình PA0 ? ch? d? Alternate Function Push-Pull
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0); // Xóa c?u hình cu
    GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0;  // Output 50MHz, AF Push-Pull

    // C?u hình PA1 ? ch? d? Alternate Function Push-Pull
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1); // Xóa c?u hình cu
    GPIOA->CRL |= GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1;  // Output 50MHz, AF Push-Pull

    // C?u hình TIM2
    TIM2->PSC = 71;  // Chia t?n s? (8MHz / (71+1) = 1MHz)
    TIM2->ARR = 5000; // Chu k? Timer 5ms

    // Kênh 1 (PA0)
    TIM2->CCR1 = 1000; // Ð? r?ng xung ban d?u (1000µs)
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM Mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Cho phép preload
    TIM2->CCER |= TIM_CCER_CC1E;    // Kích ho?t kênh 1

    // Kênh 2 (PA1)
    TIM2->CCR2 = 1000; // Ð? r?ng xung ban d?u (1000µs)
    TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // PWM Mode 1 cho kênh 2
    TIM2->CCMR1 |= TIM_CCMR1_OC2PE; // Cho phép preload
    TIM2->CCER |= TIM_CCER_CC2E;    // Kích ho?t kênh 2

    // B?t Auto-reload và kh?i d?ng Timer
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}
//uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
//  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}






#include "stm32f10x.h"                  // Device header
#include "ILI9225.h"
#include "GPIO_Drive.h"
#include "SPI_Drive.h"
#include "mpu6050.h"
#include <stdio.h>
#include "Delay_sys.h"
/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA

*/#define WHO_AM_I_REG 0x75
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
#define sample_rate		25
#define config				26
#define Level_int			55
#define interrupts		56
#define MPU6050_ADDR 0x68
#define AX_X 5
#define AX_Y 40
#define AY_Y 60
#define AZ_Y 80
#define GX_X 110
#define GX_Y 40
#define GY_Y 60
#define GZ_Y 80


int i;
char buf[4];
MPU6050_t MPU6050;
float AngX, AngY;
void PWM_Init(void);
int main(void)
{
	i2c_init(1,0x2d);
//	Sendata(MPU6050_ADDR,sample_rate,19u);
//	Sendata(MPU6050_ADDR,config,5u);
//	Sendata(MPU6050_ADDR,GYRO_CONFIG_REG,0x00);
//	Sendata(MPU6050_ADDR,ACCEL_CONFIG_REG,0x00);// 2g
//	Sendata(MPU6050_ADDR,Level_int,0x80);
//	Sendata(MPU6050_ADDR,interrupts,1u);
//	Sendata(MPU6050_ADDR,PWR_MGMT_1_REG,1u);
	PWM_Init();
	systick_init();
	SPI_init(spi_2);
  lcd_init();
  fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
	while(1)
	{
//			  MPU6050_Read_All(&MPU6050);

//				float angleX = MPU6050.KalmanAngleX;
//				float angleY = MPU6050.KalmanAngleY;

//				delay_ms(100);
//				double PWM_AX;

//				if (angleX != 0) {
//						PWM_AX = (fabs(angleX) * 1000) / angleX;
//				} else {
//						PWM_AX = 1500; // default value
//				}

//				const double MIN_PWM = 1000.0;
//				const double MAX_PWM = 2000.0;

//				if (PWM_AX < MIN_PWM)
//						PWM_AX = MIN_PWM;
//				else if (PWM_AX > MAX_PWM)
//						PWM_AX = MAX_PWM;


			for(i = 500; i <2500; i+= 100)
			{
				TIM1->CCR1 = i;
				delay_us(100);
			}
			
			
    


	    // Xóa các ký t? cu b?ng cách v? l?i màu n?n
//	    fill_rectangle(AX_X + 27.5, AX_Y , 100, 50, COLOR_BLACK); // Xóa AX
//	    fill_rectangle(AX_X + 27.5, AY_Y , 100, 70, COLOR_BLACK); // Xóa AY


//	    // V? l?i các thông s? m?i
//	    draw_string(AX_X,10,COLOR_RED,1.8,"ACCEL");
//	    sprintf(buf, "AX=%.2f", new_AX);
//	    draw_string(AX_X, AX_Y, COLOR_YELLOW, 1.75, buf);

//	    sprintf(buf, "AY=%.2f", new_AY);
//	    draw_string(AX_X, AY_Y, COLOR_BLUE, 1.75, buf);


	}
}



void PWM_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; // PA0 - TIM2_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // PA1 - TIM2_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // PA2 - TIM2_CH3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // PA3 - TIM2_CH4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 5000 - 1; // 20ms (50Hz)
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 1MHz (1us)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure; 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
		
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

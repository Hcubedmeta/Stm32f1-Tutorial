

#include <stdint.h>

#include "stm32f10x.h"     // Device header
#include "Delay_sys.h"
#include "stm32f10x_i2c.h"              // Device:StdPeriph Drivers:I2C
#include "GPIO_Drive.h"
#define ACK 0
#define NACK 1
// MPU6050 structure


typedef struct {

    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    double Ax;
    double Ay;
    double Az;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    double Gx;
    double Gy;
    double Gz;

    float Temperature;

    double KalmanAngleX;
    double KalmanAngleY;
} MPU6050_t;


// Kalman structure


typedef struct {
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman_t;



void i2c_init(char i2c, unsigned short speed_mode);
void Sendata(uint8_t I2Cadd,uint8_t address,uint8_t value);
void ReceiveOnebyte(int8_t I2Cadd,uint8_t address,uint8_t *data);
uint8_t MPU6050_Init(void);

void MPU6050_Read_Accel( MPU6050_t *DataStruct);

void MPU6050_Read_Gyro( MPU6050_t *DataStruct);

void MPU6050_Read_Temp( MPU6050_t *DataStruct);

void MPU6050_Read_All( MPU6050_t *DataStruct);

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);


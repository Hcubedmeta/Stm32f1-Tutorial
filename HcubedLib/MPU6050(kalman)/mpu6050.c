
#include <math.h>
#include "mpu6050.h"

#define RAD_TO_DEG 57.295779513082320876798154814105
/* register mpu */
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
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

//uint32_t timer;

Kalman_t KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

Kalman_t KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};
void i2c_init(char i2c, unsigned short speed_mode) {
    RCC->APB2ENR |= 1; 

    if (i2c == 1) {
        RCC->APB1ENR |= 0x200000;
        init_GPIO(PB, 6, O_50MHz, O_AF_OD);
        init_GPIO(PB, 7, O_50MHz, O_AF_OD);
        I2C1->CR1 |= 0x8000; // Software reset
        I2C1->CR1 &= ~0x8000; // clear
        I2C1->CR2 = 0x08; // PCLK1 = 8MHz
        I2C1->CCR = speed_mode; 
        I2C1->TRISE = 0x09; 
        I2C1->CR1 |= 1; // activate communication
    } else if (i2c == 2) {
        RCC->APB1ENR |= 0x400000;
        init_GPIO(PB, 10, O_50MHz, O_AF_OD);
        init_GPIO(PB, 11, O_50MHz, O_AF_OD);
        I2C2->CR1 |= 0x8000;
        I2C2->CR1 &= ~0x8000;
        I2C2->CR2 = 0x08;
        I2C2->CCR = speed_mode;
        I2C2->TRISE = 0x09;
        I2C2->CR1 |= 1;
    }
}
void Sendata(uint8_t I2Cadd,uint8_t address,uint8_t value){
		while((I2C1 ->SR2 )& 0x02){} // make sure clear is busy
		
		I2C1 ->CR1 |= 0x100; 
		while (!(I2C1->SR1 & 0x01)){}
//		delay_us(2);
		I2C1 ->DR = I2Cadd << 1u;
		while(!(I2C1 ->SR1 & 0x02)){}
		I2C1 ->SR2;
		while(!(I2C1 ->SR1&0x80)){}
		I2C1->DR = address;
		while(!(I2C1 ->SR1&0x80)){}
		I2C1 ->DR = value;
		while(!(I2C1 ->SR1&0x80 && I2C1 ->SR1 & 0x04)){}
		I2C1 ->CR1 |= 0x200;
	
}
void ReceiveOnebyte(int8_t I2Cadd,uint8_t address,uint8_t *data)
{
		while((I2C1 ->SR2 )& 0x02){} // make sure clear is busy
		
		I2C1 ->CR1 |= 0x100; 
		while (!(I2C1->SR1 & 0x01)){}
//		delay_us(10);
		I2C1 ->DR = I2Cadd << 1u;
		while(!(I2C1 ->SR1 & 0x02)){}
		I2C1 ->SR2;
		while(!(I2C1 ->SR1&0x80)){}
		I2C1->DR = address;
		while(!(I2C1 ->SR1&0x80)){}
		I2C1 ->CR1 |= 0x100;
		while (!(I2C1->SR1 & 0x01)){}
		I2C1 ->DR = (I2Cadd << 1u) | 0x01;
		while(!(I2C1 ->SR1 & 0x02)){}
		I2C1 ->CR1 &= ~ 0x400;
		I2C1 ->SR2;
		I2C1 ->CR1 |= 0x200;
		while(!(I2C1 ->SR1 & 0x40)){}
		*data = I2C1 ->DR;
}
uint8_t MPU6050_Init(void) 
{
	Sendata(MPU6050_ADDR,SMPLRT_DIV_REG,19u);
	Sendata(MPU6050_ADDR,config,5u);
	Sendata(MPU6050_ADDR,GYRO_CONFIG_REG,0x00);
	Sendata(MPU6050_ADDR,ACCEL_CONFIG_REG,0x00);// 2g
	Sendata(MPU6050_ADDR,Level_int,0x80);
	Sendata(MPU6050_ADDR,interrupts,1u);
	Sendata(MPU6050_ADDR,PWR_MGMT_1_REG,1u);
}

void MPU6050_Read_Accel( MPU6050_t *DataStruct) {
    uint8_t Rec_Data[6];

		ReceiveOnebyte(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_XOUT_H_REG + 1, Rec_Data + 1);

			
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_YOUT_H_REG, Rec_Data + 2);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_YOUT_H_REG + 1, Rec_Data + 3);	
	
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_ZOUT_H_REG, Rec_Data + 4);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_ZOUT_H_REG + 1, Rec_Data + 5);


    // Chuyển đổi dữ liệu thô thành giá trị gia tốc
    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    // Chuyển đổi giá trị thô thành gia tốc tính bằng '2g'
    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;
}



void MPU6050_Read_Gyro( MPU6050_t *DataStruct) {
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register
		ReceiveOnebyte(MPU6050_ADDR, GYRO_XOUT_H_REG, Rec_Data);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_XOUT_H_REG + 1, Rec_Data + 1);

			
		ReceiveOnebyte(MPU6050_ADDR, GYRO_YOUT_H_REG, Rec_Data + 2);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_YOUT_H_REG + 1, Rec_Data + 3);	
	
		ReceiveOnebyte(MPU6050_ADDR, GYRO_ZOUT_H_REG, Rec_Data + 4);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_ZOUT_H_REG + 1, Rec_Data + 5);
    

    DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;
}

void MPU6050_Read_Temp( MPU6050_t *DataStruct) {
    uint8_t Rec_Data[2];
    int16_t temp;

    // Read 2 BYTES of data starting from TEMP_OUT_H_REG register

    
		ReceiveOnebyte(MPU6050_ADDR,TEMP_OUT_H_REG,Rec_Data);

    temp = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
}

void MPU6050_Read_All( MPU6050_t *DataStruct) {
    uint8_t Rec_Data[12];


    // Read 6 byte of Accel
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_XOUT_H_REG + 1, Rec_Data + 1);

			
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_YOUT_H_REG, Rec_Data + 2);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_YOUT_H_REG + 1, Rec_Data + 3);	
	
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_ZOUT_H_REG, Rec_Data + 4);
		ReceiveOnebyte(MPU6050_ADDR, ACCEL_ZOUT_H_REG + 1, Rec_Data + 5);
		// read 6 byte of gyro
		ReceiveOnebyte(MPU6050_ADDR, GYRO_XOUT_H_REG, Rec_Data);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_XOUT_H_REG + 1, Rec_Data + 1);

		ReceiveOnebyte(MPU6050_ADDR, GYRO_YOUT_H_REG, Rec_Data + 2);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_YOUT_H_REG + 1, Rec_Data + 3);	
	
		ReceiveOnebyte(MPU6050_ADDR, GYRO_ZOUT_H_REG, Rec_Data + 4);
		ReceiveOnebyte(MPU6050_ADDR, GYRO_ZOUT_H_REG + 1, Rec_Data + 5);

    // Chuyển đổi dữ liệu thô thành giá trị gia tốc
    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);
    DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
    DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);

    DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
    DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
    DataStruct->Az = DataStruct->Accel_Z_RAW / Accel_Z_corrector;

    DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
    DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
    DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;

    // Kalman angle solve
    double dt = 1;
    
    double roll;
    double roll_sqrt = sqrt(
            DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
    if (roll_sqrt != 0.0) {
        roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
    } else {
        roll = 0.0;
    }
    double pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD_TO_DEG;
    if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90)) {
        KalmanY.angle = pitch;
        DataStruct->KalmanAngleY = pitch;
    } else {
        DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
    }
    if (fabs(DataStruct->KalmanAngleY) > 90)
        DataStruct->Gx = -DataStruct->Gx;
    DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gy, dt);

}

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt) {
    double rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    double S = Kalman->P[0][0] + Kalman->R_measure;
    double K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    double y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    double P00_temp = Kalman->P[0][0];
    double P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
}



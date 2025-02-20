#include "BN0055_drive.h"


// set up the BNO address is 0x29
void bno055_add(char i2c, char R_W)
{
	i2c_add(i2c,0x52,R_W);
}
// setup the transmit function
void bno055_tx(char i2c,char reg,char data)
{
	i2c_start(i2c);
	bno055_add(i2c,0);
	i2c_data(i2c,reg);
	i2c_data(i2c,data);
	i2c_stop(i2c);
}
void bno055_rx(char i2c, char reg, char * str, char data_len)
{
	int i;
	i2c_start(i2c);
	bno055_add(i2c,0);
	i2c_data(i2c,reg);
	
	i2c_start(i2c);
	bno055_add(i2c,1);
	for(i = 0; i < (data_len - 1);i++)
	{
		str[i] = i2c_rx(i2c,ACK);
	}
	str[i] = i2c_rx(i2c,NACK);
	i2c_stop(i2c);
}

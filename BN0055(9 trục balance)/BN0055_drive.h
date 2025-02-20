/* Ha Huy Hoang 
 --------------14-10-2024-----------------------*/
 
#include "i2c.h"
#define ACK 0
#define NACK 1
void bno055_add(char i2c, char R_W);
void bno055_tx(char i2c,char reg,char data);
void bno055_rx(char i2c, char reg, char * str, char data_len);


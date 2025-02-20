#include "GPIO_Drive.h"
#include "stm32f10x.h"                  // Device header
#include "ILI9225.h"

#define spi_1 1
#define spi_2 2
void SPI_init(unsigned short Spi);
void SPI_Tx(unsigned short Spi,char var);
void SPI_Tx_array(unsigned short Spi,char arr[]);


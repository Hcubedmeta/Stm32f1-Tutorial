#include "Delay_sys.h"
#include "SPI_Drive.h"
int main(void)
{
	systick_init();
	SPI_init(spi_1);
	while(1)
	{
		Delay_Ms(50);
		SPI_Tx(spi_1,'H');
		SPI_Tx_array(spi_1,"Hoang");
	}
}

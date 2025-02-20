#include "stm32f10x.h"                  // Device header
#include "SPI_Drive.h"
#include "ILI9225.h"
#include "GPIO_Drive.h"
int main(void)
{

	SPI_init(spi_2);
  lcd_init();
  fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
	while(1)
	{
		draw_star(110,88,70,COLOR_CYAN);
		delay_ms(500);
		drawCircle(110,88,70,COLOR_BEIGE,1);
		delay_ms(1000);
		draw_star(110,88,70,COLOR_DARKGREEN);
		delay_ms(500);
	}
}

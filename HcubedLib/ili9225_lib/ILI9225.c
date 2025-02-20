/*
 * LCD driver for the ILI9225 TFT LCD chips. 
 * 
 * This driver works with OTM2201A, and ILI9926 controller chips.
 * 
 * Feel free to use, change, distribute this code as desired. Use under
 * GPLv3 open-source license.
 * 
 * File:   ILI9225.c
 * Author: tommy
 *
 * Created on 2 July 2019, 7:32 PM
 */


#include "ILI9225.h"

    /* Font files. Thanks Stack Overflow!
     */

    const unsigned char FontLarge[95][13] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// space :32
    {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},// ! :33
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
    {0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
    {0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
    {0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
    {0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
    {0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
    {0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
    {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
    {0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c}, //0 : 48
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
    {0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06}, // < : 60
    {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
    {0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
    {0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, // A : 65
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}, // Z : 90
    {0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
    {0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
    {0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
    {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
    {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, // a : 97
    {0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
    {0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
    {0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00}, // i
    {0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
    {0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
    {0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00}, // o : 111
    {0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
    {0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
    {0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
    {0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00}, // z : 122
    {0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
    {0x40, 0x60, 0x70, 0x78, 0x7C, 0x7E, 0x7F, 0x7E, 0x7C, 0x78, 0x70, 0x60, 0x40}, //Special Characger 1
    {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x00, 0x00}, //Special Character 2
    {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x7E, 0x3C, 0x18, 0x00}}; //Special Character 3 :126

/*
 * Writes a byte to SPI without changing chip select (CSX) state.
 * Called by the write_command() and write_data() functions which
 * control these pins as required.
 */


int spi_write(unsigned char data) {
    // Chờ cho bộ đệm có sẵn để ghi dữ liệu
    while (!(SPI2->SR & SPI_SR_TXE)) {} // Kiểm tra TXE
    SPI2->DR = data; // Ghi dữ liệu vào DR
    while (!(SPI2->SR & SPI_SR_RXNE)) {} // Chờ nhận dữ liệu
    (void) SPI2->DR; // Đọc dữ liệu từ DR để xóa cờ RXNE
//	SPI_I2S_SendData(SPI2, data);
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
//	}
//	return SPI_I2S_ReceiveData(SPI2);

}

/*
 * Writes a data byte to the display. Pulls CS low as required.
 */
void lcd_write_data(unsigned char data) {
    //CS LOW
    W_GPIO(CSX_PORT, CSX_PIN, 0);
    //DC HIGH
    W_GPIO(CMD_PORT, CMD_PIN, 1);
    //Send data to the SPI register
    spi_write(data);
    //CS HIGH
    W_GPIO(CSX_PORT, CSX_PIN, 1);
}

/*
 * Writes a command byte to the display
 */
void lcd_write_command(unsigned char data) {
    //Pull the command AND chip select lines LOW
    W_GPIO(CMD_PORT, CMD_PIN, 0);
    //CSX = 0;
    W_GPIO(CSX_PORT, CSX_PIN, 0);
    spi_write(data);
    //Return the control lines to HIGH
    W_GPIO(CSX_PORT, CSX_PIN, 1);
}

/*
 * Writes data to a specific register.
 * Accepts a 16-bit register address, and 16-bits of data.
 */
void lcd_write_register(unsigned int reg, unsigned int data) {
    //Write each register byte, and each data byte seperately.
    lcd_write_command(reg >> 8); //regH
    lcd_write_command(reg & 0xFF); //regL
    lcd_write_data(data >> 8); //dataH
    lcd_write_data(data & 0xFF); //dataL
}

/*
 * Swaps two 16-bit integers
 */
void swap_int(int *num1, int *num2) {
    int temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}

/*
 * Swaps two 8-bit integers
 */
void swap_char(char *num1, char *num2) {
    char temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}

/*
 * Delay calcualted on 32MHz clock.
 * Does NOT adjust to clock setting
 */
void delay_ms(double millis) {
    int multiplier = 4;
    double counter = millis;
    while(multiplier--) {
        while(counter--);
        counter = millis;
    }
}

/*
 * A short microsecond delay routine
 * (not measured)
 */
void delay_us(long int cycles) {
    while(cycles--);
}

/*
 * Initialisation routine for the LCD
 * I got this from the one of the ebay sellers which make them.
 * From Open-Smart
 */
void lcd_init() {
    
    //SET control pins for the LCD HIGH (they are active LOW)
    W_GPIO(CSX_PORT, CSX_PIN, 1);
    W_GPIO(CMD_PORT, CMD_PIN, 0); //Data / command select, the datasheet isn't clear on that.
    W_GPIO(RESX_PORT, RESX_PIN, 1); //RESET pin HIGH
    
    //Cycle reset pin
    W_GPIO(RESX_PORT, RESX_PIN, 0);
    delay_ms(500);
    W_GPIO(RESX_PORT, RESX_PIN, 1);
    delay_ms(500);

    lcd_init_command_list();
    
}

/**
 * This is the magic initialisation routine. Supplied by Open-Smart
 * who sell cheap modules on eBay.
 * This routine works with OTM2201A and ILI9925.
 */
void lcd_init_command_list(void)
{
    
    lcd_write_register(ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
    lcd_write_register(ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
    lcd_write_register(ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
    lcd_write_register(ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
    lcd_write_register(ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
    
    delay_ms(10);
    
    lcd_write_register(ILI9225_POWER_CTRL2, 0xFFFF); // EVERYTHING ON
    lcd_write_register(ILI9225_POWER_CTRL3, 0x7000); // Set BT,DC1,DC2,DC3
    lcd_write_register(ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
    lcd_write_register(ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
    lcd_write_register(ILI9225_POWER_CTRL1, 0x0F00); // Set SAP,DSTB,STB
    
    delay_ms(10);
    

    lcd_write_register(ILI9225_POWER_CTRL2, 0xFFFF); // Set APON,PON,AON,VCI1EN,VC

    delay_ms(50);


    lcd_write_register(ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
    lcd_write_register(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
    lcd_write_register(ILI9225_ENTRY_MODE, 0x1030); // set GRAM write direction and BGR=1.
    lcd_write_register(ILI9225_DISP_CTRL1, 0x0000); // Display off
    lcd_write_register(ILI9225_BLANK_PERIOD_CTRL1, 0x0202); // set the back porch and front porch (2 lines, minimum)
    lcd_write_register(ILI9225_FRAME_CYCLE_CTRL, 0x0000); // set the clocks number per line
    lcd_write_register(ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
    lcd_write_register(ILI9225_OSC_CTRL, 0x0F01); // Set Osc
    lcd_write_register(ILI9225_VCI_RECYCLING, 0x0000); // Set VCI recycling
    lcd_write_register(ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
    lcd_write_register(ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address

    /* Set GRAM area */
    lcd_write_register(ILI9225_GATE_SCAN_CTRL, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000); 
    lcd_write_register(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB); 
    lcd_write_register(ILI9225_PARTIAL_DRIVING_POS2, 0x0000); 
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 

    /* Set GAMMA curve */
    lcd_write_register(ILI9225_GAMMA_CTRL1, 0x0000); 
    lcd_write_register(ILI9225_GAMMA_CTRL2, 0x0808); 
    lcd_write_register(ILI9225_GAMMA_CTRL3, 0x080A); 
    lcd_write_register(ILI9225_GAMMA_CTRL4, 0x000A); 
    lcd_write_register(ILI9225_GAMMA_CTRL5, 0x0A08); 
    lcd_write_register(ILI9225_GAMMA_CTRL6, 0x0808); 
    lcd_write_register(ILI9225_GAMMA_CTRL7, 0x0000); 
    lcd_write_register(ILI9225_GAMMA_CTRL8, 0x0A00); 
    lcd_write_register(ILI9225_GAMMA_CTRL9, 0x0710); 
    lcd_write_register(ILI9225_GAMMA_CTRL10, 0x0710); 

    lcd_write_register(ILI9225_DISP_CTRL1, 0x0012); 

    delay_ms(50); 
    
    lcd_write_register(ILI9225_DISP_CTRL1, 0x1017);

    
}

/*
 * Draws a single pixel to the LCD at position X, Y, with 
 * Colour.
 * 
 * 28 bytes per pixel. Use it wisely.
 */
void draw_pixel(char x, char y, unsigned int colour) {
    //If we are in landscape view then translate -90 degrees
    if(LANDSCAPE) {
        swap_char(&x, &y);
        y = WIDTH - y;
    }
    
    //Set the x, y position that we want to write to
    set_draw_window(x, y, x+1, y+1);
    lcd_write_data(colour >> 8);
    lcd_write_data(colour & 0xFF);
}

/*
 * Fills a rectangle with a given colour
 */
void fill_rectangle(char x1, char y1, char x2, char y2, unsigned int colour) {
    //If landscape view then translate everyting -90 degrees
    if(LANDSCAPE) {
        swap_char(&x1, &y1);
        swap_char(&x2, &y2);
        y1 = WIDTH - y1;
        y2 = WIDTH - y2;
        swap_char(&y2, &y1);
    }
    
    //Split the colour int in to two bytes
    unsigned char colour_high = colour >> 8;
    unsigned char colour_low = colour & 0xFF;
    
    //Set the drawing region
    set_draw_window(x1, y1, x2, y2);
    
    //We will do the SPI write manually here for speed
    //( the data sheet says it doesn't matter if CSX changes between 
    // data sections but I don't trust it.)
    //CSX low to begin data
    W_GPIO(CSX_PORT, CSX_PIN, 0);

    //Write colour to each pixel
    for(int y = 0; y < y2-y1+1 ; y++) {
        for(int x = 0; x < x2-x1+1; x++) {
            lcd_write_data(colour_high);
            lcd_write_data(colour_low);
        }
    }
    //Return CSX to high
    W_GPIO(CSX_PORT, CSX_PIN, 1);
}

/*
 * Sets the X,Y position for following commands on the display.
 * Should only be called within a function that draws something
 * to the display.
 * 
 * NOTE: This is 26 bytes. Use it sparingly (see draw_bitmap())
 */
void set_draw_window(char x1, char y1, char x2, char y2) {
    
    //Check that the values are in order
    if(x2 < x1)
        swap_char(&x2, &x1);
    if(y2 < y1)
        swap_char(&y2, &y1);

    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR1,x2);
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR2,x1);

    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR1,y2);
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR2,y1);

    lcd_write_register(ILI9225_RAM_ADDR_SET1,x1);
    lcd_write_register(ILI9225_RAM_ADDR_SET2,y1);

    lcd_write_command(0x00);
    lcd_write_command(0x22);
}

/*
 * Draws a single char to the screen.
 * Called by the various string writing functions like print().
 * 
 * NOTE:
 * This sends approx. 800 bytes per char to the LCD, but it does preserver
 * the background image. Use the draw_fast_char() function where possible.
 */
void draw_char(char x, char y, char c, unsigned int colour, char size) {
    int i, j;
    char line;
    unsigned int font_index = (c - 32);
    
    //Get the line of pixels from the font file
    for(i=0; i<13; i++ ) {

        line = FontLarge[font_index][12 - i];
        
        //Draw the pixels to screen
        for(j=0; j<8; j++) {
            if(line & (0x01 << j)) {
                if(size == 1) {
                    //If we are just doing the smallest size font then do a single pixel each
                    draw_pixel(x+(8-j), y+i, colour);
                }
                else {
                    // do a small box to represent each pixel
                    fill_rectangle(x+((8-j)*size), y+((i)*size), x+((8-j)*size)+size, y+((i)*size)+size, colour);
                }
            }
        }
    }
}

/*
 * Draws a char to the screen using a constant stream of pixel data whic his faster
 * than drawing individual pixels.
 * This will draw over any background image though.
 * 
 * NOTE: This sends 130 bytes for a regular sized char
 */
void draw_fast_char(char x, char y, char c, unsigned int colour, unsigned int bg_colour) {
    char line;
    char width = 8;
    char height = 13;
    unsigned int font_index = (c - 32);
    unsigned int this_px = bg_colour;
    
    //Adjust for portrait / landscape orientation
    if(LANDSCAPE) {
        swap_char(&x, &y);
        swap_char(&width, &height);
        y = WIDTH - y - height; //I don't know why this offset works. :/
    }
    
    //Set the drawing region
    set_draw_window(x, y, x + width - 1, y + height);
    
    //We will do the SPI write manually here for speed
    //CSX low to begin data
    W_GPIO(CSX_PORT, CSX_PIN, 0);
    
    //Get the line of pixels from the font file
    for(int i=0; i < height; i++ ) {
        line = FontLarge[font_index][12 - i];
        
        //Draw the pixels to screen
        for(int j = width-1; j >= 0; j--) {
            //Default pixel colour is the background colour, unless changed below
            this_px = bg_colour;
            
            if(LANDSCAPE) {
                line = FontLarge[font_index][j];
                if((line >> i) & 0x01)
                    this_px = colour;
            } else {
                //Calculate the correct pixel colour
                if((line >> (j)) & 0x01)
                    this_px = colour;
            }
            
            
            
            //Draw this pixel
            lcd_write_data(this_px >> 8);
            lcd_write_data(this_px & 0xFF);
        }
    }
    
    
    //Return CSX to high
    W_GPIO(CSX_PORT, CSX_PIN, 1);
}


/*
 * Writes a string to the display as an array of chars at position x, y with 
 * a given colour and size.
 */
void draw_string(char x, char y, unsigned int colour, char size, char *str) {
    
    //Work out the size of each character
    int char_width = size * 9;
    //Iterate through each character in the string
    int counter = 0;
    while(str[counter] != '\0') {
        //Calculate character position
        int char_pos = x + (counter * char_width);
        //Write char to the display
        draw_char(char_pos, y, str[counter], colour, size);
        //Next character
        counter++;
    }
}

/*
 * Draws a string using the draw_fast_char() function.
 * This will not preserve any background image and so a custom background
 * colour should be provided.
 * NOTE: Can only be the regular sized font. No scaling.
 */
void draw_fast_string(char x, char y, unsigned int colour, unsigned int bg_colour, char *str) {
    //Iterate through each character in the string
    int counter = 0;
    while(str[counter] != '\0') {
        //Write char to the display
        draw_fast_char(x + (counter * 9), y, str[counter], colour, bg_colour);
        //Next character
        counter++;
    }
}

/*
 * Draws a bitmap by directly writing the byte stream to the LCD.
 * 
 * So the scaling is done strangely here because writing individual pixels 
 * has an overhead of 26 bytes each.
 */
void draw_bitmap(int x1, int y1, int scale, const unsigned int *bmp) {
	int width = bmp[0];
	int height = bmp[1];
	unsigned int this_byte;
	int x2 = x1 + (width * scale);
	int y2 = y1 + (height * scale);

	//If landscape view then translate everyting -90 degrees
	if (LANDSCAPE) {
		swap_char(&x1, &y1);
		swap_char(&x2, &y2);
		y1 = WIDTH - y1;
		y2 = WIDTH - y2;
		swap_char(&y2, &y1);
		swap_int(&width, &height);
	}


	//Set the drawing region
	set_draw_window(x1, y1, x2 + scale - 1, y2);

	//We will do the SPI write manually here for speed
	//CSX low to begin data
    W_GPIO(CSX_PORT, CSX_PIN, 0);

	//Write colour to each pixel
	for (int i = 0; i < height; i++) {
		//this loop does the vertical axis scaling (two of each line))
		for (int sv = 0; sv < scale; sv++) {
			for (int j = 0; j <= width; j++) {
				//Choose which byte to display depending on the screen orientation
				//NOTE: We add a byte because of the first two bytes being dimension data in the array
				if (LANDSCAPE)
					this_byte = bmp[(height * (j + 1)) - i + 1];
				else
					this_byte = bmp[(width * (i)) + j + 1];

				//And this loop does the horizontal axis scale (two of each pixels on the line))
				for (int sh = 0; sh < scale; sh++) {
					//Draw this pixel
					lcd_write_data(this_byte >> 8);
					lcd_write_data(this_byte & 0xFF);
				}
			}
		}
	}

	//Return CSX to high
    W_GPIO(CSX_PORT, CSX_PIN, 1);

}

void drawEmptyRectangle(int x, int y, int width, int height, uint16_t color, int thickness) {
	for (int t = 0; t < thickness; t++) { // thickness
	        for (int j = y; j < y + height; j++) {
	        	// left  edge
	            draw_pixel(x + t, j, color);
	            // right edge
	            draw_pixel(x + width - 1 - t, j, color);
	        }
	        for (int i = x; i < x + width; i++) {
	        	// top edge
	            draw_pixel(i, y + t, color);
	            // bottom edge
	            draw_pixel(i, y + height - 1 - t, color);
	        }
	    }
}
void drawCircle(int centerX, int centerY, int radius, uint16_t color, int thickness) {
    for (int r = radius; r > radius - thickness; r--) {
        int x = 0;
        int y = r;
        int d = 3 - 2 * r;  // Tính giá trị ban đầu của tham số quyết định

        while (x <= y) {
            // Vẽ các điểm đối xứng quanh tâm
        	draw_pixel(centerX + x, centerY + y, color);
        	draw_pixel(centerX - x, centerY + y, color);
        	draw_pixel(centerX + x, centerY - y, color);
        	draw_pixel(centerX - x, centerY - y, color);
        	draw_pixel(centerX + y, centerY + x, color);
        	draw_pixel(centerX - y, centerY + x, color);
        	draw_pixel(centerX + y, centerY - x, color);
        	draw_pixel(centerX - y, centerY - x, color);

            // Cập nhật giá trị của d và di chuyển (x, y)
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

void drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, int thickness) {
    for (int i = -thickness/2; i <= thickness/2; i++) {
        drawLine(x0 + i, y0, x1 + i, y1, color);
    }
}
void drawLine(int x0, int y0, int x1, int y1, uint16_t color) {
    // Thuật toán vẽ đường thẳng Bresenham
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
    	draw_pixel(x0, y0, color);  // Vẽ điểm ảnh tại (x0, y0)
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}
void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color,int thickness) {
    drawThickLine(x0, y0, x1, y1, color, thickness);
    drawThickLine(x1, y1, x2, y2, color, thickness);
    drawThickLine(x2, y2, x0, y0, color, thickness);
}
void draw_star(int centerX, int centerY, int radius, int color) {
	double angle = M_PI / 2; // Bắt đầu từ góc 90 độ (đỉnh trên cùng)
	    double angleStep = 2 * M_PI / 5; // Góc giữa các đỉnh (72 độ)

	    int x[5], y[5];
	    for (int i = 0; i < 5; i++) {
	        x[i] = centerX + radius * cos(angle);
	        y[i] = centerY - radius * sin(angle);
	        angle += angleStep;
	    }

	    // Kết nối các đỉnh để tạo hình ngôi sao
	    drawLine(x[0], y[0], x[2], y[2], color);
	    drawLine(x[2], y[2], x[4], y[4], color);
	    drawLine(x[4], y[4], x[1], y[1], color);
	    drawLine(x[1], y[1], x[3], y[3], color);
	    drawLine(x[3], y[3], x[0], y[0], color);
}
void erase_star(int centerX, int centerY, int radius, int bgColor) {
    draw_star(centerX, centerY, radius, bgColor);
}

// Hàm tạo hiệu ứng nhấp nháy
void blink_star_edges(int centerX, int centerY, int radius, int starColor, int bgColor, int Delay_ms) {
    for (int i = 0; i < 10; i++) { // Lặp lại 10 lần hiệu ứng nhấp nháy
        // Hiển thị ngôi sao
        draw_star(centerX, centerY, radius, starColor);
        delay_ms(Delay_ms); // Tạo độ trễ với usleep (đơn vị là microsecond)

        // Xóa ngôi sao
        erase_star(centerX, centerY, radius, bgColor);
        delay_ms(Delay_ms); // Tạo độ trễ với usleep (đơn vị là microsecond)
    }
}







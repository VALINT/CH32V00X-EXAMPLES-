/*
 * SSD1306.h
 *
 *  Created on: Dec 6, 2023
 *      Author: VAL
 */

#ifndef USER_SSD1306_H_
#define USER_SSD1306_H_

#define USE_SPI
//#define USE_I2C

#ifdef USE_I2C
    #include "i2c.h"
#endif

#ifdef USE_SPI
    #include "spi.h"
    #include "gpio.h"
    #define CPORT       GPIOC
    #define RESET       4
    #define DC          3
    #define CS          1

    #define START       asm("NOP");//CLEAR_PIN(CPORT, CS)
    #define STOP        asm("NOP");//SET_PIN(CPORT, CS)
    #define COMMAND     CLEAR_PIN(CPORT, DC)
    #define DATA        SET_PIN(CPORT, DC)
#endif

// OLED definitions
#define OLED_ADDR         0x78    // OLED write address (0x3C << 1)
#define OLED_CMD_MODE     0x00    // set command mode
#define OLED_DAT_MODE     0x40    // set data mode

// OLED commands
#define OLED_COLUMN_LOW   0x00    // set lower 4 bits of start column (0x00 - 0x0F)
#define OLED_COLUMN_HIGH  0x10    // set higher 4 bits of start column (0x10 - 0x1F)
#define OLED_MEMORYMODE   0x20    // set memory addressing mode (following byte)
#define OLED_COLUMNS      0x21    // set start and end column (following 2 bytes)
#define OLED_PAGES        0x22    // set start and end page (following 2 bytes)
#define OLED_SCROLL_OFF   0x2E    // deactivate scroll command
#define OLED_STARTLINE    0x40    // set display start line (0x40-0x7F = 0-63)
#define OLED_CONTRAST     0x81    // set display contrast (following byte)
#define OLED_CHARGEPUMP   0x8D    // (following byte - 0x14:enable, 0x10: disable)
#define OLED_XFLIP_OFF    0xA0    // don't flip display horizontally
#define OLED_XFLIP        0xA1    // flip display horizontally
#define OLED_INVERT_OFF   0xA6    // set non-inverted display
#define OLED_INVERT       0xA7    // set inverse display
#define OLED_MULTIPLEX    0xA8    // set multiplex ratio (following byte)
#define OLED_DISPLAY_OFF  0xAE    // set display off (sleep mode)
#define OLED_DISPLAY_ON   0xAF    // set display on
#define OLED_PAGE         0xB0    // set start page (following byte)
#define OLED_YFLIP_OFF    0xC0    // don't flip display vertically
#define OLED_YFLIP        0xC8    // flip display vertically
#define OLED_OFFSET       0xD3    // set display offset (y-scroll: following byte)
#define OLED_COMPINS      0xDA    // set COM pin config (following byte)

// Macros
#ifdef USE_I2C
    #define OLED_xfer_start     I2C_start(OLED_ADDR)
    #define OLED_xfer_stop      I2C_stop
    #define OLED_send_byte(b)   I2C_write(b)
    #define OLED_data_stop      I2C_stop
    #define OLED_command_stop   I2C_stop
#endif

#ifdef USE_SPI
    #define OLED_xfer_start     START
    #define OLED_xfer_stop      STOP
    #define OLED_send_byte(b)   SPI_write(b)
    #define OLED_data_stop      STOP
    #define OLED_command_stop   STOP
#endif
// Functions
void OLED_init(void);
void OLED_data_start(void);
void OLED_command_start(void);
void OLED_send_command(uint8_t cmd);
void OLED_setpos(uint8_t x, uint8_t y);
void OLED_fill(uint8_t p);
void OLED_fill_bmp(uint8_t* bmp);
void OLED_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t* bmp);

#endif /* USER_SSD1306_H_ */

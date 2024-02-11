/*
 * SSD1306.c
 *
 *  Created on: Dec 6, 2023
 *      Author: VAL
 */

#include "SSD1306.h"

// OLED initialisation sequence
const uint8_t OLED_INIT_CMD[] = {
  OLED_MULTIPLEX,   0x3F,                 // set multiplex ratio
  OLED_CHARGEPUMP,  0x14,                 // set DC-DC enable
  OLED_MEMORYMODE,  0x00,                 // set horizontal addressing mode
  OLED_COLUMNS,     0x00, 0x7F,           // set start and end column
  OLED_PAGES,       0x00, 0x3F,           // set start and end page
  OLED_COMPINS,     0x12,                 // set com pins
  OLED_XFLIP, OLED_YFLIP,                 // flip screen
  OLED_DISPLAY_ON                         // display on
};

// OLED init function
void OLED_init(void) {
  uint8_t i;
#ifdef USE_I2C
  I2C_init();                             // initialize I2C first
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  for(i = 0; i < sizeof(OLED_INIT_CMD); i++)
    I2C_write(OLED_INIT_CMD[i]);          // send the command bytes
  I2C_stop();                             // stop transmission
#endif

#ifdef USE_SPI
  RCC->APB2PCENR |= (RCC_IOPCEN);
  CLEAR_INIT(CPORT, RESET);
  CLEAR_INIT(CPORT, DC);
  CLEAR_INIT(CPORT, CS);
  CLEAR_INIT(CPORT, 6);
  CLEAR_INIT(CPORT, 5);
  INIT_PIN(CPORT, RESET, OUTPUT_PUSH_PULL_50M);
  INIT_PIN(CPORT, DC, OUTPUT_PUSH_PULL_50M);
  INIT_PIN(CPORT, CS, ALTERN_PUSH_PULL_50M);
  INIT_PIN(CPORT, 6, ALTERN_PUSH_PULL_50M);
  INIT_PIN(CPORT, 5, ALTERN_PUSH_PULL_50M);
  SET_PIN(CPORT, RESET);
  SET_PIN(CPORT, CS);
  SET_PIN(CPORT, DC);
  SPI_init();

  Delay_Ms(10);
  CLEAR_PIN(CPORT, RESET);
  Delay_Ms(1);
  SET_PIN(CPORT, RESET);

  COMMAND;
  for(i = 0; i < sizeof(OLED_INIT_CMD); i++)
  {
      START;
      SPI_write(OLED_INIT_CMD[i]);          // send the command bytes
      STOP;// stop transmission
  }

#endif

}

// Start sending data
void OLED_data_start(void) {
#ifdef USE_I2C
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
#endif

#ifdef USE_SPI
  DATA;
#endif
}

// Start sending command
void OLED_command_start(void) {
#ifdef USE_I2C
    I2C_start(OLED_ADDR);                   // start transmission to OLED
    I2C_write(OLED_CMD_MODE);               // set command mode
#endif

#ifdef USE_SPI
  COMMAND;
#endif
}

// OLED send command
void OLED_send_command(uint8_t cmd) {
#ifdef USE_I2C
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(cmd);                         // send command
  I2C_stop();                             // stop transmission
#endif

#ifdef USE_SPI
  START;
  COMMAND;
  SPI_write(cmd);
  STOP;
#endif
}

// OLED set cursor position
void OLED_setpos(uint8_t x, uint8_t y) {
#ifdef USE_I2C
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_PAGE | y);               // set page start address
  I2C_write(x & 0x0F);                        // set lower nibble of start column
  I2C_write(OLED_COLUMN_HIGH | (x >> 4)); // set higher nibble of start column
  I2C_stop();                             // stop transmission
#endif

#ifdef USE_SPI
  START;
  COMMAND;
  SPI_write(OLED_PAGE | y);
  SPI_write(x & 0x0F);
  SPI_write(OLED_COLUMN_HIGH | (x >> 4));
  STOP;
#endif
}

// OLED fill screen
void OLED_fill(uint8_t p) {
  OLED_setpos(0, 0);                      // set cursor to display start
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(uint16_t i=128*8; i; i--) I2C_write(p); // send pattern
  I2C_stop();                             // stop transmission
}

// OLED fill screen
void OLED_fill_bmp(uint8_t* bmp) {
#ifdef USE_I2C
  OLED_setpos(0, 0);                      // set cursor to display start
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(uint16_t i=128*8; i; i--) I2C_write(*(bmp++)); // send pattern
  I2C_stop();                             // stop transmission
#endif

#ifdef USE_SPI
    OLED_setpos(0, 0);                      // set cursor to display start
    START;
    DATA;
    for(uint16_t i=128*8; i; i--) {START; SPI_write(*(bmp++)); STOP;} // send pattern
    STOP;
#endif
}

// OLED draw bitmap
void OLED_draw_bmp(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t* bmp) {
  for(uint8_t y = y0; y < y1; y++) {
    OLED_setpos(x0, y);
    I2C_start(OLED_ADDR);
    I2C_write(OLED_DAT_MODE);
    for(uint8_t x = x0; x < x1; x++)
      I2C_write(*bmp++);
    I2C_stop();
  }
}

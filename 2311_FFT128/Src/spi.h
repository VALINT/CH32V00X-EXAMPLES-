/*
 * spi.h
 *
 *  Created on: Feb 7, 2024
 *      Author: VAL
 */

#ifndef USER_SPI_H_
#define USER_SPI_H_

#include <ch32v00x.h>

// SPI Parameters


// SPI Functions
void SPI_init(void);            // I2C init function
void SPI_write(uint8_t data);   // I2C transmit one data byte via I2C

#endif /* USER_SPI_H_ */

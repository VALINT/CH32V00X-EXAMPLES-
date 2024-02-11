/*
 * i2c.h
 *
 *  Created on: Dec 6, 2023
 *      Author: VAL
 */

#ifndef USER_I2C_H_
#define USER_I2C_H_

#include <ch32v00x.h>

// I2C Parameters
#define F_CPU         48000000
#define I2C_CLKRATE   400000    // I2C bus clock rate (Hz)
#define I2C_REMAP     0         // I2C pin remapping (see above)

// I2C Functions
void I2C_init(void);            // I2C init function
void I2C_start(uint8_t addr);   // I2C start transmission, addr must contain R/W bit
void I2C_write(uint8_t data);   // I2C transmit one data byte via I2C
void I2C_stop(void);            // I2C stop transmission

#endif /* USER_I2C_H_ */

/*
 * I16FFT.h
 *
 *  Created on: Jan 25, 2024
 *      Author: VAL
 */

#ifndef I16FFT_H_
#define I16FFT_H_

#include <stdint.h>
#include <math.h>

// Hamming window

void i16fft(int16_t*, int16_t*);
void i16mag(int16_t*, int16_t*, uint8_t*);

#endif /* I16FFT_H_ */

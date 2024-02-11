/*
 * spi.c
 *
 *  Created on: Feb 7, 2024
 *      Author: VAL
 */

#include "spi.h"

void SPI_init(void)
{
    // Set-up SPI
    RCC->APB2PCENR |=  RCC_IOPCEN | RCC_SPI1EN;
    SPI1->CTLR1 =  (SPI_CTLR1_SSI | !SPI_CTLR1_SSM | SPI_CTLR1_MSTR | (SPI_CTLR1_BR & (0b010 << 3)));
    SPI1->CTLR1 |= (SPI_CTLR1_SPE);
    SPI1->CTLR2 |= (SPI_CTLR2_TXDMAEN | SPI_CTLR2_SSOE);
}

void SPI_write(uint8_t data)
{
    while((~SPI1->STATR & SPI_STATR_TXE)){asm("NOP");}
    SPI1->DATAR = data;
    while(SPI1->STATR & SPI_STATR_BSY){asm("NOP");}
}

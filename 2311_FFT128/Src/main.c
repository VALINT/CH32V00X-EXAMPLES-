/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : VAL
 * Date               : 2023/11/25
 * Description        : Spectrum analyzer.
 *********************************************************************************/

/*
 *@Note
 *128 points FFT for CH32V003
 *Result draws on the OLED display
 *For sampling and screen drawing the DMA is used
 */

// Please set __stack_size = 128; in Link.ld file

#include "debug.h"
#include "stdint.h"
#include "SSD1306.h"
#include "I16FFT.h"
#include "vals_adc.h"
#include <ch32v00x.h>

#define S_32KHZ
//#define S_16KHZ
//#define S_8KHZ

#ifdef S_32KHZ
    #define S_PERIOD 1500
#endif

#ifdef S_16KHZ
    #define S_PERIOD 3000
#endif

#ifdef S_8KHZ
    #define S_PERIOD 6000
#endif
                     //{0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
const uint8_t row[9] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};

    uint8_t screen[1024] = {};
    int16_t real1[128] = {};
    int16_t real2[128] = {};
    int16_t imag[128] = {};
    uint8_t ampl[64] = {};

    volatile uint8_t buff_num = 0;

void ADCConfig(void)
{
    // Set-up clocking
    // Enable ADC and PORTD clocking
    RCC->APB2PCENR |= (RCC_ADC1EN | RCC_IOPDEN);
    // Enable Timer2 clocking
    RCC->APB1PCENR |= (RCC_TIM2EN);
    // Enable DMA clocking
    RCC->AHBPCENR  |= (RCC_DMA1EN);
    // Set ADC prescaler to 8
    RCC->CFGR0 |= (RCC_ADCPRE & (0b00101 << 11));

    // Set-up input port
    //Set PORTD PIN4 in analog input mode
    GPIOD->CFGLR &= ~((0b11 << 16) | (0b11 << 14));

    // Set-up ADC
    // Setup ADC in RULE mode
    ADC1->CTLR1     = (ADC_CTLR1_DISCNUM(0) | ADC_CTLR1_CALVOL(1));
    ADC1->CTLR2     = (ADC_CTLR2_ADON | ADC_CTLR2_EXTTRIG | (ADC_CTLR2_EXTSEL(3)) | ADC_CTLR2_DMA);
    ADC1->SAMPTR2   = (ADC_SAMPTR2_SMP7(0b100));
    ADC1->RSQR1     = (ADC_RSQR1_L(1));
    ADC1->RSQR3     = (ADC_RSQR3_SQ1(7));

    //ResetCalibration(ADC1);
    ADC1->CTLR2 |= ADC_RSTCAL;
    while (ADC1->CTLR2 & ADC_RSTCAL);

    //StartCalibration(ADC1);
    ADC1->CTLR2 |= ADC_CAL;
    while (ADC1->CTLR2 & ADC_CAL);

    //Set-up Timer2
    TIM2->PSC       = 0;
    TIM2->ATRLR     = S_PERIOD - 1;
    TIM2->CTLR1     = (0);
    TIM2->CTLR2     = (TIM_MMS_1);

    // Set-up DMA
    // Transmission from ADC's RDATAR to MEM buffer
    DMA1_Channel1 -> CFGR = (DMA_CFGR1_TCIE | !DMA_CFGR1_DIR | !DMA_CFGR1_CIRC | DMA_CFGR1_MINC
                           | (DMA_CFGR1_PSIZE & 0b01 << 8) | (DMA_CFGR1_MSIZE & 0b01 << 10) | (DMA_CFGR1_PL & 0b11 << 12));
    DMA1_Channel1 -> PADDR = (uint32_t)&(ADC1->RDATAR);
    DMA1_Channel1 -> CNTR  = 128;
    DMA1_Channel1 -> MADDR = (uint32_t)&(real1);

    // Data transferring from MEM buffer to SPI's DATAR register
    DMA1_Channel3 -> CFGR = (DMA_CFGR1_TCIE | DMA_CFGR1_DIR  | !DMA_CFGR1_CIRC | DMA_CFGR1_MINC
            | (DMA_CFGR1_PSIZE & 0b00 << 8) | (DMA_CFGR1_MSIZE & 0b00 << 10) | (DMA_CFGR1_PL & 0b10 << 12));
    DMA1_Channel3 -> PADDR = (uint32_t)&(SPI1->DATAR);
    DMA1_Channel3 -> CNTR  = 1024;
    DMA1_Channel3 -> MADDR = (uint32_t)&(screen);
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    OLED_init();
    ADCConfig();

    while(1)
        {
            // Sampling
            TIM2->CTLR1     |= (TIM_CEN);
            TIM2->SWEVGR    =  (TIM_UG);
            DMA1_Channel1 -> CNTR  = 128;
            DMA1_Channel1 -> MADDR = (buff_num)? (uint32_t)&(real1) : (uint32_t)&(real2);
            DMA1_Channel1 -> CFGR |= DMA_CFGR1_EN;
            DMA1 -> INTFCR = DMA_CTCIF1;

            // Draw screen
            OLED_setpos(0, 0);                      // set cursor to display start
            DATA;
            DMA1_Channel3 -> PADDR = (uint32_t)&(SPI1->DATAR);
            DMA1_Channel3 -> CNTR  = 1024;
            DMA1_Channel3 -> MADDR = (uint32_t)&(screen);
            DMA1_Channel3 -> CFGR |= DMA_CFGR3_EN;
            DMA1 -> INTFCR = DMA_CTCIF3;

            // Conversion software version 7.0
            (buff_num)? i16fft(&real2[0], &imag[0])
                      : i16fft(&real1[0], &imag[0]);
            (buff_num)? i16mag(&real2[0], &imag[0], &ampl[0])
                      : i16mag(&real1[0], &imag[0], &ampl[0]);

            // Create output screen
            for(volatile uint8_t j = 0; j < 64; j++)
            {
                volatile uint8_t m = 0;
                volatile uint8_t am = ampl[j];
                if(am > 63) am = 63;
                for(volatile int16_t i = 0x0380; i >= 0x0000; i-=0x080)
                {
                    if(am > 8){
                        m = 8;
                        am -= 8;
                    }
                    else {
                        m = am;
                        am = 0;
                    }
                    screen[i|(j<<1)]   = row[m] | ((i == 0x0380)? 0x80 : 0x00);
                    screen[i|(j<<1)+1] = row[m] | ((i == 0x0380)? 0x80 : 0x00);
                }
            }

            #if defined(S_16KHZ) | defined(S_8KHZ)
                while(!(DMA1->INTFR & DMA_TCIF1)){asm("NOP");}
            #endif

            // Change buffer
            buff_num++;
            buff_num &= 0x01;
        }
}

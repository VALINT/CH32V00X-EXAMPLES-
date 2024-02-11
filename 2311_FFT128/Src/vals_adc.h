/*
 * vals_adc.h
 *
 *  Created on: Feb 11, 2024
 *      Author: VAL
 */

#ifndef USER_VALS_ADC_H_
#define USER_VALS_ADC_H_

#define ADC_STATR       *((uint32_t*)0x40012400)    // ADC status register 0x00000000
#define ADC_CTLR1       *((uint32_t*)0x40012404)    // ADC control register 1 0x00000000
#define ADC_CTLR2       *((uint32_t*)0x40012408)    // ADC control register 2 0x00000000
#define ADC_SAMPTR1     *((uint32_t*)0x4001240C)    // ADC sample time register 1 0x00000000
#define ADC_SAMPTR2     *((uint32_t*)0x40012410)    // ADC sample time register 2 0x00000000
#define ADC_IOFR1       *((uint32_t*)0x40012414)    // ADC injected channel data offset register 1 0x00000000
#define ADC_IOFR2       *((uint32_t*)0x40012418)    // ADC injected channel data offset register 2 0x00000000
#define ADC_IOFR3       *((uint32_t*)0x4001241C)    // ADC injected channel data offset register 3 0x00000000
#define ADC_IOFR4       *((uint32_t*)0x40012420)    // ADC injected channel data offset register 4 0x00000000
#define ADC_WDHTR       *((uint32_t*)0x40012424)    // ADC watchdog high threshold register 0x00000000
#define ADC_WDLTR       *((uint32_t*)0x40012428)    // ADC watchdog low threshold register 0x00000000
#define ADC_RSQR1       *((uint32_t*)0x4001242C)    // ADC regular sequence register 1 0x00000000
#define ADC_RSQR2       *((uint32_t*)0x40012430)    // ADC regular sequence register 2 0x00000000
#define ADC_RSQR3       *((uint32_t*)0x40012434)    // ADC regular sequence register 3 0x00000000
#define ADC_ISQR        *((uint32_t*)0x40012438)    // ADC injected sequence register 0x00000000
#define ADC_IDATAR1     *((uint32_t*)0x4001243C)    // ADC injected data register 1 0x00000000
#define ADC_IDATAR2     *((uint32_t*)0x40012440)    // ADC injected data register 2 0x00000000
#define ADC_IDATAR3     *((uint32_t*)0x40012444)    // ADC injected data register 3 0x00000000
#define ADC_IDATAR4     *((uint32_t*)0x40012448)    // ADC injected data register 4 0x00000000
#define ADC_RDATAR      *((uint32_t*)0x4001244C)    // ADC regular data register 0x00000000
#define ADC_DLYR        *((uint32_t*)0x40012450)    // ADC delayed data register 0x00000000

// ADC status register 0x00000000
#define ADC_STATR_AWD           (0x00000001)
#define ADC_STATR_EOC           (0x00000002)
#define ADC_STATR_JEOC          (0x00000004)
#define ADC_STATR_JSTRT         (0x00000008)
#define ADC_STATR_STRT          (0x00000010)

// ADC control register 1 0x00000000
#define ADC_CTLR1_CALVOL(x)     (0x06000000 & (x << 25))
#define ADC_CTLR1_AWDEN         (0x00800000)
#define ADC_CTLR1_JAWDEN        (0x00400000)
#define ADC_CTLR1_DISCNUM(x)    (0x0000E000 & (x << 13))
#define ADC_CTLR1_JDISCEN       (0x00001000)
#define ADC_CTLR1_DISCEN        (0x00000800)
#define ADC_CTLR1_JAUTO         (0x00000400)
#define ADC_CTLR1_AWDSGL        (0x00000200)
#define ADC_CTLR1_SCAN          (0x00000100)
#define ADC_CTLR1_JEOCIE        (0x00000080)
#define ADC_CTLR1_AWDIE         (0x00000040)
#define ADC_CTLR1_EOCIE         (0x00000020)
#define ADC_CTLR1_AWDCH(x)      (0x0000000F & x)

// ADC control register 2 0x00000000
#define ADC_CTLR2_SWSTART       (0x00400000)
#define ADC_CTLR2_JSWSTART      (0x00200000)
#define ADC_CTLR2_EXTTRIG       (0x00100000)
#define ADC_CTLR2_EXTSEL(x)     (0x000E0000  & (x << 17))
#define ADC_CTLR2_JEXTTRIG      (0x00008000)
#define ADC_CTLR2_JEXTSEL(x)    (0x00007000  & (x << 12))
#define ADC_CTLR2_ALIGN         (0x00000800)
#define ADC_CTLR2_DMA           (0x00000100)
#define ADC_CTLR2_RSTCAL        (0x00000008)
#define ADC_CTLR2_CAL           (0x00000004)
#define ADC_CTLR2_CONT          (0x00000002)
#define ADC_CTLR2_ADON          (0x00000001)

// ADC sample time register 1 0x00000000
#define ADC_SAMPTR1_SMP15(x)    (0x00038000  & (x << 15))
#define ADC_SAMPTR1_SMP14(x)    (0x00007000  & (x << 12))
#define ADC_SAMPTR1_SMP13(x)    (0x00000E00  & (x << 9))
#define ADC_SAMPTR1_SMP12(x)    (0x000001C0  & (x << 6))
#define ADC_SAMPTR1_SMP11(x)    (0x00000038  & (x << 3))
#define ADC_SAMPTR1_SMP10(x)    (0x00000007  & (x << 0))

// ADC sample time register 2 0x00000000
#define ADC_SAMPTR2_SMP9(x)     (0x38000000  & (x << 27))
#define ADC_SAMPTR2_SMP8(x)     (0x07000000  & (x << 24))
#define ADC_SAMPTR2_SMP7(x)     (0x00E00000  & (x << 21))
#define ADC_SAMPTR2_SMP6(x)     (0x001C0000  & (x << 18))
#define ADC_SAMPTR2_SMP5(x)     (0x00038000  & (x << 15))
#define ADC_SAMPTR2_SMP4(x)     (0x00007000  & (x << 12))
#define ADC_SAMPTR2_SMP3(x)     (0x00000E00  & (x << 9))
#define ADC_SAMPTR2_SMP2(x)     (0x000001C0  & (x << 6))
#define ADC_SAMPTR2_SMP1(x)     (0x00000038  & (x << 3))
#define ADC_SAMPTR2_SMP0(x)     (0x00000007  & (x << 0))

// ADC injected channel data offset register 1 0x00000000
#define ADC_IOFR1_JOFFSET1(x)   (0x000003FF  & (x))

// ADC injected channel data offset register 2 0x00000000
#define ADC_IOFR2_JOFFSET2(x)   (0x000003FF  & (x))

// ADC injected channel data offset register 3 0x00000000
#define ADC_IOFR3_JOFFSET3(x)   (0x000003FF  & (x))

// ADC injected channel data offset register 4 0x00000000
#define ADC_IOFR4_JOFFSET4(x)   (0x000003FF  & (x))

// ADC watchdog high threshold register 0x00000000
#define ADC_WDHTR_HT(x)         (0x000003FF  & (x))

// ADC watchdog low threshold register 0x00000000
#define ADC_WDLTR_LT(x)         (0x000003FF  & (x))

// ADC regular sequence register 1 0x00000000
#define ADC_RSQR1_L(x)          (0x00F00000  & (x << 20))
#define ADC_RSQR1_SQ16(x)       (0x000F8000  & (x << 15))
#define ADC_RSQR1_SQ15(x)       (0x00007c00  & (x << 10))
#define ADC_RSQR1_SQ14(x)       (0x000003E0  & (x << 5))
#define ADC_RSQR1_SQ13(x)       (0x0000001F  & (x << 0))

// ADC regular sequence register 2 0x00000000
#define ADC_RSQR2_SQ12(x)       (0x3E000000  & (x << 25))
#define ADC_RSQR2_SQ11(x)       (0x01F00000  & (x << 20))
#define ADC_RSQR2_SQ10(x)       (0x000F8000  & (x << 15))
#define ADC_RSQR2_SQ9(x)        (0x00007c00  & (x << 10))
#define ADC_RSQR2_SQ8(x)        (0x000003E0  & (x << 5))
#define ADC_RSQR2_SQ7(x)        (0x0000001F  & (x << 0))

// ADC regular sequence register 3 0x00000000
#define ADC_RSQR3_SQ6(x)        (0x3E000000  & (x << 25))
#define ADC_RSQR3_SQ5(x)        (0x01F00000  & (x << 20))
#define ADC_RSQR3_SQ4(x)        (0x000F8000  & (x << 15))
#define ADC_RSQR3_SQ3(x)        (0x00007c00  & (x << 10))
#define ADC_RSQR3_SQ2(x)        (0x000003E0  & (x << 5))
#define ADC_RSQR3_SQ1(x)        (0x0000001F  & (x << 0))

// ADC injected sequence register 0x00000000
#define ADC_ISQR_JL(x)          (0x00300000  & (x << 20))
#define ADC_ISQR_JSQ4(x)        (0x000F8000  & (x << 15))
#define ADC_ISQR_JSQ3(x)        (0x00007c00  & (x << 10))
#define ADC_ISQR_JSQ2(x)        (0x000003E0  & (x << 5))
#define ADC_ISQR_JSQ1(x)        (0x0000001F  & (x << 0))

// ADC delayed data register 0x00000000
#define ADC_DLYR_DLYSRC         (0x00000200)
#define ADC_DLYR_DLYVLU(x)      (0x000001FF  & (x))

#endif /* USER_VALS_ADC_H_ */

# CH32V00x-EXAMPLES-
This repository contains various primitive and simple demos based on the CH32V002, CH32V003, and CH32V006 MCUs.

# 1. Simple blink - CH32V003(But is not limited)
  My first blink on RISK-V
# 2. Spectrum analyzer - CH32V003(But is not limited)
  A 128-point FFT is implemented using 16-bit fixed-point arithmetic. The system is built around the CH32V003 RISC-V microcontroller, an SPD0301 (SSD1306-compatible) OLED display, an ADC, TIM2, SPI, and DMA.
  The spectrum analyzer is based on the CH32V003 RISC-V MCU, which uses an RV32E CPU core without hardware multiplication support. Software-based multiplication takes approximately 400 ns per operation, which is an acceptable performance for this application. The FFT results are rendered on an OLED display driven by the SPD0301 controller via the SPI interface.
  The schematic tracer of the device:

  The device supports three sampling rate modes:
  - 32000 Sp/s
  - 16000 Sp/s
  -  8000 Sp/s
  
  For each sampling rate, an appropriate low-pass filter must be used with a cutoff frequency equal to half of the sampling rate in order to prevent aliasing.
  The frequency resolution is determined by the sampling rate and the FFT size according to: 
  
    F0 = Fs/N 
  
  where:
  - F₀ is the fundamental frequency (frequency resolution),
  - Fs is the sampling rate,
  - N is the number of samples.

The maximum displayable frequency also depends on the sampling rate. Since only the positive-frequency spectrum is shown, 64 FFT bins are displayed:

  - For Fs = 32,000 Hz:
  64 bins from 0 Hz to 15,750 Hz with a 250 Hz step

  - For Fs = 16,000 Hz:
  64 bins from 0 Hz to 7,875 Hz with a 125 Hz step

  - For Fs = 8,000 Hz:
  64 bins from 0 Hz to 3,937.5 Hz with a 62.5 Hz step

The FFT output is visualized as 64 vertical bars with linear frequency spacing and linear or logarithmic (selectable in code) amplitude scaling.

The result of the transformation of the square signal with a frequency of 1 kHz is shown in the next picture:
  
![Top View](2311_FFT128/Description/Input_Meandr_1kHz.png)

Fs = 32 kSp/s: (Here one can see odd harmonics №1 - 15)
![Top View](2311_FFT128/Description/FFT128_32kSp.png)

Fs = 16 kSp/s: (Here one can see odd harmonics №1 - 7)
![Top View](2311_FFT128/Description/FFT128_16kSp.png)

Fs = 8 kSp/s: (Here one can see odd harmonics №1 - 3)
![Top View](2311_FFT128/Description/FFT128_8kSp.png)

  Sampling, screen rendering, and signal processing are performed in parallel to minimize display update latency. DMA is used for both ADC sampling and SPI communication with the display, as SPI provides higher throughput than I²C.

The frame rate partially depends on the sampling frequency. As shown in the flowchart below, two processes dominate the execution time: signal sampling and the Fourier transform.

The total FFT processing time—including Hamming window application, FFT computation, magnitude calculation, and display buffer preparation—is approximately 9.5 ms. The sampling time depends on the selected sampling rate: 4 ms at 32 kHz, 8 ms at 16 kHz, and 16 ms at 8 kHz.

As a result, the frame rate is limited by the FFT processing time for sampling rates of 32 kHz and 16 kHz, achieving approximately 100–105 frames per second. At a sampling rate of 8 kHz, the frame rate is limited by the sampling process and is approximately 63 frames per second.

  ![Top View](2311_FFT128/Description/CH32V003_FFT2.png)
  
  ![Top View](2311_FFT128/Description/video_freq_sweep.mp4)
  

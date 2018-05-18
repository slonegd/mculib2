#pragma once

#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif


namespace RCC_ral {

   struct CR_t {
      struct Bits {
         // Bit 0 HSION: Internal high-speed clock enable
         volatile bool HSION          :1;
         // Bit 1 HSIRDY: Internal high-speed clock ready flag
         volatile bool HSIRDY         :1; 
         // Bit 2 Reserved, must be kept at reset value.
         volatile uint32_t dcb1       :1; 
         // Bits 7:3 HSITRIM[4:0]: Internal high-speed clock trimming
         volatile uint32_t HSITRIM    :5; 
         // Bits 15:8 HSICAL[7:0]: Internal high-speed clock calibration
         volatile uint32_t HSICAL     :8; 
         // Bit 16 HSEON: HSE clock enable
         volatile bool HSEON          :1; 
         // Bit 17 HSERDY: HSE clock ready flag
         volatile bool HSERDY         :1; 
         // Bit 18 HSEBYP: HSE clock bypass
         volatile bool HSEBYP         :1; 
         // Bit 19 CSSON: Clock security system enable
         volatile bool CSSON          :1; 
         // Bits 23:20 Reserved, must be kept at reset value.
         volatile uint32_t dcb2       :4; 
         // Bit 24 PLLON: Main PLL (PLL) enable
         volatile bool PLLON          :1;	
         // Bit 25 PLLRDY: Main PLL (PLL) clock ready flag
         volatile bool PLLRDY         :1;	
#if defined(STM32F030x6)
         volatile uint32_t dcb3       :6;
#elif defined(STM32F405xx)
         // Bit 26 PLLI2SON: PLLI2S enable
         volatile bool PLLI2SON	    :1;	
         // Bit 27 PLLI2SRDY: PLLI2S clock ready flag
         volatile bool PLLI2SRDY	    :1;	
         // Bits 31:28 Reserved, must be kept at reset value.
         volatile uint32_t dcb3      :4;	
#endif
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };

#if defined(STM32F405xx)
   struct PLLCFGR_t {
      enum PLLPdiv {
         PLLdiv2 = 0b00,
         PLLdiv4 = 0b01,
         PLLdiv6 = 0b10,
         PLLdiv8 = 0b11
      };
      enum PLLsource {
         sHSI = 0b0,
         sHSE = 0b1
      };
      struct Bits_t {
         // Bits 5:0 PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
         // 2 ≤ PLLM ≤ 63
         volatile uint32_t PLLM   :6;
         // Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO
         // 50 ≤ PLLN ≤ 432
         volatile uint32_t PLLN   :9;
         // Bit 15 Reserved, must be kept at reset value.
         volatile uint32_t dcb4   :1;
         // Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock
         volatile PLLPdiv PLLP    :2;
         // Bits 21:18 Reserved, must be kept at reset value.
         volatile uint32_t dcb1   :4;
         // Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
         volatile PLLsource PLLSRC :1;
         // Bit 23 Reserved, must be kept at reset value.
         volatile uint32_t dcb2   :1;
         // Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator
         // 2 ≤ PLLQ ≤ 15
         volatile uint32_t PLLQ   :4;
         // Bits 31:28 Reserved, must be kept at reset value.
         volatile uint32_t dcb3   :4;           
      };
      union {
         volatile Bits_t bits;
         volatile uint32_t reg;
      };
   };

   struct CFGR_t {
      enum AHBprescaler {
         AHBnotdiv	= 0,
         AHBdiv2	    = 0b1000,
         AHBdiv4	    = 0b1001,
         AHBdiv8	    = 0b1010,
         AHBdiv16	= 0b1011,
         AHBdiv64	= 0b1100,
         AHBdiv128	= 0b1101,
         AHBdiv256	= 0b1110,
         AHBdiv512	= 0b1111
      };
      enum  APBprescaler {
         APBnotdiv = 0,
         APBdiv2	  = 0b100,
         APBdiv4	  = 0b101,
         APBdiv8	  = 0b110,
         APBdiv16  = 0b111
      };
      enum  SystemClockSwitch {
         CS_HSI		= 0,
         CS_HSE		= 0b01,
         CS_PLL		= 0b10
      };
      struct Bits {
         // Bits 1:0 SW: System clock switch
         volatile SystemClockSwitch SW		:2;
         // Bits 3:2 SWS: System clock switch status
         volatile SystemClockSwitch SWS	:2;
         // Bits 7:4 HPRE: AHB prescaler
         volatile AHBprescaler HPRE	:4;
         // Bits 9:8 Reserved, must be kept at reset value.
         volatile uint32_t dcb1	:2;
         // Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
         volatile APBprescaler PPRE1	:3;
         // Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
         volatile APBprescaler PPRE2	:3;
         // Bits 20:16 RTCPRE: HSE division factor for RTC clock
         // 2 ≤ PLLM ≤ 31
         volatile uint32_t RTCPRE	:5;
         // Bits 22:21 MCO1: Microcontroller clock output 1
         // 00: HSI clock selected
         // 01: LSE oscillator selected
         // 10: HSE oscillator clock selected
         // 11: PLL clock selected
         volatile uint32_t MCO1   :2;
         // Bit 23 I2SSRC: I2S clock selection
         // 0: PLLI2S clock used as I2S clock source
         // 1: External clock mapped on the I2S_CKIN pin used as I2S clock source
         volatile uint32_t I2SSRC :1;
         // Bits 24:26 MCO1PRE: MCO1 prescaler
         // 0xx: no division
         // 100: division by 2
         // 101: division by 3
         // 110: division by 4
         // 111: division by 5
         volatile uint32_t MCO1PRE    :3;
         // Bits 27:29 MCO2PRE: MCO2 prescaler
         // like MCO1PRE
         volatile uint32_t MCO2PRE	:3;
         // Bits 31:30 MCO2[1:0]: Microcontroller clock output 2
         // 00: System clock (SYSCLK) selected
         // 01: PLLI2S clock selected
         // 10: HSE oscillator clock selected
         // 11: PLL clock selected
         volatile uint32_t MCO2	:2;
      };
      union {
            volatile Bits bits;
            volatile uint32_t reg;
      };
   };

   struct APB1ENR_t {
      enum { Offset = 0x40 };
      struct Bits {
         volatile bool TIM2EN    :1;
         volatile bool TIM3EN    :1;
         volatile bool TIM4EN    :1;
         volatile bool TIM5EN    :1;
         volatile bool TIM6EN    :1;
         volatile bool TIM7EN    :1;
         volatile bool TIM12EN   :1;
         volatile bool TIM13EN   :1;
         volatile bool TIM14EN   :1;
         uint32_t dcb1           :2;
         volatile bool WWDGEN    :1;
         uint32_t dcb2           :2;
         volatile bool SPI2EN    :1;
         volatile bool SPI3EN    :1;
         uint32_t dcb3           :1;
         volatile bool USART2EN  :1;
         volatile bool USART3EN  :1;
         volatile bool UART4EN   :1;
         volatile bool UART5EN   :1;
         volatile bool I2C1EN    :1;
         volatile bool I2C2EN    :1;
         volatile bool I2C3EN    :1;
         uint32_t dcb4           :1;
         volatile bool CAN1EN    :1;
         volatile bool CAN2EN    :1;
         uint32_t dcb5           :1;
         volatile bool PWREN     :1;
         volatile bool DACEN     :1;
         uint32_t dcb6           :2;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
      
   };

   struct AHB1RSTR_t {
      uint32_t reg;
   };

   struct AHB2RSTR_t {
      uint32_t reg;
   };

   struct AHB3RSTR_t {
      uint32_t reg;
   };

   struct RESERVED1_t {
      uint32_t reg;
   };

   struct RESERVED2_t {
      uint32_t reg;
   };

   struct RESERVED3_t {
      uint32_t reg;
   };
   
   struct AHB2ENR_t {
      uint32_t reg;
   };

   struct AHB3ENR_t {
      uint32_t reg;
   };

   struct RESERVED4_t {
      uint32_t reg;
   };

#elif defined(STM32F030x6)
   struct CFGR_t {
      enum PLLdivMCO {
         PLLdiv1 = 0b0,
         PLLdiv2 = 0b1    
      };
      enum PLLmultiplier {
         _2 = 0b0000,
         _3 = 0b0001,
         _4 = 0b0010,
         _5 = 0b0011,
         _6 = 0b0100,
         _7 = 0b0101,
         _8 = 0b0110,
         _9 = 0b0111,
         _10 = 0b1000,
         _11 = 0b1001,
         _12 = 0b1010,
         _13 = 0b1011,
         _14 = 0b1100,
         _15 = 0b1101,
         _16 = 0b1110,
         _16_ = 0b1111,
      };
      enum MCOPRE {
         MCOdiv1 = 0b000,
         MCOdiv2 = 0b001,
         MCOdiv4 = 0b010,
         MCOdiv8 = 0b011,
         MCOdiv16 = 0b100,
         MCOdiv32 = 0b101,
         MCOdiv64 = 0b110,
         MCOdiv128 = 0b111
      };
      enum AHBprescaler {
         AHBnotdiv = 0,
         AHBdiv2   = 0b1000,
         AHBdiv4   = 0b1001,
         AHBdiv8   = 0b1010,
         AHBdiv16  = 0b1011,
         AHBdiv64  = 0b1100,
         AHBdiv128 = 0b1101,
         AHBdiv256 = 0b1110,
         AHBdiv512 = 0b1111
      };
      enum  APBprescaler {
         APBnotdiv = 0,
         APBdiv2   = 0b100,
         APBdiv4   = 0b101,
         APBdiv8   = 0b110,
         APBdiv16  = 0b111
      };
      enum  SystemClockSwitch {
         CS_HSI = 0,
         CS_HSE = 0b01,
         CS_PL = 0b10
      };
      enum PLLsource {
         HSIdiv2 = 0b0,
         HSEdiv  = 0b1
      };
      struct Bits_t {
         // Bits 1:0 SW: System clock switch
         volatile SystemClockSwitch SW		:2;
         // Bits 3:2 SWS: System clock switch status
         volatile SystemClockSwitch SWS	:2;
         // Bits 7:4 HPRE: AHB prescaler
         volatile AHBprescaler HPRE	:4;
         // Bits 10:8 PPRE: PCLK prescaler
         volatile APBprescaler PPRE     :3;
         // Bits 13:11 Reserved, must be kept at reset value
         volatile uint32_t dcb7      :3;
         // Bit 14 ADC prescaler
         volatile bool ADCPRE        :1;
         // Bit 15 Reserved, must be kept at reset value
         volatile uint32_t dcb8      :1;
         // Bit 16 PLL entry clock source
         volatile PLLsource PLLSRC   :1;
         // Bit 17 HSE divider for PLL input clock
         volatile bool PLLXTPRE      :1;
         // Bits 21:18 PLL  multiplication factor
         volatile PLLmultiplier PLLMUL :4;
         // Bits 23:22 Reserved, must be kept at reset value
         volatile uint32_t dcb9      :2;
         // Bits 27:24 MCO Microcontroller clock output
         volatile uint32_t MCO       :4;
         // Bits 30:28 MCOPRE Microcontroller Clock Output Prescaler
         volatile MCOPRE             :3;
         // Bit 31 PLLNODIV PLL clock not divided for MCO
         volatile PLLdivMCO PLLNOdiv  :1;
      };
      union {
            volatile Bits_t bits;
            volatile uint32_t reg;
      };
   };

   struct APB1ENR_t {
      enum { Offset = 0x1C };
      struct Bits {
         volatile bool dcb1      :1;
         volatile bool TIM3EN    :1;
         volatile bool dcb2      :2;
         volatile bool TIM6EN    :1;
         volatile bool TIM7EN    :1;
         volatile bool dcb3      :2;
         volatile bool TIM14EN   :1;
         uint32_t dcb4           :2;
         volatile bool WWDGEN    :1;
         uint32_t dcb5           :2;
         volatile bool SPI2EN    :1;
         uint32_t dcb6           :2;
         volatile bool USART2EN  :1;
         volatile bool USART3EN  :1;
         volatile bool UART4EN   :1;
         volatile bool UART5EN   :1;
         volatile bool I2C1EN    :1;
         volatile bool I2C2EN    :1;
         volatile bool USBEN     :1;
         uint32_t dcb7           :3;
         volatile bool PWREN     :1;
         uint32_t dcb8           :3;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
      
   };
#if defined(STM32F030x6)
   struct AHBENR_t {
      enum { Offset = 0x14 };
      struct Bits {
         // Bit 0 DMAEN: DMA clock enable
         volatile bool DMAEN    :1;
         // Bit 1 Reserved, must be kept at reset value.
         volatile uint32_t res1 :1;
         // Bit 2 SRAMEN: SRAM interface clock enable
         volatile bool SRAMEN   :1;
         // Bit 3 Reserved, must be kept at reset value.
         volatile uint32_t res2 :1;
         // Bit 4 FLITFEN: FLITF clock enable
         volatile bool FLITFEN  :1;
         // Bit 5 Reserved, must be kept at reset value.
         volatile uint32_t res3 :1;
         // Bit 6 CRCEN: CRC clock enable
         volatile bool CRCEN    :1;
         // Bits 16:7 Reserved, must be kept at reset value.
         volatile uint32_t res4 :10;
         // Bit 17 IOPAEN: I/O port A clock enable
         volatile bool IOPAEN   :1;
         // Bit 18 IOPBEN: I/O port B clock enable
         volatile bool IOPBEN   :1;
         // Bit 19 IOPCEN: I/O port C clock enable
         volatile bool IOPCEN   :1;
         // Bit 20 IOPDEN: I/O port D clock enable
         volatile bool IOPDEN   :1;
         // Reserved, must be kept at reset value.
         volatile uint32_t res5 :1;
         // Bit 22 IOPFEN: I/O port F clock enable
         volatile bool IOPFEN   :1;
         // Bits 31:23 Reserved, must be kept at reset value.
         volatile uint32_t res6 :9;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };
#endif

   struct BDCR_t {
      uint32_t reg;
   };

   struct CSR_t {
      uint32_t reg;
   };

   struct AHBRSTR_t {
      uint32_t reg;
   };
   struct CFGR2_t {
      uint32_t reg;
   };
   struct CFGR3_t {
      uint32_t reg;
   };
   struct CR2_t {
      uint32_t reg;
   };
   
#endif

   struct CIR_t {
      uint32_t reg;
   };

   struct APB1RSTR_t {
      uint32_t reg;
   };

   struct APB2RSTR_t {
      uint32_t reg;
   };

   struct AHB1ENR_t {
      union {
         volatile uint32_t reg;
      };    
   };
  
   struct APB2ENR_t {
#if defined(STM32F405xx)
      enum { Offset = 0x44 };
      uint32_t reg;
#elif defined(STM32F030x6)
      enum { Offset = 0x18 };
      struct Bits {
         // Bit 0 SYSCFGEN: SYSCFG clock enable
         volatile bool SYSCFGEN :1;
         // Bits 4:1 Reserved, must be kept at reset value.
         volatile uint32_t res1 :4;
         // Bit 5 USART6EN: USART6 clock enable
         volatile bool USART6EN :1;
         // Bits 8:6 Reserved, must be kept at reset value.
         volatile uint32_t res2 :3;
         // Bit 9 ADCEN: ADC interface clock enable
         volatile bool ADCEN    :1;
         // Bit 10 Reserved, must be kept at reset value.
         volatile uint32_t res3 :1;
         // Bit 11 TIM1EN: TIM1 timer clock enable
         volatile bool TIM1EN   :1;
         // Bit 12 SPI1EN: SPI1 clock enable
         volatile bool SPI1EN   :1;
         // Bit 13 Reserved, must be kept at reset value.
         volatile uint32_t res4 :1;
         // Bit 14 USART1EN: USART1 clock enable
         volatile bool USART1EN :1;
         // Bit 15 Reserved, must be kept at reset value.
         volatile uint32_t res5 :1;
         // Bit 16 TIM15EN: TIM15 timer clock enable
         volatile bool TIM15EN  :1;
         // Bit 17 TIM16EN: TIM16 timer clock enable
         volatile bool TIM16EN  :1;
         // Bit 18 TIM17EN: TIM17 timer clock enable
         volatile bool TIM17EN  :1;
         // Bits 21:19 Reserved, must be kept at reset value.
         volatile uint32_t res6 :3;
         // Bit 22 DBGMCUEN MCU debug module clock enable
         volatile bool DBGMCUEN :1;
         // Bits 31:23 Reserved, must be kept at reset value.
         volatile uint32_t res7 :9;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
#endif
   };
} // namespace RCC_ral
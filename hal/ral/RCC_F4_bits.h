#pragma once

#include "registr.h"


namespace RCC_ral {

struct CRbits {
   __IO bool     HSION     :1; // Bit 0 HSION: Internal high-speed clock enable
   __IO bool     HSIRDY    :1; // Bit 1 HSIRDY: Internal high-speed clock ready flag
   __IO uint32_t res1      :1; // Bit 2 Reserved, must be kept at reset value.
   __IO uint32_t HSITRIM   :5; // Bits 7:3 HSITRIM[4:0]: Internal high-speed clock trimming
   __IO uint32_t HSICAL    :8; // Bits 15:8 HSICAL[7:0]: Internal high-speed clock calibration
   __IO bool     HSEON     :1; // Bit 16 HSEON: HSE clock enable
   __IO bool     HSERDY    :1; // Bit 17 HSERDY: HSE clock ready flag
   __IO bool     HSEBYP    :1; // Bit 18 HSEBYP: HSE clock bypass
   __IO bool     CSSON     :1; // Bit 19 CSSON: Clock security system enable
   __IO uint32_t res2      :4; // Bits 23:20 Reserved, must be kept at reset value.
   __IO bool     PLLON     :1; // Bit 24 PLLON: Main PLL (PLL) enable
   __IO bool     PLLRDY    :1; // Bit 25 PLLRDY: Main PLL (PLL) clock ready flag
   __IO bool     PLLI2SON  :1; // Bit 26 PLLI2SON: PLLI2S enable
   __IO bool     PLLI2SRDY :1; // Bit 27 PLLI2SRDY: PLLI2S clock ready flag
   __IO uint32_t res3      :4; // Bits 31:28 Reserved, must be kept at reset value.
};

struct CRposition {
   enum { HSION = 0, HSIRDY, HSITRIM = 3, HSICAL = 8, HSEON = 16, HSERDY,
      HSEBYP, CSSON, PLLON = 24, PLLRDY, PLLI2SON, PLLI2SRDY
   };
};

enum PLLPdiv { PLLdiv2 = 0b00, PLLdiv4, PLLdiv6,  PLLdiv8 };
enum PLLsource { sHSI = 0b0, sHSE = 0b1 };

struct PLLCFGRbits {
   __IO uint32_t  PLLM   :6; // Bits 5:0 2≤PLLM≤63: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
   __IO uint32_t  PLLN   :9; // Bits 14:6 50≤PLLN≤432: Main PLL (PLL) multiplication factor for VCO
   __IO uint32_t  dcb4   :1; // Bit 15 Reserved, must be kept at reset value.
   __IO PLLPdiv   PLLP   :2; // Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock
   __IO uint32_t  dcb1   :4; // Bits 21:18 Reserved, must be kept at reset value.
   __IO PLLsource PLLSRC :1; // Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
   __IO uint32_t  dcb2   :1; // Bit 23 Reserved, must be kept at reset value.
   __IO uint32_t  PLLQ   :4; // Bits 27:24 2≤PLLQ≤15: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator
   __IO uint32_t  dcb3   :4; // Bits 31:28 Reserved, must be kept at reset value.
};

struct PLLCFGRposition {
   enum { PLLM = 0, PLLN = 6, PLLP = 16, PLLSRC = 22, PLLQ = 24 };
};

enum AHBprescaler { AHBnotdiv = 0, AHBdiv2 = 0b1000, AHBdiv4, AHBdiv8, AHBdiv16, AHBdiv64, AHBdiv128, AHBdiv256, AHBdiv512 };
enum  APBprescaler { APBnotdiv = 0, APBdiv2 = 0b100, APBdiv4, APBdiv8, APBdiv16 };
enum  SystemClockSwitch { CS_HSI = 0, CS_HSE, CS_PLL };

struct CFGRbits {
   __IO SystemClockSwitch SW      :2; // Bits 1:0 SW: System clock switch
   __IO SystemClockSwitch SWS     :2; // Bits 3:2 SWS: System clock switch status
   __IO AHBprescaler      HPRE    :4; // Bits 7:4 HPRE: AHB prescaler
   __IO uint32_t          dcb1    :2; // Bits 9:8 Reserved, must be kept at reset value.
   __IO APBprescaler      PPRE1   :3; // Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
   __IO APBprescaler      PPRE2   :3; // Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
   __IO uint32_t          RTCPRE  :5; // Bits 20:16 2≤RTCPRE≤31: HSE division factor for RTC clock
   __IO uint32_t          MCO1    :2; // Bits 22:21 MCO1: Microcontroller clock output 1
   __IO uint32_t          I2SSRC  :1; // Bit 23 I2SSRC: I2S clock selection
   __IO uint32_t          MCO1PRE :3; // Bits 24:26 MCO1PRE: MCO1 prescaler
   __IO uint32_t          MCO2PRE :3; // Bits 27:29 MCO2PRE: MCO2 prescaler
   __IO uint32_t          MCO2    :2; // Bits 31:30 MCO2[1:0]: Microcontroller clock output 2
};

struct CFGRposition {
   enum { SW = 0, SWS = 2, HPRE = 4, PPRE1 = 10, PPRE2 = 13, RTCPRE = 16, I2SSRC = 23, MCO1PRE, MCO2PRE = 27, MCO2 = 30 };
};

struct APB1ENRbits {
   __IO bool     TIM2EN   :1;
   __IO bool     TIM3EN   :1;
   __IO bool     TIM4EN   :1;
   __IO bool     TIM5EN   :1;
   __IO bool     TIM6EN   :1;
   __IO bool     TIM7EN   :1;
   __IO bool     TIM12EN  :1;
   __IO bool     TIM13EN  :1;
   __IO bool     TIM14EN  :1;
   __IO uint32_t res1     :2;
   __IO bool     WWDGEN   :1;
   __IO uint32_t res2     :2;
   __IO bool     SPI2EN   :1;
   __IO bool     SPI3EN   :1;
   __IO uint32_t res3     :1;
   __IO bool     USART2EN :1;
   __IO bool     USART3EN :1;
   __IO bool     UART4EN  :1;
   __IO bool     UART5EN  :1;
   __IO bool     I2C1EN   :1;
   __IO bool     I2C2EN   :1;
   __IO bool     I2C3EN   :1;
   __IO uint32_t res4     :1;
   __IO bool     CAN1EN   :1;
   __IO bool     CAN2EN   :1;
   __IO uint32_t res5     :1;
   __IO bool     PWREN    :1;
   __IO bool     DACEN    :1;
   __IO uint32_t res6     :2;
};


struct CR_t         : BitsRegistr<CRbits>     , Offset_t<0x00>, CRposition      {};
struct PLLCFGR_t    : BitsRegistr<PLLCFGRbits>, Offset_t<0x04>, PLLCFGRposition {};
struct CFGR_t       : BitsRegistr<CFGRbits>   , Offset_t<0x08>, CFGRposition    {};
struct CIR_t        : DataRegistr             , Offset_t<0x0C> {};
struct AHB1RSTR_t   : DataRegistr             , Offset_t<0x10> {};
struct AHB2RSTR_t   : DataRegistr             , Offset_t<0x14> {};
struct AHB3RSTR_t   : DataRegistr             , Offset_t<0x18> {};
struct APB1RSTR_t   : DataRegistr             , Offset_t<0x20> {};
struct APB2RSTR_t   : DataRegistr             , Offset_t<0x24> {};
struct AHB1ENR_t    : DataRegistr             , Offset_t<0x30> {};
struct AHB2ENR_t    : DataRegistr             , Offset_t<0x34> {};
struct AHB3ENR_t    : DataRegistr             , Offset_t<0x38> {};
struct APB1ENR_t    : BitsRegistr<APB1ENRbits>, Offset_t<0x40> {};
struct APB2ENR_t    : DataRegistr             , Offset_t<0x44> {};
struct AHB1LPENR_t  : DataRegistr             , Offset_t<0x50> {};
struct AHB2LPENR_t  : DataRegistr             , Offset_t<0x54> {};
struct AHB3LPENR_t  : DataRegistr             , Offset_t<0x58> {};
struct APB1LPENR_t  : DataRegistr             , Offset_t<0x60> {};
struct APB2LPENR_t  : DataRegistr             , Offset_t<0x64> {};
struct BDCR_t       : DataRegistr             , Offset_t<0x70> {};
struct CSR_t        : DataRegistr             , Offset_t<0x74> {};
struct SSCGR_t      : DataRegistr             , Offset_t<0x80> {};
struct PLLI2SCFGR_t : DataRegistr             , Offset_t<0x84> {};



} // namespace RCC_ral
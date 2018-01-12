/**
 * RAL над регистрами системы тактирования
 * class RCC_t можно использовать для управления 
 * тактированием с помощью статических функций
 * этого класса
 */

#pragma once

#include <stdint.h>
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
        struct Bits_t {
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
                volatile Bits_t bits;
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
        enum PLLNOdiv {
            PLLdiv1 = 0b0,
            PLLdiv2 = 0b1    
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
                    
        struct Bits_t {
            // Bits 1:0 SW: System clock switch
            volatile SystemClockSwitch SW		:2;
            // Bits 3:2 SWS: System clock switch status
            volatile SystemClockSwitch SWS	:2;
            // Bits 7:4 HPRE: AHB prescaler
            volatile AHBprescaler HPRE	:4;
            // Bits 10:8 PPRE: PCLK prescaler
            volatile uint_32_t PPRE     :2;
            // Bits 13:11 Reserved, must be kept at reset value
            volatile uint32_t dcb7      :3;
            // Bit 14 ADC prescaler
            volatile bool ADCPRE        :1;
            // Bit 15 Reserved, must be kept at reset value
            volatile bool dcb8:         :1;
            // Bit 16 PLL entry clock source
            volatile bool PLLSRC        :1;
            // Bit 17 HSE divider for PLL input clock
            volatile bool PLLXTPRE      :1;
            // Bits 21:18 PLL  multiplication factor
            volatile uint32_t PLLMUL    :4;
            // Bits 23:22 Reserved, must be kept at reset value
            volatile uint32_t dcb9      :2;
            // Bits 27:24 MCO Microcontroller clock output
            volatile uint32_t MCO       :3;
            // Bits 30:28 MCOPRE Microcontroller Clock Output Prescaler
            volatile MCOPRE             :2;
            // Bit 31 PLLNODIV PLL clock not divided for MCO
            volatile PLLNOdiv           :1;
        }
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
            uint32_t dcb7           :1;
            volatile bool USBEN     :1;
            uint32_t dcb8           :2;
            volatile bool PWREN     :1;
            uint32_t dcb9           :3;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
        
    };

    struct AHBENR_t {
    uint32_t reg;
    };

    struct BDCR_t {
        uint32_t reg;
    };

    struct CSR_t {
        uint32_t reg;
    };

    struct AHBRSTR_t {
        uint32_t reg;
    };
    struct CFGR2 {
        uint32_t reg;
    };
    struct CFGR3 {
        uint32_t reg;
    };
    struct CR2 {
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
#elif defined(STM32F030x6)
        enum { Offset = 0x18 };
#endif
        uint32_t reg;
    };
}

/*
typedef struct
{
  __IO uint32_t CR;            // RCC clock control register,                                  Address offset: 0x00
  __IO uint32_t PLLCFGR;       // RCC PLL configuration register,                              Address offset: 0x04
  __IO uint32_t CFGR;          // RCC clock configuration register,                            Address offset: 0x08
  __IO uint32_t CIR;           // RCC clock interrupt register,                                Address offset: 0x0C
  __IO uint32_t AHB1RSTR;      // RCC AHB1 peripheral reset register,                          Address offset: 0x10
  __IO uint32_t AHB2RSTR;      // RCC AHB2 peripheral reset register,                          Address offset: 0x14
  __IO uint32_t AHB3RSTR;      // RCC AHB3 peripheral reset register,                          Address offset: 0x18
  uint32_t      RESERVED0;     // Reserved, 0x1C                                                                    
  __IO uint32_t APB1RSTR;      // RCC APB1 peripheral reset register,                          Address offset: 0x20
  __IO uint32_t APB2RSTR;      // RCC APB2 peripheral reset register,                          Address offset: 0x24
  uint32_t      RESERVED1[2];  // Reserved, 0x28-0x2C                                                              
  __IO uint32_t AHB1ENR;       // RCC AHB1 peripheral clock register,                          Address offset: 0x30
  __IO uint32_t AHB2ENR;       // RCC AHB2 peripheral clock register,                          Address offset: 0x34
  __IO uint32_t AHB3ENR;       // RCC AHB3 peripheral clock register,                          Address offset: 0x38
  uint32_t      RESERVED2;     // Reserved, 0x3C                                                                   
  __IO uint32_t APB1ENR;       // RCC APB1 peripheral clock enable register,                   Address offset: 0x40
  __IO uint32_t APB2ENR;       // RCC APB2 peripheral clock enable register,                   Address offset: 0x44
  uint32_t      RESERVED3[2];  // Reserved, 0x48-0x4C                                                              
  __IO uint32_t AHB1LPENR;     // RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
  __IO uint32_t AHB2LPENR;     // RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
  __IO uint32_t AHB3LPENR;     // RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
  uint32_t      RESERVED4;     // Reserved, 0x5C                                                                   
  __IO uint32_t APB1LPENR;     // RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
  __IO uint32_t APB2LPENR;     // RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
  uint32_t      RESERVED5[2];  // Reserved, 0x68-0x6C                                                              
  __IO uint32_t BDCR;          // RCC Backup domain control register,                          Address offset: 0x70
  __IO uint32_t CSR;           // RCC clock control & status register,                         Address offset: 0x74
  uint32_t      RESERVED6[2];  // Reserved, 0x78-0x7C                                                              
  __IO uint32_t SSCGR;         // RCC spread spectrum clock generation register,               Address offset: 0x80
  __IO uint32_t PLLI2SCFGR;    // RCC PLLI2S configuration register,                           Address offset: 0x84
} RCC_TypeDef;
*/

extern const uint32_t fCPU;

using namespace RCC_ral;

class RCC_t : public RCC_ral::CR_t,
              public PLLCFGR_t,
              public CFGR_t,
              public CIR_t,
              public AHB1RSTR_t,
              public AHB2RSTR_t,
              public AHB3RSTR_t,
              public RESERVED1_t,
              public APB1RSTR_t,
              public APB2RSTR_t,
              public RESERVED2_t,
              public RESERVED3_t,
              public AHB1ENR_t,
              public AHB2ENR_t,
              public AHB3ENR_t,
              public RESERVED4_t,
              public APB1ENR_t,
              public APB2ENR_t
{
public:	
    enum Bus {
        APB1,
        APB2
    };

    static void HSEon()        { clockContr().bits.HSEON = 1; }
    static void waitHSEready() { while (!clockContr().bits.HSERDY) { } }
    static void PLLon()        { clockContr().bits.PLLON = 1; }
    static void waitPLLready() { while (!clockContr().bits.PLLRDY) { } }
    static void setPLLP (PLLPdiv val)  { pllConf().bits.PLLP = val; }

    template <uint8_t val> static void setPLLM()  
    {
        static_assert (
            val >= 2 && val <= 63,
            "значение множителя должно быть в диапазоне 2-63"
        );
        pllConf().bits.PLLM = val; 
    }

    static void setPLLM (uint16_t val) 
    {
        if (val >= 2 && val <= 63)
            pllConf().bits.PLLM = val;
    }

    template <uint16_t val> static void setPLLN()  
    {
        static_assert (
            val >= 50 && val <= 432,
            "значение множителя должно быть в диапазоне 50-432"
        );
        pllConf().bits.PLLN = val; 
    }

    static void setPLLN (uint16_t val) 
    {
        if (val >= 50 && val <= 432)
            pllConf().bits.PLLN = val; 
    }

    template <uint8_t val> static void setPLLQ()  
    {
        static_assert (
            val >= 2 && val <= 15,
            "значение множителя должно быть в диапазоне 2-15"
        );
        pllConf().bits.PLLQ = val; 
    }

    static void setPLLQ (uint8_t val)
    {
        if (val >= 2 && val <= 15)
            pllConf().bits.PLLQ = val;
    }

    static void setPLLsource (PLLsource val) { pllConf().bits.PLLSRC = val; }
    static void setAHBprescaler (AHBprescaler val) { conf().bits.HPRE = val; }
    static void setAPB1prescaler (APBprescaler val) { conf().bits.PPRE1 = val; }
    static void setAPB2prescaler (APBprescaler val) { conf().bits.PPRE2 = val; }
    static void systemClockSwitch (SystemClockSwitch val) { conf().bits.SW = val; }
    static uint32_t getAPB1clock() { return getAPBclock (conf().bits.PPRE1); }
    static uint32_t getAPB2clock() { return getAPBclock (conf().bits.PPRE2); }

protected:
    static volatile RCC_ral::CR_t      &clockContr() { return (RCC_ral::CR_t &)      RCC->CR;      }
    static volatile RCC_ral::PLLCFGR_t &pllConf()    { return (RCC_ral::PLLCFGR_t &) RCC->PLLCFGR; }
    static volatile RCC_ral::CFGR_t    &conf()       { return (RCC_ral::CFGR_t &)    RCC->CFGR;    }

private:
    static inline uint32_t getAPBclock(APBprescaler val)
    {
        return val == APBprescaler::APBnotdiv ? fCPU     :
               val == APBprescaler::APBdiv2   ? fCPU / 2 :
               val == APBprescaler::APBdiv4   ? fCPU / 4 :
               val == APBprescaler::APBdiv8   ? fCPU / 8 :
                                                fCPU / 16;
    } 
};
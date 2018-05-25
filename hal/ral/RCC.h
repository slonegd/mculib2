
/**
 * RAL над регистрами системы тактирования
 * class RCC_t можно использовать для управления 
 * тактированием с помощью статических функций
 * этого класса
 */

#pragma once

#include "RCC_bits.h"


/* STM32F4
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
/* STM32F0
typedef struct
{
  __IO uint32_t CR;       //RCC clock control register,                offset: 0x00
  __IO uint32_t CFGR;     //RCC clock configuration register,          offset: 0x04
  __IO uint32_t CIR;      //RCC clock interrupt register,              offset: 0x08
  __IO uint32_t APB2RSTR; //RCC APB2 peripheral reset register,        offset: 0x0C
  __IO uint32_t APB1RSTR; //RCC APB1 peripheral reset register,        offset: 0x10
  __IO uint32_t AHBENR;   //RCC AHB peripheral clock register,         offset: 0x14
  __IO uint32_t APB2ENR;  //RCC APB2 peripheral clock enable register, offset: 0x18
  __IO uint32_t APB1ENR;  //RCC APB1 peripheral clock enable register, offset: 0x1C
  __IO uint32_t BDCR;     //RCC Backup domain control register,        offset: 0x20
  __IO uint32_t CSR;      //RCC clock control & status register,       offset: 0x24
  __IO uint32_t AHBRSTR;  //RCC AHB peripheral reset register,         offset: 0x28
  __IO uint32_t CFGR2;    //RCC clock configuration register 2,        offset: 0x2C
  __IO uint32_t CFGR3;    //RCC clock configuration register 3,        offset: 0x30
  __IO uint32_t CR2;      //RCC clock control register 2,              offset: 0x34
} RCC_TypeDef;
*/
extern const uint32_t fCPU;

using namespace RCC_ral;

class RCC_t : public RCC_ral::CR_t,
#if defined (STM32F405xx)
              public RCC_ral::PLLCFGR_t,
              public RCC_ral::CFGR_t,
              public RCC_ral::CIR_t,
              public RCC_ral::AHB1RSTR_t,
              public RCC_ral::AHB2RSTR_t,
              public RCC_ral::AHB3RSTR_t,
              public RCC_ral::RESERVED1_t,
              public RCC_ral::APB1RSTR_t,
              public RCC_ral::APB2RSTR_t,
              public RCC_ral::RESERVED2_t,
              public RCC_ral::AHB1ENR_t,
              public RCC_ral::AHB2ENR_t,
              public RCC_ral::AHB3ENR_t,
              public RCC_ral::RESERVED3_t,
              public RCC_ral::APB1ENR_t,
              public RCC_ral::APB2ENR_t,
              public RCC_ral::RESERVED4_t
#elif defined (STM32F030x6)
           public RCC_ral::CFGR_t,
           public RCC_ral::CIR_t,
           public RCC_ral::APB2RSTR_t,
           public RCC_ral::APB1RSTR_t,
           public RCC_ral::AHBENR_t,
           public RCC_ral::APB2ENR_t,
           public RCC_ral::APB1ENR_t,
           public RCC_ral::BDCR_t,
           public RCC_ral::CSR_t,
           public RCC_ral::AHBRSTR_t,
           public RCC_ral::CFGR2_t,
           public RCC_ral::CFGR3_t,
           public RCC_ral::CR2_t
#endif
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

#if defined(STM32F405xx)
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
#endif

   
   static void setAHBprescaler (AHBprescaler val) { conf().bits.HPRE = val; }
#if defined (STM32F405xx)
   static void setPLLsource (PLLsource val) { pllConf().bits.PLLSRC = val; }
   static void setAPB1prescaler (APBprescaler val) { conf().bits.PPRE1 = val; }
   static void setAPB2prescaler (APBprescaler val) { conf().bits.PPRE2 = val; }
   static uint32_t getAPB1clock() { return getAPBclock (conf().bits.PPRE1); }
   static uint32_t getAPB2clock() { return getAPBclock (conf().bits.PPRE2); }
#elif defined (STM32F030x6)
   static void setPLLsource (PLLsource val) { conf().bits.PLLSRC = val; }
   static void setAPBprecsaler (APBprescaler val) { conf().bits.PPRE = val; }
   static void setPLLmultiplier (PLLmultiplier val) { conf().bits.PLLMUL = val; }
   static uint32_t getAPB2clock() { return getAPBclock (conf().bits.PPRE); }
#endif
   static void systemClockSwitch (SystemClockSwitch val) { conf().bits.SW = val; }
   
protected:
   static volatile RCC_ral::CR_t      &clockContr() { return (RCC_ral::CR_t &)      RCC->CR;      }
   static volatile RCC_ral::CFGR_t    &conf()       { return (RCC_ral::CFGR_t &)    RCC->CFGR;    }
#if defined (STM32F405xx)
   static volatile RCC_ral::PLLCFGR_t &pllConf()    { return (RCC_ral::PLLCFGR_t &) RCC->PLLCFGR; }
#endif
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
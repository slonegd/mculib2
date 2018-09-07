#pragma once

#include "registr.h"
#if defined(STM32F0)
#include "ADC_F0_bits.h"
#elif defined(STM32F4)
#include "ADC_F4_bits.h"
#endif
#include "ADC_common.h"
#include "DMA.h"

namespace ADC_detail {
   template<class T> struct DefaultStream_impl { using type = void; };
   template<class T>
   using DefaultStream_t = typename DefaultStream_impl<T>::type;
}


#if defined(STM32F0)
template<uint32_t adr>
struct ADC_t {
  __IO ADC_detail::SR_bits     ISR;     // interrupt and status register,        offset: 0x00
  __IO ADC_detail::IER_bits    IER;     // interrupt enable register,            offset: 0x04
  __IO ADC_detail::CR_bits     CR;      // control register,                     offset: 0x08
  __IO ADC_detail::CFGR1_bits  CFGR1;   // configuration register 1,             offset: 0x0C
  __IO ADC_detail::CFGR2_bits  CFGR2;   // configuration register 2,             offset: 0x10
  __IO ADC_detail::SMPR_bits   SMPR;    // sampling time register,               offset: 0x14
       uint32_t                RES1[2]; // Reserved,                                     0x18
  __IO ADC_detail::TR_bits     TR;      // analog watchdog 1 threshold register, offset: 0x20
       uint32_t                RES2;    // Reserved,                                     0x24
  __IO ADC_detail::CHSELR_bits CHSELR;  // group regular sequencer register,     offset: 0x28
       uint32_t                RES[5];  // Reserved,                                     0x2C
  __IO uint32_t                DR;      // group regular data register,          offset: 0x40
   ADC_t() = delete; 
   static constexpr uint32_t Base = adr; 
};

#elif defined(STM32F4)
template<uint32_t adr>
struct ADC_t {
  __IO ADC_detail::SR_bits   SR;    // status register,                         offset: 0x00
  __IO ADC_detail::CR1_bits  CR1;   // control register 1,                      offset: 0x04
  __IO ADC_detail::CR2_bits  CR2;   // control register 2,                      offset: 0x08
  __IO ADC_detail::SMPR_bits SMPR;  // sample time register 1, 2                offset: 0x0C
  __IO uint32_t              JOFR1; // injected channel data offset register 1, offset: 0x14
  __IO uint32_t              JOFR2; // injected channel data offset register 2, offset: 0x18
  __IO uint32_t              JOFR3; // injected channel data offset register 3, offset: 0x1C
  __IO uint32_t              JOFR4; // injected channel data offset register 4, offset: 0x20
  __IO uint32_t              HTR;   // watchdog higher threshold register,      offset: 0x24
  __IO uint32_t              LTR;   // watchdog lower threshold register,       offset: 0x28
  __IO ADC_detail::SQR_bits  SQR;   // regular sequence register 1, 2, 3        offset: 0x2C
  __IO uint32_t              JSQR;  // injected sequence register,              offset: 0x38
  __IO uint32_t              JDR1;  // injected data register 1,                offset: 0x3C
  __IO uint32_t              JDR2;  // injected data register 2,                offset: 0x40
  __IO uint32_t              JDR3;  // injected data register 3,                offset: 0x44
  __IO uint32_t              JDR4;  // injected data register 4,                offset: 0x48
  __IO uint32_t              DR;    // regular data register,                   offset: 0x4C
   ADC_t() = delete; 
   static constexpr uint32_t Base = adr; 
};
#endif



template <uint32_t adr, class Pointer = Pointer<ADC_t<adr>>>
class template_ADC
{
public:
#if defined(STM32F0) or defined(STM32F4)
   using Channels   = DMA_ral::Channels;
   using SampleTime = ADC_detail::SMPR_bits::SampleTime;
   using Type       = template_ADC<adr,Pointer>;
#endif
#if defined(STM32F0)
   using Clock      = ADC_detail::CFGR2_bits::Clock;
   using Resolution = ADC_detail::CFGR1_bits::Resolution;
#elif defined(STM32F4)
   using Clock      = ADC_ral::Clock;
   using Resolution = ADC_detail::CR1_bits::Resolution;
#endif


#if defined(STM32F0) or defined(STM32F4)
   static void clockEnable() { RCC::template clockEnable<template_ADC>(); }
   static void enable();
   static void disable();
   static bool is_disable();
   static void start();
   static void DMAenable();
   static void setCircularDMA();
   static void setContinuousMode();
   static void setClock (Clock val);
   static void setResolution (Resolution val);
   static size_t getDataAdr();

   using DefaultStream = typename ADC_detail::DefaultStream_t<template_ADC>;
   template <class PIN> static constexpr uint8_t ADCchannel();
   template <class DMA> static constexpr bool DMAenabled();
   template <class PIN> static constexpr bool PINenabled();
#endif

#if defined(STM32F0)
   static bool isReady();
   static void setBusy();
   static void stop();
   static bool isStoping();
   static void setSampleTime (SampleTime val);
   static void setChannel (uint8_t val);

#elif defined(STM32F4)
   template <uint8_t channel>
   static void setSampleTime (SampleTime);
   template <size_t n, uint8_t channel> // n - номер по порядку (1 - 16)
   static void setRegularSequenceOrder();
   template <size_t>
   static void setRegularSequenceLength();
   static void setScanMode();
   static constexpr Channels DMAchannel();
#endif
};

#if defined(STM32F0) or defined(STM32F4)
#define CMSIS_ADC1 ADC1
#undef ADC1
using ADC1 = template_ADC<ADC1_BASE>;
#endif

#if defined(STM32F405xx)
   #define CMSIS_ADC2 ADC2
   #undef ADC2
   using ADC2 = template_ADC<ADC2_BASE>;
   #define CMSIS_ADC3 ADC3
   #undef ADC3
   using ADC3 = template_ADC<ADC3_BASE>;
#endif

#include "ADC_src.h"








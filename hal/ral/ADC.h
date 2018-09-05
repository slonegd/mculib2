#pragma once

#if defined(STM32F030x6)
#include "ADC_F0_bits.h"
#elif defined(STM32F405xx)
#include "ADC_F4_bits.h"
#endif
#include "ADC_common.h"



template <uint32_t adr>
class ADCx
{
public:
   using Channels   = DMA_ral::Channels;
   using Clock      = ADC_ral::Clock;
   using Resolution = ADC_ral::Resolution;
   using SampleTime = ADC_ral::SampleTime;
   using Type       = ADCx<adr>;

   static const uint32_t Base = adr;

   ADCx() = delete;
   void doSome() { status().bits.res1 = 0; }

   static void clockEnable();
   static void enable();
   static void disable();
   static bool isDisable();
   static void start();
   static void DMAenable();
   static void setCircularDMA();
   static void setContinuousMode();
   static void setClock (Clock val);
   static void setResolution (Resolution val);
   static uint32_t getDataAdr();

#if defined(STM32F030x6)
   static bool isReady();
   static void setBusy();
   static void stop();
   static bool isStoping();
   static void setSampleTime (SampleTime val);
   static void setChannel (uint8_t val);
#elif defined(STM32F405xx)
   template <uint8_t channel>
   static void setSampleTime (SampleTime val);
   template <size_t n, uint8_t channel> // n - номер по порядку (1 - 16)
   static void setRegularSequenceOrder();
   template <size_t>
   static void setRegularSequenceLength();
   static void setScanMode();
   static constexpr Channels DMAchannel();

#endif



protected:
#define MakeRef(Reg,Ref) ADC_ral::Reg& Ref() { return (ADC_ral::Reg&) *(uint32_t*)(Base + ADC_ral::Reg::Offset); }
   static __IO MakeRef(SR_t,    status    );
   static __IO MakeRef(DR_t,    data      );
   static __IO MakeRef(CR_t,    control   );
   static __IO MakeRef(SMPR_t,  sampleTime);
   static __IO MakeRef(SQR_t,   sqr       );
#if defined(STM32F030x6)
   static __IO MakeRef(CFGR1_t, conf1     );
   static __IO MakeRef(CFGR2_t, conf2     );
   static __IO MakeRef(CHSELR_t,channelSelect);
#elif defined(STM32F405xx)
   static __IO MakeRef(CR2_t,   control2  );
#endif
#undef MakeRef


private:
   ADC_ral::SR_t SR; // ADC status register (F0 - ISR ADC interrupt and status register )
#if defined(STM32F405xx)
   ADC_ral::CR_t     CR;     // ADC control register 1
   ADC_ral::CR2_t    CR2;    // ADC control register 2
   ADC_ral::SMPR_t   SMPR;   // ADC sample time register
   ADC_ral::JOFR1_t  JOFR1;  // ADC injected channel data offset register 1
   ADC_ral::JOFR2_t  JOFR2;  // ADC injected channel data offset register 2
   ADC_ral::JOFR3_t  JOFR3;  // ADC injected channel data offset register 3
   ADC_ral::JOFR4_t  JOFR4;  // ADC injected channel data offset register 4
   ADC_ral::HTR_t    HTR;    // ADC watchdog higher threshold register
   ADC_ral::LTR_t    LTR;    // ADC watchdog lower threshold register
   ADC_ral::SQR_t    SQR;   // ADC regular sequence register 1 2 3
   ADC_ral::JSQR_t   JQR;    // ADC injected sequence register
   ADC_ral::JDR1_t   JDR1;   // ADC injected data register 1
   ADC_ral::JDR2_t   JDR2;   // ADC injected data register 2
   ADC_ral::JDR3_t   JDR3;   // ADC injected data register 3
   ADC_ral::JDR4_t   JDR4;   // ADC injected data register 4
#elif defined(STM32F030x6)
   ADC_ral::IER_t    IER;    // ADC interrupt enable register
   ADC_ral::CR_t     CR;     // ADC control register
   ADC_ral::CFGR1_t  CFGR1;  // ADC configuration register 1
   ADC_ral::CFGR2_t  CFGR2;  // ADC configuration register 2
   ADC_ral::SMPR_t   SMPR2;  // ADC sampling time register
   Reserve_t<2>      reserve1;
   ADC_ral::TR_t     TR;     // ADC analog watchdog 1 threshold register
   Reserve_t<1>      reserve2;
   ADC_ral::CHSELR_t CHSELR; // ADC group regular sequencer register
   Reserve_t<5>      reserve3;
#endif
   ADC_ral::DR_t     DR;     // ADC group regular data register

};


#undef ADC1
using ADC1 = ADCx<ADC1_BASE>;

#if defined(STM32F405xx)
   #undef ADC2
   using ADC2 = ADCx<ADC2_BASE>;
   #undef ADC3
   using ADC3 = ADCx<ADC3_BASE>;
#endif





#include "ADC_impl.h"
#include "ADC_src.h"








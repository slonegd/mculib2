/**
 *    Пока тут написано только для F0 серии
 */
#pragma once

#if defined(STM32F030x6)
#include "ADC_F0_bits.h"
#elif defined(STM32F405xx)
#include "ADC_F4_bits.h"
#include "bitbanding.h"
#endif



template <uint32_t ADCadr>
class ADCx
{
public:
   static const uint32_t Base = ADCadr;

   using Channels   = DMA_ral::Channels;
   using Clock      = ADC_ral::Clock;
   using Resolution = ADC_ral::Resolution;
   using SampleTime = ADC_ral::SampleTime;

   void makeDebugVar() { status().bits.res1 = 0; }

   static void ClockEnable();
   static void Enable()    { control().reg |= ADC_CR_ADEN_Msk; }
   static void Disable()   { control().reg |= ADC_CR_ADDIS_Msk; }
   static bool IsDisable() { return (control().reg & ADC_CR_ADEN_Msk) == 0; }
   static bool IsReady()   { return (status().reg & ADC_ISR_ADRDY_Msk) != 0; }
   static void SetBusy()   { status().reg |= ADC_ISR_ADRDY_Msk; }
   static void Stop()      { control().reg |= ADC_CR_ADSTP_Msk; }
   static void Start()     { control().reg |= ADC_CR_ADSTART_Msk; }
   static bool IsStoping() { return (control().reg & ADC_CR_ADSTP_Msk) != 0; }
   static void SetClock ( Clock val );
   static void DMAenable() { conf1().reg |= ADC_CFGR1_DMAEN_Msk; }
   static void SetCircularDMA() { conf1().reg |= ADC_CFGR1_DMACFG_Msk; }
   static void SetResolution (Resolution val);
   static void SetContinuousMode() { conf1().reg |= ADC_CFGR1_CONT_Msk; }
   static void SetSampleTime (SampleTime val);
   static void SetChannel (uint8_t val) { channelSelect().reg |= (1u << val); }



protected:
   #define MakeRef(Reg,Ref) ADC_ral::Reg& Ref() { return (ADC_ral::Reg&) *(uint32_t*)(Base + ADC_ral::Reg::Offset); }
   static volatile MakeRef(SR_t,    status);
   static volatile MakeRef(DR_t,    data);
   static volatile MakeRef(CR_t,    control);
   static volatile MakeRef(CFGR1_t, conf1);
   static volatile MakeRef(CFGR2_t, conf2);
   static volatile MakeRef(SMPR_t,  sampleTime);
   static volatile MakeRef(CHSELR_t, channelSelect);
   #undef MakeRef


private:
#if defined(STM32F405xx)
   static constexpr uint32_t ClkEnMask =
      Base == ADC1_BASE ? RCC_APB2ENR_ADC1EN_Msk :
      Base == ADC2_BASE ? RCC_APB2ENR_ADC2EN_Msk :
      Base == ADC3_BASE ? RCC_APB2ENR_ADC3EN_Msk : 0;
#elif defined(STM32F030x6)
   static constexpr uint32_t ClkEnMask = RCC_APB2ENR_ADCEN_Msk;
#endif

   ADC_ral::SR_t SR; // ADC status register (F0 - ISR ADC interrupt and status register )
#if defined(STM32F405xx)
   ADC_ral::CR_t     CR;     // ADC control register 1
   ADC_ral::CR2_t    CR2;    // ADC control register 2
   ADC_ral::SMPR1_t  SMPR1;  // ADC sample time register 1
   ADC_ral::SMPR2_t  SMPR2;  // ADC sample time register 2
   ADC_ral::JOFR1_t  JOFR1;  // ADC injected channel data offset register 1
   ADC_ral::JOFR2_t  JOFR2;  // ADC injected channel data offset register 2
   ADC_ral::JOFR3_t  JOFR3;  // ADC injected channel data offset register 3
   ADC_ral::JOFR4_t  JOFR4;  // ADC injected channel data offset register 4
   ADC_ral::HTR_t    HTR;    // ADC watchdog higher threshold register
   ADC_ral::LTR_t    LTR;    // ADC watchdog lower threshold register
   ADC_ral::SQR1_t   SQR1;   // ADC regular sequence register 1
   ADC_ral::SQR2_t   SQR2;   // ADC regular sequence register 2
   ADC_ral::SQR3_t   SQR3;   // ADC regular sequence register 3
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








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
class ADCx : private ADC_ral::SR_t,
#if defined(STM32F405xx)
             private ADC_ral::CR_t,
             private ADC_ral::CR2_t,
             private ADC_ral::SMPR1_t,
             private ADC_ral::SMPR2_t,
             private ADC_ral::JOFR1_t,
             private ADC_ral::JOFR2_t,
             private ADC_ral::JOFR3_t,
             private ADC_ral::JOFR4_t,
             private ADC_ral::HTR_t,
             private ADC_ral::LTR_t,
             private ADC_ral::SQR1_t,
             private ADC_ral::SQR2_t,
             private ADC_ral::SQR3_t,
             private ADC_ral::JSQR_t,
             private ADC_ral::JDR1_t,
             private ADC_ral::JDR2_t,
             private ADC_ral::JDR3_t,
             private ADC_ral::JDR4_t,
#elif defined(STM32F030x6)
             private ADC_ral::IER_t,
             private ADC_ral::CR_t,
             private ADC_ral::CFGR1_t,
             private ADC_ral::CFGR2_t,
             private ADC_ral::SMPR_t,
             private ADC_ral::Reserved<2>,
             private ADC_ral::TR_t,
             private ADC_ral::Reserved<1>,
             private ADC_ral::CHSELR_t,
             private ADC_ral::Reserved<5>,
#endif
             private ADC_ral::DR_t
{
public:
   static const uint32_t Base = ADCadr;

   using Channels   = DMA_ral::CR_t::Channels;
   using Clock      = ADC_ral::CFGR2_t::Clock;
   using Resolution = ADC_ral::CFGR1_t::Resolution;
   using SampleTime = ADC_ral::SMPR_t::SampleTime;

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







template <uint32_t ADCadr>
void ADCx<ADCadr>::ClockEnable()
{
   RCC->APB2ENR |= ClkEnMask;
   while ( (RCC->APB2ENR & ClkEnMask) == 0 ) { }
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetClock ( Clock val )
{
   conf2().reg &= ~ADC_CFGR2_CKMODE_Msk;
   conf2().reg |= (uint32_t)val << ADC_CFGR2_CKMODE_Pos;
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetResolution ( Resolution val )
{
   conf1().reg &= ~ADC_CFGR1_RES_Msk;
   conf1().reg |= (uint32_t)val << ADC_CFGR1_RES_Pos;
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetSampleTime ( SampleTime val )
{
   sampleTime().reg &= ~ADC_SMPR_SMP_Msk;
   sampleTime().reg |= (uint32_t)val << ADC_SMPR_SMP_Pos;
}
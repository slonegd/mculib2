#pragma once

#include "ADC.h"

#if defined(STM32F405xx) or defined(STM32F030x6)



#endif


#if defined(STM32F405xx)

template <uint32_t adr>
void ADCx<adr>::ClockEnable()
{
   constexpr uint32_t ClkEnMask =
      Base == ADC1_BASE ? RCC_APB2ENR_ADC1EN_Msk :
      Base == ADC2_BASE ? RCC_APB2ENR_ADC2EN_Msk :
      Base == ADC3_BASE ? RCC_APB2ENR_ADC3EN_Msk : 0;
   RCC->APB2ENR |= ClkEnMask;
   while ( (RCC->APB2ENR & ClkEnMask) == 0 ) { }
}


template <uint32_t adr>
void ADCx<adr>::Enable()
{
   Bit_BAND(control(), ADEN) = true;
}


template <uint32_t adr>
void ADCx<adr>::Disable()
{
   Bit_BAND(control(), ADDIS) = true;
}


#elif defined(STM32F030x6)

template <uint32_t adr>
void ADCx<adr>::ClockEnable()
{
   static constexpr uint32_t ClkEnMask = RCC_APB2ENR_ADCEN_Msk;
   RCC->APB2ENR |= ClkEnMask;
   while ( (RCC->APB2ENR & ClkEnMask) == 0 ) { }
}


template <uint32_t adr>
void ADCx<adr>::Enable()
{
   SET(control(), ADEN);
}


template <uint32_t adr>
void ADCx<adr>::Disable()
{
   SET(control(), ADDIS);
}


template <uint32_t adr>
bool ADCx<adr>::IsDisable()
{
   return IS_SET(control(), ADEN);
}


template <uint32_t adr>
bool ADCx<adr>::IsReady()
{
   return IS_SET(status(), ADRDY);
}


template <uint32_t adr>
void ADCx<adr>::SetBusy()
{
   SET(status(), ADRDY);
}


template <uint32_t adr>
void ADCx<adr>::Stop()
{
   SET(control(), ADSTP);
}


template <uint32_t adr>
void ADCx<adr>::Start()
{
   SET(control(), ADSTART);
}


template <uint32_t adr>
bool ADCx<adr>::IsStoping()
{
   return IS_SET(control(), ADSTP);
}


template <uint32_t adr>
void ADCx<adr>::SetClock ( Clock val )
{
   uint32_t tmp = conf2().reg;
   tmp &= ~_2BIT_TO_MASK(conf2(), CKMODE);
   tmp |= VAL_TO_MASK(conf2(), CKMODE, val);
   conf2().reg = tmp;
}


template <uint32_t adr>
void ADCx<adr>::DMAenable()
{
   SET(conf1(), DMAEN);
}


template <uint32_t adr>
void ADCx<adr>::SetCircularDMA()
{
   SET(conf1(), DMACFG);
}




template <uint32_t adr>
void ADCx<adr>::SetResolution ( Resolution val )
{
   conf1().reg &= ~ADC_CFGR1_RES_Msk;
   conf1().reg |= (uint32_t)val << ADC_CFGR1_RES_Pos;
}


template <uint32_t adr>
void ADCx<adr>::SetSampleTime ( SampleTime val )
{
   sampleTime().reg &= ~ADC_SMPR_SMP_Msk;
   sampleTime().reg |= (uint32_t)val << ADC_SMPR_SMP_Pos;
}

#endif
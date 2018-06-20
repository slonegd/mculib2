#pragma once

#include "ADC.h"

#if defined(STM32F405xx) || defined(STM32F030x6)

template <uint32_t adr>
void ADCx<adr>::clockEnable()
{
   RCC::template clockEnable<ADCx<adr>>();
}

template <uint32_t adr>
void ADCx<adr>::disable()
{
   SET(control(), ADDIS);
}


template <uint32_t adr>
bool ADCx<adr>::isDisable()
{
   return IS_SET(control(), ADDIS);
}


template <uint32_t adr>
bool ADCx<adr>::isReady()
{
   return IS_SET(status(), ADRDY);
}

template <uint32_t adr>
void ADCx<adr>::setBusy()
{
   SET(status(), ADRDY);
}


template <uint32_t adr>
void ADCx<adr>::stop()
{
   SET(control(), ADSTP);
}


template <uint32_t adr>
void ADCx<adr>::start()
{
   SET(control(), ADSTART);
}


template <uint32_t adr>
bool ADCx<adr>::isStoping()
{
   return IS_SET(control(), ADSTP);
}

#endif


#if defined(STM32F405xx)

template <uint32_t adr>
void ADCx<adr>::setClock ( Clock val )
{
   uint32_t tmp = ADCC::control().reg;
   tmp &= ~_2BIT_TO_MASK(ADCC::control(), ADCPRE);
   tmp |= VAL_TO_MASK(ADCC::control(), ADCPRE, val);
   ADCC::control().reg = tmp;
}

template <uint32_t adr>
void ADCx<adr>::enable()
{
   SET(control2(), ADON);
}



#elif defined(STM32F030x6)

template <uint32_t adr>
void ADCx<adr>::setClock ( Clock val )
{
   uint32_t tmp = conf2().reg;
   tmp &= ~_2BIT_TO_MASK(conf2(), CKMODE);
   tmp |= VAL_TO_MASK(conf2(), CKMODE, val);
   conf2().reg = tmp;
}


template <uint32_t adr>
void ADCx<adr>::enable()
{
   SET(control(), ADEN);
}


template <uint32_t adr>
void ADCx<adr>::DMAenable()
{
   SET(conf1(), DMAEN);
}


template <uint32_t adr>
void ADCx<adr>::setCircularDMA()
{
   SET(conf1(), DMACFG);
}


template <uint32_t adr>
void ADCx<adr>::setResolution ( Resolution val )
{
   uint32_t tmp = conf1().reg;
   tmp &= ~_2BIT_TO_MASK(conf1(), RES);
   tmp |= VAL_TO_MASK(conf1(), RES, val);
   conf1().reg = tmp;
}


template <uint32_t adr>
void ADCx<adr>::setContinuousMode()
{
   SET(conf1(), CONT);
}


template <uint32_t adr>
void ADCx<adr>::setSampleTime ( SampleTime val )
{
   uint32_t tmp = sampleTime().reg;
   tmp &= ~_3BIT_TO_MASK(sampleTime(), SMP);
   tmp |= VAL_TO_MASK(sampleTime(), SMP, val);
   sampleTime().reg = tmp;
}


template <uint32_t adr>
void ADCx<adr>::setChannel (uint8_t val )
{
   channelSelect().reg |= ((uint32_t)1 << val);
}

#endif
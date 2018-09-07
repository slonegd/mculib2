#pragma once

#include "ADC.h"
#include "pin.h"
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////
//  00   00       0000000
//  00   00       00   00
//  00   00       00   00
//  0000000       00   00
//       00       00   00
//       00       0000000
///////////////////////////////////////////////////////////////////////////////
#if defined(STM32F405xx) || defined(STM32F030x6)

template <uint32_t adr, class Pointer>
size_t template_ADC<adr,Pointer>::getDataAdr()
{
   return reinterpret_cast<size_t>(&(Pointer::get()->DR));
}


#endif


///////////////////////////////////////////////////////////////////////////////
//  00   00
//  00   00
//  00   00
//  0000000
//       00
//       00
///////////////////////////////////////////////////////////////////////////////

#if defined(STM32F405xx)

template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::enable()
{
   Pointer::get()->CR2.ADON = true;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::disable()
{
   Pointer::get()->CR2.ADON = false;
}


template <uint32_t adr, class Pointer>
bool template_ADC<adr,Pointer>::is_disable()
{
   return not Pointer::get()->CR2.ADON;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::start()
{
   Pointer::get()->CR2.SWSTART = true;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::DMAenable()
{
   Pointer::get()->CR2.DMA = true;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::setCircularDMA()
{
   Pointer::get()->CR2.DDS = true;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::setContinuousMode()
{
   Pointer::get()->CR2.CONT = true;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::setClock (Clock v)
{
   ADCC::setClock (v);
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::setResolution (Resolution v)
{
   Pointer::get()->CR1.RES = v;
}


namespace ADC_detail {
   template<> struct DefaultStream_impl<ADC1> { using type = DMA2stream0; };
   template<> struct DefaultStream_impl<ADC2> { using type = DMA2stream2; };
   template<> struct DefaultStream_impl<ADC3> { using type = DMA2stream1; };

//    template<class T>
//    using DefaultStream_t = typename DefaultStream_impl<T>::type;
}


template <uint32_t adr, class Pointer>
template <class PIN>
constexpr uint8_t template_ADC<adr,Pointer>::ADCchannel()
{
   return
      std::is_same_v<template_ADC,ADC1> or std::is_same_v<template_ADC,ADC2> ? (
         std::is_same_v<PIN,PA0> ? 0  :
         std::is_same_v<PIN,PA1> ? 1  :
         std::is_same_v<PIN,PA2> ? 2  :
         std::is_same_v<PIN,PA3> ? 3  :
         std::is_same_v<PIN,PA4> ? 4  :
         std::is_same_v<PIN,PA5> ? 5  :
         std::is_same_v<PIN,PA6> ? 6  :
         std::is_same_v<PIN,PA7> ? 7  :
         std::is_same_v<PIN,PB0> ? 8  :
         std::is_same_v<PIN,PB1> ? 9  :
         std::is_same_v<PIN,PC0> ? 10 :
         std::is_same_v<PIN,PC1> ? 11 :
         std::is_same_v<PIN,PC2> ? 12 :
         std::is_same_v<PIN,PC3> ? 13 :
         std::is_same_v<PIN,PC4> ? 14 :
         std::is_same_v<PIN,PC5> ? 15 : 255
      ) : std::is_same_v<template_ADC,ADC3> ? (
         std::is_same_v<PIN,PA0>  ? 0  :
         std::is_same_v<PIN,PA1>  ? 1  :
         std::is_same_v<PIN,PA2>  ? 2  :
         std::is_same_v<PIN,PA3>  ? 3  :
         std::is_same_v<PIN,PF6>  ? 4  :
         std::is_same_v<PIN,PF7>  ? 5  :
         std::is_same_v<PIN,PF8>  ? 6  :
         std::is_same_v<PIN,PF9>  ? 7  :
         std::is_same_v<PIN,PF10> ? 8  :
         std::is_same_v<PIN,PF3>  ? 9  :
         std::is_same_v<PIN,PC0>  ? 10 :
         std::is_same_v<PIN,PC1>  ? 11 :
         std::is_same_v<PIN,PC2>  ? 12 :
         std::is_same_v<PIN,PC3>  ? 13 :
         std::is_same_v<PIN,PF4>  ? 14 :
         std::is_same_v<PIN,PF5>  ? 15 : 255
      ) : 255;
}


template <uint32_t adr, class Pointer>
template <class DMA>
constexpr bool template_ADC<adr,Pointer>::DMAenabled()
{
   return 
      std::is_same_v<template_ADC,ADC1> ? std::is_same_v<DMA,DMA2stream0> or std::is_same_v<DMA,DMA2stream4> :
      std::is_same_v<template_ADC,ADC2> ? std::is_same_v<DMA,DMA2stream2> or std::is_same_v<DMA,DMA2stream3> :
      std::is_same_v<template_ADC,ADC3> ? std::is_same_v<DMA,DMA2stream0> or std::is_same_v<DMA,DMA2stream1> : false;
}


template <uint32_t adr, class Pointer>
template <class PIN>
constexpr bool template_ADC<adr,Pointer>::PINenabled()
{
   return template_ADC<adr,Pointer>::ADCchannel<PIN>() != 255;
}


template <uint32_t adr, class Pointer>
template <uint8_t channel>
void template_ADC<adr,Pointer>::setSampleTime (SampleTime v)
{
   static_assert (channel >= 0 and channel <= 18);
   if      constexpr (channel == 0)  Pointer::get()->SMPR.SMP0  = v;
   else if constexpr (channel == 1)  Pointer::get()->SMPR.SMP1  = v;
   else if constexpr (channel == 2)  Pointer::get()->SMPR.SMP2  = v;
   else if constexpr (channel == 3)  Pointer::get()->SMPR.SMP3  = v;
   else if constexpr (channel == 4)  Pointer::get()->SMPR.SMP4  = v;
   else if constexpr (channel == 5)  Pointer::get()->SMPR.SMP5  = v;
   else if constexpr (channel == 6)  Pointer::get()->SMPR.SMP6  = v;
   else if constexpr (channel == 7)  Pointer::get()->SMPR.SMP7  = v;
   else if constexpr (channel == 8)  Pointer::get()->SMPR.SMP8  = v;
   else if constexpr (channel == 9)  Pointer::get()->SMPR.SMP9  = v;
   else if constexpr (channel == 10) Pointer::get()->SMPR.SMP10 = v;
   else if constexpr (channel == 11) Pointer::get()->SMPR.SMP11 = v;
   else if constexpr (channel == 12) Pointer::get()->SMPR.SMP12 = v;
   else if constexpr (channel == 13) Pointer::get()->SMPR.SMP13 = v;
   else if constexpr (channel == 14) Pointer::get()->SMPR.SMP14 = v;
   else if constexpr (channel == 15) Pointer::get()->SMPR.SMP15 = v;
   else if constexpr (channel == 16) Pointer::get()->SMPR.SMP15 = v;
   else if constexpr (channel == 17) Pointer::get()->SMPR.SMP15 = v;
   else if constexpr (channel == 18) Pointer::get()->SMPR.SMP15 = v;
}


template <uint32_t adr, class Pointer>
template <size_t n, uint8_t channel> // n - номер по порядку (1 - 16)
void template_ADC<adr,Pointer>::setRegularSequenceOrder()
{
   static_assert (n >= 1 and n <= 16);
   static_assert (channel >= 0 and channel <= 18);
   if      constexpr (n == 1)  Pointer::get()->SQR.SQ1  = channel;
   else if constexpr (n == 2)  Pointer::get()->SQR.SQ2  = channel;
   else if constexpr (n == 3)  Pointer::get()->SQR.SQ3  = channel;
   else if constexpr (n == 4)  Pointer::get()->SQR.SQ4  = channel;
   else if constexpr (n == 5)  Pointer::get()->SQR.SQ5  = channel;
   else if constexpr (n == 6)  Pointer::get()->SQR.SQ6  = channel;
   else if constexpr (n == 7)  Pointer::get()->SQR.SQ7  = channel;
   else if constexpr (n == 8)  Pointer::get()->SQR.SQ8  = channel;
   else if constexpr (n == 9)  Pointer::get()->SQR.SQ9  = channel;
   else if constexpr (n == 10) Pointer::get()->SQR.SQ10 = channel;
   else if constexpr (n == 11) Pointer::get()->SQR.SQ11 = channel;
   else if constexpr (n == 12) Pointer::get()->SQR.SQ12 = channel;
   else if constexpr (n == 13) Pointer::get()->SQR.SQ13 = channel;
   else if constexpr (n == 14) Pointer::get()->SQR.SQ14 = channel;
   else if constexpr (n == 15) Pointer::get()->SQR.SQ15 = channel;
   else if constexpr (n == 16) Pointer::get()->SQR.SQ16 = channel;
}


template <uint32_t adr, class Pointer>
template <size_t length>
void template_ADC<adr,Pointer>::setRegularSequenceLength()
{
   static_assert (length >= 1 and length <= 16);
   Pointer::get()->SQR.L = length - 1;
}


template <uint32_t adr, class Pointer>
void template_ADC<adr,Pointer>::setScanMode()
{
   Pointer::get()->CR1.SCAN = true;
}


template <uint32_t adr, class Pointer>
constexpr typename template_ADC<adr,Pointer>::Channels template_ADC<adr,Pointer>::DMAchannel()
{
   return
      std::is_same_v<template_ADC,ADC1> ? Channels::_0 :
      std::is_same_v<template_ADC,ADC2> ? Channels::_1 :
      std::is_same_v<template_ADC,ADC3> ? Channels::_2 : Channels::_0;
} 





///////////////////////////////////////////////////////////////////////////////
//  0000000
//  00   00
//  00   00
//  00   00
//  00   00
//  0000000
///////////////////////////////////////////////////////////////////////////////
#elif defined(STM32F030x6)

template <uint32_t adr>
void ADCx<adr>::disable()
{
   stop();
   while ( isStoping() ) { }
   SET(control(), ADDIS);
   while ( not isDisable() ) { }
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
   if (isReady())
      setBusy();
   SET(control(), ADEN);
   while ( not isReady() ) { }
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
void ADCx<adr>::setContinuousMode()
{
   SET(conf1(), CONT);
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
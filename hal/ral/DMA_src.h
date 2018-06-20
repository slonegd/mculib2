#pragma once

#include "DMA.h"

namespace DMAhelper {
#if defined(STM32F405xx)
   template<int stream>
   constexpr int DMAn()
   {
      return stream >= 4 ? 1 : 0;
   }
   template<int stream>
   constexpr uint32_t TCIpos()
   {
      return stream == 0 or stream == 4 ? 5  :
             stream == 1 or stream == 5 ? 11 :
             stream == 2 or stream == 6 ? 21 : 27;
   }
#elif defined(STM32F030x6)
   template<int stream>
   constexpr uint32_t TCImask()
   {
      return stream == 1 ? DMA_ISR_TCIF1_Msk :
             stream == 2 ? DMA_ISR_TCIF2_Msk :
             stream == 3 ? DMA_ISR_TCIF3_Msk :
             stream == 4 ? DMA_ISR_TCIF4_Msk : DMA_ISR_TCIF5_Msk;
   }
#endif
} // namespace DMAhelper {

#if defined(STM32F405xx) || defined(STM32F030x6)

template<uint32_t adr>
void DMAx<adr>::ClockEnable()
{
   RCC::template clockEnable<DMAx<adr>>();
}

#endif

#if defined(STM32F405xx)

template<uint32_t adr>
template<int stream>
bool DMAx<adr>::IsTransferCompleteInterrupt()
{
   static_assert (stream >= 0 and stream <= 7, "DMAstream 0-7");
   constexpr int n = DMAhelper::DMAn<stream>();
   constexpr uint32_t pos = DMAhelper::TCIpos<stream>();
   return (status().reg[n] & ((uint32_t)1 << pos)) != 0;
}


template<uint32_t adr>
template<int stream>
void DMAx<adr>::ClearFlagTransferCompleteInterrupt()
{
   static_assert (stream >= 0 and stream <= 7, "DMAstream 0-7");
   constexpr int n = DMAhelper::DMAn<stream>();
   constexpr uint32_t pos = DMAhelper::TCIpos<stream>();
   clear().reg[n] &= ~((uint32_t)1 << pos);
}

#elif defined(STM32F030x6)

template<uint32_t adr>
template<int stream>
bool DMAx<adr>::IsTransferCompleteInterrupt()
{
   static_assert (stream >= 1 and stream <= 5, "DMAstream 1-5");
   constexpr uint32_t mask = DMAhelper::TCImask<stream>();
   return (status().reg & mask) != 0;
}


template<uint32_t adr>
template<int stream>
void DMAx<adr>::ClearFlagTransferCompleteInterrupt()
{
   static_assert (stream >= 1 and stream <= 5, "DMAstream 1-5");
   constexpr uint32_t mask = DMAhelper::TCImask<stream>();
   clear().reg &= ~mask;
}

#endif
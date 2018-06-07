#pragma once

#include "DMAstream.h"


#if defined(STM32F405xx) || defined(STM32F030x6)

template<uint32_t adr>
void DMAstream<adr>::ClockEnable()
{
   DMA::ClockEnable();
}


template<uint32_t adr>
void DMAstream<adr>::SetMemoryAdr (uint32_t val)
{
   memAdr0().reg = val;
}


template<uint32_t adr>
void DMAstream<adr>::SetPeriphAdr (uint32_t val)
{
   perAdr().reg = val;
}


template<uint32_t adr>
void DMAstream<adr>::SetQtyTransactions (uint16_t val)
{
   nData().reg = (uint32_t)val;
}


template<uint32_t adr>
uint16_t DMAstream<adr>::QtyTransactionsLeft()
{
   return nData().reg;
}


template<uint32_t adr>
void DMAstream<adr>::ClearFlagTransferCompleteInterrupt()
{
   DMA::template ClearFlagTransferCompleteInterrupt<stream()>();
}


template<uint32_t adr>
bool DMAstream<adr>::IsTransferCompleteInterrupt()
{
   return DMA::template IsTransferCompleteInterrupt<stream()>();
}


template<uint32_t adr>
void DMAstream<adr>::Disable()
{
   CLEAR(conf(), EN); 
   while (IS_SET(conf(), EN)) {}
}


template<uint32_t adr>
bool DMAstream<adr>::IsDisable()
{
   return IS_CLEAR(conf(), EN);
}


template<uint32_t adr>
void DMAstream<adr>::Enable()
{
   SET(conf(), EN);
}


template<uint32_t adr>
void DMAstream<adr>::EnableTransferCompleteInterrupt()
{
   SET(conf(), TCIE);
}


#endif

#if defined(STM32F405xx)

template<uint32_t adr>
constexpr int DMAstream<adr>::stream()
{
   return adr == DMA1_Stream0_BASE or DMA2_Stream0_BASE ? 0 :
          adr == DMA1_Stream1_BASE or DMA2_Stream1_BASE ? 1 :
          adr == DMA1_Stream2_BASE or DMA2_Stream2_BASE ? 2 :
          adr == DMA1_Stream3_BASE or DMA2_Stream3_BASE ? 3 :
          adr == DMA1_Stream4_BASE or DMA2_Stream4_BASE ? 4 :
          adr == DMA1_Stream5_BASE or DMA2_Stream5_BASE ? 5 :
          adr == DMA1_Stream6_BASE or DMA2_Stream6_BASE ? 6 :
          adr == DMA1_Stream7_BASE or DMA2_Stream7_BASE ? 7 : -1;
}


template<uint32_t adr>
constexpr IRQn_Type DMAstream<adr>::IRQn()
{
   return
      adr == DMA1_Stream0_BASE ? DMA1_Stream0_IRQn :
      adr == DMA1_Stream1_BASE ? DMA1_Stream1_IRQn :
      adr == DMA1_Stream2_BASE ? DMA1_Stream2_IRQn :
      adr == DMA1_Stream3_BASE ? DMA1_Stream3_IRQn :
      adr == DMA1_Stream4_BASE ? DMA1_Stream4_IRQn :
      adr == DMA1_Stream5_BASE ? DMA1_Stream5_IRQn :
      adr == DMA1_Stream6_BASE ? DMA1_Stream6_IRQn :
      adr == DMA1_Stream7_BASE ? DMA1_Stream7_IRQn :
      adr == DMA2_Stream0_BASE ? DMA1_Stream0_IRQn :
      adr == DMA2_Stream1_BASE ? DMA1_Stream1_IRQn :
      adr == DMA2_Stream2_BASE ? DMA1_Stream2_IRQn :
      adr == DMA2_Stream3_BASE ? DMA1_Stream3_IRQn :
      adr == DMA2_Stream4_BASE ? DMA1_Stream4_IRQn :
      adr == DMA2_Stream5_BASE ? DMA1_Stream5_IRQn :
      adr == DMA2_Stream6_BASE ? DMA1_Stream6_IRQn :
      adr == DMA2_Stream7_BASE ? DMA1_Stream7_IRQn : NonMaskableInt_IRQn;
}


template<> struct DMAn<DMA1_Stream0_BASE> { using type = DMA1; };
template<> struct DMAn<DMA1_Stream1_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream2_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream3_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream4_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream5_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream6_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA1_Stream7_BASE> : DMAn<DMA1_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream0_BASE> { using type = DMA2; };
template<> struct DMAn<DMA2_Stream1_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream2_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream3_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream4_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream5_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream6_BASE> : DMAn<DMA2_Stream0_BASE> {};
template<> struct DMAn<DMA2_Stream7_BASE> : DMAn<DMA2_Stream0_BASE> {};



#elif defined(STM32F030x6)

template<uint32_t adr>
constexpr int DMAstream<adr>::stream()
{
   return adr == DMA1_Channel1_BASE ? 1 :
          adr == DMA1_Channel2_BASE ? 2 :
          adr == DMA1_Channel3_BASE ? 3 :
          adr == DMA1_Channel4_BASE ? 4 :
          adr == DMA1_Channel5_BASE ? 5 : -1;
}


template<uint32_t adr>
constexpr IRQn_Type DMAstream<adr>::IRQn()
{
   return
      adr == DMA1_Channel1_BASE ? DMA1_Channel1_IRQn       :
      adr == DMA1_Channel2_BASE ? DMA1_Channel2_3_IRQn     :
      adr == DMA1_Channel3_BASE ? DMA1_Channel2_3_IRQn     :
      adr == DMA1_Channel4_BASE ? DMA1_Channel4_5_6_7_IRQn :
      adr == DMA1_Channel5_BASE ? DMA1_Channel4_5_6_7_IRQn : NonMaskableInt_IRQn;
}


template<> struct DMAn<DMA1_Channel1_BASE> { using type = DMA1; };
template<> struct DMAn<DMA1_Channel2_BASE> : DMAn<DMA1_Channel1_BASE> {};
template<> struct DMAn<DMA1_Channel3_BASE> : DMAn<DMA1_Channel1_BASE> {};
template<> struct DMAn<DMA1_Channel4_BASE> : DMAn<DMA1_Channel1_BASE> {};
template<> struct DMAn<DMA1_Channel5_BASE> : DMAn<DMA1_Channel1_BASE> {};

#endif





template<uint32_t adr>
void DMAstream<adr>::Configure (DMAstream<adr>::Configure_t& c)
{
   conf().reg = 0;
   DMA_ral::CR_t tmp;
   tmp.reg = 0;
   tmp.bits.DIR   = c.dataDir;
   tmp.bits.MSIZE = c.memSize;
   tmp.bits.PSIZE = c.perSize;
   tmp.bits.MINC  = c.memInc;
   tmp.bits.PINC  = c.perInc;
   tmp.bits.CIRC  = c.circularMode;
#if defined(STM32F405xx)
   tmp.bits.CHSEL = c.channel;
#endif
   conf().reg = tmp.reg;
}
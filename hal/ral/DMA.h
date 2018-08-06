#pragma once

#include "DMA_bits.h"


template<uint32_t adr>
class DMAx 
{
public:
   static const uint32_t Base = adr;
   void makeDebugVar() { ISR.bits.res1 = 0; }

   static void ClockEnable();
   template<int stream>
   static bool IsTransferCompleteInterrupt();
   template<int stream>
   static void ClearFlagTransferCompleteInterrupt();
   template<int stream>
   static void clearInterruptFlags();


protected:
   #define MakeRef(Reg,Ref) DMA_ral::Reg& Ref() { return (DMA_ral::Reg&) *(uint32_t*)(Base + DMA_ral::Reg::Offset); }
   static volatile MakeRef(ISR_t,  status);
   static volatile MakeRef(IFCR_t, clear);
   #undef MakeRef


private:
   DMA_ral::ISR_t  ISR;
   DMA_ral::IFCR_t IFCR;
};


#undef DMA1
using DMA1 = DMAx<DMA1_BASE>;
#if defined(STM32F405xx)
#undef DMA2
using DMA2 = DMAx<DMA2_BASE>;
#endif

#include "DMA_src.h"
#include "DMAstream.h"

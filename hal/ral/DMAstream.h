#pragma once

#include "DMAstream_bits.h"
#include "DMA.h"
#if defined(STM32F405xx)
#include "bitbanding.h"
#endif

/// номер dma в зависимости от адреса, хелпер
template<uint32_t adr> struct DMAn;

template <uint32_t adr> 
class DMAstream
{
public:
   void makeDebugVar() { conf().bits.res1 = 0; }

   static constexpr uint32_t Base = adr;

   using DataDirection = DMA_ral::DataDirection;
   using DataSize      = DMA_ral::DataSize;
#if defined(STM32F405xx)
   using Channels = DMA_ral::Channels;
#endif
   using DMA = typename DMAn<Base>::type;


   static constexpr int stream();
   static constexpr IRQn_Type IRQn();


   struct Configure_t { 
      DataDirection dataDir;
      DataSize      memSize;
      DataSize      perSize;
      bool          memInc;
      bool          perInc;
      bool          circularMode;
#if defined(STM32F405xx)
      Channels      channel;
#endif
   };

   static void ClockEnable();
   static void Configure (Configure_t& c);
   static void Enable();
   static bool IsDisable();
   static void Disable();
   static void SetMemoryAdr (uint32_t val);
   static void SetPeriphAdr (uint32_t val);
   static void SetQtyTransactions (uint16_t val);
   static uint16_t QtyTransactionsLeft();
   static void EnableTransferCompleteInterrupt();
   static bool IsTransferCompleteInterrupt();
   static void ClearFlagTransferCompleteInterrupt();
   


protected:
   #define MakeRef(Reg,Ref) DMA_ral::Reg& Ref() { return (DMA_ral::Reg&) *(uint32_t*)(Base + DMA_ral::Reg::Offset); }
   static volatile MakeRef(CR_t, conf);
   static volatile MakeRef(NDTR_t, nData);
   static volatile MakeRef(PAR_t, perAdr);
   static volatile MakeRef(M0AR_t, memAdr0);
#if defined(STM32F405xx)
   static volatile MakeRef(M1AR_t, memAdr1);
   static volatile MakeRef(FCR_t, FIFOcontr);
#endif
   #undef MakeRef



private:
   DMA_ral::CR_t CR;
   DMA_ral::NDTR_t NDTR;
   DMA_ral::PAR_t PAR;
   DMA_ral::M0AR_t MOAR;
#if defined(STM32F405xx)
   DMA_ral::M1AR_t M1AR;
   DMA_ral::FCR_t FCR;
#endif

};




#if defined(STM32F405xx)
   using DMA1stream0 = DMAstream<DMA1_Stream0_BASE>;
   using DMA1stream1 = DMAstream<DMA1_Stream1_BASE>;
   using DMA1stream2 = DMAstream<DMA1_Stream2_BASE>;
   using DMA1stream3 = DMAstream<DMA1_Stream3_BASE>;
   using DMA1stream4 = DMAstream<DMA1_Stream4_BASE>;
   using DMA1stream5 = DMAstream<DMA1_Stream5_BASE>;
   using DMA1stream6 = DMAstream<DMA1_Stream6_BASE>;
   using DMA1stream7 = DMAstream<DMA1_Stream7_BASE>;

   using DMA2stream0 = DMAstream<DMA2_Stream0_BASE>;
   using DMA2stream1 = DMAstream<DMA2_Stream1_BASE>;
   using DMA2stream2 = DMAstream<DMA2_Stream2_BASE>;
   using DMA2stream3 = DMAstream<DMA2_Stream3_BASE>;
   using DMA2stream4 = DMAstream<DMA2_Stream4_BASE>;
   using DMA2stream5 = DMAstream<DMA2_Stream5_BASE>;
   using DMA2stream6 = DMAstream<DMA2_Stream6_BASE>;
   using DMA2stream7 = DMAstream<DMA2_Stream7_BASE>;

#elif defined(STM32F030x6)
   using DMA1channel1 = DMAstream<DMA1_Channel1_BASE>;
   using DMA1channel2 = DMAstream<DMA1_Channel2_BASE>;
   using DMA1channel3 = DMAstream<DMA1_Channel3_BASE>;
   using DMA1channel4 = DMAstream<DMA1_Channel4_BASE>;
   using DMA1channel5 = DMAstream<DMA1_Channel5_BASE>;
#endif


#include "DMAstream_src.h"

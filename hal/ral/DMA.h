#pragma once

#include "DMA_bits.h"
#if defined(STM32F405xx)
#include "bitbanding.h"
#endif

/* STM32F4
typedef struct
{
  __IO uint32_t LISR;   // DMA low interrupt status register,      Address offset: 0x00
  __IO uint32_t HISR;   // DMA high interrupt status register,     Address offset: 0x04
  __IO uint32_t LIFCR;  // DMA low interrupt flag clear register,  Address offset: 0x08
  __IO uint32_t HIFCR;  // DMA high interrupt flag clear register, Address offset: 0x0C
} DMA_TypeDef;          */
/* STM32F0
typedef struct
{
  __IO uint32_t ISR;  // DMA interrupt status register,     Address offset: 0x00
  __IO uint32_t IFCR; // DMA interrupt flag clear register, Address offset: 0x04
} DMA_TypeDef;        */


template<uint32_t BaseAdr> struct DMAx : 
#if defined(STM32F405xx)
   public DMA_ral::LISR_t,
   public DMA_ral::HISR_t,
   public DMA_ral::LIFCR_t,
   public DMA_ral::HIFCR_t
#elif defined(STM32F030x6)
   public DMA_ral::ISR_t,
   public DMA_ral::IFCR_t
#endif
{
   static const uint32_t Base = BaseAdr;
#if defined(STM32F405xx)
   using ISR_t = DMA_ral::LISR_t;
   using IFCR_t = DMA_ral::LIFCR_t;
#endif
   void makeDebugVar() { ISR_t::bits.res1 = 0; }
};


#undef DMA1
using DMA1 = DMAx<DMA1_BASE>;
#if defined(STM32F405xx)
#undef DMA2
using DMA2 = DMAx<DMA2_BASE>;
#endif




/* STM32F4
typedef struct
{
  __IO uint32_t CR;     // DMA stream x configuration register
  __IO uint32_t NDTR;   // DMA stream x number of data register
  __IO uint32_t PAR;    // DMA stream x peripheral address register
  __IO uint32_t M0AR;   // DMA stream x memory 0 address register
  __IO uint32_t M1AR;   // DMA stream x memory 1 address register
  __IO uint32_t FCR;    // DMA stream x FIFO control register
} DMA_Stream_TypeDef;   */
/* STM32F0
typedef struct
{
  __IO uint32_t CCR;   // DMA channel x configuration register     
  __IO uint32_t CNDTR; // DMA channel x number of data register    
  __IO uint32_t CPAR;  // DMA channel x peripheral address register
  __IO uint32_t CMAR;  // DMA channel x memory address register    
} DMA_Channel_TypeDef; */


template <uint32_t DMAstreamAdr> class DMAstream : 
   public DMA_ral::CR_t,
   public DMA_ral::NDTR_t,
   public DMA_ral::PAR_t,
   public DMA_ral::M0AR_t
#if defined(STM32F405xx)
   ,
   public DMA_ral::M1AR_t,
   public DMA_ral::FCR_t
#endif
{
public:
   void makeDebugVar() { conf().bits.res1 = 0; }

   static const uint32_t Base = DMAstreamAdr;

   using DataDirection = DMA_ral::CR_t::DataDirection;
   using DataSize = DMA_ral::CR_t::DataSize;

#if defined(STM32F405xx)
   using Channels = DMA_ral::CR_t::Channels;
   static constexpr IRQn_Type IRQn = 
      Base == DMA1_Stream0_BASE ? DMA1_Stream0_IRQn :
      Base == DMA1_Stream1_BASE ? DMA1_Stream1_IRQn :
      Base == DMA1_Stream2_BASE ? DMA1_Stream2_IRQn :
      Base == DMA1_Stream3_BASE ? DMA1_Stream3_IRQn :
      Base == DMA1_Stream4_BASE ? DMA1_Stream4_IRQn :
      Base == DMA1_Stream5_BASE ? DMA1_Stream5_IRQn :
      Base == DMA1_Stream6_BASE ? DMA1_Stream6_IRQn :
      Base == DMA1_Stream7_BASE ? DMA1_Stream7_IRQn :
      Base == DMA2_Stream0_BASE ? DMA1_Stream0_IRQn :
      Base == DMA2_Stream1_BASE ? DMA1_Stream1_IRQn :
      Base == DMA2_Stream2_BASE ? DMA1_Stream2_IRQn :
      Base == DMA2_Stream3_BASE ? DMA1_Stream3_IRQn :
      Base == DMA2_Stream4_BASE ? DMA1_Stream4_IRQn :
      Base == DMA2_Stream5_BASE ? DMA1_Stream5_IRQn :
      Base == DMA2_Stream6_BASE ? DMA1_Stream6_IRQn :
      Base == DMA2_Stream7_BASE ? DMA1_Stream7_IRQn :
                                  NonMaskableInt_IRQn;
#endif

   
   static void SetMemoryAdr (uint32_t val) { memAdr0().reg = val; }
   static void SetPeriphAdr (uint32_t val) { perAdr().reg = val; }
   static void SetQtyTransactions (uint16_t val) { nData().reg = (uint32_t)val; }
   static uint16_t QtyTransactionsLeft()   { return nData().reg; }


   struct Configure_t { 
      DataDirection dataDir;
      DataSize memSize;
      DataSize perSize;
      bool memInc;
      bool perInc;
      bool circularMode;
#if defined(STM32F405xx)
      Channels channel;
#endif
   };
   static void Configure (Configure_t& c)
   {
      conf().reg = 0;
      DMA_ral::CR_t tmp = {0};
      tmp.bits.DIR = c.dataDir;
      tmp.bits.MSIZE = c.memSize;
      tmp.bits.PSIZE = c.perSize;
      tmp.bits.MINC = c.memInc;
      tmp.bits.PINC = c.perInc;
      tmp.bits.CIRC = c.circularMode;
#if defined(STM32F405xx)
      tmp.bits.CHSEL = c.channel;
#endif
      conf().reg = tmp.reg;
   }


#if defined(STM32F405xx)
   static void ClockEnable() { RCC->AHB1ENR |= (uint32_t)1 << (DMAn + 20); }
   static void Enable() { BITBAND_SET(conf(), EN, true); }
   static bool IsDisable() { return BB_REG(conf(), EN) == 0; }
   static void Disable()
   { 
      BITBAND_SET(conf(), EN, false); 
      while (conf().reg & ENmask) {}
   }
   static void EnableTransferCompleteInterrupt() { BITBAND_SET(conf(), TCIE, true); }
   static bool TransferCompleteInterrupt()
   {
      return  (interruptStatus().reg & TCImask) != 0;
   }
   static void ClearFlagTransferCompleteInterrupt() { BITBAND_SET(conf(), TCIpos, true); }
#elif defined(STM32F030x6)
   static void ClockEnable() { RCC->AHBENR |= RCC_AHBENR_DMAEN_Msk; }
   static void Enable() { conf().reg |= ENmask; }
   static bool IsDisable() { return (conf().reg & ENmask) == 0; }
   static void Disable()
   {
      conf().reg &= ~ENmask;; 
      while (conf().reg & ENmask) {}
   }
   static void EnableTransferCompleteInterrupt() { conf().reg |= TCIEmask; }
   static bool TransferCompleteInterrupt()
   {
      return  (interruptStatus().reg & TCImask) != 0;
   }
   static void ClearFlagTransferCompleteInterrupt()
   {
      clearInterruptFlag().reg |= TCImask;
   }
#endif



protected:
#define MakeRef(Reg,Ref) DMA_ral::Reg& Ref() { return (DMA_ral::Reg&) *(uint32_t*)(Base + DMA_ral::Reg::Offset); }
   static volatile MakeRef(CR_t, conf);
   static volatile MakeRef(NDTR_t, nData);
   static volatile MakeRef(PAR_t, perAdr);
   static volatile MakeRef(M0AR_t, memAdr0);
#if defined(STM32F405xx)
   static volatile MakeRef(M1AR_t, memAdr1);
   static volatile MakeRef(FCR_t, FIFOcontr);
   static volatile DMA_ral::LISR_t& interruptStatus()
   { return (DMA_ral::LISR_t&)  *((uint32_t*)ISRadr); }
   static volatile DMA_ral::LIFCR_t& clearInterruptFlag()
   { return (DMA_ral::LIFCR_t&) *((uint32_t*)IFCRadr); }
#elif defined(STM32F030x6)
   static volatile DMA_ral::ISR_t& interruptStatus()
   { return (DMA_ral::ISR_t&)  *((uint32_t*)(DMA1::Base + DMA1::ISR_t::Offset)); }
   static volatile DMA_ral::IFCR_t& clearInterruptFlag()
   { return (DMA_ral::IFCR_t&) *((uint32_t*)(DMA1::Base + DMA1::IFCR_t::Offset)); }
#endif
#undef MakeRef



private:
#if defined(STM32F405xx)
   static constexpr uint8_t DMAn =
        Base == DMA1_Stream0_BASE
     || Base == DMA1_Stream1_BASE
     || Base == DMA1_Stream2_BASE
     || Base == DMA1_Stream3_BASE
     || Base == DMA1_Stream4_BASE
     || Base == DMA1_Stream5_BASE
     || Base == DMA1_Stream6_BASE
     || Base == DMA1_Stream7_BASE
      ? 1 : 2;
   static constexpr uint8_t DMAstreamN =
      Base == DMA1_Stream0_BASE || Base == DMA2_Stream0_BASE ? 0 :
      Base == DMA1_Stream1_BASE || Base == DMA2_Stream1_BASE ? 1 :
      Base == DMA1_Stream2_BASE || Base == DMA2_Stream2_BASE ? 2 :
      Base == DMA1_Stream3_BASE || Base == DMA2_Stream3_BASE ? 3 :
      Base == DMA1_Stream4_BASE || Base == DMA2_Stream4_BASE ? 4 :
      Base == DMA1_Stream5_BASE || Base == DMA2_Stream5_BASE ? 5 :
      Base == DMA1_Stream6_BASE || Base == DMA2_Stream6_BASE ? 6 : 7;
   static constexpr uint32_t ISRadr =
      DMAn == 1 && DMAstreamN < 5 ? DMA1_BASE + DMA_ral::LISR_t::Offset :
      DMAn == 1 && DMAstreamN > 4 ? DMA1_BASE + DMA_ral::HISR_t::Offset :
      DMAn == 2 && DMAstreamN < 5 ? DMA2_BASE + DMA_ral::LISR_t::Offset :
                                    DMA2_BASE + DMA_ral::HISR_t::Offset;

   static constexpr uint32_t IFCRadr =
      DMAn == 1 && DMAstreamN < 5 ? DMA1_BASE + DMA_ral::LIFCR_t::Offset :
      DMAn == 1 && DMAstreamN > 4 ? DMA1_BASE + DMA_ral::HIFCR_t::Offset :
      DMAn == 2 && DMAstreamN < 5 ? DMA2_BASE + DMA_ral::LIFCR_t::Offset :
                                    DMA2_BASE + DMA_ral::HIFCR_t::Offset;
   
   static constexpr uint32_t TCIpos = 
      DMAstreamN == 0 || DMAstreamN == 4 ? 5  :
      DMAstreamN == 1 || DMAstreamN == 5 ? 11 :
      DMAstreamN == 2 || DMAstreamN == 6 ? 21 : 27;
   static constexpr uint32_t TCImask = 1 << TCIpos;

#elif defined(STM32F030x6)
   static constexpr uint8_t DMAchannelN =
      Base == DMA1_Channel1_BASE ? 1 :
      Base == DMA1_Channel2_BASE ? 2 :
      Base == DMA1_Channel3_BASE ? 3 :
      Base == DMA1_Channel4_BASE ? 4 :
      Base == DMA1_Channel5_BASE ? 5 : 0;
   static constexpr uint32_t TCImask = 
      (uint32_t)1 << ((DMAchannelN - 1) * 4 + 1);
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
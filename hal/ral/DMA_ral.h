#pragma once

#include <stdint.h>
#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#include "bitbanding.h"
#endif
//#include "something.h"

namespace DMA_ral {

   struct CR_t {
      enum { Offset = 0x00 };
      enum DataDirection {
         PerToMem = 0b00, MemToPer,
#if defined(STM32F405xx) 
         MemToMem
#endif
      };
      enum DataSize {
         byte8 = 0b00, word16, dword32
      };
      enum Priority {
         low = 0b00, medium, high, veryHi = 0b11
      };
      enum Channels {
         _0 = 0b000, _1, _2, _3, _4, _5, _6, _7
      };
      struct Bits {
         // Bit 0 EN: Stream enable / flag stream ready when read low
         volatile bool EN            :1;
#if defined(STM32F405xx)
         // Bit 1 DMEIE: Direct mode error interrupt enable
         volatile bool DMEIE         :1;
         // Bit 2 TEIE: Transfer error interrupt enable
         volatile bool TEIE          :1;
         // Bit 3 HTIE: Half transfer interrupt enable
         volatile bool HTIE          :1;
         // Bit 4 TCIE: Transfer complete interrupt enable
         volatile bool TCIE          :1;
         // Bit 5 PFCTRL: Peripheral flow controller
         volatile bool PFCTRL        :1;
         // Bits 7:6 DIR[1:0]: Data transfer direction
         volatile DataDirection DIR  :2;
         // Bit 8 CIRC: Circular mode
         volatile bool CIRC          :1;
         // Bit 9 PINC: Peripheral increment mode
         volatile bool PINC          :1;
         // Bit 10 MINC: Memory increment mode
         volatile bool MINC          :1;
         // Bits 12:11 PSIZE[1:0]: Peripheral data size
         volatile DataSize PSIZE     :2;
         // Bits 14:13 MSIZE[1:0]: Memory data size
         volatile DataSize MSIZE     :2;
         // Bit 15 PINCOS: Peripheral increment offset size
         volatile uint32_t PINCOS    :1;
         // Bits 17:16 PL[1:0]: Priority level
         volatile Priority PL        :2;
         // Bit 18 DBM: Double buffer mode
         volatile uint32_t DBM       :1;
         // Bit 19 CT: Current target (only in double buffer mode)
         volatile uint32_t CT        :1;
         // Bit 20 Reserved, must be kept at reset value.
         volatile uint32_t res1      :1;
         // Bits 22:21 PBURST[1:0]: Peripheral burst transfer configuration
         volatile uint32_t PBURST    :2;
         // Bits 24:23 MBURST: Memory burst transfer configuration
         volatile uint32_t MBURST    :2;
         // Bits 27:25 CHSEL[2:0]: Channel selection
         volatile Channels CHSEL     :3;
         // Bits 31:28 Reserved, must be kept at reset value.
         volatile uint32_t res2      :4;
#elif defined(STM32F030x6)
         // Bit 1 TCIE: Transfer complete interrupt enable
         volatile bool TCIE          :1;
         // Bit 2 HTIE: Half transfer interrupt enable
         volatile bool HTIE          :1;
         // Bit 3 TEIE: Transfer error interrupt enable
         volatile bool TEIE          :1;
         // Bit 4 DIR: Data transfer direction
         volatile DataDirection DIR  :1;
         // Bit 5 CIRC: Circular mode
         volatile bool CIRC          :1;
         // Bit 6 PINC: Peripheral increment mode
         volatile bool PINC          :1;
         // Bit 7 MINC: Memory increment mode
         volatile bool MINC          :1;
         // Bits 9:8 PSIZE[1:0]: Peripheral size
         volatile DataSize PSIZE     :2;
         // Bits 11:10 MSIZE[1:0]: Memory size
         volatile DataSize MSIZE     :2;
         // Bits 13:12 PL[1:0]: Channel priority level
         volatile Priority PL        :2;
         // Bit 14 MEM2MEM: Memory to memory mode
         volatile bool MEM2MEM       :1;
         // Bits 31:15 Reserved, must be kept at reset value.
         volatile uint32_t res1      :17;
#endif
      };
#if defined(STM32F405xx)
      enum { EN = 0, DMEIE, TEIE, HTIE, TCIE, PFCTRL, DIR, CIRC = 8, PINC,
         MINC, PSIZE, MSIZE = 13, PINCOS = 15, PL, DBM = 18, CT, PBURST,
         MBURST = 23, CHSEL = 25
      };
      enum {
         ENmask = DMA_SxCR_EN_Msk,
         TCIEmask = DMA_SxCR_TCIE_Msk
      };
#elif defined(STM32F030x6)
      enum {
         ENmask = DMA_CCR_EN_Msk,
         TCIEmask = DMA_CCR_TCIE_Msk
      };
#endif
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };


   struct NDTR_t {
      enum { Offset = 0x04 };
      volatile uint32_t reg;
   };


   struct PAR_t {
      enum { Offset = 0x08 };
      volatile uint32_t reg;
   };


   struct M0AR_t {
      enum { Offset = 0x0C };
      volatile uint32_t reg;
   };


#if defined(STM32F405xx)
   struct M1AR_t {
      enum { Offset = 0x10 };
      volatile uint32_t reg;
   };


   struct FCR_t {
      enum { Offset = 0x14 };
      volatile uint32_t reg;
   };
#endif

#if defined(STM32F405xx)
   struct LISR_t {
      enum { Offset = 0 };
      struct Bits {
         // Bits 22, 16, 6, 0 FEIFx: Stream x FIFO error interrupt flag (x=3..0)
         volatile bool FEIF0     :1;
         // Bits 23, 17, 7, 1 Reserved, must be kept at reset value
         volatile uint32_t res1  :1;
         // Bits 24, 18, 8, 2 DMEIFx: Stream x direct mode error interrupt flag (x=3..0)
         volatile bool DMEIF0    :1;
         // Bits 25, 19, 9, 3 TEIFx: Stream x transfer error interrupt flag (x=3..0)
         volatile bool TEIF0     :1;
         // Bits 26, 20, 10, 4 HTIFx: Stream x half transfer interrupt flag (x=3..0)
         volatile bool HTIF0     :1;
         // Bits 27, 21, 11, 5 TCIFx: Stream x transfer complete interrupt flag (x = 3..0)
         volatile bool TCIF0     :1;
         volatile bool FEIF1     :1;
         volatile uint32_t res2  :1;
         volatile bool DMEIF1    :1;
         volatile bool TEIF1     :1;
         volatile bool HTIF1     :1;
         volatile bool TCIF1     :1;
         // Bits 31:28, 15:12 Reserved, must be kept at reset value.
         volatile uint32_t res3  :4;
         volatile bool FEIF2     :1;
         volatile uint32_t res4  :1;
         volatile bool DMEIF2    :1;
         volatile bool TEIF2     :1;
         volatile bool HTIF2     :1;
         volatile bool TCIF2     :1;
         volatile bool FEIF3     :1;
         volatile uint32_t res5  :1;
         volatile bool DMEIF3    :1;
         volatile bool TEIF3     :1;
         volatile bool HTIF3     :1;
         volatile bool TCIF3     :1;
         volatile uint32_t res6  :4;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };

   struct HISR_t {
      enum { Offset = 0x04 };
      struct Bits {
         volatile bool FEIF4     :1;
         volatile uint32_t res1  :1;
         volatile bool DMEIF4    :1;
         volatile bool TEIF4     :1;
         volatile bool HTIF4     :1;
         volatile bool TCIF4     :1;
         volatile bool FEIF5     :1;
         volatile uint32_t res2  :1;
         volatile bool DMEIF5    :1;
         volatile bool TEIF5     :1;
         volatile bool HTIF5     :1;
         volatile bool TCIF5     :1;
         volatile uint32_t res3  :4;
         volatile bool FEIF6     :1;
         volatile uint32_t res4  :1;
         volatile bool DMEIF6    :1;
         volatile bool TEIF6     :1;
         volatile bool HTIF6     :1;
         volatile bool TCIF6     :1;
         volatile bool FEIF7     :1;
         volatile uint32_t res5  :1;
         volatile bool DMEIF7    :1;
         volatile bool TEIF7     :1;
         volatile bool HTIF7     :1;
         volatile bool TCIF7     :1;
         volatile uint32_t res6  :4;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };

   struct LIFCR_t {
      enum { Offset = 0x08 };
      struct Bits {
         volatile bool CFEIF0     :1;
         volatile uint32_t res1   :1;
         volatile bool CDMEIF0    :1;
         volatile bool CTEIF0     :1;
         volatile bool CHTIF0     :1;
         volatile bool CTCIF0     :1;
         volatile bool CFEIF1     :1;
         volatile uint32_t res2   :1;
         volatile bool CDMEIF1    :1;
         volatile bool CTEIF1     :1;
         volatile bool CHTIF1     :1;
         volatile bool CTCIF1     :1;
         volatile uint32_t res3   :4;
         volatile bool CFEIF2     :1;
         volatile uint32_t res4   :1;
         volatile bool CDMEIF2    :1;
         volatile bool CTEIF2     :1;
         volatile bool CHTIF2     :1;
         volatile bool CTCIF2     :1;
         volatile bool CFEIF3     :1;
         volatile uint32_t res5   :1;
         volatile bool CDMEIF3    :1;
         volatile bool CTEIF3     :1;
         volatile bool CHTIF3     :1;
         volatile bool CTCIF3     :1;
         volatile uint32_t res6   :4;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };

   struct HIFCR_t {
      enum { Offset = 0x0C };
      struct Bits {
         volatile bool CFEIF4     :1;
         volatile uint32_t res1   :1;
         volatile bool CDMEIF4    :1;
         volatile bool CTEIF4     :1;
         volatile bool CHTIF4     :1;
         volatile bool CTCIF4     :1;
         volatile bool CFEIF5     :1;
         volatile uint32_t res2   :1;
         volatile bool CDMEIF5    :1;
         volatile bool CTEIF5     :1;
         volatile bool CHTIF5     :1;
         volatile bool CTCIF5     :1;
         volatile uint32_t res3   :4;
         volatile bool CFEIF6     :1;
         volatile uint32_t res4   :1;
         volatile bool CDMEIF6    :1;
         volatile bool CTEIF6     :1;
         volatile bool CHTIF6     :1;
         volatile bool CTCIF6     :1;
         volatile bool CFEIF7     :1;
         volatile uint32_t res5   :1;
         volatile bool CDMEIF7    :1;
         volatile bool CTEIF7     :1;
         volatile bool CHTIF7     :1;
         volatile bool CTCIF7     :1;
         volatile uint32_t res6   :4;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };
#elif defined(STM32F030x6)
   struct ISR_t {
      enum { Offset = 0x00 };
      struct Bits {
         // Bits 16, 12, 8, 4, 0 GIFx: Channel x global interrupt flag (x = 1..5)
         volatile bool GIF1  :1;
         // Bits 17, 13, 9, 5, 1 TCIFx: Channel x transfer complete flag (x = 1..5)
         volatile bool TCIF1 :1;
         // Bits 18, 14, 10, 6, 2 HTIFx: Channel x half transfer flag (x = 1..5)
         volatile bool HTIF1 :1;
         // Bits 19, 15, 11, 7, 3 TEIFx: Channel x transfer error flag (x = 1..5)
         volatile bool TEIF1 :1;
         volatile bool GIF2  :1;
         volatile bool TCIF2 :1;
         volatile bool HTIF2 :1;
         volatile bool TEIF2 :1;
         volatile bool GIF3  :1;
         volatile bool TCIF3 :1;
         volatile bool HTIF3 :1;
         volatile bool TEIF3 :1;
         volatile bool GIF4  :1;
         volatile bool TCIF4 :1;
         volatile bool HTIF4 :1;
         volatile bool TEIF4 :1;
         volatile bool GIF5  :1;
         volatile bool TCIF5 :1;
         volatile bool HTIF5 :1;
         volatile bool TEIF5 :1;
         volatile uint32_t res1 :12;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };


   struct IFCR_t {
      enum { Offset = 0x04 };
      struct Bits {
         volatile bool CGIF1  :1;
         volatile bool CTCIF1 :1;
         volatile bool CHTIF1 :1;
         volatile bool CTEIF1 :1;
         volatile bool CGIF2  :1;
         volatile bool CTCIF2 :1;
         volatile bool CHTIF2 :1;
         volatile bool CTEIF2 :1;
         volatile bool CGIF3  :1;
         volatile bool CTCIF3 :1;
         volatile bool CHTIF3 :1;
         volatile bool CTEIF3 :1;
         volatile bool CGIF4  :1;
         volatile bool CTCIF4 :1;
         volatile bool CHTIF4 :1;
         volatile bool CTEIF4 :1;
         volatile bool CGIF5  :1;
         volatile bool CTCIF5 :1;
         volatile bool CHTIF5 :1;
         volatile bool CTEIF5 :1;
         volatile uint32_t res1 :12;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };
#endif
} // namespace


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
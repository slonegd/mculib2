#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "bitbanding.h"

namespace DMA_ral {

    struct CR_t {
        enum { Offset = 0x00 };
        enum DataDirection {
            PerToMem    = 0b00,
            MemToPer    = 0b01,
            MemToMem    = 0b10
        };
        enum DataSize {
            byte8   = 0b00,
            word16  = 0b01,
            dword32 = 0b10
        };
        enum Priority {
            low     = 0b00,
            medium  = 0b01,
            high    = 0b10,
            veryHi  = 0b11
        };
        enum Channels {
            _0 = 0b000,
            _1, _2, _3, _4, _5, _6, _7
        };
        struct Bits {
            // Bit 0 EN: Stream enable / flag stream ready when read low
            volatile bool EN            :1;
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
            volatile uint32_t dcb1      :1;
            // Bits 22:21 PBURST[1:0]: Peripheral burst transfer configuration
            volatile uint32_t PBURST    :2;
            // Bits 24:23 MBURST: Memory burst transfer configuration
            volatile uint32_t MBURST    :2;
            // Bits 27:25 CHSEL[2:0]: Channel selection
            volatile Channels CHSEL     :3;
            // Bits 31:28 Reserved, must be kept at reset value.
            volatile uint32_t dcb2      :4;
        };
        enum { EN = 0, DMEIE, TEIE, HTIE, TCIE, PFCTRL, DIR, CIRC = 8, PINC,
            MINC, PSIZE, MSIZE = 13, PINCOS = 15, PL, DBM = 18, CT, PBURST,
            MBURST = 23, CHSEL = 25
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct NDTR_t {
        volatile uint32_t reg;
    };

    struct PAR_t {
        volatile uint32_t reg;
    };

    struct M0AR_t {
        volatile uint32_t reg;
    };

    struct M1AR_t {
        volatile uint32_t reg;
    };

    struct FCR_t {
        volatile uint32_t reg;
    };

    struct LISR_t {
        enum { Offset = 0 };
        struct Bits {
            // Bits 22, 16, 6, 0 FEIFx: Stream x FIFO error interrupt flag (x=3..0)
            volatile bool FEIF0     :1;
            // Bits 23, 17, 7, 1 Reserved, must be kept at reset value
            volatile uint32_t dcb1  :1;
            // Bits 24, 18, 8, 2 DMEIFx: Stream x direct mode error interrupt flag (x=3..0)
            volatile bool DMEIF0    :1;
            // Bits 25, 19, 9, 3 TEIFx: Stream x transfer error interrupt flag (x=3..0)
            volatile bool TEIF0     :1;
            // Bits 26, 20, 10, 4 HTIFx: Stream x half transfer interrupt flag (x=3..0)
            volatile bool HTIF0     :1;
            // Bits 27, 21, 11, 5 TCIFx: Stream x transfer complete interrupt flag (x = 3..0)
            volatile bool TCIF0     :1;
            volatile bool FEIF1     :1;
            volatile uint32_t dcb2  :1;
            volatile bool DMEIF1    :1;
            volatile bool TEIF1     :1;
            volatile bool HTIF1     :1;
            volatile bool TCIF1     :1;
            // Bits 31:28, 15:12 Reserved, must be kept at reset value.
            volatile uint32_t dcb3  :4;
            volatile bool FEIF2     :1;
            volatile uint32_t dcb4  :1;
            volatile bool DMEIF2    :1;
            volatile bool TEIF2     :1;
            volatile bool HTIF2     :1;
            volatile bool TCIF2     :1;
            volatile bool FEIF3     :1;
            volatile uint32_t dcb5  :1;
            volatile bool DMEIF3    :1;
            volatile bool TEIF3     :1;
            volatile bool HTIF3     :1;
            volatile bool TCIF3     :1;
            volatile uint32_t dcb6  :4;
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
            volatile uint32_t dcb1  :1;
            volatile bool DMEIF4    :1;
            volatile bool TEIF4     :1;
            volatile bool HTIF4     :1;
            volatile bool TCIF4     :1;
            volatile bool FEIF5     :1;
            volatile uint32_t dcb2  :1;
            volatile bool DMEIF5    :1;
            volatile bool TEIF5     :1;
            volatile bool HTIF5     :1;
            volatile bool TCIF5     :1;
            volatile uint32_t dcb3  :4;
            volatile bool FEIF6     :1;
            volatile uint32_t dcb4  :1;
            volatile bool DMEIF6    :1;
            volatile bool TEIF6     :1;
            volatile bool HTIF6     :1;
            volatile bool TCIF6     :1;
            volatile bool FEIF7     :1;
            volatile uint32_t dcb5  :1;
            volatile bool DMEIF7    :1;
            volatile bool TEIF7     :1;
            volatile bool HTIF7     :1;
            volatile bool TCIF7     :1;
            volatile uint32_t dcb6  :4;
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
            volatile uint32_t dcb1   :1;
            volatile bool CDMEIF0    :1;
            volatile bool CTEIF0     :1;
            volatile bool CHTIF0     :1;
            volatile bool CTCIF0     :1;
            volatile bool CFEIF1     :1;
            volatile uint32_t dcb2   :1;
            volatile bool CDMEIF1    :1;
            volatile bool CTEIF1     :1;
            volatile bool CHTIF1     :1;
            volatile bool CTCIF1     :1;
            volatile uint32_t dcb3   :4;
            volatile bool CFEIF2     :1;
            volatile uint32_t dcb4   :1;
            volatile bool CDMEIF2    :1;
            volatile bool CTEIF2     :1;
            volatile bool CHTIF2     :1;
            volatile bool CTCIF2     :1;
            volatile bool CFEIF3     :1;
            volatile uint32_t dcb5   :1;
            volatile bool CDMEIF3    :1;
            volatile bool CTEIF3     :1;
            volatile bool CHTIF3     :1;
            volatile bool CTCIF3     :1;
            volatile uint32_t dcb6   :4;
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
            volatile uint32_t dcb1   :1;
            volatile bool CDMEIF4    :1;
            volatile bool CTEIF4     :1;
            volatile bool CHTIF4     :1;
            volatile bool CTCIF4     :1;
            volatile bool CFEIF5     :1;
            volatile uint32_t dcb2   :1;
            volatile bool CDMEIF5    :1;
            volatile bool CTEIF5     :1;
            volatile bool CHTIF5     :1;
            volatile bool CTCIF5     :1;
            volatile uint32_t dcb3   :4;
            volatile bool CFEIF6     :1;
            volatile uint32_t dcb4   :1;
            volatile bool CDMEIF6    :1;
            volatile bool CTEIF6     :1;
            volatile bool CHTIF6     :1;
            volatile bool CTCIF6     :1;
            volatile bool CFEIF7     :1;
            volatile uint32_t dcb5   :1;
            volatile bool CDMEIF7    :1;
            volatile bool CTEIF7     :1;
            volatile bool CHTIF7     :1;
            volatile bool CTCIF7     :1;
            volatile uint32_t dcb6   :4;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };
}

/*
typedef struct
{
  __IO uint32_t CR;     // DMA stream x configuration register
  __IO uint32_t NDTR;   // DMA stream x number of data register
  __IO uint32_t PAR;    // DMA stream x peripheral address register
  __IO uint32_t M0AR;   // DMA stream x memory 0 address register
  __IO uint32_t M1AR;   // DMA stream x memory 1 address register
  __IO uint32_t FCR;    // DMA stream x FIFO control register
} DMA_Stream_TypeDef;
*/
struct DMAstream_t : public DMA_ral::CR_t,
                     public DMA_ral::NDTR_t,
                     public DMA_ral::PAR_t,
                     public DMA_ral::M0AR_t,
                     public DMA_ral::M1AR_t,
                     public DMA_ral::FCR_t
{ };

/*
typedef struct
{
  __IO uint32_t LISR;   // DMA low interrupt status register,      Address offset: 0x00
  __IO uint32_t HISR;   // DMA high interrupt status register,     Address offset: 0x04
  __IO uint32_t LIFCR;  // DMA low interrupt flag clear register,  Address offset: 0x08
  __IO uint32_t HIFCR;  // DMA high interrupt flag clear register, Address offset: 0x0C
} DMA_TypeDef;
*/
struct DMA_t : public DMA_ral::LISR_t,
               public DMA_ral::HISR_t,
               public DMA_ral::LIFCR_t,
               public DMA_ral::HIFCR_t
{ };




template <uint32_t DMAstreamPtr>
class DMAstream : DMAstream_t, DMA_t
{
public:
    using DataDirection = DMA_ral::CR_t::DataDirection;
    using DataSize = DMA_ral::CR_t::DataSize;
    using Channels = DMA_ral::CR_t::Channels;

    static const uint32_t Base = DMAstreamPtr;
    static constexpr IRQn_Type IRQn = 
        DMAstreamPtr == DMA1_Stream0_BASE ? DMA1_Stream0_IRQn :
        DMAstreamPtr == DMA1_Stream1_BASE ? DMA1_Stream1_IRQn :
        DMAstreamPtr == DMA1_Stream2_BASE ? DMA1_Stream2_IRQn :
        DMAstreamPtr == DMA1_Stream3_BASE ? DMA1_Stream3_IRQn :
        DMAstreamPtr == DMA1_Stream4_BASE ? DMA1_Stream4_IRQn :
        DMAstreamPtr == DMA1_Stream5_BASE ? DMA1_Stream5_IRQn :
        DMAstreamPtr == DMA1_Stream6_BASE ? DMA1_Stream6_IRQn :
        DMAstreamPtr == DMA1_Stream7_BASE ? DMA1_Stream7_IRQn :
        DMAstreamPtr == DMA2_Stream0_BASE ? DMA1_Stream0_IRQn :
        DMAstreamPtr == DMA2_Stream1_BASE ? DMA1_Stream1_IRQn :
        DMAstreamPtr == DMA2_Stream2_BASE ? DMA1_Stream2_IRQn :
        DMAstreamPtr == DMA2_Stream3_BASE ? DMA1_Stream3_IRQn :
        DMAstreamPtr == DMA2_Stream4_BASE ? DMA1_Stream4_IRQn :
        DMAstreamPtr == DMA2_Stream5_BASE ? DMA1_Stream5_IRQn :
        DMAstreamPtr == DMA2_Stream6_BASE ? DMA1_Stream6_IRQn :
        DMAstreamPtr == DMA2_Stream7_BASE ? DMA1_Stream7_IRQn :
                                            NonMaskableInt_IRQn;


    static void ClockEnable() { RCC->AHB1ENR |= (uint32_t)1 << (DMAn + 20); }
    static void SetMemoryAdr (uint32_t val) { memAdr0().reg = val; }
    static void SetPeriphAdr (uint32_t val) { perAdr().reg = val; }
    static void Enable()  { 
        DMA1_Stream6->CR |= DMA_SxCR_EN_Msk;
    //    BITBAND_SET(conf(), EN, true); 
    }
    static void Disable() { 
        BITBAND_SET(conf(), EN, false); 
        while (conf().reg & (uint32_t)1<<EN) {}
    }
    static void SetDirection (DataDirection val) { BIT2BAND_SET(conf(), DIR, val); }
    static void SetMemoryTransactionSize (DataSize val) { BIT2BAND_SET(conf(), MSIZE, val); }
    static void SetPeriphTransactionSize (DataSize val) { BIT2BAND_SET(conf(), PSIZE, val); }
    static void SetMemoryInc (bool val)     { BITBAND_SET(conf(), MINC, val); }
    static void SetPeriphInc (bool val)     { BITBAND_SET(conf(), PINC, val); }
    static void SetCircularMode (bool val)  { BITBAND_SET(conf(), CIRC, val); }
    static void SetChannel (Channels val)   { BIT3BAND_SET(conf(), CHSEL, val); }
    static void EnableTransferCompleteInterrupt() { BITBAND_SET(conf(), TCIE, true); }
    struct Configure_t { 
        DataDirection dataDir;
        DataSize memSize;
        DataSize perSize;
        bool memInc;
        bool perInc;
        bool circularMode;
        Channels channel;
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
        tmp.bits.CHSEL = c.channel;
        conf().reg = tmp.reg;
    }
    static void SetQtyTransactions (uint16_t val) { nData().reg = (uint32_t)val; }
    static uint16_t QtyTransactionsLeft()   { return nData().reg; }
    
    static bool TransferCompleteInterrupt() 
    {
        return  (interruptStatus().reg & ((uint32_t)1 << bitPosInDMAregs)) != 0;
    }
    static void ClearFlagTransferCompleteInterrupt()
    {
        clearInterruptFlag().reg |= (uint32_t)1 << bitPosInDMAregs;
    }


protected:
    static volatile DMA_ral::CR_t   &conf()      
    { return (DMA_ral::CR_t &)   (*(DMA_Stream_TypeDef*)DMAstreamPtr).CR;   }
    static volatile DMA_ral::NDTR_t &nData()     
    { return (DMA_ral::NDTR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).NDTR; }
    static volatile DMA_ral::PAR_t  &perAdr()    
    { return (DMA_ral::PAR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).PAR;  }
    static volatile DMA_ral::M0AR_t &memAdr0()   
    { return (DMA_ral::M0AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M0AR; }
    static volatile DMA_ral::M1AR_t &memAdr1()   
    { return (DMA_ral::M1AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M1AR; }
    static volatile DMA_ral::FCR_t  &FIFOcontr() 
    { return (DMA_ral::FCR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).FCR;  }

    static volatile DMA_ral::LISR_t &interruptStatus()
    { return (DMA_ral::LISR_t&)  *((uint32_t*)ISRadr); }
    static volatile DMA_ral::LIFCR_t &clearInterruptFlag()
    { return (DMA_ral::LIFCR_t&) *((uint32_t*)IFCRadr); }

private:
    static constexpr uint8_t DMAn =
         DMAstreamPtr == DMA1_Stream0_BASE
      || DMAstreamPtr == DMA1_Stream1_BASE
      || DMAstreamPtr == DMA1_Stream2_BASE
      || DMAstreamPtr == DMA1_Stream3_BASE
      || DMAstreamPtr == DMA1_Stream4_BASE
      || DMAstreamPtr == DMA1_Stream5_BASE
      || DMAstreamPtr == DMA1_Stream6_BASE
      || DMAstreamPtr == DMA1_Stream7_BASE
       ? 1 : 2;
    static constexpr uint8_t DMAstreamN =
        DMAstreamPtr == DMA1_Stream0_BASE || DMAstreamPtr == DMA2_Stream0_BASE ? 0 :
        DMAstreamPtr == DMA1_Stream1_BASE || DMAstreamPtr == DMA2_Stream1_BASE ? 1 :
        DMAstreamPtr == DMA1_Stream2_BASE || DMAstreamPtr == DMA2_Stream2_BASE ? 2 :
        DMAstreamPtr == DMA1_Stream3_BASE || DMAstreamPtr == DMA2_Stream3_BASE ? 3 :
        DMAstreamPtr == DMA1_Stream4_BASE || DMAstreamPtr == DMA2_Stream4_BASE ? 4 :
        DMAstreamPtr == DMA1_Stream5_BASE || DMAstreamPtr == DMA2_Stream5_BASE ? 5 :
        DMAstreamPtr == DMA1_Stream6_BASE || DMAstreamPtr == DMA2_Stream6_BASE ? 6 :
                                                                                 7;
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
    
    static constexpr uint32_t bitPosInDMAregs = 
        DMAstreamN == 0 || DMAstreamN == 4 ? 5  :
        DMAstreamN == 1 || DMAstreamN == 5 ? 11 :
        DMAstreamN == 2 || DMAstreamN == 6 ? 21 :
                                             27;

    

};


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
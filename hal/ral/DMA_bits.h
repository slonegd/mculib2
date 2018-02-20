#pragma once

#include <stdint.h>
#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif


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
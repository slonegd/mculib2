#pragma once

#include "registr.h"



namespace DMA_ral {

enum DataDirection { PerToMem = 0b00, MemToPer,
#if defined(STM32F405xx) 
         MemToMem
#endif
};
enum DataSize { byte8 = 0b00, word16, dword32 };
enum Priority { low = 0b00, medium, high, veryHi = 0b11 };
enum Channels { _0 = 0b000, _1, _2, _3, _4, _5, _6, _7 };

struct CRbits {
   __IO bool EN            :1; // Bit 0 EN: Stream enable / flag stream ready when read low
#if defined(STM32F405xx)
   __IO bool          DMEIE  :1; // Bit 1 DMEIE: Direct mode error interrupt enable
   __IO bool          TEIE   :1; // Bit 2 TEIE: Transfer error interrupt enable
   __IO bool          HTIE   :1; // Bit 3 HTIE: Half transfer interrupt enable
   __IO bool          TCIE   :1; // Bit 4 TCIE: Transfer complete interrupt enable
   __IO bool          PFCTRL :1; // Bit 5 PFCTRL: Peripheral flow controller
   __IO DataDirection DIR    :2; // Bits 7:6 DIR[1:0]: Data transfer direction
   __IO bool          CIRC   :1; // Bit 8 CIRC: Circular mode
   __IO bool          PINC   :1; // Bit 9 PINC: Peripheral increment mode
   __IO bool          MINC   :1; // Bit 10 MINC: Memory increment mode
   __IO DataSize      PSIZE  :2; // Bits 12:11 PSIZE[1:0]: Peripheral data size
   __IO DataSize      MSIZE  :2; // Bits 14:13 MSIZE[1:0]: Memory data size
   __IO uint32_t      PINCOS :1; // Bit 15 PINCOS: Peripheral increment offset size
   __IO Priority      PL     :2; // Bits 17:16 PL[1:0]: Priority level
   __IO uint32_t      DBM    :1; // Bit 18 DBM: Double buffer mode
   __IO uint32_t      CT     :1; // Bit 19 CT: Current target (only in double buffer mode)
   __IO uint32_t      res1   :1; // Bit 20 Reserved, must be kept at reset value.
   __IO uint32_t      PBURST :2; // Bits 22:21 PBURST[1:0]: Peripheral burst transfer configuration
   __IO uint32_t      MBURST :2; // Bits 24:23 MBURST: Memory burst transfer configuration
   __IO Channels      CHSEL  :3; // Bits 27:25 CHSEL[2:0]: Channel selection
   __IO uint32_t      res2   :4; // Bits 31:28 Reserved, must be kept at reset value.
#elif defined(STM32F030x6)
   __IO bool          TCIE   :1; // Bit 1 TCIE: Transfer complete interrupt enable
   __IO bool          HTIE   :1; // Bit 2 HTIE: Half transfer interrupt enable
   __IO bool          TEIE   :1; // Bit 3 TEIE: Transfer error interrupt enable
   __IO DataDirection DIR    :1; // Bit 4 DIR: Data transfer direction
   __IO bool          CIRC   :1;  // Bit 5 CIRC: Circular mode
   __IO bool          PINC   :1; // Bit 6 PINC: Peripheral increment mode
   __IO bool          MINC   :1; // Bit 7 MINC: Memory increment mode
   __IO DataSize      PSIZE  :2; // Bits 9:8 PSIZE[1:0]: Peripheral size
   __IO DataSize      MSIZE  :2; // Bits 11:10 MSIZE[1:0]: Memory size
   __IO Priority      PL     :2; // Bits 13:12 PL[1:0]: Channel priority level
   __IO bool          MEM2MEM:1; // Bit 14 MEM2MEM: Memory to memory mode
   __IO uint32_t      res1   :17; // Bits 31:15 Reserved, must be kept at reset value.
#endif
};

struct CRposition {
#if defined(STM32F405xx)
   enum { EN = 0, DMEIE, TEIE, HTIE, TCIE, PFCTRL, DIR, CIRC = 8, PINC,
      MINC, PSIZE, MSIZE = 13, PINCOS = 15, PL, DBM = 18, CT, PBURST,
      MBURST = 23, CHSEL = 25
   };
#elif defined(STM32F030x6)
   enum { EN = 0, TCIE, HTIE, TEIE, DIR, CIRC, PINC, MINC, PSIZE,
      MSIZE = 10, PL = 12, MEM2MEM = 14
   };
#endif
};

struct CR_t   : BitsRegistr<CRbits> , Offset_t<0x00>, CRposition  {};
struct NDTR_t : DataRegistr         , Offset_t<0x04> {};
struct PAR_t  : DataRegistr         , Offset_t<0x08> {};
struct M0AR_t : DataRegistr         , Offset_t<0x0C> {};
#if defined(STM32F405xx)
struct M1AR_t : DataRegistr         , Offset_t<0x10> {};
struct FCR_t  : DataRegistr         , Offset_t<0x14> {};
#endif






#if defined(STM32F405xx)
   struct LISR_t {
      enum { Offset = 0 };
      struct Bits {
         __IO bool     FEIF0  :1; // Bits 22, 16, 6, 0 FEIFx: Stream x FIFO error interrupt flag (x=3..0)
         __IO uint32_t res1   :1; // Bits 23, 17, 7, 1 Reserved, must be kept at reset value
         __IO bool     DMEIF0 :1; // Bits 24, 18, 8, 2 DMEIFx: Stream x direct mode error interrupt flag (x=3..0)
         __IO bool     TEIF0  :1; // Bits 25, 19, 9, 3 TEIFx: Stream x transfer error interrupt flag (x=3..0)
         __IO bool     HTIF0  :1; // Bits 26, 20, 10, 4 HTIFx: Stream x half transfer interrupt flag (x=3..0)
         __IO bool     TCIF0  :1; // Bits 27, 21, 11, 5 TCIFx: Stream x transfer complete interrupt flag (x = 3..0)
         __IO bool     FEIF1  :1;
         __IO uint32_t res2   :1;
         __IO bool     DMEIF1 :1;
         __IO bool     TEIF1  :1;
         __IO bool     HTIF1  :1;
         __IO bool     TCIF1  :1;
         __IO uint32_t res3   :4; // Bits 31:28, 15:12 Reserved, must be kept at reset value.
         __IO bool     FEIF2  :1;
         __IO uint32_t res4   :1;
         __IO bool     DMEIF2 :1;
         __IO bool     TEIF2  :1;
         __IO bool     HTIF2  :1;
         __IO bool     TCIF2  :1;
         __IO bool     FEIF3  :1;
         __IO uint32_t res5   :1;
         __IO bool     DMEIF3 :1;
         __IO bool     TEIF3  :1;
         __IO bool     HTIF3  :1;
         __IO bool     TCIF3  :1;
         __IO uint32_t res6   :4;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };

   struct HISR_t {
      enum { Offset = 0x04 };
      struct Bits {
         __IO bool FEIF4     :1;
         __IO uint32_t res1  :1;
         __IO bool DMEIF4    :1;
         __IO bool TEIF4     :1;
         __IO bool HTIF4     :1;
         __IO bool TCIF4     :1;
         __IO bool FEIF5     :1;
         __IO uint32_t res2  :1;
         __IO bool DMEIF5    :1;
         __IO bool TEIF5     :1;
         __IO bool HTIF5     :1;
         __IO bool TCIF5     :1;
         __IO uint32_t res3  :4;
         __IO bool FEIF6     :1;
         __IO uint32_t res4  :1;
         __IO bool DMEIF6    :1;
         __IO bool TEIF6     :1;
         __IO bool HTIF6     :1;
         __IO bool TCIF6     :1;
         __IO bool FEIF7     :1;
         __IO uint32_t res5  :1;
         __IO bool DMEIF7    :1;
         __IO bool TEIF7     :1;
         __IO bool HTIF7     :1;
         __IO bool TCIF7     :1;
         __IO uint32_t res6  :4;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };

   struct LIFCR_t {
      enum { Offset = 0x08 };
      struct Bits {
         __IO bool CFEIF0     :1;
         __IO uint32_t res1   :1;
         __IO bool CDMEIF0    :1;
         __IO bool CTEIF0     :1;
         __IO bool CHTIF0     :1;
         __IO bool CTCIF0     :1;
         __IO bool CFEIF1     :1;
         __IO uint32_t res2   :1;
         __IO bool CDMEIF1    :1;
         __IO bool CTEIF1     :1;
         __IO bool CHTIF1     :1;
         __IO bool CTCIF1     :1;
         __IO uint32_t res3   :4;
         __IO bool CFEIF2     :1;
         __IO uint32_t res4   :1;
         __IO bool CDMEIF2    :1;
         __IO bool CTEIF2     :1;
         __IO bool CHTIF2     :1;
         __IO bool CTCIF2     :1;
         __IO bool CFEIF3     :1;
         __IO uint32_t res5   :1;
         __IO bool CDMEIF3    :1;
         __IO bool CTEIF3     :1;
         __IO bool CHTIF3     :1;
         __IO bool CTCIF3     :1;
         __IO uint32_t res6   :4;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };

   struct HIFCR_t {
      enum { Offset = 0x0C };
      struct Bits {
         __IO bool CFEIF4     :1;
         __IO uint32_t res1   :1;
         __IO bool CDMEIF4    :1;
         __IO bool CTEIF4     :1;
         __IO bool CHTIF4     :1;
         __IO bool CTCIF4     :1;
         __IO bool CFEIF5     :1;
         __IO uint32_t res2   :1;
         __IO bool CDMEIF5    :1;
         __IO bool CTEIF5     :1;
         __IO bool CHTIF5     :1;
         __IO bool CTCIF5     :1;
         __IO uint32_t res3   :4;
         __IO bool CFEIF6     :1;
         __IO uint32_t res4   :1;
         __IO bool CDMEIF6    :1;
         __IO bool CTEIF6     :1;
         __IO bool CHTIF6     :1;
         __IO bool CTCIF6     :1;
         __IO bool CFEIF7     :1;
         __IO uint32_t res5   :1;
         __IO bool CDMEIF7    :1;
         __IO bool CTEIF7     :1;
         __IO bool CHTIF7     :1;
         __IO bool CTCIF7     :1;
         __IO uint32_t res6   :4;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };
#elif defined(STM32F030x6)
   struct ISR_t {
      enum { Offset = 0x00 };
      struct Bits {
         // Bits 16, 12, 8, 4, 0 GIFx: Channel x global interrupt flag (x = 1..5)
         __IO bool GIF1  :1;
         // Bits 17, 13, 9, 5, 1 TCIFx: Channel x transfer complete flag (x = 1..5)
         __IO bool TCIF1 :1;
         // Bits 18, 14, 10, 6, 2 HTIFx: Channel x half transfer flag (x = 1..5)
         __IO bool HTIF1 :1;
         // Bits 19, 15, 11, 7, 3 TEIFx: Channel x transfer error flag (x = 1..5)
         __IO bool TEIF1 :1;
         __IO bool GIF2  :1;
         __IO bool TCIF2 :1;
         __IO bool HTIF2 :1;
         __IO bool TEIF2 :1;
         __IO bool GIF3  :1;
         __IO bool TCIF3 :1;
         __IO bool HTIF3 :1;
         __IO bool TEIF3 :1;
         __IO bool GIF4  :1;
         __IO bool TCIF4 :1;
         __IO bool HTIF4 :1;
         __IO bool TEIF4 :1;
         __IO bool GIF5  :1;
         __IO bool TCIF5 :1;
         __IO bool HTIF5 :1;
         __IO bool TEIF5 :1;
         __IO uint32_t res1 :12;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };


   struct IFCR_t {
      enum { Offset = 0x04 };
      struct Bits {
         __IO bool CGIF1  :1;
         __IO bool CTCIF1 :1;
         __IO bool CHTIF1 :1;
         __IO bool CTEIF1 :1;
         __IO bool CGIF2  :1;
         __IO bool CTCIF2 :1;
         __IO bool CHTIF2 :1;
         __IO bool CTEIF2 :1;
         __IO bool CGIF3  :1;
         __IO bool CTCIF3 :1;
         __IO bool CHTIF3 :1;
         __IO bool CTEIF3 :1;
         __IO bool CGIF4  :1;
         __IO bool CTCIF4 :1;
         __IO bool CHTIF4 :1;
         __IO bool CTEIF4 :1;
         __IO bool CGIF5  :1;
         __IO bool CTCIF5 :1;
         __IO bool CHTIF5 :1;
         __IO bool CTEIF5 :1;
         __IO uint32_t res1 :12;
      };
      union {
         __IO Bits bits;
         __IO uint32_t reg;
      };
   };
#endif
} // namespace DMA_ral {
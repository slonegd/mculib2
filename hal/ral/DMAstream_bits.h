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



} // namespace DMA_ral {
/**
 * RAL над регистрами FLASH
 */

#pragma once

#include <stdint.h>
#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif

namespace FLASH_ral {

   struct ACR_t {
      enum Latency {
         _0 = 0, _1,
#if defined(STM32F405xx)
         _2, _3,_4, _5, _6, _7
#endif
      };
      struct Bits {
         // Bits 2:0 LATENCY[2:0]: Latency
         volatile Latency LATENCY    :3;
#if defined(STM32F030x6)
         // Bit 3 Reserved, must be kept at reset value.
         volatile uint32_t res1      :1;
         // Bit 4 PRFTBE: Prefetch buffer enable
         volatile bool PRFTBE        :1;
         // Bit 5 PRFTBS: Prefetch buffer status
         volatile bool PRFTBS        :1;
         // Bits 31:6 Reserved, must be kept at reset value.
         volatile uint32_t res2      :26;
#elif defined(STM32F405xx)
         // Bits 7:3 Reserved, must be kept cleared.
         volatile uint32_t res1      :5;
         // Bit 8 PRFTEN: Prefetch enable
         volatile uint32_t PRFTEN    :1;
         // Bit 9 ICEN: Instruction cache enable
         volatile uint32_t ICEN      :1;
         // Bit 10 DCEN: Data cache enable
         volatile uint32_t DCEN      :1;
         // Bit 11 ICRST: Instruction cache reset
         volatile uint32_t ICRST     :1;
         // Bit 12 DCRST: Data cache reset
         volatile uint32_t DCRST     :1;
         // Bits 31:13 Reserved, must be kept cleared.
         volatile uint32_t res2      :19;
#endif
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct KEYR_t {
      volatile uint32_t reg;
   };



   struct OPTKEYR_t {
      volatile uint32_t reg;
   };



   struct SR_t {
      struct Bits {
#if defined(STM32F405xx)
         // Bit 0 EOP: End of operation
         volatile bool EOP       :1;
         // Bit 1 OPERR: Operation error
         volatile bool OPERR     :1;
         // Bits 3:2 Reserved, must be kept cleared.
         volatile uint32_t res1  :2;
         // Bit 4 WRPERR: Write protection error
         volatile bool WRPERR    :1;
         // Bit 5 PGAERR: Programming alignment error
         volatile bool PGAERR    :1;
         // Bit 6 PGPERR: Programming parallelism error
         volatile bool PGPERR    :1;
         // Bit 7 PGSERR: Programming sequence error
         volatile bool PGSERR    :1;
         // Bits 15:8 Reserved, must be kept cleared.
         volatile uint32_t res2  :8;
         // Bit 16 BSY: Busy
         volatile bool BSY       :1;
         // Bits 31:17 Reserved, must be kept cleared.
         volatile uint32_t res3  :15;
#elif defined(STM32F030x6)
         // Bit 0 BSY: Busy
         volatile bool BSY       :1;
         // Bit 1 Reserved, must be kept at reset value
         volatile uint32_t res1  :1;
         // Bit 2 PGERR: Programming error
         volatile bool PGERR     :1;
         // Bit 3 Reserved, must be kept at reset value.
         volatile uint32_t res2  :1;
         // Bit 4 WRPRTERR: Write protection error
         volatile bool WRPRTERR  :1;
         // Bit 5 EOP: End of operation
         volatile bool EOP       :1;
         // Bits 31:6 Reserved, must be kept at reset value.
         volatile uint32_t res3  :26;
#endif
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CR_t {
#if defined(STM32F405xx)
      enum Sector { _0 = 0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11 };
      enum ProgSize { x8  = 0b00, x16, x32, x64 };
#endif
      struct Bits {
         // Bit 0 PG: Programming
         volatile bool PG         :1;
         // Bit 1 SER: Sector Erase
         volatile bool SER        :1;
         // Bit 2 MER: Mass Erase
         volatile bool MER        :1;
#if defined(STM32F405xx)
         // Bits 6:3 SNB[3:0]: Sector number
         volatile Sector SNB      :4;
         // Bit 7 Reserved, must be kept cleared.
         volatile uint32_t res1   :1;
         // Bits 9:8 PSIZE[1:0]: Program size
         volatile ProgSize PSIZE  :2;
         // Bits 15:10 Reserved, must be kept cleared.
         volatile uint32_t res2   :6;
         // Bit 16 STRT: Start
         volatile bool STRT       :1;
         // Bits 23:17 Reserved, must be kept cleared.
         volatile uint32_t res3   :7;
         // Bit 24 EOPIE: End of operation interrupt enable
         volatile bool EOPIE      :1;
         // Bit 25 ERRIE: Error interrupt enable
         volatile bool ERRIE      :1;
         // Bits 30:26 Reserved, must be kept cleared.
         volatile uint32_t res4   :5;
         // Bit 31 LOCK: Lock
         volatile bool LOCK       :1;
#elif defined(STM32F030x6)
         // Bit 3 Reserved, must be kept at reset value.
         volatile uint32_t res1   :1;
         // Bit 4 OPTPG: Option byte programming
         volatile bool OPTPG      :1;
         // Bit 5 OPTER: Option byte erase
         volatile bool OPTER      :1;
         // Bit 6 STRT: Start
         volatile bool STRT       :1;
         // Bit 7 LOCK: Lock
         volatile bool LOCK       :1;
         // Bit 8 Reserved, must be kept at reset value.
         volatile uint32_t res2   :1;
         // Bit 9 OPTWRE: Option byte write enable
         volatile bool OPTWRE     :1;
         // Bit 10 ERRIE: Error interrupt enable
         volatile bool ERRIE      :1;
         // Bit 11 Reserved, must be kept at reset value
         volatile uint32_t res3   :1;
         // Bit 12 EOPIE: End of operation interrupt enable
         volatile bool EOPIE      :1;
         // Bit 13 OBL_LAUNCH: Force option byte loading
         volatile bool OBL_LAUNCH :1;
         // Bits 31:14 Reserved, must be kept at reset value.
         volatile uint32_t res4   :16;
#endif
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



#if defined(STM32F405xx)
   struct OPTCR_t {
      volatile uint32_t reg;
   };



   struct OPTCR1_t {
      volatile uint32_t reg;
   };



#elif defined(STM32F030x6)
   struct AR_t {
      volatile uint32_t reg;
   };



   struct RESERVED_t {
      volatile uint32_t reg;
   };



   struct OBR_t {
      volatile uint32_t reg;
   };




   struct WRPR_t {
      volatile uint32_t reg;
   };

#endif
} // namespace



/* STM32F4
typedef struct
{
  __IO uint32_t ACR;      // FLASH access control register,   Address offset: 0x00 
  __IO uint32_t KEYR;     // FLASH key register,              Address offset: 0x04 
  __IO uint32_t OPTKEYR;  // FLASH option key register,       Address offset: 0x08 
  __IO uint32_t SR;       // FLASH status register,           Address offset: 0x0C 
  __IO uint32_t CR;       // FLASH control register,          Address offset: 0x10 
  __IO uint32_t OPTCR;    // FLASH option control register ,  Address offset: 0x14 
  __IO uint32_t OPTCR1;   // FLASH option control register 1, Address offset: 0x18 
} FLASH_TypeDef;
   STM32F0
typedef struct
{
  __IO uint32_t ACR;          // FLASH access control register, Address offset: 0x00
  __IO uint32_t KEYR;         // FLASH key register,            Address offset: 0x04
  __IO uint32_t OPTKEYR;      // FLASH OPT key register,        Address offset: 0x08
  __IO uint32_t SR;           // FLASH status register,         Address offset: 0x0C
  __IO uint32_t CR;           // FLASH control register,        Address offset: 0x10
  __IO uint32_t AR;           // FLASH address register,        Address offset: 0x14
  __IO uint32_t RESERVED;     //  Reserved,                     0x18
  __IO uint32_t OBR;          // FLASH option bytes register,   Address offset: 0x1C
  __IO uint32_t WRPR;         // FLASH option bytes register,   Address offset: 0x20
} FLASH_TypeDef;
*/

//using namespace FLASH_ral;

class FLASH_t : private FLASH_ral::ACR_t,
                private FLASH_ral::KEYR_t,
                private FLASH_ral::OPTKEYR_t,
                private FLASH_ral::SR_t,
                private FLASH_ral::CR_t,
#if defined(STM32F405xx)
                private FLASH_ral::OPTCR_t,
                private FLASH_ral::OPTCR1_t
#elif defined(STM32F030x6)
                private FLASH_ral::AR_t,
                private FLASH_ral::RESERVED_t,
                private FLASH_ral::OBR_t,
                private FLASH_ral::WRPR_t
#endif
{
public:
   void makeDebugVar() { FLASH_ral::ACR_t::bits.res1 = 0; }


   using Latency  = FLASH_ral::ACR_t::Latency;
#if defined(STM32F405xx)
   using Sector   = FLASH_ral::CR_t::Sector;
   using ProgSize = FLASH_ral::CR_t::ProgSize;
#endif


   static inline void SetLatency (Latency L)  { accessContr().reg |= (uint32_t)L << FLASH_ACR_LATENCY_Pos; }
   static inline void Lock()                  { conf().reg |= FLASH_CR_LOCK_Msk; }
   static inline bool IsLock()                { return (conf().reg & FLASH_CR_LOCK_Msk) != 0; }
   static inline void SetProgMode()           { conf().reg |= FLASH_CR_PG_Msk; }
   static inline void EndOfProgInterruptEn()  { conf().reg |= FLASH_CR_EOPIE_Msk; }
   static inline bool EndOfProg()             { return (status().reg & FLASH_SR_EOP_Msk) != 0; }
   static inline void ClearEndOfProgFlag()    { status().reg |= FLASH_SR_EOP_Msk; }
   static inline bool Busy()                  { return (status().reg & FLASH_SR_BSY_Msk) != 0; }


   static inline void Unlock ()
   {
      if ( IsLock() ) {
         key().reg = Key1;
         key().reg = Key2;
      }
   }


// для F4 номер сектора, для F0 адрес сектора (страницы)
   template <uint32_t sector> static inline void StartEraseSector ()
   {
#if defined(STM32F405xx)
      conf().reg |= FLASH_CR_SER_Msk;
      conf().bits.SNB = (Sector)sector;
#elif defined(STM32F030x6)
      conf().reg |= FLASH_CR_PER_Msk;
      address().reg = sector;
#endif
      conf().reg |= FLASH_CR_STRT_Msk;
   }


#if defined(STM32F405xx)
   static inline void SetProgSize(ProgSize s) { conf().bits.PSIZE = s; }
#endif



protected:
   static volatile FLASH_ral::ACR_t  &accessContr() { return (FLASH_ral::ACR_t &)  FLASH->ACR;  }
   static volatile FLASH_ral::KEYR_t &key()         { return (FLASH_ral::KEYR_t &) FLASH->KEYR; }
   static volatile FLASH_ral::CR_t   &conf()        { return (FLASH_ral::CR_t &)   FLASH->CR;   }
   static volatile FLASH_ral::SR_t   &status()      { return (FLASH_ral::SR_t &)   FLASH->SR;   }
#if defined(STM32F030x6)
   static volatile FLASH_ral::AR_t   &address()     { return (FLASH_ral::AR_t &)   FLASH->AR;   }
#endif
   static const uint32_t Key1 = 0x45670123;
   static const uint32_t Key2 = 0xCDEF89AB;
};


#pragma once

#include "registr.h"


namespace FLASH_detail {

struct ACRbits {
   enum Latency { _0 = 0, _1, _2, _3,_4, _5, _6, _7 };
   Latency  LATENCY :3; // Bits 2:0 LATENCY[2:0]: Latency
   uint32_t res1    :5; // Bits 7:3 Reserved, must be kept cleared.
   bool     PRFTEN  :1; // Bit 8 PRFTEN: Prefetch enable
   bool     ICEN    :1; // Bit 9 ICEN: Instruction cache enable
   bool     DCEN    :1; // Bit 10 DCEN: Data cache enable
   bool     ICRST   :1; // Bit 11 ICRST: Instruction cache reset
   bool     DCRST   :1; // Bit 12 DCRST: Data cache reset
   uint32_t res2    :19; // Bits 31:13 Reserved, must be kept cleared.
};

struct SRbits {
   bool     EOP    :1; // Bit 0 EOP: End of operation
   bool     OPERR  :1; // Bit 1 OPERR: Operation error
   uint32_t res1   :2; // Bits 3:2 Reserved, must be kept cleared.
   bool     WRPERR :1; // Bit 4 WRPERR: Write protection error
   bool     PGAERR :1; // Bit 5 PGAERR: Programming alignment error
   bool     PGPERR :1; // Bit 6 PGPERR: Programming parallelism error
   bool     PGSERR :1; // Bit 7 PGSERR: Programming sequence error
   uint32_t res2   :8; // Bits 15:8 Reserved, must be kept cleared.
   bool     BSY    :1; // Bit 16 BSY: Busy
   uint32_t res3   :15; // Bits 31:17 Reserved, must be kept cleared.
};



struct CRbits {
   enum Sector { _0 = 0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11 };
   enum ProgSize { x8  = 0b00, x16, x32, x64 };
   bool     PG    :1; // Bit 0 PG: Programming
   bool     SER   :1; // Bit 1 SER: Sector Erase
   bool     MER   :1; // Bit 2 MER: Mass Erase
   Sector   SNB   :4; // Bits 6:3 SNB[3:0]: Sector number
   uint32_t res1  :1; // Bit 7 Reserved, must be kept cleared.
   ProgSize PSIZE :2; // Bits 9:8 PSIZE[1:0]: Program size
   uint32_t res2  :6; // Bits 15:10 Reserved, must be kept cleared.
   bool     STRT  :1; // Bit 16 STRT: Start
   uint32_t res3  :7; // Bits 23:17 Reserved, must be kept cleared.
   bool     EOPIE :1; // Bit 24 EOPIE: End of operation interrupt enable
   bool     ERRIE :1; // Bit 25 ERRIE: Error interrupt enable
   uint32_t res4  :5; // Bits 30:26 Reserved, must be kept cleared.
   bool LOCK      :1; // Bit 31 LOCK: Lock

};

} // namespace FLASH_detail {



struct FLASH_t {

   __IO FLASH_detail::ACRbits ACR;     // access control register,   offset: 0x00
   __IO uint32_t              KEYR;    // key register,              offset: 0x04
   __IO uint32_t              OPTKEYR; // option key register,       offset: 0x08
   __IO FLASH_detail::SRbits  SR;      // status register,           offset: 0x0C
   __IO FLASH_detail::CRbits  CR;      // control register,          offset: 0x10
   __IO uint32_t              OPTCR;   // option control register ,  offset: 0x14
   __IO uint32_t              OPTCR1;  // option control register 1, offset: 0x18
   FLASH_t() = delete;
   static constexpr uint32_t Base = FLASH_R_BASE; 
};


template<class Pointer = Pointer<FLASH_t>>
struct template_FLASH
{
   using periph_type = FLASH_t;
   using CMSIS_type  = std::remove_pointer_t<decltype(FLASH)>;
   using this_type   = template_FLASH<Pointer>;
   using Latency     = FLASH_detail::ACRbits::Latency;
   using Sector      = FLASH_detail::CRbits::Sector;
   using ProgSize    = FLASH_detail::CRbits::ProgSize;

   static void set (Latency v)            { Pointer::get()->ACR.LATENCY = v;    }
   static void lock()                     { Pointer::get()->CR.LOCK     = true; }
   static bool is_lock()                  { return Pointer::get()->CR.LOCK;     }
   static void unlock();
   static void setProgMode()              { Pointer::get()->CR.PG       = true; }
   static bool is_endOfProg()             { return Pointer::get()->SR.EOP;      }
   static void clearEndOfProgFlag()       { Pointer::get()->SR.EOP      = true; }
   static bool is_busy()                  { return Pointer::get()->SR.BSY;      }
   template<ProgSize v> static void set() { Pointer::get()->CR.PSIZE    = v;    }
   // static void endOfProgInterruptEn();

   template <Sector> static void startErase();

   template<Sector> static constexpr uint32_t address();
   template<Sector> static constexpr int32_t  size();
   template<Sector> static constexpr Sector   next();
};


#define CMSIS_FLASH FLASH
#undef FLASH
using FLASH = template_FLASH<>;

#include "flash_periph_src.h"


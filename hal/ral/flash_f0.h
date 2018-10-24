#pragma once

#include "registr.h"


namespace FLASH_detail {

struct ACRbits {
   enum Latency { _0 = 0, _1 };
   Latency  LATENCY :3; // Bits 2:0 LATENCY[2:0]: Latency
   uint32_t res1    :1; // Bit 3 Reserved, must be kept at reset value.
   bool     PRFTBE  :1; // Bit 4 PRFTBE: Prefetch buffer enable
   bool     PRFTBS  :1; // Bit 5 PRFTBS: Prefetch buffer status
   uint32_t res2    :26; // Bits 31:6 Reserved, must be kept at reset value.
};

struct SRbits {
   bool     BSY      :1; // Bit 0 BSY: Busy
   uint32_t res1     :1; // Bit 1 Reserved, must be kept at reset value
   bool     PGERR    :1; // Bit 2 PGERR: Programming error
   uint32_t res2     :1; // Bit 3 Reserved, must be kept at reset value.
   bool     WRPRTERR :1; // Bit 4 WRPRTERR: Write protection error
   bool     EOP      :1; // Bit 5 EOP: End of operation
   uint32_t res3     :26;
};

struct CRbits {
   bool     PG         :1; // Bit 0 PG: Programming
   bool     PER        :1; // Bit 1 SER: Sector Erase
   bool     MER        :1; // Bit 2 MER: Mass Erase
   uint32_t res1       :1; // Bit 3 Reserved, must be kept at reset value.
   bool     OPTPG      :1; // Bit 4 OPTPG: Option byte programming
   bool     OPTER      :1; // Bit 5 OPTER: Option byte erase
   bool     STRT       :1; // Bit 6 STRT: Start
   bool     LOCK       :1; // Bit 7 LOCK: Lock
   uint32_t res2       :1; // Bit 8 Reserved, must be kept at reset value.
   bool     OPTWRE     :1; // Bit 9 OPTWRE: Option byte write enable
   bool     ERRIE      :1; // Bit 10 ERRIE: Error interrupt enable
   uint32_t res3       :1; // Bit 11 Reserved, must be kept at reset value
   bool     EOPIE      :1; // Bit 12 EOPIE: End of operation interrupt enable
   bool     OBL_LAUNCH :1; // Bit 13 OBL_LAUNCH: Force option byte loading
   uint32_t res4       :16; // Bits 31:14 Reserved, must be kept at reset value.
};

} // namespace FLASH_detail {

struct FLASH_t {
   __IO FLASH_detail::ACRbits  ACR;     // access control register, offset: 0x00
   __IO uint32_t               KEYR;    // key register,            offset: 0x04
   __IO uint32_t               OPTKEYR; // OPT key register,        offset: 0x08
   __IO FLASH_detail::SRbits   SR;      // status register,         offset: 0x0C
   __IO FLASH_detail::CRbits   CR;      // control register,        offset: 0x10
   __IO uint32_t               AR;      // address register,        offset: 0x14
        uint32_t               RES;     // Reserved,                        0x18
   __IO uint32_t               OBR;     // option bytes register,   offset: 0x1C
   __IO uint32_t               WRPR;    // option bytes register,   offset: 0x20
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
   /// фактически это страница, чтобы было единообразно с F4
   enum Sector { _0,_1 ,_2 ,_3 ,_4 ,_5 ,_6 ,_7 ,_8 ,_9 ,
                _10,_11,_12,_13,_14,_15,_16,_17,_18,_19,
                _20,_21,_22,_23,_24,_25,_26,_27,_28,_29,
                _30,_31 };

   static void set (Latency v)      { Pointer::get()->ACR.LATENCY = v;    }
   static void lock()               { Pointer::get()->CR.LOCK     = true; }
   static bool is_lock()            { return Pointer::get()->CR.LOCK;     }
   static void unlock();
   static void setProgMode()        { Pointer::get()->CR.PG       = true; }
   static bool is_endOfProg()       { return Pointer::get()->SR.EOP;      }
   static void clearEndOfProgFlag() { Pointer::get()->SR.EOP      = true; }
   static bool is_busy()            { return Pointer::get()->SR.BSY;      }
   // static void endOfProgInterruptEn();

   /// параметр шаблона - адрес сектора (страницы)
   template <Sector> static void startErase();

   template<Sector> static constexpr size_t address();
   template<Sector> static constexpr int32_t  size();
};


#define CMSIS_FLASH FLASH
#undef FLASH
using FLASH = template_FLASH<>;

#include "flash_periph_src.h"

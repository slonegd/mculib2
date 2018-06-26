#pragma once

#include "registr.h"


namespace FLASH_ral {

enum Latency { _0 = 0, _1 };

struct ACRbits {
   Latency  LATENCY :3; // Bits 2:0 LATENCY[2:0]: Latency
   uint32_t res1    :1; // Bit 3 Reserved, must be kept at reset value.
   bool     PRFTBE  :1; // Bit 4 PRFTBE: Prefetch buffer enable
   bool     PRFTBS  :1; // Bit 5 PRFTBS: Prefetch buffer status
   uint32_t res2    :26; // Bits 31:6 Reserved, must be kept at reset value.
};

struct ACRposition {
   enum { LATENCY = 0, PRFTBE = 4, PRFTBS };
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

struct SRposition {
   enum { BSY = 0, PGERR = 2, WRPRTERR = 4, EOP };
};

struct CRbits {
   bool     PG         :1; // Bit 0 PG: Programming
   bool     SER        :1; // Bit 1 SER: Sector Erase
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

struct CRposition {
   enum { PG = 0, SER, MER, OPTPG = 4, OPTER, STRT, LOCK, OPTWRE = 9, ERRIE, EOPIE = 12, OBL_LAUNCH };
};


struct ACR_t     : BitsRegistr<ACRbits>, Offset_t<0x00>, ACRposition {};
struct KEYR_t    : DataRegistr         , Offset_t<0x04>              {};
struct OPTKEYR_t : DataRegistr         , Offset_t<0x08>              {};
struct SR_t      : BitsRegistr<SRbits> , Offset_t<0x0C>, SRposition  {};
struct CR_t      : BitsRegistr<CRbits> , Offset_t<0x10>, CRposition  {};
struct AR_t      : DataRegistr         , Offset_t<0x14>              {};
struct OBR_t     : DataRegistr         , Offset_t<0x1C>              {};
struct WRPR_t    : DataRegistr         , Offset_t<0x20>              {};

} // namespace FLASH_ral {








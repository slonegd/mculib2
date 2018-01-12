/**
 * RAL над регистрами FLASH
 */

#pragma once

#include <stdint.h>
#include "stm32f4xx.h"

namespace FLASH_ral {

    struct ACR_t {
        enum Latency {
            latency_0 = 0,
            latency_1,
            latency_2,
            latency_3,
            latency_4,
            latency_5,
            latency_6,
            latency_7
        };
        struct Bits_t {
            // Bits 2:0 LATENCY[2:0]: Latency
            volatile Latency LATENCY  :3;
            // Bits 7:3 Reserved, must be kept cleared.
            volatile uint32_t dcb1      :5;
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
            volatile uint32_t dcb2      :19;
        };
        volatile Bits_t bits;
    };

    struct KEYR_t {
        volatile uint32_t reg;
    };

    struct OPTKEYR_t {
        volatile uint32_t reg;
    };

    struct SR_t {
        struct Bits {
            // Bit 0 EOP: End of operation
            volatile bool EOP       :1;
            // Bit 1 OPERR: Operation error
            volatile bool OPERR     :1;
            // Bits 3:2 Reserved, must be kept cleared.
            volatile uint32_t dcb1  :2;
            // Bit 4 WRPERR: Write protection error
            volatile bool WRPERR    :1;
            // Bit 5 PGAERR: Programming alignment error
            volatile bool PGAERR    :1;
            // Bit 6 PGPERR: Programming parallelism error
            volatile bool PGPERR    :1;
            // Bit 7 PGSERR: Programming sequence error
            volatile bool PGSERR    :1;
            // Bits 15:8 Reserved, must be kept cleared.
            volatile uint32_t dcb2  :8;
            // Bit 16 BSY: Busy
            volatile bool BSY       :1;
            // Bits 31:17 Reserved, must be kept cleared.
            volatile uint32_t dcb3  :15;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct CR_t {
        enum Sectors {
            sector0 = 0,
            sector1 = 1,
            sector2, sector3, sector4, sector5,
            sector6, sector7, sector8, sector9,
            sector10, sector11
        };
        enum ProgSize {
            x8  = 0b00,
            x16, x32, x64
        };
        struct Bits {
            // Bit 0 PG: Programming
            volatile bool PG        :1;
            // Bit 1 SER: Sector Erase
            volatile bool SER       :1;
            // Bit 2 MER: Mass Erase
            volatile bool MER       :1;
            // Bits 6:3 SNB[3:0]: Sector number
            volatile Sectors SNB    :4;
            // Bit 7 Reserved, must be kept cleared.
            volatile uint32_t dcb1  :1;
            // Bits 9:8 PSIZE[1:0]: Program size
            volatile ProgSize PSIZE :2;
            // Bits 15:10 Reserved, must be kept cleared.
            volatile uint32_t dcb2  :6;
            // Bit 16 STRT: Start
            volatile bool STRT      :1;
            // Bits 23:17 Reserved, must be kept cleared.
            volatile uint32_t dcb3  :7;
            // Bit 24 EOPIE: End of operation interrupt enable
            volatile bool EOPIE     :1;
            // Bit 25 ERRIE: Error interrupt enable
            volatile bool ERRIE     :1;
            // Bits 30:26 Reserved, must be kept cleared.
            volatile uint32_t dcb4  :5;
            // Bit 31 LOCK: Lock
            volatile bool LOCK      :1;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
        
    };

    struct OPTCR_t {
        volatile uint32_t reg;
    };

    struct OPTCR1_t {
        volatile uint32_t reg;
    };
}
/*
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
*/

using namespace FLASH_ral;

class FLASH_t : public ACR_t,
                public KEYR_t,
                public OPTKEYR_t,
                public FLASH_ral::SR_t,
                public FLASH_ral::CR_t,
                public OPTCR_t,
                public OPTCR1_t
// остальные регистры пока не нужны
{
public:
    using Latency = ACR_t::Latency;
    using Sectors = FLASH_ral::CR_t::Sectors;
    using ProgSize = FLASH_ral::CR_t::ProgSize;

    static volatile FLASH_ral::ACR_t  &accessContr() { return (FLASH_ral::ACR_t &)  FLASH->ACR;  }
    static volatile FLASH_ral::KEYR_t &key()         { return (FLASH_ral::KEYR_t &) FLASH->KEYR; }
    static volatile FLASH_ral::CR_t   &conf()        { return (FLASH_ral::CR_t &)   FLASH->CR;   }
    static volatile FLASH_ral::SR_t   &status()      { return (FLASH_ral::SR_t &)   FLASH->SR;   }
    static const uint32_t Key1 = 0x45670123;
    static const uint32_t Key2 = 0xCDEF89AB;

    static inline void SetLatency (Latency L)  { accessContr().bits.LATENCY = L; }
    static inline void Lock ()                 { conf().bits.LOCK = true; }
    static inline void SetProgMode()           { conf().bits.PG = true; }
    static inline void SetProgSize(ProgSize s) { conf().bits.PSIZE = s; }
    static inline void EndOfProgInterruptEn()  { conf().bits.EOPIE = true; }
    static inline bool EndOfProg()             { return status().bits.EOP; }
    static inline void ClearEndOfProgFlag()    { status().bits.EOP = true; }
    static inline bool Busy()                  { return status().bits.BSY; }
    static inline void Unlock ()
    {
        if ( conf().bits.LOCK ) {
            key().reg = Key1;
            key().reg = Key2;
        }
    }
    template <Sectors s>
    static inline void StartEraseSector ()
    {
        conf().bits.SER = true;
        conf().bits.SNB = s;
        conf().bits.STRT = true;
    }

};


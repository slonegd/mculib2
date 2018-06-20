#pragma once

#if defined(STM32F030x6)
#include "FLASH_F0_bits.h"
#elif defined(STM32F405xx)
#include "FLASH_F4_bits.h"
#endif

#undef FLASH
class FLASH
{
public:
   using Latency  = FLASH_ral::Latency;
#if defined(STM32F405xx)
   using Sector   = FLASH_ral::Sector;
   using ProgSize = FLASH_ral::ProgSize;
#endif

   static constexpr uint32_t Base = FLASH_R_BASE;

   FLASH() = delete;
   static FLASH* create() { return reinterpret_cast<FLASH*>(Base); } 
   void doSome() { accessContr().bits.res1 = 0; }

   static void setLatency (Latency);
   static void lock();
   static void unlock();
   static bool isLock();
   static void setProgMode();
   static void endOfProgInterruptEn();
   static bool isEndOfProg();
   static void clearEndOfProgFlag();
   static bool isBusy();
   /// для F4 номер сектора, для F0 адрес сектора (страницы)
   template <uint32_t> static void startEraseSector();
#if defined(STM32F405xx)
   static void setProgSize(ProgSize);
#endif




protected:
#define MAKE_REG(Type, name) static __IO Type& name() { return *(Type *)(Base + Type::Offset); }
   MAKE_REG(FLASH_ral::ACR_t , accessContr)
   MAKE_REG(FLASH_ral::KEYR_t, key        )
   MAKE_REG(FLASH_ral::CR_t  , conf       )
   MAKE_REG(FLASH_ral::SR_t  , status     )
#if defined(STM32F030x6)
   MAKE_REG(FLASH_ral::AR_t  , address    )
#endif
#undef MAKE_REG




private:
   FLASH_ral::ACR_t     ACR;     // access control register
   FLASH_ral::KEYR_t    KEYR;    // key register
   FLASH_ral::OPTKEYR_t OPTKEYR; // OPT key register
   FLASH_ral::SR_t      SR;      // status register
   FLASH_ral::CR_t      CR;      // control register
#if defined(STM32F405xx)
   FLASH_ral::OPTCR_t   OPTCR;   // option control register
   FLASH_ral::OPTCR1_t  OPTCR1;  // option control register 1
#elif defined(STM32F030x6)
   FLASH_ral::AR_t      AR;      // address register
   Reserve_t<1>         reserve1;
   FLASH_ral::OBR_t     OBR;     // option bytes register
   FLASH_ral::WRPR_t    WRPR;    // write protection register
#endif
};





#include "FLASH_src.h"
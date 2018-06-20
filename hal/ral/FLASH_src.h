#pragma once

#include <stddef.h>



#if defined(STM32F405xx) || defined(STM32F030x6)

void FLASH::setLatency (Latency val)
{
   auto tmp = accessContr().reg;
   tmp &= ~_3BIT_TO_MASK(accessContr(), LATENCY);
   tmp |= VAL_TO_MASK(accessContr(), LATENCY, val);
   accessContr().reg = tmp;
}


void FLASH::lock()
{
   SET (conf(), LOCK);
}


void FLASH::unlock()
{
   static constexpr uint32_t Key1 = 0x45670123;
   static constexpr uint32_t Key2 = 0xCDEF89AB;
   if ( isLock() ) {
      key().reg = Key1;
      key().reg = Key2;
   }
}


bool FLASH::isLock()
{
   return IS_SET(conf(), LOCK);
}


void FLASH::setProgMode()
{
   SET (conf(), PG);
}


void FLASH::endOfProgInterruptEn()
{
   SET (conf(), EOPIE);
}


bool FLASH::isEndOfProg()
{
   return IS_SET(status(), EOP);
}


void FLASH::clearEndOfProgFlag()
{
   SET (status(), EOP);
}


bool FLASH::isBusy()
{
   return IS_SET(status(), BSY);
}


#endif
#if defined(STM32F405xx)

template <uint32_t sector>
void FLASH::startEraseSector()
{
   SET (conf(), SER);
   auto tmp = conf().reg;
   tmp &= ~_4BIT_TO_MASK(conf(), SNB);
   tmp |= VAL_TO_MASK(conf(), SNB, sector);
   conf().reg = tmp;
   SET (conf(), STRT);
}


void FLASH::setProgSize (ProgSize val)
{
   auto tmp = conf().reg;
   tmp &= ~_2BIT_TO_MASK(conf(), PSIZE);
   tmp |= VAL_TO_MASK(conf(), PSIZE, val);
   conf().reg = tmp;
}


#elif defined(STM32F030x6)

template <uint32_t adr>
void FLASH::startEraseSector()
{
   SET (conf(), SER);
   address().reg = adr;
   SET (conf(), STRT);
}

#endif
#define STM32F030x6

#include "RCC.h"
#include "flash_periph.h"
#include <iostream>
#include <type_traits>
#include <thread>

struct MockPointer
{
   static FLASH::CMSIS_type* p;
   static auto get() { return reinterpret_cast<FLASH::periph_type*>(p); }
};
FLASH::CMSIS_type mock;
FLASH::CMSIS_type* MockPointer::p = &mock;
using TFLASH = template_FLASH<MockPointer>;

// тесты возвращают true, если прошли
bool setLatency()
{
   bool good {true};

   mock.ACR = 0;
   TFLASH::set (TFLASH::Latency::_1);
   good &=     (mock.ACR & FLASH_ACR_LATENCY_Msk);

   TFLASH::set (TFLASH::Latency::_0);
   good &= not (mock.ACR & FLASH_ACR_LATENCY_Msk);

   return good;
}

bool lock()
{
   mock.CR = 0;
   TFLASH::lock();
   return mock.CR & FLASH_CR_LOCK_Msk;
}

bool is_lock()
{
   bool good {true};

   mock.CR = 0;
   good &= not TFLASH::is_lock();
   mock.CR |= FLASH_CR_LOCK_Msk;
   good &=     TFLASH::is_lock();

   return good;
}

bool unlock()
{
   mock.KEYR = 0;
   mock.CR |= FLASH_CR_LOCK_Msk;
   std::thread {TFLASH::unlock}.detach();
   while (mock.KEYR != FLASH_KEY1) {}
   while (mock.KEYR != FLASH_KEY2) {}
   return true;
}

bool setProgMode()
{
   mock.CR = 0;
   TFLASH::setProgMode();
   return mock.CR & FLASH_CR_PG_Msk;
}

bool is_endOfProg()
{
   bool good {true};

   mock.SR = 0;
   good &= not TFLASH::is_endOfProg();
   mock.SR |= FLASH_SR_EOP_Msk;
   good &=     TFLASH::is_endOfProg();

   return good;
}

bool clearEndOfProgFlag()
{
   mock.SR = 0;
   TFLASH::clearEndOfProgFlag();
   return mock.SR & FLASH_SR_EOP_Msk;
}

bool is_busy()
{
   bool good {true};

   mock.SR = 0;
   good &= not TFLASH::is_busy();
   mock.SR |= FLASH_SR_BSY_Msk;
   good &=     TFLASH::is_busy();

   return good;
}

bool startEraseSector()
{
   mock.CR = 0;
   mock.AR = 0;
   std::thread {TFLASH::startErase<TFLASH::Sector::_0>}.detach();
   while ( not (mock.CR & FLASH_CR_PER_Msk) ) { }
   while ( mock.AR != 0x08000000 ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR = 0;
   mock.AR = 0;
   std::thread {TFLASH::startErase<TFLASH::Sector::_1>}.detach();
   while ( not (mock.CR & FLASH_CR_PER_Msk) ) { }
   while ( mock.AR != 0x08000400 ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR = 0;
   mock.AR = 0;
   std::thread {TFLASH::startErase<TFLASH::Sector::_2>}.detach();
   while ( not (mock.CR & FLASH_CR_PER_Msk) ) { }
   while ( mock.AR != 0x08000800 ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR = 0;
   mock.AR = 0;
   std::thread {TFLASH::startErase<TFLASH::Sector::_30>}.detach();
   while ( not (mock.CR & FLASH_CR_PER_Msk) ) { }
   while ( mock.AR != 0x08007800 ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR = 0;
   mock.AR = 0;
   std::thread {TFLASH::startErase<TFLASH::Sector::_31>}.detach();
   while ( not (mock.CR & FLASH_CR_PER_Msk) ) { }
   while ( mock.AR != 0x08007C00 ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   return true;
}

bool address()
{
   return TFLASH::address<TFLASH::Sector::_0>()  == 0x08000000
      and TFLASH::address<TFLASH::Sector::_1>()  == 0x08000400
      and TFLASH::address<TFLASH::Sector::_2>()  == 0x08000800
      and TFLASH::address<TFLASH::Sector::_3>()  == 0x08000C00
      and TFLASH::address<TFLASH::Sector::_4>()  == 0x08001000
      and TFLASH::address<TFLASH::Sector::_5>()  == 0x08001400
      and TFLASH::address<TFLASH::Sector::_6>()  == 0x08001800
      and TFLASH::address<TFLASH::Sector::_7>()  == 0x08001C00
      and TFLASH::address<TFLASH::Sector::_8>()  == 0x08002000
      and TFLASH::address<TFLASH::Sector::_9>()  == 0x08002400
      and TFLASH::address<TFLASH::Sector::_10>() == 0x08002800
      and TFLASH::address<TFLASH::Sector::_11>() == 0x08002C00
      and TFLASH::address<TFLASH::Sector::_12>() == 0x08003000
      and TFLASH::address<TFLASH::Sector::_13>() == 0x08003400
      and TFLASH::address<TFLASH::Sector::_14>() == 0x08003800
      and TFLASH::address<TFLASH::Sector::_15>() == 0x08003C00
      and TFLASH::address<TFLASH::Sector::_16>() == 0x08004000
      and TFLASH::address<TFLASH::Sector::_17>() == 0x08004400
      and TFLASH::address<TFLASH::Sector::_18>() == 0x08004800
      and TFLASH::address<TFLASH::Sector::_19>() == 0x08004C00
      and TFLASH::address<TFLASH::Sector::_20>() == 0x08005000
      and TFLASH::address<TFLASH::Sector::_21>() == 0x08005400
      and TFLASH::address<TFLASH::Sector::_22>() == 0x08005800
      and TFLASH::address<TFLASH::Sector::_23>() == 0x08005C00
      and TFLASH::address<TFLASH::Sector::_24>() == 0x08006000
      and TFLASH::address<TFLASH::Sector::_25>() == 0x08006400
      and TFLASH::address<TFLASH::Sector::_26>() == 0x08006800
      and TFLASH::address<TFLASH::Sector::_27>() == 0x08006C00
      and TFLASH::address<TFLASH::Sector::_28>() == 0x08007000
      and TFLASH::address<TFLASH::Sector::_29>() == 0x08007400
      and TFLASH::address<TFLASH::Sector::_30>() == 0x08007800
      and TFLASH::address<TFLASH::Sector::_31>() == 0x08007C00;
}

bool size()
{
   return TFLASH::size<TFLASH::Sector::_0>()  == 1024
      and TFLASH::size<TFLASH::Sector::_1>()  == 1024
// ...
      and TFLASH::size<TFLASH::Sector::_30>() == 1024
      and TFLASH::size<TFLASH::Sector::_31>() == 1024;
}







int main()
{
   std::cout << '\n'
             << "Тесты класса FLASH для STM32F0:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

   test ("FLASH::setLatency            ", setLatency);
   test ("FLASH::lock                  ", lock);
   test ("FLASH::is_lock               ", is_lock);
   test ("FLASH::unlock                ", unlock);
   test ("FLASH::setProgMode           ", setProgMode);
   test ("FLASH::is_endOfProg          ", is_endOfProg);
   test ("FLASH::clearEndOfProgFlag    ", clearEndOfProgFlag);
   test ("FLASH::is_busy               ", is_busy);
   test ("FLASH::startEraseSector      ", startEraseSector);
   test ("FLASH::address               ", address);
   test ("FLASH::size                  ", size);

   std::cout << std::endl;
}
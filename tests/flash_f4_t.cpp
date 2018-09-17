#define STM32F405xx

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
   TFLASH::set (TFLASH::Latency::_7);
   good &= (mock.ACR == FLASH_ACR_LATENCY_7WS);

   TFLASH::set (TFLASH::Latency::_6);
   good &= (mock.ACR == FLASH_ACR_LATENCY_6WS);

   TFLASH::set (TFLASH::Latency::_5);
   good &= (mock.ACR == FLASH_ACR_LATENCY_5WS);

   TFLASH::set (TFLASH::Latency::_4);
   good &= (mock.ACR == FLASH_ACR_LATENCY_4WS);

   TFLASH::set (TFLASH::Latency::_3);
   good &= (mock.ACR == FLASH_ACR_LATENCY_3WS);

   TFLASH::set (TFLASH::Latency::_2);
   good &= (mock.ACR == FLASH_ACR_LATENCY_2WS);

   TFLASH::set (TFLASH::Latency::_1);
   good &= (mock.ACR == FLASH_ACR_LATENCY_1WS);

   TFLASH::set (TFLASH::Latency::_0);
   good &= (mock.ACR == FLASH_ACR_LATENCY_0WS);

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
   while (mock.KEYR != 0x45670123) {}
   while (mock.KEYR != 0xCDEF89AB) {}
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

bool setProgSize()
{
   bool good {true};

   mock.CR = 0;
   TFLASH::set<TFLASH::ProgSize::x64>();
   good &=     (mock.CR & FLASH_CR_PSIZE_0)
       and     (mock.CR & FLASH_CR_PSIZE_1);

   TFLASH::set<TFLASH::ProgSize::x32>();
   good &= not (mock.CR & FLASH_CR_PSIZE_0)
       and     (mock.CR & FLASH_CR_PSIZE_1);

   TFLASH::set<TFLASH::ProgSize::x16>();
   good &=     (mock.CR & FLASH_CR_PSIZE_0)
       and not (mock.CR & FLASH_CR_PSIZE_1);

   TFLASH::set<TFLASH::ProgSize::x8>();
   good &= not (mock.CR & FLASH_CR_PSIZE_0)
       and not (mock.CR & FLASH_CR_PSIZE_1);
   
   return good;
}


bool startEraseSector()
{
   mock.CR = 0;

   std::thread {TFLASH::startErase<TFLASH::Sector::_11>}.detach();
   while ( not (mock.CR & FLASH_CR_SER_Msk) ) { }

   while ( not (       (mock.CR & FLASH_CR_SNB_0)
               and     (mock.CR & FLASH_CR_SNB_1)
               and not (mock.CR & FLASH_CR_SNB_2)
               and     (mock.CR & FLASH_CR_SNB_3)
           )
   ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR &= ~(FLASH_CR_SER_Msk | FLASH_CR_STRT_Msk);

   std::thread {TFLASH::startErase<TFLASH::Sector::_7>}.detach();
   while ( not (mock.CR & FLASH_CR_SER_Msk) ) { }

   while ( not (       (mock.CR & FLASH_CR_SNB_0)
               and     (mock.CR & FLASH_CR_SNB_1)
               and     (mock.CR & FLASH_CR_SNB_2)
               and not (mock.CR & FLASH_CR_SNB_3)
           )
   ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }

   mock.CR &= ~(FLASH_CR_SER_Msk | FLASH_CR_STRT_Msk);

   std::thread {TFLASH::startErase<TFLASH::Sector::_0>}.detach();
   while ( not (mock.CR & FLASH_CR_SER_Msk) ) { }

   while ( not (   not (mock.CR & FLASH_CR_SNB_0)
               and not (mock.CR & FLASH_CR_SNB_1)
               and not (mock.CR & FLASH_CR_SNB_2)
               and not (mock.CR & FLASH_CR_SNB_3)
           )
   ) { }
   while ( not (mock.CR & FLASH_CR_STRT_Msk) ) { }


   return true;
}

static_assert (TFLASH::address<TFLASH::Sector::_0>()  == 0x08000000);
static_assert (TFLASH::address<TFLASH::Sector::_1>()  == 0x08004000);
static_assert (TFLASH::address<TFLASH::Sector::_2>()  == 0x08008000);
static_assert (TFLASH::address<TFLASH::Sector::_3>()  == 0x0800C000);
static_assert (TFLASH::address<TFLASH::Sector::_4>()  == 0x08010000);
static_assert (TFLASH::address<TFLASH::Sector::_5>()  == 0x08020000);
static_assert (TFLASH::address<TFLASH::Sector::_6>()  == 0x08040000);
static_assert (TFLASH::address<TFLASH::Sector::_7>()  == 0x08060000);
static_assert (TFLASH::address<TFLASH::Sector::_8>()  == 0x08080000);
static_assert (TFLASH::address<TFLASH::Sector::_9>()  == 0x080A0000);
static_assert (TFLASH::address<TFLASH::Sector::_10>() == 0x080C0000);
static_assert (TFLASH::address<TFLASH::Sector::_11>() == 0x080E0000);

static_assert (TFLASH::size<TFLASH::Sector::_0>()  ==  16 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_1>()  ==  16 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_2>()  ==  16 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_3>()  ==  16 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_4>()  ==  64 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_5>()  == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_6>()  == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_7>()  == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_8>()  == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_9>()  == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_10>() == 128 * 1024);
static_assert (TFLASH::size<TFLASH::Sector::_11>() == 128 * 1024);


int main()
{
   std::cout << '\n'
             << "Тесты класса FLASH для STM32F4:" << std::endl;

   // \033[32mТЕКСТ\033[0m - для цвета
   std::cout << "FLASH::setLatency            " << (setLatency()            ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::lock                  " << (lock()                  ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::is_lock               " << (is_lock()               ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::unlock                " << (unlock()                ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::setProgMode           " << (setProgMode()           ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::is_endOfProg          " << (is_endOfProg()          ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::clearEndOfProgFlag    " << (clearEndOfProgFlag()    ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::is_busy               " << (is_busy()               ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::setProgSize           " << (setProgSize()           ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "FLASH::startEraseSector      " << (startEraseSector()      ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << std::endl;
}

// для продолжение надо SectorSize выделить

#define STM32F405xx

#include "flash.h"
#include <iostream>

auto constexpr size_ {10};
static uint8_t sector0[size_];
void errase()
{
   std::fill (std::begin(sector0), std::end(sector0), 0xFF);
}

bool lock_ {true};
auto eop_count {0};

struct FlashMock {
   enum Sector { _0 };
   enum ProgSize { x16 };
   
   template<Sector> static size_t address() { return reinterpret_cast<size_t>(sector0); }
   template<Sector> static constexpr int32_t size() { return size_; }
   static void lock() { lock_ = true; }
   static bool is_empty() { return false; }
   static bool is_busy() { return false; }
   static bool is_lock() { return lock_; }
   static void unlock() { lock_ = false; }
   static void setProgMode() {}
   template<ProgSize> static void set() {}
   static bool is_endOfProg() { return not ((eop_count +=1) %= 5); }
   static void clearEndOfProgFlag() {}
   template<Sector> static void startErase() {}
};

struct FlashData {
   uint16_t d1 {1};
   uint16_t d2 {2};
};
using Flash_t = Flash_impl<FlashData, FlashMock, FlashMock::Sector::_0>;


bool ctor()
{
   errase();
   Flash_t flash { FlashData{} };
   auto qty {100};
   while (qty--)
      tickUpdater.notify();
   return flash.d1 == 1 and flash.d2 == 2
      and sector0[0] == 0 and sector0[1] == 1
      and sector0[2] == 1 and sector0[3] == 0
      and sector0[4] == 2 and sector0[5] == 2
      and sector0[6] == 1 and sector0[7] == 0;
}

bool change()
{
   // errase();
   Flash_t flash { FlashData{} };
   flash.d1 = 3;
   return flash.d1 == 1 and flash.d2 == 2;
}


int main()
{
   std::cout << '\n'
             << "Тесты класса Flash:" << std::endl;

   // \033[32mТЕКСТ\033[0m - для цвета
   std::cout << "Flash::ctor            " << (ctor()            ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
}

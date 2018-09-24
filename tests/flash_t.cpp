#define STM32F405xx

#include "flash.h"
#include <iostream>

auto constexpr size_ {20};
static uint8_t sector0[size_];
bool erase_ {false};
void erase()
{
   std::fill (std::begin(sector0), std::end(sector0), 0xFF);
}

bool lock_ {true};
auto eop_count {0};

struct FlashMock {
   enum Sector   { _0  };
   enum ProgSize { x16 };
   
   template<Sector> static size_t address() { return reinterpret_cast<size_t>(&sector0); }
   template<Sector> static constexpr int32_t size() { return size_; }
   static void lock() { lock_ = true; }
   static bool is_empty() { return false; }
   static bool is_busy() { return false; }
   static bool is_lock() { return lock_; }
   static void unlock() { lock_ = false; }
   static void setProgMode() {}
   template<ProgSize> static void set() {}
   static bool is_endOfProg() { return not ((eop_count += 1) %= 5); }
   static void clearEndOfProgFlag() { erase_ = false; }
   template<Sector> static void startErase() { erase(); erase_ = true; }
};

struct Data {
   uint16_t d1 {1};
   uint16_t d2 {2};
};
using Flash_t = Flash_impl<Data, FlashMock, FlashMock::Sector::_0>;


bool ctor()
{
   erase();
   Flash_t flash {};
   auto qty {100};
   while (qty--)
      tickUpdater.notify();
   return flash.d1 == 1 and flash.d2 == 2
      and sector0[0] == 0 and sector0[1] == 1
      and sector0[2] == 1 and sector0[3] == 0
      and sector0[4] == 2 and sector0[5] == 2
      and sector0[6] == 3 and sector0[7] == 0;
}

bool change()
{
   Flash_t flash {};
   flash.d1 = 0x0301;
   auto qty {100};
   while (qty--)
      tickUpdater.notify();
   return flash.d1 == 0x0301 and flash.d2 == 2
      and sector0[0] == 0 and sector0[1] == 1
      and sector0[2] == 1 and sector0[3] == 0
      and sector0[4] == 2 and sector0[5] == 2
      and sector0[6] == 3 and sector0[7] == 0
      and sector0[8] == 1 and sector0[9] == 3;
}

bool ctor_after_change()
{
   Flash_t flash {};
   return flash.d1 == 0x0301 and flash.d2 == 2;
}

/// если сектор кончается, то запись не останавливается, начинается заново
bool end_of_sector()
{
   {
      Flash_t flash {};
      auto qty {size_};
      while (qty--) {
         flash.d2++;
         auto ms {100};
         while (ms--)
            tickUpdater.notify();
      }
   } // отключили питание

   Flash_t test {};
   return test.d1 == 0x0301 and test.d2 == 22;
}

/// плохой вариант, потеря данных при отключеии питания при стирании сектора
bool off_when_erase()
{
   bool good {true};
   {
      erase();
      Flash_t flash {};
      auto ms {100};
      while (ms--)
         tickUpdater.notify();
      
      auto time {0};
      while (not erase_) {
         tickUpdater.notify();
         if (not (++time % 100))
            flash.d1++;
      }
      good &= (flash.d1 == 8);
   } // off

   Flash_t flash {};

   return good and flash.d1 == 1;
}

bool new_data()
{
   {
      Flash_t flash {};
      flash.d2 = 100;
      auto ms {100};
      while (ms--)
         tickUpdater.notify();
   }
   struct NewData {
      uint16_t d1 {1};
      uint16_t d2 {2};
      uint16_t d3 {0};
   };
   Flash_impl<NewData, FlashMock, FlashMock::Sector::_0> flash {};
   auto ms {100};
   while (ms--)
      tickUpdater.notify();
   
   return flash.d1 == 1 and flash.d2 == 2 and flash.d3 == 0;
}


int main()
{
   std::cout << '\n'
             << "Тесты класса Flash:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

   test ("Flash::ctor                  ", ctor);
   test ("Flash::change                ", change);
   test ("Flash::ctor_after_change     ", ctor_after_change);
   test ("Flash::end_of_sector         ", end_of_sector);
   test ("Flash::off_when_erase        ", off_when_erase);
   test ("Flash::new_data              ", new_data);
}


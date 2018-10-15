#pragma once

#include <stdbool.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include "flash_periph.h"
#include "timers.h"


// для STM32F0 sector на самом деле page из refmanual
template <class Data, class FLASH_, typename FLASH_::Sector sector>
class Flash_impl : public Data, private TickSubscriber
{
public:
    Flash_impl();
   ~Flash_impl() { unsubscribe(); }

private:
   uint8_t* original = reinterpret_cast<uint8_t*>(static_cast<Data*>(this));
   uint8_t copy[sizeof(Data)];
   int32_t flashOffset {-1};
   bool needErase {false};
   struct Pair {
      uint8_t offset; 
      uint8_t value;
   };
   union Flash_t {
      Pair     pair[FLASH_::template size<sector>()/2];
      uint16_t word[FLASH_::template size<sector>()/2];
   };
   // volatile Flash_t* flash = (Flash_t*)FLASH_::template address<sector>();
   Flash_t* flash = (Flash_t*)FLASH_::template address<sector>();
   // Flash_t* flash2 = (Flash_t*)FLASH_::template address<FLASH_::template next<sector>()>();

   Flash_impl (Data d) : Data{d} {}
   // возвращает true, если данные прочитаны
   // false, если нет или данные не полные
   bool readFromFlash();
   void notify() override;
};


/// алиасинг для более быстрой записи
template<class Data, typename FLASH::Sector sector>
using Flash = Flash_impl<Data,FLASH,sector>;















template <class Data, class FLASH_, typename FLASH_::Sector sector>
Flash_impl<Data,FLASH_,sector>::Flash_impl()
{
   static_assert (
      sizeof(Data) < 255,
      "Размер сохраняемой структуры должен быть менее 255 байт"
   );
   static_assert (
      std::is_trivially_copyable_v<Data>,
      "Можно сохранять только тривиально копируемую структуру"
   );
   FLASH_::lock();
   if (not readFromFlash())
      Flash_impl {Data{}};
   subscribe();
}



template <class Data, class FLASH_, typename FLASH_::Sector sector>
bool Flash_impl<Data,FLASH_,sector>::readFromFlash()
{
   // обнуляем буфер перед заполнением
   memset (copy, 0xFF, sizeof(copy));

   // чтение данных в копию data в виде массива
   flashOffset = -1;
   bool indExist[sizeof(Data)] {};
   for (auto& pair : flash->pair) {
      flashOffset++;
      if (pair.offset < sizeof(Data)) {
         copy[pair.offset] = pair.value;
         indExist[pair.offset] = true;
      } else if (pair.offset == 0xFF) {
         break;
      }
   }

   // проверка остальной части сектора флэш
   if (not std::all_of (
              std::begin(flash->word) + flashOffset
            , std::end(flash->word)
            , [](auto& word){ return word == 0xFFFF; }
           )
   ) {
      needErase = true;
      return false;
   }

   // проверка, что все данные прочитаны
   if (std::all_of (std::begin(indExist), std::end(indExist), [](auto& v){return v;})) {
      memcpy (original, copy, sizeof(copy));
      return true;
   } else {
      return false;
   }
}



template <class Data, class FLASH_, typename FLASH_::Sector sector>
void Flash_impl<Data,FLASH_,sector>::notify()
{
   // реализация автоматом
   enum State {
      CheckChanges,
      StartWrite,
      CheckWrite,
      Erase,
      CheckErase
   };
   static State state = CheckChanges;
   static volatile uint8_t dataWrite = 0;
   static uint8_t byteN = 0;

   switch (state) {

   case CheckChanges:
      if (needErase) {
         state = Erase;
      } else if (original[byteN] == copy[byteN]) {
         byteN++;
         if (byteN == sizeof(Data)) {
            byteN = 0;
         }
      } else {
         state = StartWrite;
      }
      break;

   case StartWrite:
      if ( not FLASH_::is_busy() and FLASH_::is_lock() ) {
         FLASH_::unlock();
         FLASH_::setProgMode();
         #if defined(STM32F4)
            FLASH_::template set<FLASH_::ProgSize::x16>();
            FLASH_::endOfProgInterruptEn(); // уже не помню зачем это
         #endif

         dataWrite = original[byteN];
         flash->word[flashOffset] = (uint16_t)dataWrite << 8 | byteN;
         state = CheckWrite;
      }
      break;

   case CheckWrite:
      if ( FLASH_::is_endOfProg() ) {
         FLASH_::clearEndOfProgFlag();
         FLASH_::lock();
         copy[byteN] = dataWrite;
         flashOffset++;
         if ( static_cast<size_t>(flashOffset) > sizeof(Flash_t) / sizeof(Pair) )
            needErase = true;
         state = CheckChanges;
      }
      break;

   case Erase:
      if ( not FLASH_::is_busy() and FLASH_::is_lock() ) {
         FLASH_::unlock();
         FLASH_::template startErase<sector>();
         state = CheckErase;
      }
      break;

   case CheckErase:
      if ( FLASH_::is_endOfProg() ) {
         FLASH_::clearEndOfProgFlag();
         FLASH_::lock();
         needErase = false;
         memset (copy, 0xFF, sizeof(copy));
         flashOffset = 0;
         state = CheckChanges;
      }
      break;
   } // switch
}










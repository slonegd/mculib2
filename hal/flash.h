/** шаблонный класс сохранения данных во flash
 *  при инициализации необходимо указать
 *      структуру, которая будет сохраняться
 *      сектор флеша, куда записывать
 *  Размер структуры не более 255 байт, поскольку кодируються во флеше
 *  в виде двух байт, один данные, второй их индекс в байтовом массиве
 * 
 *  Перед работой с данными, их надо сначала прочитать, и если результат
 *  отрицательный, то инициировать значениями по умолчанию
 * 
 *  Для обновления изменённых данных периодически вызывать update
 * 
 *////////////////////////////////////////////////////////////////////////////
  
#pragma once

#include <stdbool.h>
#include <string.h>
#include <algorithm>
#include "flash_periph.h"
#include "timers.h"


// для STM32F0 sector на самом деле page из refmanual
template <class Data, class FLASH_, typename FLASH_::Sector sector>
class Flash_impl : public Data
{
public:
   // конструктор принимает значения, которые необходимо записать
   // при первой прошивке (по умолчанию)
   Flash_impl (Data d)
   {
      static_assert (
         sizeof(Data) < 255,
         "Размер сохраняемой структуры не может превышать 255 байт"
      );
      // FLASH_::endOfProgInterruptEn(); // уже не помню зачем это
      #if defined(STM32F4)
         FLASH_::template set<FLASH_::ProgSize::x16>();
      #endif
      if ( not readFromFlash() ) {
         memcpy (this, &d, sizeof(Data));
      }
   }

   


private:
   uint8_t copy[sizeof(Data)];
   uint8_t* original = (uint8_t*)this;
   int32_t flashOffset;
   bool needErase;
   struct Pair {
      uint8_t key; 
      uint8_t value;
   };
   union Flash_t {
      Pair     data[FLASH_::template size<sector>()/2];
      uint16_t word[FLASH_::template size<sector>()/2];
   };
//    volatile Flash_t& flash = *(Flash_t*)FLASH_::template address<sector>();
   Flash_t* flash = (Flash_t*)FLASH_::template address<sector>();

   // возвращает true, если данные прочитаны
   // false, если нет или данные не полные
   bool readFromFlash();
   void tick();



   /// пришлось делать эту структуру, потому что
   /// основная при наследовании ItickSubscribed затирала базовый класс
   /// почему так и не выяснил
   class FlashUpdater : TickSubscriber
   {
   public:
    using Parent = Flash_impl<Data,FLASH_,sector>;
      FlashUpdater (Parent* parent) : parent(parent) { subscribe(); }
      ~FlashUpdater() { unsubscribe(); }
   private:
      Parent* parent;
      void notify() override { parent->tick(); }
   } flashUpdater {this};
};

template<class Data, typename FLASH::Sector sector>
using Flash = Flash_impl<Data,FLASH,sector>;



template <class Data, class FLASH_, typename FLASH_::Sector sector>
bool Flash_impl<Data,FLASH_,sector>::readFromFlash ()
{
   // обнуляем буфер перед заполнением
   memset (copy, 0xFF, sizeof(copy));
 
   // чтение данных в копию data в виде массива
   flashOffset = -1;
   bool indExist[sizeof(Data)] {};
   for (auto& pair : flash->data) {
      flashOffset++;
      auto index {pair.key};
      if (index < sizeof(Data)) {
         copy[index] = pair.value;
         indExist[index] = true;
      } else if (index == 0xFF) {
         break;
      }
   }

   // проверка есть ли ещё место
   if ( flashOffset == -1) {
      needErase = true;
      return false;    
   }

   // проверка остальной части сектора флэш
   if (not std::all_of (
              std::begin(flash->word) + flashOffset
            , std::end(flash->word)
            , [](auto& word) { return word == 0xFFFF; }
           )
   ) {
      needErase = true;
      return false;
   }


   // проверка, что все данные прочитаны
   if (std::all_of (std::begin(indExist), std::end(indExist), [](auto& v) { return v; })) {
      memcpy (original, copy, sizeof(copy));
      return true;
   } else {
      return false;
   }
}



template <class Data, class FLASH_, typename FLASH_::Sector sector>
void Flash_impl<Data,FLASH_,sector>::tick()
{
   // реализация автоматом
   enum State {
      CheckChanges,
      StartWrite,
      CheckWrite,
      Errase,
      CheckErase
   };
   static State state = CheckChanges;
   static volatile uint8_t dataWrite = 0;
   static uint8_t byteN = 0;

   switch (state) {

   case CheckChanges:
      if (needErase) {
         state = Errase;
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

   case Errase:
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










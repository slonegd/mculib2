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
#include "flash_periph.h"
#include "timers.h"


// для STM32F0 sector на самом деле page из refmanual
template <class DATA, class FLASH, typename FLASH::Sector sector>
class Flash_impl : public DATA
{
public:
   // конструктор принимает значения, которые необходимо записать
   // при первой прошивке (по умолчанию)
   Flash_impl (DATA d)
   {
      static_assert (
         sizeof(DATA) < 255,
         "Размер сохраняемой структуры не может превышать 255 байт"
      );
      // FLASH::endOfProgInterruptEn(); // уже не помню зачем это
      if ( not readFromFlash() ) {
         memcpy (this, &d, sizeof(DATA));
      }
   }

   


private:
   static constexpr uint8_t QtyBytes = sizeof(DATA);

   uint8_t copy[QtyBytes];
   uint8_t* original = (uint8_t*)this;
   int32_t flashOffset;
   bool needErase;
   struct Pair {
      uint8_t key; 
      uint8_t value;
   };
   union Flash_t {
      Pair     data[FLASH::template size<sector>()/2];
      uint16_t word[FLASH::template size<sector>()/2];
   };
   volatile Flash_t& flash = *(Flash_t*)FLASH::template address<sector>() ;

   // возвращает true, если данные прочитаны
   // false, если нет или данные не полные
   bool readFromFlash();



   /// пришлось делать эту структуру, потому что
   /// основная при наследовании ItickSubscribed затирала базовый класс
   /// почему так и не выяснил
   class FlashUpdater : TickSubscriber
   {
   public:
      FlashUpdater (Flash_impl<DATA,FLASH,sector>* parent) : parent(parent)
      {
          subscribe();
      }
   private:
      Flash_impl<DATA,FLASH,sector>* parent;
      void notify() override { parent->tick(); }
   } flashUpdater {this};
   void tick();
};

template<class Data, typename FLASH::Sector sector>
using Flash = Flash_impl<Data,FLASH,sector>;



template <class Data, class FLASH, typename FLASH::Sector sector>
bool Flash_impl<Data,FLASH,sector>::readFromFlash ()
{
   // обнуляем буфер перед заполнением
   memset (copy, 0xFF, QtyBytes);
 
   // чтение данных в копию data в виде массива
   flashOffset = -1;
   bool indExist[QtyBytes] = {false};
   for (auto i {0}; i < FLASH::template size<sector>(); i++) {
      uint8_t index;
      index = flash.data[i].key;
      if ( index < QtyBytes) {
         copy[index] = flash.data[i].value;
         indExist[index] = true;
      } else if (index == 0xFF) {
         flashOffset = i;
         break;
      }
   }

   // проверка есть ли ещё место
   if ( flashOffset == -1) {
      needErase = true;
      return false;    
   }

   // проверка остальной части сектора флэш
   for (auto i {flashOffset}; i < FLASH::template size<sector>(); i++) {
      if (flash.word[i] != 0xFFFF) {
         needErase = true;
         return false;    
      }
   }

   // проверка, что все данные прочитаны
   bool tmp = true;
   for (uint8_t i = 0; i < QtyBytes; i++) {
      tmp &= indExist[i];
   }
   if (tmp) {
      memcpy (original, copy, QtyBytes);
      return true;
   } else {
      return false;
   }
}



template <class Data, class FLASH, typename FLASH::Sector sector>
void Flash_impl<Data,FLASH,sector>::tick()
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
         if (byteN == QtyBytes) {
            byteN = 0;
         }
      } else {
         FLASH::lock();
         state = StartWrite;
      }
      break;

   case StartWrite:
      if ( !FLASH::is_busy() and FLASH::is_lock() ) {
         FLASH::unlock();
         FLASH::setProgMode();
         #if defined(STM32F4)
            FLASH::template set<FLASH::ProgSize::x16>();
         #endif
         dataWrite = original[byteN];
         flash.word[flashOffset] = (uint16_t)dataWrite << 8 | byteN;
         state = CheckWrite;
      }
      break;

   case CheckWrite:
      if ( FLASH::is_endOfProg() ) {
         FLASH::clearEndOfProgFlag();
         FLASH::lock();
         copy[byteN] = dataWrite;
         flashOffset++;
         if ( flashOffset >= FLASH::template size<sector>() ) {
            needErase = true;
         }
         state = CheckChanges;
      }
      break;

   case Errase:
      if ( not FLASH::is_busy() and FLASH::is_lock() ) {
         FLASH::unlock();
         FLASH::template startErase<sector>();
         state = CheckErase;
      }
      break;

   case CheckErase:
      if ( FLASH::is_endOfProg() ) {
         FLASH::clearEndOfProgFlag();
         FLASH::lock();
         // проверка, что стёрли
         bool tmp = true;
         for (uint32_t i = 0; i < FLASH::template size<sector>() / 2; i++) {
            tmp &= (flash.word[i] == 0xFFFF);
         }
         if (tmp) {
            needErase = false;
            memset (copy, 0xFF, QtyBytes);
            flashOffset = 0;
         }
         state = CheckChanges;
      }
      break;
   } // switch
}










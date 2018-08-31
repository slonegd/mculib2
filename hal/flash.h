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
#include "FLASH.h"
#include "timers.h"


// для STM32F0 sector на самом деле page из refmanual
template <class DATA, uint8_t sector>
class Flash : public DATA
{
public:
   // конструктор принимает значения, которые необходимо записать
   // при первой прошивке (по умолчанию)
   Flash (DATA d)
   {
      static_assert (
         SectorAddr != 0,
         "Недопустимый сектор памяти"
      );
      static_assert (
         sizeof(DATA) < 255,
         "Размер сохраняемой структуры не может превышать 255 байт"
      );
      FLASH::endOfProgInterruptEn(); // уже не помню зачем это
      if ( !readFromFlash() ) {
         memcpy (this, &d, sizeof(DATA));
      }
   }

   


private:
   static constexpr uint8_t QtyBytes = sizeof(DATA);
#if defined(STM32F405xx)
   static constexpr uint32_t SectorAddr =
      sector == 1  ? 0x08004000 :
      sector == 2  ? 0x08008000 :
      sector == 3  ? 0x0800C000 :
      sector == 4  ? 0x08010000 :
      sector == 5  ? 0x08020000 :
      sector == 6  ? 0x08040000 :
      sector == 7  ? 0x08060000 :
      sector == 8  ? 0x08080000 :
      sector == 9  ? 0x080A0000 :
      sector == 10 ? 0x080C0000 :
      sector == 11 ? 0x080E0000 : 0;
   static constexpr int32_t SectorSize =
      sector > 0 && sector < 4  ? 16*1024 :
      sector == 4               ? 64*1024 :
      sector > 4 && sector < 12 ? 128*1024 : 0;
#elif defined(STM32F030x6)
   static constexpr uint32_t SectorAddr =
      sector > 0 && sector < 31 ? 0x08000000 + 1024*sector : 0;
   static constexpr int32_t SectorSize =
      sector > 0 && sector < 31 ? 1024 : 0;
#endif

   uint8_t copy[QtyBytes];
   uint8_t* original = (uint8_t*)this;
   int32_t flashOffset;
   bool needErase;
   struct Pair {
      uint8_t key; 
      uint8_t value;
   };
   union Flash_t {
      Pair     data[SectorSize/2];
      uint16_t word[SectorSize/2];
   };
   volatile Flash_t& flash = *(Flash_t*)SectorAddr ;

   // возвращает true, если данные прочитаны
   // false, если нет или данные не полные
   bool readFromFlash();



   /// пришлось делать эту структуру, потому что
   /// основная при наследовании ItickSubscribed затирала базовый класс
   /// почему так и не выяснил
   class FlashUpdater : TickSubscriber
   {
   public:
      FlashUpdater (Flash<DATA,sector>* parent) : parent(parent)
      {
          subscribe();
      }
   private:
      Flash<DATA,sector>* parent;
      void notify() override { parent->tick(); }
   } flashUpdater {this};
   void tick();
};



template <class Data, uint8_t sector>
bool Flash<Data,sector>::readFromFlash ()
{
   // обнуляем буфер перед заполнением
   memset (copy, 0xFF, QtyBytes);
 
   // чтение данных в копию data в виде массива
   flashOffset = -1;
   bool indExist[QtyBytes] = {false};
   for (uint32_t i = 0; i < SectorSize; i++) {
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
   for (uint32_t i = flashOffset; i < SectorSize; i++) {
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



template <class Data, uint8_t sector>
void Flash<Data,sector>::tick()
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
      if ( !FLASH::isBusy() and FLASH::isLock() ) {
         FLASH::unlock();
         FLASH::setProgMode();
         #if defined(STM32F405xx)
            FLASH::setProgSize (FLASH::ProgSize::x16);
         #endif
         dataWrite = original[byteN];
         flash.word[flashOffset] = (uint16_t)dataWrite << 8 | byteN;
         state = CheckWrite;
      }
      break;

   case CheckWrite:
      if ( FLASH::isEndOfProg() ) {
         FLASH::clearEndOfProgFlag();
         FLASH::lock();
         copy[byteN] = dataWrite;
         flashOffset++;
         if ( flashOffset >= SectorSize ) {
            needErase = true;
         }
         state = CheckChanges;
      }
      break;

   case Errase:
      if ( !FLASH::isBusy() and FLASH::isLock() ) {
         FLASH::unlock();
         #if defined(STM32F405xx)
            FLASH::template startEraseSector<sector>();
         #elif defined(STM32F030x6)
            FLASH::template startEraseSector<SectorAddr>();
         #endif
         state = CheckErase;
      }
      break;

   case CheckErase:
      if ( FLASH::isEndOfProg() ) {
         FLASH::clearEndOfProgFlag();
         FLASH::lock();
         // проверка, что стёрли
         bool tmp = true;
         for (uint32_t i = 0; i < SectorSize / 2; i++) {
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










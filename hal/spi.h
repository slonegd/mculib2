#pragma once

#include "SPI.h"

// просто отправляет по dma данные из data
// сигнал CS(NSS) хард
// пины пока тоже без альтернатив
// dataSize - размер в битах 1 отправки (пока только для 8 и 16)
template<class SPI_, class Data, uint8_t dataSize = 8>
class SPIoverDMA //  : private SPI_
{
public:
   // без этого буфера не работало, не понял почему
   volatile uint32_t buf[0];
   union {
      volatile Data data;
      volatile uint8_t arr[sizeof(Data)];
   };


   using SCK  = PA5;
   using MOSI = PA7;
   using NSS  = PA4;
   using DMAtx = typename SPI_::DMAtx;


   SPIoverDMA() : arr()
   {
      init();
   }


   void startTx()
   {
      if ( DMAtx::IsTransferCompleteInterrupt() or DMAtx::IsDisable() ) {
         DMAtx::ClearFlagTransferCompleteInterrupt();
         DMAtx::Disable();
         DMAtx::SetQtyTransactions (sizeof(Data) * 8 / dataSize);
         DMAtx::Enable();
      }
   }



private:
   void init()
   {
      CONFIGURE_PIN (SCK,  AlternateFunc0);
      CONFIGURE_PIN (MOSI, AlternateFunc0);
      CONFIGURE_PIN (NSS,  AlternateFunc0);

      SPI_::clockEnable();
      SPI_::setAsMaster();
      SPI_::template setBoudRate<SPI_::Div::Div256>();
      SPI_::slaveSelectEnable();
      SPI_::slaveSelectPulseEnable();
      if (dataSize == 8)
         SPI_::template setDataSize<SPI_::DataSize::_8bits>();
      else if (dataSize == 16)
         SPI_::template setDataSize<SPI_::DataSize::_16bits>();
      SPI_::txDMAenable();
      SPI_::enable();
      

      DMAtx::ClockEnable();
      DMAtx::SetMemoryAdr ( (uint32_t)arr );
      DMAtx::SetPeriphAdr ( SPI_::getDataAdr() );
      // DMAtx::SetQtyTransactions (sizeof(Data));
      typename DMAtx::Configure_t conf;
      conf.dataDir = DMAtx::DataDirection::MemToPer;
      if (dataSize == 8) {
         conf.memSize = DMAtx::DataSize::byte8;
         conf.perSize = DMAtx::DataSize::byte8;
      } else if (dataSize == 16) {
         conf.memSize = DMAtx::DataSize::word16;
         conf.perSize = DMAtx::DataSize::word16;
      }
      conf.memInc = true;
      conf.perInc = false;
      conf.circularMode = false;
      DMAtx::Configure (conf);
   }

};
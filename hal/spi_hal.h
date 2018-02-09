#pragma once

#include "SPI_ral.h"

// просто отправляет по dma данные из data
// сигнал CS(NSS) хард
// пины пока тоже без альтернатив
template<class SPI_, class Data>
class SPI : private SPI_
{
public:
   union {
      Data data;
      uint8_t arr[sizeof(Data)];
   };


   using SCK  = PA5;
   using MOSI = PA7;
   using NSS  = PA4;
   using DMAtx = typename SPI_::DMAtx;


   SPI() : arr()
   {
      init();
   }


   void startTx()
   {
      // TODO проверить установлен ли этот бит при старте (вроде да)
      if ( DMAtx::TransferCompleteInterrupt() ) {
         DMAtx::ClearFlagTransferCompleteInterrupt();
         DMAtx::Disable();
         DMAtx::SetQtyTransactions (sizeof(Data));
         DMAtx::Enable(); 
      }
   }



private:
   void init()
   {
      CONFIGURE (SCK,  AlternateFunc0PushPull);
      CONFIGURE (MOSI, AlternateFunc0PushPull);
      CONFIGURE (NSS,  AlternateFunc0PushPull);

      SPI_::ClockEnable();
      SPI_::SetAsMaster();
      SPI_::template SetBoudRate<SPI_::Div::Div256>();
      SPI_::SlaveSelectEnable();
      SPI_::template SetDataSize<SPI_::DataSize::_8bits>();
      SPI_::TxDMAenable();
      SPI_::Enable();

      DMAtx::ClockEnable();
      DMAtx::SetMemoryAdr ( (uint32_t)arr );
      DMAtx::SetPeriphAdr ( (uint32_t) &(SPI_::data()) );
      // DMAtx::SetQtyTransactions (sizeof(Data));
      typename DMAtx::Configure_t conf;
      conf.dataDir = DMAtx::DataDirection::MemToPer;
      conf.memSize = DMAtx::DataSize::byte8;
      conf.perSize = DMAtx::DataSize::byte8;
      conf.memInc = true;
      conf.perInc = false;
      conf.circularMode = false;
      DMAtx::Configure (conf);
   }

};
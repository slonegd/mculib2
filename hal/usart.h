#pragma once

#include "USART.h"
#include "pins_variadic.h"


template<class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
class USART
{
public:
   static_assert (
      USART_::template IsRXsupport<RX>(),
      "выбранный вывод не поддерживает функцию RX"
   );
   static_assert (
      USART_::template IsTXsupport<TX>(),
      "выбранный вывод не поддерживает функцию TX"
   );
   static_assert (
      USART_::template IsRTSsupport<RTS>(),
      "выбранный вывод не поддерживает функцию RTS"
   );

   uint8_t buffer[bufSize];

   using Periph_type = USART_;
   using DMArx    = typename USART_::DMArx;
   using DMAtx    = typename USART_::DMAtx;
   using Boudrate = typename USART_::Boudrate;
   using Parity   = typename USART_::Parity;
   using StopBits = typename USART_::StopBits;
   enum ParityEn { disable, enable };
   struct Settings {
      Boudrate boudrate;
      ParityEn parityEn;
      Parity parity;
      StopBits stopBits;
   };

   /// приставка s для обозначения сериализованных данных
   enum sParity   { even = 0b0, odd };
   enum sStopBits { _1 = 0b0, _2 };
   enum sBoudrate { _9600 = 0b000, _14400, _19200, _28800, _38400, _57600, _76800, _115200 };
   struct sSettings {
      bool      parityEnable :1;
      sParity   parity       :1;
      sStopBits stopBits     :1;
      sBoudrate boudrate     :3;
      uint16_t  res          :10;
   };
   static Settings deserialize (const sSettings& set);
   
   void init (const Settings& set);
   void init (const sSettings& set) { init(deserialize(set)); }
   void enableRX();
   uint32_t byteQtyRX();
   void startTX (uint32_t qty);
   void DMAtxCompleteHandler();
#if defined(STM32F030x6)
   bool rxTimeOutHandler();
#elif defined(STM32F405xx)
   bool isIDLE();
   bool isTXcomplete();
   void txCompleteHandler();
#endif

};














template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::init (const Settings& set)
{
   // пины
   #if defined(STM32F030x6)
      Pins<RX,TX,RTS>::template configure<USART_::PinConfigure()>();
      CONFIGURE_PIN (LED, Output);
   #elif defined(STM32F405xx)
      Pins<RX,TX>::template configure<USART_::PinConfigure()>();
      CONFIGURE_PIN (TYPE(Pins<LED,RTS>), Output);
   #endif

   // уарт
   USART_::clockEnable();
   USART_::setBoudRate (set.boudrate);
   if (set.parityEn == ParityEn::enable) {
      USART_::parityEnable (true);
      USART_::setParity(set.parity);
   } else {
      USART_::parityEnable (false);
   }
   USART_::setStopBits (set.stopBits);
   USART_::rxEnable (true);
   USART_::txEnable (true);
   USART_::DMArxEnable();
   USART_::DMAtxEnable();
   #if defined(STM32F030x6)
      USART_::setTimeOutBitQty(42); // 3.5 слова в битах
      USART_::enableReceiveTimeout();
      USART_::rtsEnable();
      USART_::driverEnable();
   #endif
   USART_::enable (true);

   // дма
   DMArx::ClockEnable();
   DMArx::SetMemoryAdr ( (uint32_t)buffer );
   DMArx::SetPeriphAdr ( USART_::ReceiveDataAdr() );
   DMArx::SetQtyTransactions (bufSize);
   union {
      typename DMArx::Configure_t configureRx;
      typename DMAtx::Configure_t configureTx;
   };
   configureRx.dataDir = DMArx::DataDirection::PerToMem;
   configureRx.memSize = DMArx::DataSize::byte8;
   configureRx.perSize = DMArx::DataSize::byte8;
   configureRx.memInc = true;
   configureRx.perInc = false;
   configureRx.circularMode = true;
   #if defined(STM32F405xx)
      configureRx.channel = USART_::DMAChannel();
   #endif
   DMArx::Configure (configureRx);
   DMArx::Enable();

   DMAtx::SetMemoryAdr ( (uint32_t)buffer );
   DMAtx::SetPeriphAdr ( USART_::TransmitDataAdr() );
   configureTx.dataDir = DMArx::DataDirection::MemToPer;
   configureTx.circularMode = false;
   DMAtx::Configure (configureTx);

   // прерывания
   #if defined(STM32F405xx)
      USART_::enableIDLEinterrupt();
   #elif defined(STM32F030x6)
      USART_::enableReceiveTimeoutInterupt();
   #endif
   NVIC_EnableIRQ (USART_::IRQn());
   DMAtx::EnableTransferCompleteInterrupt();
   NVIC_EnableIRQ (DMAtx::IRQn());
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
typename USART<USART_, bufSize, RX, TX, RTS, LED>::Settings
USART<USART_, bufSize, RX, TX, RTS, LED>::deserialize (const sSettings& set)
{ enum sBoudrate { _9600 = 0b000, _14400, _19200, _28800, _38400, _57600, _76800, _115200 };
   auto br = set.boudrate == sBoudrate::_14400  ? Boudrate::BR14400  :
             set.boudrate == sBoudrate::_19200  ? Boudrate::BR19200  :
             set.boudrate == sBoudrate::_28800  ? Boudrate::BR28800  :
             set.boudrate == sBoudrate::_38400  ? Boudrate::BR38400  :
             set.boudrate == sBoudrate::_57600  ? Boudrate::BR57600  :
             set.boudrate == sBoudrate::_76800  ? Boudrate::BR76800  :
             set.boudrate == sBoudrate::_115200 ? Boudrate::BR115200 : Boudrate::BR9600;
   auto parEn = set.parityEnable ? ParityEn::enable : ParityEn::disable;
   auto par = set.parity == sParity::even ? Parity::even : Parity::odd;
   auto sb = set.stopBits == sStopBits::_1 ? StopBits::_1 : StopBits::_2;
   return { br, parEn, par, sb };
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::enableRX()
{
   DMArx::Disable(); 
   DMArx::SetQtyTransactions (bufSize);
   DMArx::Enable(); 
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
USART<USART_, bufSize, RX, TX, RTS, LED>::byteQtyRX()
{
   return bufSize - DMArx::QtyTransactionsLeft();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::startTX (uint32_t qty)
{
   #if defined(STM32F405xx)
      RTS::set();
   #endif
   LED::set();
   DMArx::Disable();
   DMAtx::Disable();
   DMAtx::SetQtyTransactions (qty);
   DMAtx::Enable();
}



template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::DMAtxCompleteHandler()
{
   if ( DMAtx::IsTransferCompleteInterrupt() ) {
      DMAtx::Disable();
      #if defined(STM32F030x6)
         LED::clear();
         enableRX();
      #elif defined(STM32F405xx)
         USART_::enableTXcompleteInterrupt (true);
      #endif
      DMAtx::ClearFlagTransferCompleteInterrupt();
   }
}



#if defined(STM32F030x6)

template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
bool USART<USART_, bufSize, RX, TX, RTS, LED>::rxTimeOutHandler()
{
   bool tmp = USART_::isReceiveTimeoutInterrupt();
   if (tmp) {
      DMArx::Disable();
      USART_::clearReceiveTimeoutInterruptFlag();
   }
   return tmp;
}

#elif defined(STM32F405xx)

template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::txCompleteHandler()
{
   USART_::enableTXcompleteInterrupt (false);
   RTS::clear();
   LED::clear();
   enableRX();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
bool USART<USART_, bufSize, RX, TX, RTS, LED>::isIDLE()
{
   return USART_::isIDLEinterrupt();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
bool USART<USART_, bufSize, RX, TX, RTS, LED>::isTXcomplete()
{
   return USART_::isTXcompleteInterrupt() and USART_::isTXcompleteInterruptEnable();
}



#endif







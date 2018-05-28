//////////////////////////////////////////////////////////////////////////////
/** реализую методы
 *      инициализации, поскольку в конструкторе как правило еще
 *  не известно какие настройки подключения
 *      слышать
 *      определять конец пакета
 *      определять сколько пришло
 *      отправлять сколько надо
 *      говорить, что отправка произошла
 *////////////////////////////////////////////////////////////////////////////
#pragma once

#include "USART.h"
#include "pins_variadic.h"

namespace USART_HAL {

} // namespace USART_HAL {


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
   volatile uint8_t buffer[bufSize];

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


   void init (Settings set);
   void DMAenableRX();
   void disableRx();
   uint32_t byteQtyRX();
   void sendByte (uint8_t val);
   void startTX (uint32_t qty); 
   void disableTx();
   bool isCompleteTX();
   bool idleHandler();
   void txCompleteHandler();



private:

};










// void UARTInit (	struct UARTSettingsStruc Set,
// 				struct UartBufSt* pBuf )
// {


	
// 	/**************************************************************************
// 	 * прерывания
// 	 */
// 	//по молчанию на прием, если признак конца пакета по модбасу
// 	if (Set.PackEnd == PE_MBRTU) {
// 		UARTSetTimeOutBitQty (42);	// 3.5 слова в битах
// 		UARTEnableReceiveTimeOut();
// 		UARTEnableInteruptReceiveTimeOut();

// //		SET_MASK (USART1->CR1, USART_CR1_RXNEIE_Msk);
// //		SET_MASK (USART1->RQR, USART_RQR_RXFRQ_Msk);

// 		NVIC_EnableIRQ(USART1_IRQn);
// 	}
// 	//по дма на отправку
// 	DMAEnableInterruptTransferComplete(DMA_UART_TRANSMIT);
// 	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

// }//void UARTInit()	





template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::init (Settings set)
{
   // пины
   Pins<RX,TX,RTS>::template configure<USART_::PinConfigure()>();
   CONFIGURE_PIN (LED, Output);

   // уарт
   USART_::ClockEnable();
   USART_::SetBoudRate (set.boudrate);
   if (set.parityEn == ParityEn::enable) {
      USART_::ParityEnable (true);
      USART_::SetParity(set.parity);
   } else {
      USART_::ParityEnable (false);
   }
   USART_::SetStopBits (set.stopBits);
   USART_::RXenable (true);
   USART_::TXenable (true);
   USART_::RTSenable();
   USART_::DMArxEnable();
   USART_::DMAtxEnable();
#if defined(STM32F030x6)
   USART_::SetTimeOutBitQty(42); // 3.5 слова в битах
   USART_::EnableReceiveTimeout();
#endif
   USART_::Enable (true);

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
   // DMAenableRX(); для отладки закомент

   DMAtx::SetMemoryAdr ( (uint32_t)buffer );
   DMAtx::SetPeriphAdr ( USART_::TransmitDataAdr() );
   configureTx.dataDir = DMArx::DataDirection::MemToPer;
   configureTx.circularMode = false;
   DMAtx::Configure (configureTx);

   // прерывания
#if defined(STM32F405xx)
   USART_::EnableIDLEinterrupt();
#elif defined(STM32F030x6)
   USART_::EnableReceiveTimeoutInterupt();
#endif
   NVIC_EnableIRQ(USART_::IRQn());
   DMAtx::EnableTransferCompleteInterrupt();
   NVIC_EnableIRQ(DMAtx::IRQn());
}



template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::DMAenableRX()
{
   DMArx::SetQtyTransactions (bufSize);
   DMArx::Enable(); 
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::disableRx()
{
   DMArx::Disable();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
uint32_t USART<USART_, bufSize, RX, TX, RTS, LED>::byteQtyRX()
{
   return bufSize - DMArx::QtyTransactionsLeft();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::sendByte (uint8_t val)
{
   USART_::sendByte(val);
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::startTX (uint32_t qty)
{
   LED::Set();
   DMAtx::Disable();
   DMAtx::SetQtyTransactions (qty);
   DMAtx::Enable();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::disableTx()
{
   DMAtx::Disable();
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
bool USART<USART_, bufSize, RX, TX, RTS, LED>::isCompleteTX()
{
   return false; // PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!!!!
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
bool USART<USART_, bufSize, RX, TX, RTS, LED>::idleHandler()
{
   bool tmp = USART_::IsIDLEinterrupt();
   if (tmp) {
      disableRx();
      // TODO:
      // метод сбрасывает все флаги прерывания,
      // но в этом приложении пофиг
      USART_::ClearIDLEinterruptFlag();
   }
   return tmp;
}


template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::txCompleteHandler()
{
   if ( DMAtx::IsTransferCompleteInterrupt() ) {
      LED::Clear();
      // DMAtx::Disable();
      // DMAenableRX();
      DMAtx::ClearFlagTransferCompleteInterrupt();
   }
}







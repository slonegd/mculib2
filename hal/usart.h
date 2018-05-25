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

namespace USART_HAL {

}


template<class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
class USART : USART_
{
public:
    volatile uint8_t buffer[bufSize];

    using Boudrate = typename USART_::Boudrate;
    enum ParityEn { disable, enable };
    using Parity = typename USART_::Parity;
    using StopBits = typename USART_::StopBits;
    struct Settings {
        Boudrate boudrate;
        ParityEn parityEn;
        Parity parity;
        StopBits stopBits;
    };
    using DMArx = typename USART_::DMArx;
    using DMAtx = typename USART_::DMAtx;

    void init (Settings set);
    inline void DMAenableRX ()
    {
        DMArx::SetQtyTransactions (bufSize);
        DMArx::Enable(); 
    }
    inline void disableRx()     { DMArx::Disable(); }
    inline uint32_t byteQtyRX() { return bufSize - DMArx::QtyTransactionsLeft(); }
    inline void sendByte (uint8_t val) { USART_::sendByte(val); }
    void startTX (uint32_t qty)
    {
        LED::Set();
        DMAtx::Disable();
        DMAtx::SetQtyTransactions (qty);
        DMAtx::Enable();   
    }
    inline void disableTx() { DMAtx::Disable(); }
    inline bool isCompleteTX()  { return false; }
    // обработчики прерываний
    // возвращает true если источник прерывания наш
    // тут возможно надо будет дораьотать, потому что
    // метод сбрасывает все флаги прерывания,
    // но в этом приложении пофиг
    inline bool idleHandler()
    {
        bool tmp = USART_::IsIDLEinterrupt();
        if (tmp) {
           disableRx();
           USART_::ClearIDLEinterruptFlag();
        }
        return tmp;
    }
    inline void txCompleteHandler()
    {
        if ( DMAtx::IsTransferCompleteInterrupt() ) {
            LED::Clear();
            //DMAtx::Disable();
//            DMAenableRX();
            DMAtx::ClearFlagTransferCompleteInterrupt();
        }
    }
private:

};

template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::init (Settings set)
{
    // пины
    RX::Port::ClockEnable();
    RX::Configure (
        RX::Mode::Alternate,
        RX::OutType::PushPull,
        RX::OutSpeed::High,
        RX::PullResistor::No
    );
    RX::template SetAltFunc <PA1::AF::_7> ();

    TX::Port::ClockEnable();
    TX::Configure (
        TX::Mode::Alternate,
        TX::OutType::PushPull,
        TX::OutSpeed::High,
        TX::PullResistor::No
    );
    TX::template SetAltFunc <PA1::AF::_7> ();

    RTS::Port::ClockEnable();
    RTS::Configure (
        RTS::Mode::Alternate,
        RTS::OutType::PushPull,
        RTS::OutSpeed::High,
        RTS::PullResistor::No
    );
    RTS::template SetAltFunc <PA1::AF::_7> ();

    LED::Port::ClockEnable();
    LED::Configure (
        LED::Mode::Output,
        LED::OutType::PushPull,
        LED::OutSpeed::Low,
        LED::PullResistor::No
    );
    LED::template SetAltFunc <PA1::AF::_0> ();

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
    USART_::DMArxEnable();
    USART_::DMAtxEnable();
    USART_::Enable (true);

    // дма
    DMArx::ClockEnable();
    DMArx::SetMemoryAdr ( (uint32_t)buffer );
    DMArx::SetPeriphAdr ( (uint32_t) &(USART_::data()) );
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
    configureRx.channel = USART_::DMAChannel();
    DMArx::Configure (configureRx);
    //DMAenableRX(); для отладки закомент

    DMAtx::SetMemoryAdr ( (uint32_t)buffer );
    DMAtx::SetPeriphAdr ( (uint32_t) &(USART_::data()) );
    configureTx.dataDir = DMArx::DataDirection::MemToPer;
    configureTx.circularMode = false;
    DMAtx::Configure (configureTx);

/*    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN_Msk;
    DMA1_Stream6->CR = 0;
    while ( (DMA1_Stream6->CR & DMA_SxCR_EN_Msk) != 0) { }
    DMA1_Stream6->M0AR = (uint32_t) buffer;
    DMA1_Stream6->PAR  = (uint32_t) &(USART_::data());
    DMA1_Stream6->CR = 0;
    DMA1_Stream6->CR |= (uint32_t)0b01 << DMA_SxCR_DIR_Pos;
    DMA1_Stream6->CR |= DMA_SxCR_MINC_Msk;
    DMA1_Stream6->CR |= (uint32_t)0b100 << DMA_SxCR_CHSEL_Pos;
    DMA1_Stream6->CR |= DMA_SxCR_TCIE_Msk;
*/

    // прерывания
    USART_::EnableIDLEinterrupt();
    NVIC_EnableIRQ(USART_::IRQn());
    DMAtx::EnableTransferCompleteInterrupt();
    NVIC_EnableIRQ(DMAtx::IRQn());
}



#pragma once

#include <type_traits>

#if defined(STM32F405xx) || defined(STM32F030x6)

template <uint32_t adr, class DMArx_, class DMAtx_>
void USARTx<adr,DMArx_,DMAtx_>::clockEnable()
{
   RCC::template clockEnable<USARTx<adr,DMArx_,DMAtx_>>();
}


template<uint32_t adr, class DMArx, class DMAtx> 
bool USARTx<adr,DMArx,DMAtx>::isIDLEinterrupt()
{
   return IS_SET(status(), IDLE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::enableIDLEinterrupt()
{
   SET(conf1(), IDLEIE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::DMAtxEnable()
{
   SET(conf3(), DMAT);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::DMArxEnable()
{
   SET(conf3(), DMAR);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::rtsEnable()
{
   SET(conf3(), RTSE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setStopBits (StopBits val)
{
   uint32_t tmp = conf2().reg;
   tmp &= ~_2BIT_TO_MASK(conf2(), STOP);
   tmp |= VAL_TO_MASK(conf2(), STOP, val);
   conf2().reg = tmp;
}

#endif


#if defined(STM32F405xx)

template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::enable (bool val)
{
   BIT_BAND(conf1(), UE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::rxEnable (bool val)
{
   BIT_BAND(conf1(), RE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::txEnable (bool val)
{
   BIT_BAND(conf1(), TE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setBoudRate (Boudrate val)
{
   if (bus == RCC::Bus::APB1) {
      boudrate().reg = RCC::getAPB1clock() / val;
   } else if (bus == RCC::Bus::APB2) {
      boudrate().reg = RCC::getAPB2clock() / val;
   }
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::parityEnable (bool val)
{
   BIT_BAND(conf1(), PCE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setParity (Parity val)
{
   BIT_BAND(conf1(), PS) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::clearIDLEinterruptFlag()
{
   status().reg;
   data().reg;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::sendByte (uint8_t val)
{
   data().reg = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
constexpr typename USARTx<adr,DMArx,DMAtx>::Channels
USARTx<adr,DMArx,DMAtx>::DMAChannel()
{
   return Base == USART6_BASE ? Channels::_5 : Channels::_4;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr IRQn_Type
USARTx<adr,DMArx,DMAtx>::IRQn()
{
   return Base == USART1_BASE ? USART1_IRQn :
          Base == USART2_BASE ? USART2_IRQn :
          Base == USART3_BASE ? USART3_IRQn :
          Base == USART6_BASE ? USART6_IRQn : NonMaskableInt_IRQn;
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class RXpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsRXsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<RXpin, PA10>::value
                            or std::is_same<RXpin, PB7>::value
      :
      Base == USART2_BASE ?    std::is_same<RXpin, PA3>::value
                            or std::is_same<RXpin, PD6>::value
      :
      Base == USART3_BASE ?    std::is_same<RXpin, PB11>::value
                            or std::is_same<RXpin, PD9>::value
                            or std::is_same<RXpin, PC11>::value
      :
      Base == USART6_BASE ?    std::is_same<RXpin, PC7>::value
                            or std::is_same<RXpin, PG9>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class TXpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsTXsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<TXpin, PA9>::value
                            or std::is_same<TXpin, PB6>::value
      :
      Base == USART2_BASE ?    std::is_same<TXpin, PA2>::value
                            or std::is_same<TXpin, PD5>::value
      :
      Base == USART3_BASE ?    std::is_same<TXpin, PB10>::value
                            or std::is_same<TXpin, PD8>::value
                            or std::is_same<TXpin, PC10>::value
      :
      Base == USART6_BASE ?    std::is_same<TXpin, PC6>::value
                            or std::is_same<TXpin, PG14>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class RTSpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsRTSsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<RTSpin, PA12>::value
      :
      Base == USART2_BASE ?    std::is_same<RTSpin, PD4>::value
      :
      Base == USART3_BASE ?    std::is_same<RTSpin, PB14>::value
                            or std::is_same<RTSpin, PD12>::value
      :
      Base == USART6_BASE ?    std::is_same<RTSpin, PG8>::value
                            or std::is_same<RTSpin, PG12>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr PinConf_t USARTx<adr,DMArx,DMAtx>::PinConfigure()
{
   return
      Base == USART1_BASE ? PinConf_t::AlternateFunc7HighSpeed
      :
      Base == USART2_BASE ? PinConf_t::AlternateFunc7HighSpeed
      :
      Base == USART3_BASE ? PinConf_t::AlternateFunc7HighSpeed
      :
      Base == USART6_BASE ? PinConf_t::AlternateFunc8HighSpeed
      :
      PinConf_t::Input;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr uint32_t USARTx<adr,DMArx,DMAtx>::ReceiveDataAdr()
{
   return Base + USART_ral::DR_t::Offset;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr uint32_t USARTx<adr,DMArx,DMAtx>::TransmitDataAdr()
{
   return Base + USART_ral::DR_t::Offset;
}


#elif defined(STM32F030x6)


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::driverEnable()
{
   SET(conf3(),DEM);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::enable (bool val)
{
   if (val)
      SET(conf1(), UE);
   else
      CLEAR(conf1(), UE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::rxEnable (bool val)
{
   if (val)
      SET(conf1(), RE);
   else
      CLEAR(conf1(), RE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::txEnable (bool val)
{
   if (val)
      SET(conf1(), TE);
   else
      CLEAR(conf1(), TE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setBoudRate (Boudrate val)
{
   boudrate().reg = RCC::getAPB2clock() / val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::parityEnable (bool val)
{
   if (val)
      SET(conf1(), PCE);
   else
      CLEAR(conf1(), PCE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setParity (Parity val)
{
   if (val)
      SET(conf1(), PS);
   else
      CLEAR(conf1(), PS);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::clearIDLEinterruptFlag()
{
   SET(clear(), IDLECF);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::sendByte (uint8_t val)
{
   transmitData().reg = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::setTimeOutBitQty (uint32_t val)
{
   recieverTmeout().reg = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::enableReceiveTimeout()
{
   SET(conf2(), RTOEN);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::enableReceiveTimeoutInterupt()
{
   SET(conf1(), RTOIE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
bool USARTx<adr,DMArx,DMAtx>::isReceiveTimeoutInterrupt()
{
   return IS_SET(status(), RTOF);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::clearReceiveTimeoutInterruptFlag()
{
   SET(clear(), RTOCF);
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class RXpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsRXsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<RXpin, PA3>::value
                            or std::is_same<RXpin, PA10>::value
                            or std::is_same<RXpin, PA15>::value
                            or std::is_same<RXpin, PB7>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class TXpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsTXsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<TXpin, PA2>::value
                            or std::is_same<TXpin, PA9>::value
                            or std::is_same<TXpin, PA14>::value
                            or std::is_same<TXpin, PB6>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
template<class RTSpin>
constexpr bool USARTx<adr,DMArx,DMAtx>::IsRTSsupport()
{
   return
      Base == USART1_BASE ?    std::is_same<RTSpin, PA1>::value
                            or std::is_same<RTSpin, PA12>::value
      :
      false;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr PinConf_t USARTx<adr,DMArx,DMAtx>::PinConfigure()
{
   return
      Base == USART1_BASE ? PinConf_t::AlternateFunc1
      :
      PinConf_t::Input;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr uint32_t USARTx<adr,DMArx,DMAtx>::ReceiveDataAdr()
{
   return Base + USART_ral::RDR_t::Offset;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr uint32_t USARTx<adr,DMArx,DMAtx>::TransmitDataAdr()
{
   return Base + USART_ral::TDR_t::Offset;
}


template<uint32_t adr, class DMArx, class DMAtx>
constexpr IRQn_Type
USARTx<adr,DMArx,DMAtx>::IRQn()
{
   return Base == USART1_BASE ? USART1_IRQn : NonMaskableInt_IRQn;
}

#endif

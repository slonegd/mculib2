#pragma once

// пока тут всё для f4 серии, а надо бы сначала для f0 сделать
#if defined(STM32F405xx) or defined(STM32F030x6)



#endif


#if defined(STM32F405xx)

template <uint32_t adr, class DMArx_, class DMAtx_>
void USARTx<adr,DMArx_,DMAtx_>::ClockEnable()
{
   static constexpr uint32_t Mask = 
         Base == USART1_BASE ? RCC_APB2ENR_USART1EN_Msk :
         Base == USART2_BASE ? RCC_APB1ENR_USART2EN_Msk :
         Base == USART3_BASE ? RCC_APB1ENR_USART3EN_Msk :
         Base == USART6_BASE ? RCC_APB2ENR_USART6EN_Msk : 0;
   static constexpr uint32_t Offset = 
         Base == USART1_BASE ? (uint32_t)RCC_ral::APB2ENR_t::Offset :
         Base == USART2_BASE ? (uint32_t)RCC_ral::APB1ENR_t::Offset :
         Base == USART3_BASE ? (uint32_t)RCC_ral::APB1ENR_t::Offset :
         Base == USART6_BASE ? (uint32_t)RCC_ral::APB2ENR_t::Offset : 0;
   *(uint32_t*)(RCC_BASE + Offset) |= Mask;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::Enable (bool val)
{
   BIT_BAND(conf1(), UE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::RXenable (bool val)
{
   BIT_BAND(conf1(), RE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::TXenable (bool val)
{
   BIT_BAND(conf1(), TE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::DMAtxEnable()
{
   BIT_BAND(conf3(), DMAT) = true;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::DMArxEnable()
{
   BIT_BAND(conf3(), DMAR) = true;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::SetBoudRate (Boudrate val)
{
   if (bus == RCC_t::Bus::APB1) {
      boudrate().reg = RCC_t::getAPB1clock() / val;
   } else if (bus == RCC_t::Bus::APB2) {
      boudrate().reg = RCC_t::getAPB2clock() / val;
   }
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::ParityEnable (bool val)
{
   BIT_BAND(conf1(), PCE) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::SetParity (Parity val)
{
   BIT_BAND(conf1(), PS) = val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::SetStopBits (StopBits val)
{
   auto& tmp = BIT_BAND(conf2(), STOP);
   tmp = val;
   BIT_BAND_NEXT(tmp) = val >> 1;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::EnableIDLEinterrupt()
{
   BIT_BAND(conf1(), IDLEIE) = true;
}


template<uint32_t adr, class DMArx, class DMAtx> 
bool USARTx<adr,DMArx,DMAtx>::IsIDLEinterrupt()
{
   return BIT_BAND(status(), IDLE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::ClearIDLEinterruptFlag()
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

#elif defined(STM32F030x6)

template <uint32_t adr, class DMArx_, class DMAtx_>
void USARTx<adr,DMArx_,DMAtx_>::ClockEnable()
{
   RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::Enable (bool val)
{
   if (val)
      SET(conf1(), UE);
   else
      CLEAR(conf1(), UE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::RXenable (bool val)
{
   if (val)
      SET(conf1(), RE);
   else
      CLEAR(conf1(), RE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::TXenable (bool val)
{
   if (val)
      SET(conf1(), TE);
   else
      CLEAR(conf1(), TE);
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
void USARTx<adr,DMArx,DMAtx>::SetBoudRate (Boudrate val)
{
   boudrate().reg = RCC_t::getAPB2clock() / val;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::ParityEnable (bool val)
{
   if (val)
      SET(conf1(), PCE);
   else
      CLEAR(conf1(), PCE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::SetParity (Parity val)
{
   if (val)
      SET(conf1(), PS);
   else
      CLEAR(conf1(), PS);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::SetStopBits (StopBits val)
{
   uint32_t tmp = conf2().reg;
   tmp &= ~_2BIT_TO_MASK(conf2(), STOP);
   tmp |= VAL_TO_MASK(conf2(), STOP, val);
   conf2().reg = tmp;
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::EnableIDLEinterrupt()
{
   SET(conf1(), IDLEIE);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::ClearIDLEinterruptFlag()
{
   SET(clear(), IDLECF);
}


template<uint32_t adr, class DMArx, class DMAtx> 
void USARTx<adr,DMArx,DMAtx>::sendByte (uint8_t val)
{
   transmitData().reg = val;
}


#endif

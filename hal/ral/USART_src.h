#pragma once

// пока тут всё для f4 серии, а надо бы сначала для f0 сделать

template <uint32_t Adr, class DMArx_, class DMAtx_>
void USARTx<Adr,DMArx_,DMAtx_>::ClockEnable()
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
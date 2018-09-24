#pragma once

#include "pin.h"
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////
//  00   00       0000000
//  00   00       00   00
//  00   00       00   00
//  0000000       00   00
//       00       00   00
//       00       0000000
///////////////////////////////////////////////////////////////////////////////
#if defined(STM32F4) or defined(STM32F0)

#endif


///////////////////////////////////////////////////////////////////////////////
//  00   00
//  00   00
//  00   00
//  0000000
//       00
//       00
///////////////////////////////////////////////////////////////////////////////

#if defined(STM32F4)


///////////////////////////////////////////////////////////////////////////////
//  0000000
//  00   00
//  00   00
//  00   00
//  00   00
//  0000000
///////////////////////////////////////////////////////////////////////////////
#elif defined(STM32F0)

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::preloadEnable()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCMR.output.OC1PE = true;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCMR.output.OC2PE = true;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCMR.output.OC3PE = true;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCMR.output.OC4PE = true;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::preloadDisable()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCMR.output.OC1PE = false;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCMR.output.OC2PE = false;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCMR.output.OC3PE = false;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCMR.output.OC4PE = false;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::compareEnable()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCER.CC1E = true;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCER.CC2E = true;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCER.CC3E = true;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCER.CC4E = true;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::compareDisable()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCER.CC1E = false;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCER.CC2E = false;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCER.CC3E = false;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCER.CC4E = false;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::compareToggle()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCER.CC1E ^= true;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCER.CC2E ^= true;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCER.CC3E ^= true;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCER.CC4E ^= true;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
bool template_TIM<adr, Pointer>::isCompareEnable()
{
   if      constexpr (channel == Channel::_1)  return Pointer::get()->CCER.CC1E;
   else if constexpr (channel == Channel::_2)  return Pointer::get()->CCER.CC2E;
   else if constexpr (channel == Channel::_3)  return Pointer::get()->CCER.CC3E;
   else if constexpr (channel == Channel::_4)  return Pointer::get()->CCER.CC4E;
}

template <uint32_t adr, class Pointer>
template<typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::setCompareValue(uint32_t v)
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCR1 = v;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCR2 = v;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCR3 = v;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCR4 = v;
}

template <uint32_t adr, class Pointer>
template<typename TIM_detail::SelectionCompareMode v, typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::selectCompareMode()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCMR.output.CC1S = v;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCMR.output.CC2S = v;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCMR.output.CC3S = v;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCMR.output.CC4S = v;
}

template <uint32_t adr, class Pointer>
template<typename TIM_detail::Output_bits::CompareMode v, typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::set()
{
   if      constexpr (channel == Channel::_1)  Pointer::get()->CCMR.output.OC1M = v;
   else if constexpr (channel == Channel::_2)  Pointer::get()->CCMR.output.OC2M = v;
   else if constexpr (channel == Channel::_3)  Pointer::get()->CCMR.output.OC3M = v;
   else if constexpr (channel == Channel::_4)  Pointer::get()->CCMR.output.OC4M = v;
}

template <uint32_t adr, class Pointer>
template<typename TIM_detail::CCER_bits::Polarity v, typename template_TIM<adr, Pointer>::Channel channel>
void template_TIM<adr, Pointer>::set()
{
   if        constexpr (channel == Channel::_1) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC1P  = false;
         Pointer::get()->CCER.CC1NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.CC1P  = true;
         Pointer::get()->CCER.CC1NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC1P  = true;
         Pointer::get()->CCER.CC1NP = true;
      }
   } else if constexpr (channel == Channel::_2) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC2P  = false;
         Pointer::get()->CCER.CC2NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.CC2P  = true;
         Pointer::get()->CCER.CC2NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC2P  = true;
         Pointer::get()->CCER.CC2NP = true;
      }
   } else if constexpr (channel == Channel::_3) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC3P  = false;
         Pointer::get()->CCER.CC3NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.CC3P  = true;
         Pointer::get()->CCER.CC3NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC3P  = true;
         Pointer::get()->CCER.CC3NP = true;
      }
   } else if constexpr (channel == Channel::_4) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC4P  = false;
         Pointer::get()->CCER.CC4NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.CC4P  = true;
         Pointer::get()->CCER.CC4NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC4P  = true;
         Pointer::get()->CCER.CC4NP = true;
      }
   }
}

template <uint32_t adr, class Pointer>
template <class PIN>
constexpr typename template_TIM<adr, Pointer>::Channel template_TIM<adr,Pointer>::channel()
{
   if        constexpr (std::is_same_v<template_TIM,TIM1>) {

      if      constexpr (std::is_same_v<PIN,PA8>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PA9>)  return Channel::_2;
      else if constexpr (std::is_same_v<PIN,PA10>) return Channel::_3;
      else if constexpr (std::is_same_v<PIN,PA11>) return Channel::_4;

   } else if constexpr (std::is_same_v<template_TIM,TIM3>) {

      if      constexpr (std::is_same_v<PIN,PA6>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PB4>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PC6>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PA7>)  return Channel::_2;
      else if constexpr (std::is_same_v<PIN,PB5>)  return Channel::_2;
      else if constexpr (std::is_same_v<PIN,PC7>)  return Channel::_2;
      else if constexpr (std::is_same_v<PIN,PB0>)  return Channel::_3;
      else if constexpr (std::is_same_v<PIN,PC8>)  return Channel::_3;
      else if constexpr (std::is_same_v<PIN,PB1>)  return Channel::_4;
      else if constexpr (std::is_same_v<PIN,PC9>)  return Channel::_4;

   } else if constexpr (std::is_same_v<template_TIM,TIM14>) {

      if      constexpr (std::is_same_v<PIN,PA4>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PA7>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PB1>)  return Channel::_1;

   } else if constexpr (std::is_same_v<template_TIM,TIM16>) {

      if      constexpr (std::is_same_v<PIN,PA6>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PB8>)  return Channel::_1;

   } else if constexpr (std::is_same_v<template_TIM,TIM17>) {

      if      constexpr (std::is_same_v<PIN,PA7>)  return Channel::_1;
      else if constexpr (std::is_same_v<PIN,PB9>)  return Channel::_1;
   }

}

template <uint32_t adr, class Pointer>
template <class PIN>
constexpr typename GPIO_ral::AF template_TIM<adr,Pointer>::AltFunc()
{
   if      constexpr (std::is_same_v<template_TIM,TIM1>) return GPIO_ral::AF::_2;
   else if constexpr (std::is_same_v<template_TIM,TIM3>) {

      if      constexpr (std::is_same_v<PIN,PA6>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PB4>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PC6>) return GPIO_ral::AF::_0;
      else if constexpr (std::is_same_v<PIN,PA7>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PB5>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PC7>) return GPIO_ral::AF::_0;
      else if constexpr (std::is_same_v<PIN,PB0>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PC8>) return GPIO_ral::AF::_0;
      else if constexpr (std::is_same_v<PIN,PB1>) return GPIO_ral::AF::_1;
      else if constexpr (std::is_same_v<PIN,PC9>) return GPIO_ral::AF::_0;

   } else if constexpr (std::is_same_v<template_TIM,TIM14>) {

      if      constexpr (std::is_same_v<PIN,PA4>) return GPIO_ral::AF::_4;
      else if constexpr (std::is_same_v<PIN,PA7>) return GPIO_ral::AF::_4;
      else if constexpr (std::is_same_v<PIN,PB1>) return GPIO_ral::AF::_0;

   } else if constexpr (std::is_same_v<template_TIM,TIM16>) {

      if      constexpr (std::is_same_v<PIN,PA6>) return GPIO_ral::AF::_5;
      else if constexpr (std::is_same_v<PIN,PB8>) return GPIO_ral::AF::_2;

   } else if constexpr (std::is_same_v<template_TIM,TIM17>) {

      if      constexpr (std::is_same_v<PIN,PA7>) return GPIO_ral::AF::_5;
      else if constexpr (std::is_same_v<PIN,PB9>) return GPIO_ral::AF::_2;
   }

}

#endif



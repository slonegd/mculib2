#pragma once

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
template<uint8_t channel>
void template_TIM<adr, Pointer>::preloadEnable()
{
   if      constexpr (channel == 1)  Pointer::get()->CCMR.output.OC1PE = true;
   else if constexpr (channel == 2)  Pointer::get()->CCMR.output.OC2PE = true;
   else if constexpr (channel == 3)  Pointer::get()->CCMR.output.OC3PE = true;
   else if constexpr (channel == 4)  Pointer::get()->CCMR.output.OC4PE = true;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::preloadDisable()
{
   if      constexpr (channel == 1)  Pointer::get()->CCMR.output.OC1PE = false;
   else if constexpr (channel == 2)  Pointer::get()->CCMR.output.OC2PE = false;
   else if constexpr (channel == 3)  Pointer::get()->CCMR.output.OC3PE = false;
   else if constexpr (channel == 4)  Pointer::get()->CCMR.output.OC4PE = false;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::compareEnable()
{
   if      constexpr (channel == 1)  Pointer::get()->CCER.CC1E = true;
   else if constexpr (channel == 2)  Pointer::get()->CCER.CC2E = true;
   else if constexpr (channel == 3)  Pointer::get()->CCER.CC3E = true;
   else if constexpr (channel == 4)  Pointer::get()->CCER.CC4E = true;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::compareDisable()
{
   if      constexpr (channel == 1)  Pointer::get()->CCER.CC1E = false;
   else if constexpr (channel == 2)  Pointer::get()->CCER.CC2E = false;
   else if constexpr (channel == 3)  Pointer::get()->CCER.CC3E = false;
   else if constexpr (channel == 4)  Pointer::get()->CCER.CC4E = false;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::compareToggle()
{
   if      constexpr (channel == 1)  Pointer::get()->CCER.CC1E ^= true;
   else if constexpr (channel == 2)  Pointer::get()->CCER.CC2E ^= true;
   else if constexpr (channel == 3)  Pointer::get()->CCER.CC3E ^= true;
   else if constexpr (channel == 4)  Pointer::get()->CCER.CC4E ^= true;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::isCompareEnable()
{
   if      constexpr (channel == 1)  return Pointer::get()->CCER.CC1E;
   else if constexpr (channel == 2)  return Pointer::get()->CCER.CC2E;
   else if constexpr (channel == 3)  return Pointer::get()->CCER.CC3E;
   else if constexpr (channel == 4)  return Pointer::get()->CCER.CC4E;
}

template <uint32_t adr, class Pointer>
template<uint8_t channel>
void template_TIM<adr, Pointer>::setCompareValue(uint32_t v)
{
   if      constexpr (channel == 1)  Pointer::get()->CCR1 = v;
   else if constexpr (channel == 2)  Pointer::get()->CCR2 = v;
   else if constexpr (channel == 3)  Pointer::get()->CCR3 = v;
   else if constexpr (channel == 4)  Pointer::get()->CCR4 = v;
}

template <uint32_t adr, class Pointer>
template<SelectionCompareMode v, uint8_t channel>
void template_TIM<adr, Pointer>::selectCompareMode()
{
   if      constexpr (channel == 1)  Pointer::get()->CCMR.output.CC1S = v;
   else if constexpr (channel == 2)  Pointer::get()->CCMR.output.CC2S = v;
   else if constexpr (channel == 3)  Pointer::get()->CCMR.output.CC3S = v;
   else if constexpr (channel == 4)  Pointer::get()->CCMR.output.CC4S = v;
}

template <uint32_t adr, class Pointer>
template<CompareMode v, uint8_t channel>
void template_TIM<adr, Pointer>::set()
{
   if      constexpr (channel == 1)  Pointer::get()->CCMR.output.OC1M = v;
   else if constexpr (channel == 2)  Pointer::get()->CCMR.output.OC2M = v;
   else if constexpr (channel == 3)  Pointer::get()->CCMR.output.OC3M = v;
   else if constexpr (channel == 4)  Pointer::get()->CCMR.output.OC4M = v;
}

template <uint32_t adr, class Pointer>
template<Polarity v, uint8_t channel>
void template_TIM<adr, Pointer>::set()
{
   if        constexpr (channel == 1) {
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
   } else if constexpr (channel == 2) {
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
   } else if constexpr (channel == 3) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC3P  = false;
         Pointer::get()->CCER.CC3NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.CC3P  = true;
         Pointer::get()->CCER.CC3NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC1P  = true;
         Pointer::get()->CCER.CC1NP = true;
      }
   } else if constexpr (channel == 4) {
      if      constexpr (v == Polarity::rising) {
         Pointer::get()->CCER.CC4P  = false;
         Pointer::get()->CCER.CC4NP = false;
      } else if constexpr (v == Polarity::falling) {
         Pointer::get()->CCER.C41P  = true;
         Pointer::get()->CCER.C41NP = false;
      } else if constexpr (v == Polarity::both) {
         Pointer::get()->CCER.CC4P  = true;
         Pointer::get()->CCER.CC4NP = true;
      }
   }
}

#endif



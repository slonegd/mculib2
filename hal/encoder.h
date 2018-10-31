#pragma once

#include "tim_periph.h"
#include "pin.h"
#include "pins_variadic.h"
#include <type_traits>

template<class TIM_, class PinA, class PinB, bool inverted = false>
struct Encoder
{
   Encoder ();  
   operator int16_t();
};


template<class TIM_, class PinA, class PinB, bool inverted>
Encoder<TIM_,PinA,PinB,inverted>::Encoder()
{
   constexpr auto pinAchannel = TIM_::template channel<PinA>();
   constexpr auto pinBchannel = TIM_::template channel<PinB>();
   static_assert (
      pinAchannel == 1 or pinAchannel == 2,
      "PinA вывод контроллера не поддерживает функцию энкодера с этим таймером" 
   );
   static_assert (
      pinBchannel == 1 or pinBchannel == 2,
      "PinB вывод контроллера не поддерживает функцию энкодера с этим таймером" 
   );
   static_assert (
      pinAchannel != pinBchannel,
      "PinA и PinB не должны принадлежать одному каналу таймера" 
   );

   constexpr auto altFuncPinA = TIM_::template AltFunc<PinA>();
   constexpr auto altFuncPinB = TIM_::template AltFunc<PinB>();
   PinA::template configureAltFunction<altFuncPinA>();
   PinB::template configureAltFunction<altFuncPinB>();
  
   TIM_::clockEnable();
   TIM_::template set<TIM_::SlaveMode::Encoder1>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::Input, pinAchannel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::Input, pinBchannel>();
   if (inverted) {
      TIM_::template set<TIM_::Polarity::falling, pinAchannel>();
   }
   TIM_::clearCounter();
   TIM_::counterEnable();
}


template<class TIM_, class PinA, class PinB, bool inverted>
Encoder<TIM_,PinA,PinB,inverted>::operator int16_t()
{
   int16_t res = static_cast<int16_t>(TIM_::getCounter());
   TIM_::clearCounter();
   return res;
}


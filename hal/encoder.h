#pragma once

#include "TIM.h"
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
   constexpr auto pinAchannel = Channel<TIM_,PinA>();
   constexpr auto pinBchannel = Channel<TIM_,PinB>();
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

   constexpr auto altFuncPinA = AltFunc<TIM_,PinA>();
   constexpr auto altFuncPinB = AltFunc<TIM_,PinB>();
   PinA::template configureAltFunction<altFuncPinA>();
   PinB::template configureAltFunction<altFuncPinB>();
  
   TIM_::clockEnable();
   TIM_::template setSlaveMode<TIM_::SlaveMode::Encoder1>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, pinAchannel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, pinBchannel>();
   if (inverted) {
      TIM_::template setPolarity<TIM_::Polarity::falling, pinAchannel>();
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


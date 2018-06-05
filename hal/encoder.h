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
   static_assert (
      (std::is_same<TIM_,TIM3>::value) | (std::is_same<TIM_,TIM8>::value),
      "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
   );

   Pins<PinA,PinB>::template configure<PinConf_t::AlternateFunc3>();
  
   TIM_::clockEnable();
   TIM_::template setSlaveMode<TIM_::SlaveMode::Encoder1>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 1_channel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 2_channel>();
   if (inverted) {
      TIM_::template setPolarity<TIM_::Polarity::falling, 1_channel>();
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


#pragma once

#include "TIM.h"
#include "pin_hal.h"
#include <type_traits>

template<class TIM_, class PinA, class PinB>
class Encoder
{
public:
   Encoder () 
   {
      static_assert (
         (std::is_same_v<TIM_,TIM3>) | (std::is_same_v<TIM_,TIM8>),
         "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
      );
      init();
   }

  uint16_t getCounter()  { return counter; }

   void operator() ();

private:
   uint16_t counter;
   
   void init();
  

};


template<class TIM_, class PinA, class PinB>
void Encoder<TIM_,Pin_>::init()
{
  
   TIM_::clockEnable();
   TIM_::template setSlaveMode<TIM_::SlaveMode::Encoder3>();
   TIM_::template SelectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 1_channel>();
   TIM_::template SelectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 2_channel>();
   TIM_::clearCounter();
   TIM_::CounterEnable();
}

template<class TIM_, class PinA, class PinB>
void Encoder<TIM_,Pin_>::operator() ()
{
   counter = TIM_::getCounter();
}
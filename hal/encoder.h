#pragma once

#include "TIM.h"
#include "pin.h"
#include <type_traits>

template<class TIM_, class PinA, class PinB>
class Encoder
{
public:
   Encoder () 
   {
      static_assert (
         (std::is_same<TIM_,TIM3>::value) | (std::is_same<TIM_,TIM8>::value),
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
void Encoder<TIM_,PinA,PinB>::init()
{
  
   TIM_::clockEnable();
   TIM_::template setSlaveMode<TIM_::SlaveMode::Encoder3>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 1_channel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::InputTIFirst, 2_channel>();
   TIM_::clearCounter();
   TIM_::counterEnable();
}

template<class TIM_, class PinA, class PinB>
void Encoder<TIM_,PinA,PinB>::operator() ()
{
   counter = TIM_::getCounter();
}
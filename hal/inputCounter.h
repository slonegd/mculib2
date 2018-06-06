/*
 * Класс, который считает входящие импульсы
 */
#pragma once

#include "TIM.h"
#include "pin.h"
#include <type_traits>


template<class TIM_, class Pin_>
class InputCounter
{
public:
   InputCounter () : frequency {0}
   {
      static_assert (
         (channel == 1) | (channel == 2),
         "Вывод контроллера не поддерживает функцию счёта внешнего сигнала"
      );
      init();
   }
	
  uint16_t get()  { return frequency; }
   
   void operator() ();

   
private:
   static const uint8_t channel = Channel<TIM_,Pin_>();
   uint16_t frequency;
   Timer timer;
   void init();
   using Trigger = typename TIM_::Trigger;
};





template<class TIM_, class Pin_>
void InputCounter<TIM_,Pin_>::init()
{
  
   TIM_::clockEnable();
   TIM_::template setTrigger <
      channel == 1 ? Trigger::FiltrTI1 : Trigger::FiltrTI2
   >();
   TIM_::template setPolarity<TIM_::Polarity::both, channel>();
   TIM_::template setSlaveMode<TIM_::SlaveMode::ExternalClock>();

   constexpr PinConf_t conf =
      std::is_same<TIM_,TIM1>::value  ? PinConf_t::AlternateFunc2: 
                                        PinConf_t::AlternateFunc1;
   Pin_::template configure<conf>();
   TIM_::counterEnable();
   timer.setTimeAndStart(500_ms);
}


template<class TIM_, class Pin_>
void InputCounter<TIM_,Pin_>::operator() ()
{
   if (timer.event())
   {
      frequency = TIM_::getCounter();
      TIM_::clearCounter();
   }
}
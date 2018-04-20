/*
 * Класс, который считает входящие импульсы
 */
#pragma once

#include "TIM.h"
#include "pin_hal.h"
#include <type_traits>


template<class TIM_, class Pin_>
class InputCounter
{
public:
   InputCounter (Timer& timer) : frequency(0), timer(timer) 
   {
      static_assert (
         (channel == 1) | (channel == 2),
         "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
      );
      init();
   }
	
  uint16_t getFrequency()  { return frequency; }
   
   void operator() ();

   
private:
   static const uint8_t channel = Channel<TIM_,Pin_>();
   uint16_t frequency;
   Timer& timer;
   void init();
   using Filtr = typename TIM_::Trigger;
};





template<class TIM_, class Pin_>
void InputCounter<TIM_,Pin_>::init()
{
  
   TIM_::clockEnable();
   constexpr Filtr filtr = channel == 1 ? Filtr::FiltrTI1 : Filtr::FiltrTI2;
   TIM_::template setTrigger<filtr>();

    TIM_::template setOutputPolarity<TIM_::OutputPolarity::both, channel>();
   
    constexpr typename Pin_::PinConf_t conf =  std::is_same<TIM_,TIM1>::value  ? Pin_::PinConf_t::AlternateFunc2PushPull: 
	 																									 Pin_::PinConf_t::AlternateFunc1PushPull;

   
   Pin_::template Configure<conf>();
   TIM_::CounterEnable();
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
/*
 * Класс, который считает входящие импульсы
 */
#pragma once

#include "TIM.h"
#include "pin.h"
#include "timers.h"
#include <type_traits>


template<class TIM_, class Pin_>
class InputCounter : TickSubscriber
{
public:
   InputCounter();
   operator uint16_t()  { return frequency; }

   
private:
   static constexpr uint8_t channel = Channel<TIM_,Pin_>();
   uint16_t frequency {0};
   uint16_t tickCounter {0};
   void notify() override;
};




template<class TIM_, class Pin_>
InputCounter<TIM_,Pin_>::InputCounter()
{
   static_assert (
      (channel == 1) | (channel == 2),
      "Вывод контроллера не поддерживает функцию счёта внешнего сигнала"
   );

   TIM_::clockEnable();
   using Trigger = typename TIM_::Trigger;
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
   tickUpdater.subscribe (this);
}



template<class TIM_, class Pin_>
void InputCounter<TIM_,Pin_>::notify()
{
   if (++tickCounter == 500_ms) {
      tickCounter = 0;
      frequency = TIM_::getCounter();
      TIM_::clearCounter();
   }
}
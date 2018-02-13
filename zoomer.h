/******************************************************************************
 * 
 * Класс управления ультразвуковой пищалкой
 * 
 */////////////////////////////////////////////////////////////////////////////


#pragma once

#include "pwm_hal.h"
#include "timers.h"
#include "meta.h"
#include <initializer_list>
		


template<class PWM, uint8_t QueueSize = 6>
class Zoomer
{
public:
   // freq - частота кварцевой пищалки
   Zoomer(PWM& pwm, Timer& timer, uint32_t freq);
   // добавляет очередь сигналов/пауз, первый всегда сигнал
   // не более QueueSize аргументов
   template<class ... T>
   void addBeepPause (T ... args);
   // непосредственно включает/выключает пищалку
   // должна периодически вызываться
   void operator () ();



private:
   // очередь длительности гудков/пауз, первый всегда гудок
   uint32_t queue[QueueSize];
   uint8_t currentN;
   PWM& pwm;
   Timer& timer;
};



template<class PWM, uint8_t QueueSize> 
Zoomer<PWM, QueueSize>::Zoomer(PWM& pwm, Timer& timer, uint32_t freq)
   : queue{0}, currentN(0), pwm(pwm), timer(timer)
{
   pwm.setFreq(freq);
   pwm.setD(50);
}


template<class PWM, uint8_t QueueSize> 
template<class ... T>
void Zoomer<PWM, QueueSize>::addBeepPause (T ... args)
{
   static_assert(
      QtyTypes<T...>::value < QueueSize,
      "увеличьте в определении класса размер очереди (шаблонный параметр)"
   );
   uint8_t i = 0;
   for (auto&& arg : std::initializer_list<uint32_t>{args...} )
      queue[i++] = arg;
   currentN = 0;
   timer.setTimeAndStart (queue[currentN]);
   pwm.outEnable();
}


template<class PWM, uint8_t QueueSize> 
void Zoomer<PWM, QueueSize>::operator () ()
{
   if ( timer.event() ) {
      queue[currentN++] = 0;
      if ( queue[currentN] != 0 ) {
         timer.setTime (queue[currentN]);
         pwm.outToggle();
      } else {
         pwm.outDisable();
         timer.stop();
      }
   }
}
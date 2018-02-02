/******************************************************************************
 * 
 * Класс управления ультразвуковой пищалкой
 * 
 */////////////////////////////////////////////////////////////////////////////


#pragma once

#include "pwm_hal.h"
#include "timers.h"


template<class PWM>
class Zoomer
{
public:
   // freq - частота кварцевой пищалки
   Zoomer(PWM& pwm, Timer& timer, uint32_t freq);
   // qty - количество гудков, длительностью ms
   void beep (uint32_t ms, uint8_t qty);
   // непосредственно включает/выключает пищалку
   // должна периодически вызываться
   void operator () ();

private:
   // Количество гудков и пауз между ними
   uint8_t qtyLeft;
   PWM& pwm;
   Timer& timer;
};



template<class PWM> Zoomer<PWM>::Zoomer(PWM& pwm, Timer& timer, uint32_t freq)
   : qtyLeft(0), pwm(pwm), timer(timer) 
{
   pwm.setFreq(freq);
   pwm.setD(50);
}


template<class PWM> void Zoomer<PWM>::beep (uint32_t ms, uint8_t qty)
{
   qtyLeft = qty * 2 - 1;
   timer.setTimeAndStart(ms);
   pwm.outEnable();
}


template<class PWM> void Zoomer<PWM>::operator () ()
{
   if (qtyLeft != 0 && timer.event()) {
      qtyLeft--;
      pwm.outToggle();
      if (qtyLeft == 0) {
         timer.stop();
         pwm.outDisable();
      }
   }
}
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
   static const uint32_t ShortBeepDur = 150_ms;
   static const uint32_t LongBeepDur  = 1_s;

   Zoomer(PWM& pwm, Timer& timer, uint32_t freq)
      : beepQty(0), pwm(pwm), timer(timer) 
   {
      pwm.setFreq(freq);
      pwm.setD(50);
   }


   void shortBeep (uint8_t qty)
   {
      beepQty = qty;
      timer.setTimeAndStart(ShortBeepDur);
      pwm.outEnable();
   }


   void longBeep (uint8_t qty)
   {
      beepQty = qty;
      timer.setTimeAndStart(LongBeepDur);
      pwm.outEnable();
   }


   void operator () ()
   {
      if (beepQty != 0) {
         if (timer.event()) {
            if (beepQty == 1) {
               beepQty = 0;
               pwm.outDisable();
               timer.stop();
            } else if (pause) {
               beepQty--;
               pwm.outEnable();
               pause = false;
            } else {
               pwm.outDisable();
               pause = true;
            }
         }
      }
   }



private:
   uint8_t beepQty;
   bool pause;
   PWM& pwm;
   Timer& timer;
};
/**
 * пример конечного автомата
 **/

#include <stdint.h>

#include "defines.h"
#include "RCC.h"
#include "FLASH.h"
#include "pin.h"
#include "timers.h"
#include "buttons.h"
#include "literals.h"

// эта функция вызываеться первой в startup файле
extern "C" void CLKinit (void)
{
   FLASH::setLatency (FLASH::Latency::_5);
   RCC::HSEon();
   RCC::waitHSEready();
   RCC::setAHBprescaler (RCC_ral::AHBprescaler::AHBnotdiv);
   RCC::setAPB1prescaler (RCC_ral::APBprescaler::APBdiv4);
   RCC::setAPB2prescaler (RCC_ral::APBprescaler::APBdiv2);
   RCC::systemClockSwitch (RCC_ral::SystemClockSwitch::CS_PLL);
   RCC::setPLLM<4>();
   RCC::setPLLN<168>();
   RCC::setPLLP (RCC_ral::PLLPdiv::PLLdiv2);
//  RCC::setPLLQ<4>();
   RCC::setPLLsource (RCC_ral::PLLsource::sHSE);
   RCC::PLLon();
   RCC::waitPLLready();
}


using BlueLed   = PD15;
using RedLed    = PD14;
using OrangeLed = PD13;
using GreenLed  = PD12;

using User      = PA0;

using US    = BlueLed;
using Pump  = RedLed;
using Buble = OrangeLed;
using Tick  = GreenLed;




int main(void)
{

   Pins<US,Pump,Buble,Tick>::configure<PinConf_t::Output>();
   Timer timer;
   Buttons<false, User> button;


   enum class State {
      us, pump, buble, wait
   };
   State state {State::wait};
   
   while (1)
   {

      auto stop = [&]() {
         if (button.push<User>()) {
            US::clear();
            Pump::clear();
            Buble::clear();
            state = State::wait;
         }
      };


      switch (state) {
         case State::wait :
            if (button.push<User>())
               state = State::us;
         break;

         case State::us :
            timer.start (5_s);
            US::set();
            if (timer.done()) {
               timer.stop();
               US::clear();
               state = State::pump;
            }
            stop();
         break;

         case State::pump :
            timer.start (3_s);
            Pump::set();
            if (timer.done()) {
               timer.stop();
               Pump::clear();
               state = State::buble;
            }
            stop();
         break;

         case State::buble :
            timer.start (5_s);
            Buble::set();
            if (timer.done()) {
               timer.stop();
               Buble::clear();
               state = State::wait;
            }
            stop();
         break;
      } // switch (state) {
      
      __WFI();
   } // while (1)
}


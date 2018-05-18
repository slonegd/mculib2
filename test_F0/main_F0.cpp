#include "init.h"
#include "meta.h"
#include "pins_variadic.h"


volatile uint32_t f;


int main(void)
{
   makeDebugVar();

   Pins<Led,BlueLed>::configure<PinConf_t::Output>();

   // CONFIGURE_PIN (Led, Output);
   // CONFIGURE_PIN (BlueLed, Output);

   //test
   TIM1_d->CNT.reg = 0;
   RCC_d->CR_t::bits.dcb1 = 0;


   pwm.setFreq(2000_Hz);
   pwm.setD(50_percent);
   pwm.outEnable();
  
  
   ledTimer.setTimeAndStart (100_ms);  
   
   offTimer.setTimeAndStart (1000);
   spiTimer.setTimeAndStart (100);

   // тест метапрограммирования на вариадиках
   static_assert (QtyTypes<PA0,PA1,PA3>::value == 3, "");
   using Test = At<3,PA0,PA1,PA3>::Result;
   static_assert (std::is_same<Test,PA3>::value, "");
   static_assert (Position<PA1,PA0,PA1,PA3>::value == 2, "");

   buttons.push<But1>();

   while (1)
   {
      timers.update();
      zoomer();
      buttons();
      counter();
      ssi();
      
      f = counter.getFrequency();

      if (ledTimer.event())
         BlueLed::Toggle();

      if (offTimer.event()) {
         Led::Set();
         offTimer.stop();
         onTimer.setTimeAndStart(1000);
         zoomer.beep (100_ms, 2_cnt);
      };
      if (onTimer.event()) {
         Led::Clear();
         onTimer.stop();
         offTimer.setTimeAndStart(1000);
      };


      if ( spiTimer.event() ) {
         flash.update();
         spi.data.time++;
         spi.startTx();
      }

   }

}
extern "C" void SysTick_Handler()
{
    timers.tick();
}

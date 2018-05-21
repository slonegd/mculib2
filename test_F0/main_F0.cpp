#include "init.h"
#include "meta.h"
#include "pins_variadic.h"


volatile uint32_t f;


int main(void)
{
   makeDebugVar();

   // Pins<GreenLed,BlueLed>::configure<PinConf_t::Output>();

   CONFIGURE_PIN (GreenLed, Output);
   // CONFIGURE_PIN (BlueLed, Output);


   pwm.setFreq(1000_Hz);
   pwm.setD(50_percent);
   pwm.outEnable();
  
  
   ledTimer.setTimeAndStart (500_ms);  
   
   spiTimer.setTimeAndStart (1_s);

   buttons.push<But1>();

   while (1)
   {
      timers.update();
      zoomer();
      buttons();
      counter();
      // ssi();
      // modbus(mbRegInAction);
      
      f = counter.get();

      if (ledTimer.event())
         GreenLed::Toggle();


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

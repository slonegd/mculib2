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

   modbus.init ( {
      USART_::Boudrate::BR9600,
      USART_::ParityEn::disable,
      USART_::Parity::even,
      USART_::StopBits::_1
   } );
   modbus.address = 1;

   while (1)
   {
      zoomer();
      buttons();
      counter();
      // ssi();
      modbus (reaction);
      
      f = counter.get();

      if (ledTimer.event())
         GreenLed::Toggle();


      if ( spiTimer.event() ) {
         flash();
         spi.data.time++;
         spi.startTx();
      }

   }

}

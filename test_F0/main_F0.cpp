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


   pwm.freq = 1000_Hz;
   pwm.fillRatio = 500_from1000;
   pwm.outEnable();
  
  
   ledTimer.start (500_ms);  
   
   spiTimer.start (1_s);

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
      modbus (reaction);
      
      f = counter;

      if (ledTimer.event()) {
         GreenLed::toggle();
         current.computeAverage();
         buzzer.beep(1_s);
      }


      if ( spiTimer.event() ) {
         spi.data.time++;
         spi.startTx();
      }

   }

}

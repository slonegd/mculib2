/*****************************************************************************
 * для того, чтобы кирилица вместилась в char этот файл должен быть
 * в кодировке cp1251
 *////////////////////////////////////////////////////////////////////////////
#include "init.h"
#include "something.h"
#include <type_traits>


volatile uint8_t i = 0;
volatile uint32_t N = 0;

auto encoder = Encoder<TIM8, PC6, PC7>();

volatile auto& flash_ = FLASH_t::make();

int main(void)
{
   volatile auto t = sizeof (flash_.CR);
   // к этому моменту уже вызваны CLKinit (инициализация системных частот)
   // и конструкторы глобальных объектов из файла init.h
   makeDebugVar();

   PortsInit ();

   modbus.init ( USART_::Settings {
      USART_::Boudrate::BR9600,
      USART_::ParityEn::disable,
      USART_::Parity::even,
      USART_::StopBits::_1
   } );
   modbus.address = 1;


   // таймер с шим
   // прескаллер спецом, чтбы было видно на индикаторе высокие частоты
   // закоментил для отладки пищалки, которая работает с тем же pwm
   // PWMtimer::SetPrescaller (1000);
   // pwm.setFreq (20000);
   // pwm.setD (50);
   // pwm.outEnable();

   // adc - пока не работает (только для F0 серии)
   // ADC1::ClockEnable();
   // ADCaverage<ADC1, PC0, 16> current;

   // инициализация программных таймеров задач
   ledTimer.start (100_ms);
   // butTimer.setTimeAndStart (200);
   // lcdTimer.setTimeAndStart (5);



   
   while (1)
   {
      modbus (reaction);

      N = encoder;

      if ( ledTimer.event() )
         Leds::Write(i++);

      if ( butTimer.event() ) {
         static bool butActDone = false;
         if ( !Button::isSet() ) {
            butActDone = false;
         } else if ( !butActDone ) {
            butActDone = true;

            static bool goUp = true;
            static uint8_t d = 50;
            d = goUp ? d+10 : d-10;
            goUp = (d == 100) ? false :
                   (d == 0)   ? true  : goUp;
            pwm.fillRatio = d;

            if ( pwm.isOutEnable() )
               pwm.outDisable();
            else 
               pwm.outEnable();

            flash.d2++;

            buzzer.beep(50_ms, 2_cnt);
         }
      }

   } // while (1)
}


//////////////////////////////////////////////////////////////////////////////
//       ПРЕРЫВАНИЯ
//////////////////////////////////////////////////////////////////////////////
// extern "C" void USART2_IRQHandler()
// {
//    modbus.recieveInterruptHandler();
// }

// extern "C" void DMA1_Stream6_IRQHandler()
// {
//    modbus.transmitInterruptHandler();
// }

// extern "C" void Default_Handler()
// {
//    // modbus.recieveInterruptHandler();
// }
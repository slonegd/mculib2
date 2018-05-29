/*****************************************************************************
 * для того, чтобы кирилица вместилась в char этот файл должен быть
 * в кодировке cp1251
 *////////////////////////////////////////////////////////////////////////////
#include "init.h"
#include "something.h"
#include <type_traits>


uint8_t i = 0;
volatile uint16_t N;

// volatile auto TIM2_d = reinterpret_cast<TIM2*>(TIM2::Base);
auto encoder = Encoder<TIM8, PC6, PC7>();

int main(void)
{
   // к этому моменту уже вызваны CLKinit (инициализация системных частот)
   // и конструкторы глобальных объектов из файла init.h
   makeDebugVar();

   PortsInit ();

   modbus.init ( {
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
   ledTimer.setTimeAndStart (500);
   butTimer.setTimeAndStart (200);
   txTimer.setTimeAndStart  (100);
   lcdTimer.setTimeAndStart (5);

   // для отладки
   // modbus.uart.disableRx();

   char string[] = "ПрЁ";
   string[1] = 'i';
   LCD.setLine(string, 0);
   LCD.setLine("пока", 1);

   
   while (1)
   {
      timers.update();
      modbus (reaction);

      N = encoder.getCounter();

      if (std::is_same<PWMout,Rled>::value)
         zoomer();


      if ( lcdTimer.event() ) {
         LCD.setLine("0123456789abcdef",0);
         LCD.setLine("f0123456789abcd",1);
      }


      if ( ledTimer.event() )
         Leds::Write(i++);

      if ( butTimer.event() ) {
         flash.update();
         static bool butActDone = false;
         if ( !Button::IsSet() ) {
            butActDone = false;
         } else if ( !butActDone ) {
            butActDone = true;

            static bool goUp = true;
            static uint8_t d = 50;
            d = goUp ? d+10 : d-10;
            goUp = (d == 100) ? false :
                   (d == 0)   ? true  : goUp;
            pwm.setD (d);

            if ( pwm.isOutEnable() )
               pwm.outDisable();
            else 
               pwm.outEnable();

            flash.data.d2++;

            zoomer.beep(50_ms, 2_cnt);
         }
      }

   } // while (1)
}


//////////////////////////////////////////////////////////////////////////////
//       ПРЕРЫВАНИЯ
//////////////////////////////////////////////////////////////////////////////
extern "C" void SysTick_Handler()
{
   timers.tick();
}

extern "C" void USART1_IRQHandler()
{
   modbus.recieveInterruptHandler();
}

extern "C" void DMA1_Stream6_IRQHandler()
{
   modbus.transmitInterruptHandler();
}
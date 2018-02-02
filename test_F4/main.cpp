/*****************************************************************************
 * для того, чтобы кирилица вместилась в char этот файл должен быть
 * в кодировке cp1251
 *////////////////////////////////////////////////////////////////////////////
#include "init.h"
#include "something.h"
#include <type_traits>

uint8_t i = 0;

int main(void)
{
   // к этому моменту уже вызваны CLKinit (инициализация системных частот)
   // и конструкторы глобальных объектов из файла init.h
   makeDebugVar();

   PortsInit ();

   modbus.uart.init ( {
      USART_::Boudrate::BR9600,
      USART_::ParityEn::disable,
      USART_::Parity::even,
      USART_::StopBits::_1
   } );

   // таймер с шим
   // прескаллер спецом, чтбы было видно на индикаторе высокие частоты
   // закоментил для отладки пищалки, которая работает с тем же pwm
   // PWMtimer::SetPrescaller (1000);
   // pwm.setFreq (20000);
   // pwm.setD (50);
   // pwm.outEnable();

   // adc
   ADC1_t::ClockEnable();
   ADCaverage<ADC1_t, 16, PC0, DMA1stream0> current;

   // инициализация программных таймеров задач
   ledTimer.setTimeAndStart (500);
   butTimer.setTimeAndStart (200);
   txTimer.setTimeAndStart  (100);
   lcdTimer.setTimeAndStart (5);

   //для отладки
   modbus.uart.disableRx();

   char string[] = "ПрЁ";
   string[1] = 'i';
   LCD.setLine(string, 0);
   LCD.setLine("пока", 1);

   
   while (1)
   {
      timers.update();

      if (std::is_same<PWMout,Rled>::value)
         zoomer();

      if ( modbus.incomingMessage() ) {
         modbus.handler();
         modbus.foreachRegForActions (mbRegInAction);
      }

      if ( txTimer.event() ) {
         modbus.uart.buffer[4] = string[0];
         modbus.uart.buffer[5] = string[1];
         modbus.uart.buffer[6] = string[2];
         modbus.uart.buffer[7] = size(string);
         modbus.uart.buffer[8] = StaticAssertTypeEq<PA2,TXpin>();
         modbus.uart.buffer[9] = i;
         modbus.uart.startTX(15);
      }

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
   modbus.idleHandler();
}

extern "C" void DMA1_Stream6_IRQHandler()
{
   modbus.uart.txCompleteHandler();
}
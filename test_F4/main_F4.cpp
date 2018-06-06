/*****************************************************************************
 * ��� ����, ����� �������� ���������� � char ���� ���� ������ ����
 * � ��������� cp1251
 *////////////////////////////////////////////////////////////////////////////
#include "init.h"
#include "something.h"
#include <type_traits>


volatile uint8_t i = 0;
volatile uint32_t N = 0;

auto encoder = Encoder<TIM8, PC6, PC7>();

int main(void)
{
   // � ����� ������� ��� ������� CLKinit (������������� ��������� ������)
   // � ������������ ���������� �������� �� ����� init.h
   makeDebugVar();

   PortsInit ();

   modbus.init ( {
      USART_::Boudrate::BR9600,
      USART_::ParityEn::disable,
      USART_::Parity::even,
      USART_::StopBits::_1
   } );
   modbus.address = 1;


   // ������ � ���
   // ���������� ������, ���� ���� ����� �� ���������� ������� �������
   // ���������� ��� ������� �������, ������� �������� � ��� �� pwm
   // PWMtimer::SetPrescaller (1000);
   // pwm.setFreq (20000);
   // pwm.setD (50);
   // pwm.outEnable();

   // adc - ���� �� �������� (������ ��� F0 �����)
   // ADC1::ClockEnable();
   // ADCaverage<ADC1, PC0, 16> current;

   // ������������� ����������� �������� �����
   ledTimer.setTimeAndStart (100);
   // butTimer.setTimeAndStart (200);
   // lcdTimer.setTimeAndStart (5);



   
   while (1)
   {
      modbus (reaction);
      zoomer();

      N = encoder;

      



      if ( ledTimer.event() )
         Leds::Write(i++);

      if ( butTimer.event() ) {
         flash();
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
            pwm.fillRatio = d;

            if ( pwm.isOutEnable() )
               pwm.outDisable();
            else 
               pwm.outEnable();

            flash.d2++;

            zoomer.beep(50_ms, 2_cnt);
         }
      }

   } // while (1)
}


//////////////////////////////////////////////////////////////////////////////
//       ����������
//////////////////////////////////////////////////////////////////////////////
extern "C" void USART2_IRQHandler()
{
   modbus.recieveInterruptHandler();
}

extern "C" void DMA1_Stream6_IRQHandler()
{
   modbus.transmitInterruptHandler();
}

// extern "C" void Default_Handler()
// {
//    // modbus.recieveInterruptHandler();
// }
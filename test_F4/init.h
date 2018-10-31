#pragma once

#include <stdint.h>
#include "defines.h"
#include "DebugVar.h"
#include "RCC.h"
#include "pin.h"
#include "flash.h"
#include "pwm.h"
#include "flash.h"
#include "timers.h"
#include "pinlist.h"
#include "modbusSlave.h"
#include "HD44780_hal.h"
#include "buzzer.h"
#include "literals.h"
#include "inputCounter.h"
#include "encoder.h"
#include "adc.h"



// discoveri 
using LedPort = PD;
using Bled = PD15;
using Rled = PD14;
using Oled = PD13;
using Gled = PD12;
using Leds = PinList<Bled, Oled>;
using Button = PA0;

Timer ledTimer;
Timer butTimer;
Timer lcdTimer;

// энергонезависимые данные
struct FlashData {
   uint16_t d1 {1};
   uint16_t d2 {3};
};
Flash<FlashData, FLASH::Sector::_2> flash {};

// шим
using PWMout = Rled;
using PWMtimer = TIM4;
using PWM_ = PWM<PWMtimer, PWMout>;
PWM_ pwm;

// зуммер
auto buzzer = Buzzer<PWM_> (pwm, 4000_Hz); 

// LCD
using RSpin = PC4;
using RWpin = PA4;
using Epin  = PA5;
using D4pin = PC0;
using D5pin = PC1;
using D6pin = PC2;
using D7pin = PC3;
using LCDtim = TIM8;
using LCDdma = DMA2stream2;
using LCD_ = HD44780<RSpin, RWpin, Epin, D4pin, D5pin, D6pin, D7pin>;
LCD_ LCD;

// уарт модбаса
using RXpin = PA3;
using TXpin = PA2;
using RTSpin = PD4; // временно изменил с PA5 для отладки LCD
using LEDpin = Gled;
const uint8_t bufSize = 30;
using USART_ = USART<USART2, bufSize, RXpin, TXpin, RTSpin, LEDpin>;
USART_ uart;

// модбас
struct InRegs {
   uint16_t reg0;
   uint16_t reg1;
};
struct OutRegs {
   uint16_t reg0;
   uint16_t reg1;
};
auto modbus = MBslave<InRegs, OutRegs, USART_> (uart);
// действия на входные регистры модбаса
#define ADR(reg)    GET_ADR(InRegs, reg)
inline void reaction (uint16_t regAdr)
{
   switch ( regAdr ) {
      case ADR(reg0):
         ; // сделать чтото
         break;
      case ADR(reg1):
         ; // сделать чтото
         break;
      default: ;
   }
}


ADCaverage<ADC1,PA0> adc;




// эта функция вызываеться первой в startup файле
extern "C" void CLKinit (void)
{
   FLASH::set (FLASH::Latency::_5);
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


inline void PortsInit (void)
{
   LedPort::clockEnable();

   Bled::configure (Bled::Mode::Output,
                Bled::OutType::PushPull,
                Bled::OutSpeed::High,
                Bled::PullResistor::No);
   Oled::configure (Oled::Mode::Output,
                Oled::OutType::PushPull,
                Oled::OutSpeed::High,
                Oled::PullResistor::No);

   Button::Port::clockEnable();
}




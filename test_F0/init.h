#pragma once

#include "RCC.h"
#include "DebugVar.h"
#include "timers.h"
#include "flash.h"
#include "pin.h"
#include "spi.h"
#include "zoomer.h"
#include "literals.h"
#include "buttons.h"
#include "inputCounter.h"
#include "seven_segment_indicator.h"
// #include "modbusSlave.h"

const uint8_t timersQty = 8;
Timers<timersQty> timers;
auto& onTimer      = timers.all[0];
auto& offTimer     = timers.all[1];
auto& spiTimer     = timers.all[2];
auto& zoomerTimer  = timers.all[3];
auto& butTimer     = timers.all[4];
auto& counterTimer = timers.all[5];
auto& ledTimer     = timers.all[6];
auto& ssiTimer     = timers.all[7];

using BlueLed = PC8;

// семисегментный индикатор
// auto ssi = SSI<PD0,PD1,PD2,PD4,PD5,PD6,PD7,PC0,PC1,PC2>(ssiTimer);


// энергонезависимые данные
struct FlashData {
   uint16_t d1;
   uint16_t d2;
};
const uint8_t flashSector = 10;
auto flash = Flash<FlashData, flashSector> ( {
   .d1 = 1,
   .d2 = 3
} );


struct SPIdata {
   uint16_t time;
   uint16_t currentTemperature;
   uint16_t targetTemperature;
};
SPIoverDMA<SPI1, SPIdata> spi;

// шим зуммера
using PWMout = PA6;
using PWMtimer = TIM3;
using PWM_ = PWM<PWMtimer, PWMout>;
PWM_ pwm;

// зуммер
auto zoomer = Zoomer<PWM_> (pwm, zoomerTimer, 4000_Hz); 


using But1 = PA0;
using But2 = PA1;
using But3 = PA2;
auto buttons = Buttons<false,But1,But2,But3>(butTimer);


using GreenLed = PC9;

// частотометр
auto counter = InputCounter<TIM1, PA9> (counterTimer);

// // уарт модбаса
// using RXpin = PA3;
// using TXpin = PA2;
// using RTSpin = PA5;
// using LEDpin = GreenLed;
// const uint8_t bufSize = 30;
// using USART_ = USART<USART2_t, bufSize, RXpin, TXpin, RTSpin, LEDpin>;
// USART_ uart;

// // модбас
// struct InRegs {
//    uint16_t reg0;
//    uint16_t reg1;
// };
// struct OutRegs {
//    uint16_t reg0;
//    uint16_t reg1;
// };
// auto modbus = MBslave<InRegs, OutRegs, USART_> (uart, mbTimer);
// // действия на входные регистры модбаса
// #define ADR(reg)    GET_ADR(InRegs, reg)
// inline void mbRegInAction ()
// {
//    switch ( modbus.getInRegAdrForAction() ) {
//       case ADR(reg0):
//          ; // сделать чтото
//          break;
//       case ADR(reg1):
//          ; // сделать чтото
//          break;
//       default: ;
//    }
// }


// эта функция вызывается первой в startup файле
extern "C" void CLKinit (void)
{
   FLASH->ACR |= FLASH_ACR_PRFTBE;
   FLASH_t::SetLatency (FLASH_t::Latency::_1);

   RCC_t::setAHBprescaler (RCC_t::AHBprescaler::AHBnotdiv);
   RCC_t::setAPBprecsaler (RCC_t::APBprescaler::APBnotdiv);
   RCC_t::systemClockSwitch (RCC_t::SystemClockSwitch::CS_PLL);
   RCC_t::setPLLsource (RCC_t::PLLsource::HSIdiv2);
   RCC_t::setPLLmultiplier (RCC_t::PLLmultiplier::_12);
   RCC_t::PLLon();
   RCC_t::waitPLLready();
}

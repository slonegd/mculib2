#pragma once

#include "RCC_ral.h"
#include "DebugVar.h"
#include "timers.h"
#include "flash_hal.h"
#include "pin_hal.h"
#include "spi_hal.h"
#include "zoomer.h"
#include "literals.h"
#include "buttons.h"

const uint8_t timersQty = 6;
Timers<timersQty> timers;
auto& ledTimer = timers.all[0];
auto& butTimer = timers.all[1];
auto& mbTimer  = timers.all[2];
auto& txTimer  = timers.all[3];
auto& lcdTimer = timers.all[4];
auto& counterTimer = timers.all[5];

// эта функция вызывается первой в startup файле
extern "C" void CLKinit (void)
{
   FLASH->ACR |= FLASH_ACR_PRFTBE;
   FLASH_t::SetLatency (FLASH_t::Latency::_1);

   RCC_t::setAHBprescaler (RCC_t::AHBprescaler::AHBnotdiv);
   RCC_t::setAPBprecsaler (RCC_t::APBprescaler::APBnotdiv);
   RCC_t::systemClockSwitch (RCC_t::SystemClockSwitch::CS_PLL);
   RCC_t::setPLLmultiplier (RCC_t::PLLmultiplier::_6);
   RCC_t::setPLLsource (false);
   RCC_t::PLLon();
   RCC_t::waitPLLready();


}

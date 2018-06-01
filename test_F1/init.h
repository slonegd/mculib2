#pragma once



// эта функция вызывается первой в startup файле
extern "C" void CLKinit (void)
{
   // FLASH->ACR |= FLASH_ACR_PRFTBE;
   // FLASH_t::SetLatency (FLASH_t::Latency::_1);

   // RCC_t::setAHBprescaler (RCC_ral::AHBprescaler::AHBnotdiv);
   // RCC_t::setAPBprecsaler (RCC_ral::APBprescaler::APBnotdiv);
   // RCC_t::systemClockSwitch (RCC_ral::SystemClockSwitch::CS_PLL);
   // RCC_t::setPLLsource (RCC_ral::PLLsource::HSIdiv2);
   // RCC_t::setPLLmultiplier (RCC_ral::PLLmultiplier::_12);
   // RCC_t::PLLon();
   // RCC_t::waitPLLready();
}

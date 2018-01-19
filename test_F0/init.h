#pragma once

#include "RCC_ral.h"
//#include "DebugVar.h"

// эта функция вызываеться первой в startup файле
extern "C" void CLKinit (void)
{
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
   	FLASH->ACR |= (uint32_t) 5;    
 
    RCC_t::setPLLsource(false);
    RCC_t::setPLLmultiplier(RCC_t::PLLmultiplier::PLLmul12);

    RCC_t::PLLon();
    RCC_t::waitPLLready();
}
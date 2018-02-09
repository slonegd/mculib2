#pragma once

#include "RCC_ral.h"
#include "DebugVar.h"
#include "flash_hal.h"
#include "pin_hal.h"

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
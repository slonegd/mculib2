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

const uint8_t timersQty = 5;
Timers<timersQty> timers;
auto& onTimer  = timers.all[0];
auto& offTimer = timers.all[1];
auto& spiTimer = timers.all[2];
auto& zoomerTimer = timers.all[3];
auto& butTimer = timers.all[4];

using Led = PC8;


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
SPI<SPI1, SPIdata> spi;

// шим
using PWMout = Led;
using PWMtimer = TIM3;
using PWM_ = PWM<PWMtimer, PWMout>;
PWM_ pwm;

// зуммер
auto zoomer = Zoomer<PWM_> (pwm, zoomerTimer, 4000_Hz); 


using But1 = PA0;
using But2 = PA1;
using But3 = PA2;
auto buttons = Buttons<But1,But2,But3>(butTimer);


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
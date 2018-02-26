/**
 * RAL над портами ввода вывода
 * в конце файла определяються статические классы,
 * которые необходимы для конкретизации шаблонных классов
 * в pin_hal
 */

#pragma once

#include "GPIO_bits.h"

/*
typedef struct
{
__IO uint32_t MODER;    // GPIO port mode register,               Address offset: 0x00
__IO uint32_t OTYPER;   // GPIO port output type register,        Address offset: 0x04
__IO uint32_t OSPEEDR;  // GPIO port output speed register,       Address offset: 0x08
__IO uint32_t PUPDR;    // GPIO port pull-up/pull-down register,  Address offset: 0x0C
__IO uint32_t IDR;      // GPIO port input data register,         Address offset: 0x10
__IO uint32_t ODR;      // GPIO port output data register,        Address offset: 0x14
__IO uint32_t BSRR;     // GPIO port bit set/reset register,      Address offset: 0x18
__IO uint32_t LCKR;     // GPIO port configuration lock register, Address offset: 0x1C
__IO uint32_t AFR[2];   // GPIO alternate function registers,     Address offset: 0x20-0x24
} GPIO_TypeDef;
*/

static constexpr uint32_t MakeMask (MODER_t::Mode_t m, 
                                    OTYPER_t::OutType_t t,
                                    OSPEEDR_t::OutSpeed_t s,
                                    PUPDR_t::PullResistor_t r,
                                    AFR_t::AF af)
{
   return (uint32_t)m | (uint32_t)t << 2 
                      | (uint32_t)s << 3
                      | (uint32_t)r << 5
                      | (uint32_t)af << 7;
}

class GPIO_t : public MODER_t,
            public OTYPER_t,
            public OSPEEDR_t,
            public PUPDR_t,
            public IDR_t,
            public ODR_t,
            public BSRR_t,
            public LCKR_t,
            public AFR_t
//LCKR AFR пока не нужны
{
public:
   using Mode_t = MODER_t::Mode_t;
   using OutType_t = OTYPER_t::OutType_t;
   using OutSpeed_t = OSPEEDR_t::OutSpeed_t;
   using PullResistor_t = PUPDR_t::PullResistor_t;
   using AF = AFR_t::AF;


   enum PinConf_t {
      OutputPushPullLowSpeedNoResistor =
         MakeMask(Mode_t::Output, OutType_t::PushPull, OutSpeed_t::Low, PullResistor_t::No, AF::_0),
      Input =
         MakeMask(Mode_t::Input, OutType_t::PushPull, OutSpeed_t::Low, PullResistor_t::No, AF::_0),
      AlternateFunc0PushPull =
         MakeMask(Mode_t::Alternate, OutType_t::PushPull, OutSpeed_t::Low, PullResistor_t::No, AF::_0),
      AlternateFunc0PushPullHighSpeed =
         MakeMask(Mode_t::Alternate, OutType_t::PushPull, OutSpeed_t::High, PullResistor_t::No, AF::_0),
      AnalogInput = 
         MakeMask(Mode_t::Analog, OutType_t::PushPull, OutSpeed_t::Low, PullResistor_t::No, AF::_0),
   };



protected:
   static constexpr Mode_t     getMode (PinConf_t val)  { return (Mode_t)val; }
   static constexpr OutType_t  getType (PinConf_t val)  { return (OutType_t)(val >> 2); }
   static constexpr OutSpeed_t getSpeed(PinConf_t val)  { return (OutSpeed_t)(val >> 3); }
   static constexpr PullResistor_t getResistor(PinConf_t val) { return (PullResistor_t)(val >> 5); }
   static constexpr AF         getAltFunc(PinConf_t val) { return (AF)(val >> 7); }
};



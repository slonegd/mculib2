/**
 * RAL над портами ввода вывода
 * в конце файла определяються статические классы,
 * которые необходимы для конкретизации шаблонных классов
 * в pin_hal
 */

#pragma once

#include "GPIO_bits.h"
#include "GPIO_configure.h"

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

template <uint32_t Adr>
class GPIOx 
 {
public:
   using Mode_t         = GPIO_ral::Mode_t;
   using OutType_t      = GPIO_ral::OutType_t;
   using OutSpeed_t     = GPIO_ral::OutSpeed_t;
   using PullResistor_t = GPIO_ral::PullResistor_t;
   using AF             = GPIO_ral::AF;

   static constexpr uint32_t Base = Adr;

   static auto Create() { return reinterpret_cast< GPIOx<Adr>* > (Adr); }

   void makeDebugVar() { bsr().reg = 0; }
 
   static void       clockEnable();
   static uint16_t   read();                  
   static void       write (uint16_t val);
   static void       set (uint16_t val);
   static void       clear (uint16_t val);
   static void       clearAndSet (uint16_t clearMask, uint16_t val);
   static void       toggle (uint16_t val);
   static uint16_t   pinRead();  


   template<uint16_t val>                          static void toggle();
   template<uint16_t val>                          static void set();
   template<uint16_t val>                          static void clear();
 
   template<AF func,             uint8_t pin>      static void setAltFunc();
   template<PinConf_t pinConf,   uint8_t pin>      static void configure();
   template<uint16_t clearMask,  uint16_t val>     static void clearAndSet();



protected:

   static constexpr Mode_t          getMode (PinConf_t val);
   static constexpr OutType_t       getType (PinConf_t val);
   static constexpr OutSpeed_t      getSpeed(PinConf_t val);
   static constexpr PullResistor_t  getResistor(PinConf_t val);
   static constexpr AF              getAltFunc(PinConf_t val);
 
#define MakeRef(Reg,Ref) GPIO_ral::Reg& Ref() { return (GPIO_ral::Reg&) *(uint32_t*)(Base + GPIO_ral::Reg::Offset); }
   static volatile MakeRef (MODER_t,   mode);
   static volatile MakeRef (OTYPER_t,  otype);
   static volatile MakeRef (OSPEEDR_t, ospeed);
   static volatile MakeRef (PUPDR_t,   pupd);
   static volatile MakeRef (IDR_t,     id);
   static volatile MakeRef (ODR_t,     od);
   static volatile MakeRef (BSRR_t,    bsr);
   static volatile MakeRef (AFR_t,     af);   
#undef MakeRef

private:
   GPIO_ral::MODER_t    MODER;
   GPIO_ral::OTYPER_t   OTYPER;
   GPIO_ral::OSPEEDR_t  OSPEEDR;
   GPIO_ral::PUPDR_t    PUPDR;
   GPIO_ral::IDR_t      IDR;
   GPIO_ral::ODR_t      ODR;
   GPIO_ral::BSRR_t     BSRR;
   GPIO_ral::LCKR_t     LCKR;
   GPIO_ral::AFR_t      AFR;
   
   

};

using PA = GPIOx<GPIOA_BASE>;
using PB = GPIOx<GPIOB_BASE>;
using PC = GPIOx<GPIOC_BASE>;
using PD = GPIOx<GPIOD_BASE>;
using PF = GPIOx<GPIOF_BASE>;
#if defined(STM32F405xx)
using PE = GPIOx<GPIOE_BASE>;
using PG = GPIOx<GPIOG_BASE>;
using PH = GPIOx<GPIOH_BASE>;
using PI = GPIOx<GPIOI_BASE>;
#endif

#include "GPIO_src.h"
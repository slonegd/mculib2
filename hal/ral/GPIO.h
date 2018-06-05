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

template <uint32_t Adr, int ID>
class GPIOx 
//LCKR AFR пока не нужны


{
public:
   using Mode_t = GPIO_ral::Mode_t;
   using OutType_t = GPIO_ral::OutType_t;
   using OutSpeed_t = GPIO_ral::OutSpeed_t;
   using PullResistor_t = GPIO_ral::PullResistor_t;
   using AF = GPIO_ral::AF;

   static constexpr uint32_t Base = Adr;

   static auto Create() { return reinterpret_cast< GPIOx<Adr,ID>* > (Adr); }

   void makeDebugVar() { bsr().reg = 0; }
 
   static void ClockEnable()
   {
#if defined(STM32F030x6)
   RCC->AHBENR |= ClkEnMask;
#elif defined(STM32F405xx)
   RCC->AHB1ENR |= ClkEnMask;
#endif
   }


   // using PinConf_t = GPIOx::PinConf_t;
   template<PinConf_t pinConf, uint8_t pin> static void Configure()
   {
      ClockEnable();
      mode().reg   &= ~((uint32_t)0b11 << pin*2);
      mode().reg   |=  (uint32_t)GPIOx::getMode(pinConf)  << pin*2;
      otype().reg  &= ~((uint32_t)0b1  << pin);
      otype().reg  |=  (uint32_t)GPIOx::getType(pinConf)  << pin;
      ospeed().reg &= ~((uint32_t)0b11 << pin*2);
      ospeed().reg |=  (uint32_t)GPIOx::getSpeed(pinConf) << pin*2;
      pupd().reg   &= ~((uint32_t)0b1  << pin);
      pupd().reg   |=  (uint32_t)GPIOx::getResistor(pinConf) << pin;
      SetAltFunc<GPIOx::getAltFunc(pinConf), pin>();
   }

   static uint16_t Read()                  { return od().reg; }  
   static void Write (uint16_t val)        { od().reg = val; }
   static void Set (uint16_t val)          { bsr().reg = val; }
   static void Clear (uint16_t val)        { bsr().reg = val << 16; }
   static void ClearAndSet (uint16_t clearMask, uint16_t val)
   {
      Clear(clearMask);
      Set(val);
   }
   static void Toggle (uint16_t val)       { od().reg ^= val; }
   static uint16_t PinRead()               { return id().reg; }
   template <AF func, uint8_t pin> static void SetAltFunc()
   {
      constexpr uint8_t reg = pin / 8;
      constexpr uint32_t mask = (uint32_t)func << (pin - 8*reg) * 4;
      af().reg[reg] |= mask;
   }

   // конфигурация (пока не все методы)
   static void Enable()  { ClockEnable(); }
   static void Disable()
   {
#if defined(STM32F030x6)
      RCC->AHBENR |= ClkEnMask;
#elif defined(STM32F405xx)
      RCC->AHB1ENR |= ClkEnMask;
#endif
   }

   // методы шаблоны
   template<uint16_t clearMask, uint16_t val> static void ClearAndSet()
   {
      Clear(clearMask);
      Set(val);
   }
   template<uint16_t val> static void Toggle() { od().reg ^= val; }
   template<uint16_t val> static void Set()    { bsr().reg = val; }
   template<uint16_t val> static void Clear()  { bsr().reg = val << 16; }

   enum { Id = ID };




protected:

   static constexpr Mode_t     getMode (PinConf_t val)  { return (Mode_t)val; }
   static constexpr OutType_t  getType (PinConf_t val)  { return static_cast<OutType_t>(static_cast<uint32_t>(val) >> 2); }
   static constexpr OutSpeed_t getSpeed(PinConf_t val)  { return static_cast<OutSpeed_t>(static_cast<uint32_t>(val) >> 3); }
   static constexpr PullResistor_t getResistor(PinConf_t val) { return static_cast<PullResistor_t>(static_cast<uint32_t>(val) >> 5); }
   static constexpr AF         getAltFunc(PinConf_t val) { return static_cast<AF>(static_cast<uint32_t>(val) >> 7); }


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
   
   
   #if defined(STM32F405xx)
   static constexpr uint32_t ClkEnMask =
      Base == GPIOA_BASE ? RCC_AHB1ENR_GPIOAEN_Msk :
      Base == GPIOB_BASE ? RCC_AHB1ENR_GPIOBEN_Msk :
      Base == GPIOC_BASE ? RCC_AHB1ENR_GPIOCEN_Msk :
      Base == GPIOD_BASE ? RCC_AHB1ENR_GPIODEN_Msk :
      Base == GPIOE_BASE ? RCC_AHB1ENR_GPIOEEN_Msk :
      Base == GPIOF_BASE ? RCC_AHB1ENR_GPIOFEN_Msk :
      Base == GPIOG_BASE ? RCC_AHB1ENR_GPIOGEN_Msk :
      Base == GPIOH_BASE ? RCC_AHB1ENR_GPIOHEN_Msk :
      Base == GPIOI_BASE ? RCC_AHB1ENR_GPIOIEN_Msk : 0;
#elif defined(STM32F030x6)
   static constexpr uint32_t ClkEnMask =
      Base == GPIOA_BASE ? RCC_AHBENR_GPIOAEN_Msk :
      Base == GPIOB_BASE ? RCC_AHBENR_GPIOBEN_Msk :
      Base == GPIOC_BASE ? RCC_AHBENR_GPIOCEN_Msk :
      Base == GPIOD_BASE ? RCC_AHBENR_GPIODEN_Msk :
      Base == GPIOF_BASE ? RCC_AHBENR_GPIOFEN_Msk : 0;
#endif
};

using PA = GPIOx<GPIOA_BASE, 'A'>;
using PB = GPIOx<GPIOB_BASE, 'B'>;
using PC = GPIOx<GPIOC_BASE, 'C'>;
using PD = GPIOx<GPIOD_BASE, 'D'>;
using PF = GPIOx<GPIOF_BASE, 'F'>;
#if defined(STM32F405xx)
using PE = GPIOx<GPIOE_BASE, 'E'>;
using PG = GPIOx<GPIOG_BASE, 'G'>;
using PH = GPIOx<GPIOH_BASE, 'H'>;
using PI = GPIOx<GPIOI_BASE, 'I'>;
#endif

#pragma once

#include "GPIO.h"

template <uint32_t PortPtr, int ID>
class Port_t : protected GPIO_t
{
/*public:
   using Mode = MODER_t::Mode_t;
   using OutType = OTYPER_t::OutType_t;
   using OutSpeed = OSPEEDR_t::OutSpeed_t;
   using PullResistor = PUPDR_t::PullResistor_t;*/
public:
   static void ClockEnable()
   {
#if defined(STM32F030x6)
      RCC->AHBENR |= ClkEnMask;
#elif defined(STM32F405xx)
      RCC->AHB1ENR |= ClkEnMask;
#endif
   }


   // using PinConf_t = GPIO_t::PinConf_t;
   template<PinConf_t pinConf, uint8_t pin> static void Configure()
   {
      ClockEnable();
      mode().reg   &= ~((uint32_t)0b11 << pin*2);
      mode().reg   |=  (uint32_t)GPIO_t::getMode(pinConf)  << pin*2;
      otype().reg  &= ~((uint32_t)0b1  << pin);
      otype().reg  |=  (uint32_t)GPIO_t::getType(pinConf)  << pin;
      ospeed().reg &= ~((uint32_t)0b11 << pin*2);
      ospeed().reg |=  (uint32_t)GPIO_t::getSpeed(pinConf) << pin*2;
      pupd().reg   &= ~((uint32_t)0b1  << pin);
      pupd().reg   |=  (uint32_t)GPIO_t::getResistor(pinConf) << pin;
      SetAltFunc<GPIO_t::getAltFunc(pinConf), pin>();
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
   static volatile MODER_t   &mode()   { return (MODER_t &)  (*(GPIO_TypeDef*)PortPtr).MODER;   }
   static volatile OTYPER_t  &otype()  { return (OTYPER_t &) (*(GPIO_TypeDef*)PortPtr).OTYPER;  }
   static volatile OSPEEDR_t &ospeed() { return (OSPEEDR_t &)(*(GPIO_TypeDef*)PortPtr).OSPEEDR; }
   static volatile PUPDR_t   &pupd()   { return (PUPDR_t &)  (*(GPIO_TypeDef*)PortPtr).PUPDR;   }
   static volatile ODR_t     &od()     { return (ODR_t &)    (*(GPIO_TypeDef*)PortPtr).ODR;     }
   static volatile IDR_t     &id()     { return (IDR_t &)    (*(GPIO_TypeDef*)PortPtr).IDR;     }
   static volatile BSRR_t    &bsr()    { return (BSRR_t &)   (*(GPIO_TypeDef*)PortPtr).BSRR;    }
   static volatile AFR_t     &af()     { return (AFR_t &)    (*(GPIO_TypeDef*)PortPtr).AFR[0];  }



private:
#if defined(STM32F405xx)
   static constexpr uint32_t ClkEnMask =
      PortPtr == GPIOA_BASE ? RCC_AHB1ENR_GPIOAEN_Msk :
      PortPtr == GPIOB_BASE ? RCC_AHB1ENR_GPIOBEN_Msk :
      PortPtr == GPIOC_BASE ? RCC_AHB1ENR_GPIOCEN_Msk :
      PortPtr == GPIOD_BASE ? RCC_AHB1ENR_GPIODEN_Msk :
      PortPtr == GPIOE_BASE ? RCC_AHB1ENR_GPIOEEN_Msk :
      PortPtr == GPIOF_BASE ? RCC_AHB1ENR_GPIOFEN_Msk :
      PortPtr == GPIOG_BASE ? RCC_AHB1ENR_GPIOGEN_Msk :
      PortPtr == GPIOH_BASE ? RCC_AHB1ENR_GPIOHEN_Msk :
      PortPtr == GPIOI_BASE ? RCC_AHB1ENR_GPIOIEN_Msk : 0;
#elif defined(STM32F030x6)
   static constexpr uint32_t ClkEnMask =
      PortPtr == GPIOA_BASE ? RCC_AHBENR_GPIOAEN_Msk :
      PortPtr == GPIOB_BASE ? RCC_AHBENR_GPIOBEN_Msk :
      PortPtr == GPIOC_BASE ? RCC_AHBENR_GPIOCEN_Msk :
      PortPtr == GPIOD_BASE ? RCC_AHBENR_GPIODEN_Msk :
      PortPtr == GPIOF_BASE ? RCC_AHBENR_GPIOFEN_Msk : 0;
#endif
};

using PA = Port_t<GPIOA_BASE, 'A'>;
using PB = Port_t<GPIOB_BASE, 'B'>;
using PC = Port_t<GPIOC_BASE, 'C'>;
using PD = Port_t<GPIOD_BASE, 'D'>;
using PF = Port_t<GPIOF_BASE, 'F'>;
#if defined(STM32F405xx)
using PE = Port_t<GPIOE_BASE, 'E'>;
using PG = Port_t<GPIOG_BASE, 'G'>;
using PH = Port_t<GPIOH_BASE, 'H'>;
using PI = Port_t<GPIOI_BASE, 'I'>;
#endif
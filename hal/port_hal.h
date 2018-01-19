#pragma once

#include "GPIO_ral.h"

template <uint32_t PortPtr, uint32_t ClkEnMask, int ID>
class Port_t : protected GPIO_t
{
/*public:
    using Mode = MODER_t::Mode_t;
    using OutType = OTYPER_t::OutType_t;
    using OutSpeed = OSPEEDR_t::OutSpeed_t;
    using PullResistor = PUPDR_t::PullResistor_t;*/
public:
    static void ClockEnable (void)          { RCC->AHB1ENR |= ClkEnMask; }
/*
    template<PinConf_t pinConf, uint8_t pin>
    static void Configure()
    {
        mode().reg    &= ~((uint32_t)0b11 << pin*2);
        mode().reg    |=  (uint32_t)pinConf.mode  << pin*2;
        otype().reg   &= ~((uint32_t)0b1  << pin);
        otype().reg   |=  (uint32_t)pinConf.outType  << pin;
        ospeed().reg  &= ~((uint32_t)0b11 << pin*2);
        ospeed().reg  |=  (uint32_t)pinConf.outSpeed << pin*2;
        pupd().reg    &= ~((uint32_t)0b1  << pin);
        pupd().reg    |=  (uint32_t)pinConf.pullResistor << pin;
    }
*/

    static uint16_t Read()                  { return od().reg; }  
    static void Write (uint16_t val)        { od().reg = val; }
    static void Set (uint16_t val)          { bsr().reg = val; }
    static void Clear (uint16_t val)        { bsr().reg = val << 16; }
    static void ClearAndSet (uint16_t clearMask, uint16_t val)
    {
        Clear(clearMask);
        Set(val);
    }
    static void Toggle (uint16_t val)       { ClearAndSet (val, ~od().reg & val); }
    static uint16_t PinRead()               { return id().reg; }

    // конфигурация (пока не все методы)
    static void Enable (void)  { RCC->AHB1ENR |= ClkEnMask; }
    static void Disable (void) { RCC->AHB1ENR &= ~ClkEnMask; }

    // методы шаблоны
    template<uint16_t clearMask, uint16_t val> static void ClearAndSet()
    {
        Clear(clearMask);
        Set(val);
    }
    template<uint16_t val> static void Toggle() { ClearAndSet(val,  ~od().reg & val); }
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

};

using PA = Port_t<GPIOA_BASE, RCC_AHB1ENR_GPIOAEN_Msk, 'A'>;
using PB = Port_t<GPIOB_BASE, RCC_AHB1ENR_GPIOBEN_Msk, 'B'>;
using PC = Port_t<GPIOC_BASE, RCC_AHB1ENR_GPIOCEN_Msk, 'C'>;
using PD = Port_t<GPIOD_BASE, RCC_AHB1ENR_GPIODEN_Msk, 'D'>;
using PE = Port_t<GPIOE_BASE, RCC_AHB1ENR_GPIOEEN_Msk, 'E'>;
using PF = Port_t<GPIOF_BASE, RCC_AHB1ENR_GPIOFEN_Msk, 'F'>;
using PG = Port_t<GPIOG_BASE, RCC_AHB1ENR_GPIOGEN_Msk, 'G'>;
using PH = Port_t<GPIOH_BASE, RCC_AHB1ENR_GPIOHEN_Msk, 'H'>;
using PI = Port_t<GPIOI_BASE, RCC_AHB1ENR_GPIOIEN_Msk, 'I'>;
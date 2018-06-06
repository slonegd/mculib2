#pragma once

template<uint32_t adr>
void GPIOx<adr>::clockEnable()
{
#if defined(STM32F405xx)
   constexpr uint32_t ClkEnMask =
      adr == GPIOA_BASE ? RCC_AHB1ENR_GPIOAEN_Msk :
      adr == GPIOB_BASE ? RCC_AHB1ENR_GPIOBEN_Msk :
      adr == GPIOC_BASE ? RCC_AHB1ENR_GPIOCEN_Msk :
      adr == GPIOD_BASE ? RCC_AHB1ENR_GPIODEN_Msk :
      adr == GPIOE_BASE ? RCC_AHB1ENR_GPIOEEN_Msk :
      adr == GPIOF_BASE ? RCC_AHB1ENR_GPIOFEN_Msk :
      adr == GPIOG_BASE ? RCC_AHB1ENR_GPIOGEN_Msk :
      adr == GPIOH_BASE ? RCC_AHB1ENR_GPIOHEN_Msk :
      adr == GPIOI_BASE ? RCC_AHB1ENR_GPIOIEN_Msk : 0;
#elif defined(STM32F030x6)
   constexpr uint32_t ClkEnMask =
      adr == GPIOA_BASE ? RCC_AHBENR_GPIOAEN_Msk :
      adr == GPIOB_BASE ? RCC_AHBENR_GPIOBEN_Msk :
      adr == GPIOC_BASE ? RCC_AHBENR_GPIOCEN_Msk :
      adr == GPIOD_BASE ? RCC_AHBENR_GPIODEN_Msk :
      adr == GPIOF_BASE ? RCC_AHBENR_GPIOFEN_Msk : 0;
#endif

#if defined(STM32F030x6)
   RCC->AHBENR |= ClkEnMask;
#elif defined(STM32F405xx)
   RCC->AHB1ENR |= ClkEnMask;
#endif
}

template<uint32_t adr>
uint16_t GPIOx<adr>::read()     
{
   return od().reg;
}

template<uint32_t adr>
void GPIOx<adr>::write (uint16_t val)  
{
   od().reg = val;
}

template<uint32_t adr>
void GPIOx<adr>::set (uint16_t val)  
{
   bsr().reg = val;
}

template<uint32_t adr>
void GPIOx<adr>::clear (uint16_t val)  
{
   bsr().reg = val << 16; 
}

template<uint32_t adr>
void GPIOx<adr>::clearAndSet (uint16_t clearMask, uint16_t val)
{
   clear(clearMask);
   set(val);
}

template<uint32_t adr>
void GPIOx<adr>::toggle (uint16_t val)  
{
   od().reg ^= val; 
}

template<uint32_t adr>
uint16_t GPIOx<adr>::pinRead()     
{
   return id().reg;
}

template<uint32_t adr>
template<PinConf_t pinConf, uint8_t pin>
void GPIOx<adr>::configure()
{
   clockEnable();
   mode().reg   &= ~((uint32_t)0b11 << pin*2);
   mode().reg   |=  (uint32_t)GPIOx::getMode(pinConf)  << pin*2;
   otype().reg  &= ~((uint32_t)0b1  << pin);
   otype().reg  |=  (uint32_t)GPIOx::getType(pinConf)  << pin;
   ospeed().reg &= ~((uint32_t)0b11 << pin*2);
   ospeed().reg |=  (uint32_t)GPIOx::getSpeed(pinConf) << pin*2;
   pupd().reg   &= ~((uint32_t)0b1  << pin);
   pupd().reg   |=  (uint32_t)GPIOx::getResistor(pinConf) << pin;
   setAltFunc<GPIOx::getAltFunc(pinConf), pin>();
    
}

template<uint32_t adr>
template<uint16_t clearMask, uint16_t val>
void GPIOx<adr>::clearAndSet()
{
   clear(clearMask);
   set(val);
}

template<uint32_t adr>
template<uint16_t val>
void GPIOx<adr>::toggle()
{ 
   od().reg ^= val;
}

template<uint32_t adr>
template<uint16_t val>
void GPIOx<adr>::set()
{ 
   bsr().reg = val;
}

template<uint32_t adr>
template<uint16_t val>
void GPIOx<adr>::clear()
{ 
   bsr().reg = val << 16;
}

template<uint32_t adr>
template<GPIO_ral::AF func, uint8_t pin>
void GPIOx<adr>::setAltFunc()
{
   constexpr uint8_t reg = pin / 8;
   constexpr uint32_t mask = (uint32_t)func << (pin - 8*reg) * 4;
   af().reg[reg] |= mask;
}

template<uint32_t adr>
constexpr typename GPIOx<adr>::Mode_t GPIOx<adr>::getMode(PinConf_t val)
{ return (Mode_t)val; }

template<uint32_t adr>
constexpr typename GPIOx<adr>::OutType_t GPIOx<adr>::getType(PinConf_t val)
{ return static_cast<OutType_t>(static_cast<uint32_t>(val) >> 2); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::OutSpeed_t GPIOx<adr>::getSpeed(PinConf_t val)
{ return static_cast<OutSpeed_t>(static_cast<uint32_t>(val) >> 3); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::PullResistor_t GPIOx<adr>::getResistor(PinConf_t val)
{ return static_cast<PullResistor_t>(static_cast<uint32_t>(val) >> 5); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::AF GPIOx<adr>::getAltFunc(PinConf_t val)
{ return static_cast<AF>(static_cast<uint32_t>(val) >> 7); }


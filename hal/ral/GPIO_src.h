#pragma once



template<uint32_t adr>
void GPIOx<adr>::clockEnable()
{
   RCC::template clockEnable<GPIOx<adr>>();
}

template<uint32_t adr>
uint16_t GPIOx<adr>::read()     
{
   return id().reg;
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
{ return static_cast<Mode_t>(static_cast<uint32_t>(val) & 0b11); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::OutType_t GPIOx<adr>::getType(PinConf_t val)
{ return static_cast<OutType_t>((static_cast<uint32_t>(val) >> 2) & 0b1); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::OutSpeed_t GPIOx<adr>::getSpeed(PinConf_t val)
{ return static_cast<OutSpeed_t>((static_cast<uint32_t>(val) >> 3) & 0b11); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::PullResistor_t GPIOx<adr>::getResistor(PinConf_t val)
{ return static_cast<PullResistor_t>((static_cast<uint32_t>(val) >> 5) & 0b11); }

template<uint32_t adr>
constexpr typename GPIOx<adr>::AF GPIOx<adr>::getAltFunc(PinConf_t val)
{ return static_cast<AF>((static_cast<uint32_t>(val) >> 7) & 0b1111); }


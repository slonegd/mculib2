/**
 * HAL над работой с пинами микроконтроллера
 * представляет из себя шаблонный класс со стандартными статическими функциями
 * параметры функции Configure() зависят от контроллера,
 * от этого никуда не деться.
 * Первый параметр шаблона выбираеться из классов портов,
 * описнныз в GPIO_ral.h
 */

#pragma once

#include "GPIO.h"
#include <stdint.h>
#include <stdbool.h>
#include <type_traits>

namespace Pin_HAL {

}


template <class PORT, uint8_t pin>
class Pin_t : protected PORT
{
public:
   using Port = PORT;
   using Mode = GPIO_ral::Mode_t;
   using OutType = GPIO_ral::OutType_t;
   using OutSpeed = GPIO_ral::OutSpeed_t;
   using PullResistor = GPIO_ral::PullResistor_t;
   using AF = GPIO_ral::AF;

   static const unsigned Number = pin;
   static const bool Inverted = false;

   inline static void configure ( Mode mode,
                           OutType type,
                           OutSpeed speed,
                           PullResistor res)
   {
      PORT::mode().reg    &= ~((uint32_t)0b11 << pin*2);
      PORT::mode().reg    |=  (uint32_t)mode  << pin*2;
      PORT::otype().reg   &= ~((uint32_t)0b1  << pin);
      PORT::otype().reg   |=  (uint32_t)type  << pin;
      PORT::ospeed().reg  &= ~((uint32_t)0b11 << pin*2);
      PORT::ospeed().reg  |=  (uint32_t)speed << pin*2;
      PORT::pupd().reg    &= ~((uint32_t)0b1  << pin);
      PORT::pupd().reg    |=  (uint32_t)res   << pin;
   }


   // using PinConf_t = typename Port::PinConf_t;
   template<PinConf_t pinConf>
   static void configure() { Port::template configure<pinConf, pin>(); }
   #define CONFIGURE_PIN(Pin,Conf) Pin::template configure<PinConf_t::Conf>()
   #define CONFIGURE_PIN_VALUE(Pin,Conf) Pin::template configure<Conf>()

   template<AF af>
   static void configureAltFunction();


   template <AF func> static void SetAltFunc()
   {
      Port::template setAltFunc<func, pin>();
   }

   static void set()          { PORT::template set<1u << pin> (); }
   static void clear()        { PORT::template clear<1u << pin> (); }
   static void toggle()       { PORT::template toggle<1u << pin> (); }
   static void set(bool b)    { b ? set() : clear(); }
   static bool isSet()        { return ( (PORT::pinRead() & (1u << pin) ) != 0); }
   static bool isClear()      { return ( (PORT::pinRead() & (1u << pin) ) == 0); }
   static void waitForSet()   { while( isSet() == 0) {} }
   static void waitForClear() { while( isSet() ) {} }

};

class NullPin
{
public:

   using Mode = GPIO_ral::Mode_t;
   using OutType = GPIO_ral::OutType_t;
   using OutSpeed = GPIO_ral::OutSpeed_t;
   using PullResistor = GPIO_ral::PullResistor_t;
   using AF = GPIO_ral::AF;

   inline static void configure (Mode mode,
                           OutType type,
                           OutSpeed speed,
                           PullResistor res){}
   template<PinConf_t pinConf>
   static void configure() {}
   template<AF af>
   static void configureAltFunction(){}
   template <AF func> static void SetAltFunc(){}

   static void set()          {}
   static void clear()        {}
   static void toggle()       {}
   static void set(bool b)    {}
   static bool isSet()        {return false;}
   static bool isClear()      {return false;}
   static void waitForSet()   {}
   static void waitForClear() {}

};

using PA0 = Pin_t<PA, 0>;
using PA1 = Pin_t<PA, 1>;
using PA2 = Pin_t<PA, 2>;
using PA3 = Pin_t<PA, 3>;
using PA4 = Pin_t<PA, 4>;
using PA5 = Pin_t<PA, 5>;
using PA6 = Pin_t<PA, 6>;
using PA7 = Pin_t<PA, 7>;
using PA8 = Pin_t<PA, 8>;
using PA9 = Pin_t<PA, 9>;
using PA10 = Pin_t<PA, 10>;
using PA11 = Pin_t<PA, 11>;
using PA12 = Pin_t<PA, 12>;
using PA13 = Pin_t<PA, 13>;
using PA14 = Pin_t<PA, 14>;
using PA15 = Pin_t<PA, 15>;

using PB0 = Pin_t<PB, 0>;
using PB1 = Pin_t<PB, 1>;
using PB2 = Pin_t<PB, 2>;
using PB3 = Pin_t<PB, 3>;
using PB4 = Pin_t<PB, 4>;
using PB5 = Pin_t<PB, 5>;
using PB6 = Pin_t<PB, 6>;
using PB7 = Pin_t<PB, 7>;
using PB8 = Pin_t<PB, 8>;
using PB9 = Pin_t<PB, 9>;
using PB10 = Pin_t<PB, 10>;
using PB11 = Pin_t<PB, 11>;
using PB12 = Pin_t<PB, 12>;
using PB13 = Pin_t<PB, 13>;
using PB14 = Pin_t<PB, 14>;
using PB15 = Pin_t<PB, 15>;

using PC0 = Pin_t<PC, 0>;
using PC1 = Pin_t<PC, 1>;
using PC2 = Pin_t<PC, 2>;
using PC3 = Pin_t<PC, 3>;
using PC4 = Pin_t<PC, 4>;
using PC5 = Pin_t<PC, 5>;
using PC6 = Pin_t<PC, 6>;
using PC7 = Pin_t<PC, 7>;
using PC8 = Pin_t<PC, 8>;
using PC9 = Pin_t<PC, 9>;
using PC10 = Pin_t<PC, 10>;
using PC11 = Pin_t<PC, 11>;
using PC12 = Pin_t<PC, 12>;
using PC13 = Pin_t<PC, 13>;
using PC14 = Pin_t<PC, 14>;
using PC15 = Pin_t<PC, 15>;

using PD0 = Pin_t<PD, 0>;
using PD1 = Pin_t<PD, 1>;
using PD2 = Pin_t<PD, 2>;
using PD3 = Pin_t<PD, 3>;
using PD4 = Pin_t<PD, 4>;
using PD5 = Pin_t<PD, 5>;
using PD6 = Pin_t<PD, 6>;
using PD7 = Pin_t<PD, 7>;
using PD8 = Pin_t<PD, 8>;
using PD9 = Pin_t<PD, 9>;
using PD10 = Pin_t<PD, 10>;
using PD11 = Pin_t<PD, 11>;
using PD12 = Pin_t<PD, 12>;
using PD13 = Pin_t<PD, 13>;
using PD14 = Pin_t<PD, 14>;
using PD15 = Pin_t<PD, 15>;

using PF0 = Pin_t<PF, 0>;
using PF1 = Pin_t<PF, 1>;
using PF2 = Pin_t<PF, 2>;
using PF3 = Pin_t<PF, 3>;
using PF4 = Pin_t<PF, 4>;
using PF5 = Pin_t<PF, 5>;
using PF6 = Pin_t<PF, 6>;
using PF7 = Pin_t<PF, 7>;
using PF8 = Pin_t<PF, 8>;
using PF9 = Pin_t<PF, 9>;
using PF10 = Pin_t<PF, 10>;
using PF11 = Pin_t<PF, 11>;
using PF12 = Pin_t<PF, 12>;
using PF13 = Pin_t<PF, 13>;
using PF14 = Pin_t<PF, 14>;
using PF15 = Pin_t<PF, 15>;

#if defined(STM32F405xx)
using PE0 = Pin_t<PE, 0>;
using PE1 = Pin_t<PE, 1>;
using PE2 = Pin_t<PE, 2>;
using PE3 = Pin_t<PE, 3>;
using PE4 = Pin_t<PE, 4>;
using PE5 = Pin_t<PE, 5>;
using PE6 = Pin_t<PE, 6>;
using PE7 = Pin_t<PE, 7>;
using PE8 = Pin_t<PE, 8>;
using PE9 = Pin_t<PE, 9>;
using PE10 = Pin_t<PE, 10>;
using PE11 = Pin_t<PE, 11>;
using PE12 = Pin_t<PE, 12>;
using PE13 = Pin_t<PE, 13>;
using PE14 = Pin_t<PE, 14>;
using PE15 = Pin_t<PE, 15>;

using PG0 = Pin_t<PG, 0>;
using PG1 = Pin_t<PG, 1>;
using PG2 = Pin_t<PG, 2>;
using PG3 = Pin_t<PG, 3>;
using PG4 = Pin_t<PG, 4>;
using PG5 = Pin_t<PG, 5>;
using PG6 = Pin_t<PG, 6>;
using PG7 = Pin_t<PG, 7>;
using PG8 = Pin_t<PG, 8>;
using PG9 = Pin_t<PG, 9>;
using PG10 = Pin_t<PG, 10>;
using PG11 = Pin_t<PG, 11>;
using PG12 = Pin_t<PG, 12>;
using PG13 = Pin_t<PG, 13>;
using PG14 = Pin_t<PG, 14>;
using PG15 = Pin_t<PG, 15>;
#endif




template <class PORT, uint8_t pin>
template<GPIO_ral::AF af>
void Pin_t<PORT,pin>::configureAltFunction()
{
   using PIN = Pin_t<PORT,pin>;
   if      (af == GPIO_ral::AF::_0) CONFIGURE_PIN(PIN, AlternateFunc0);
   else if (af == GPIO_ral::AF::_1) CONFIGURE_PIN(PIN, AlternateFunc1);
   else if (af == GPIO_ral::AF::_2) CONFIGURE_PIN(PIN, AlternateFunc2);
   else if (af == GPIO_ral::AF::_3) CONFIGURE_PIN(PIN, AlternateFunc3);
   else if (af == GPIO_ral::AF::_4) CONFIGURE_PIN(PIN, AlternateFunc4);
   else if (af == GPIO_ral::AF::_5) CONFIGURE_PIN(PIN, AlternateFunc5);
   else if (af == GPIO_ral::AF::_6) CONFIGURE_PIN(PIN, AlternateFunc6);
   else if (af == GPIO_ral::AF::_7) CONFIGURE_PIN(PIN, AlternateFunc7);
   
}

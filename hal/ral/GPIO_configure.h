/**
 * Тут определяются маски конфигурации пинов
 * в виде перечисления для передаче в качестве
 * параметра шаблона
 */

#pragma once

#include "GPIO_bits.h"

namespace GPIO {

static constexpr uint32_t MakeMask (
   GPIO_ral::Mode_t m, 
   GPIO_ral::OutType_t t,
   GPIO_ral::OutSpeed_t s,
   GPIO_ral::PullResistor_t r,
   GPIO_ral::AF af
) {
   return (uint32_t)m | (uint32_t)t  << 2 
                      | (uint32_t)s  << 3
                      | (uint32_t)r  << 5
                      | (uint32_t)af << 7;
}

} // namespace GPIO {




enum class PinConf_t {
   Output = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Output,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_0
   ),
   OutputHighSpeed = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Output,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::High,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_0
   ),
   Input = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Input,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral                 ::AF::_0
   ),
   AlternateFunc0 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_0
   ),
   AlternateFunc0HighSpeed = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::High,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_0
   ),
   AnalogInput = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Analog,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_0
   ),
   AlternateFunc1 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_1
   ),
   AlternateFunc1HighSpeed = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::High,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_1
   ),
   AlternateFunc2 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_2
   ),
   AlternateFunc3 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_3
   ),
   AlternateFunc4 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_4
   ),
   AlternateFunc5 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_5
   ),
   AlternateFunc6 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_6
   ),
   AlternateFunc7 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_7
   ),
   AlternateFunc7HighSpeed = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::High,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_7
   ),
#if defined(STM32F405xx)
   AlternateFunc8 = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::Low,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_8
   ),
   AlternateFunc8HighSpeed = GPIO::MakeMask (
      GPIO_ral::Mode_t         ::Alternate,
      GPIO_ral::OutType_t      ::PushPull,
      GPIO_ral::OutSpeed_t     ::High,
      GPIO_ral::PullResistor_t ::No,
      GPIO_ral::AF             ::_8
   ),
#endif
};
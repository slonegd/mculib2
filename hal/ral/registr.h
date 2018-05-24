#pragma once

#if defined(STM32F030x6)
   #include "stm32f0xx.h"
#elif defined(STM32F405xx)
   #include "stm32f4xx.h"
#endif

#include <type_traits>

template<class Bits>
struct BitsRegistr {
   union {
      __IO Bits     bits;
      __IO uint32_t reg;
   };
   static_assert (sizeof(Bits) == sizeof(uint32_t), "use BitsRegistrs");
};


template<class Bits, uint32_t n = sizeof(Bits)/4+1>
struct BitsRegistrs {
   union {
      __IO Bits     bits;
      __IO uint32_t reg[n];
   };
};


struct DataRegistr {
   __IO uint32_t reg;
};


template<int n>
struct ArrayDataRegistr {
   __IO uint32_t reg[n];
};


template<int n>
class Reserve_t {
   uint32_t reg[n];
};


template <uint32_t offset>
struct Offset_t { enum { Offset = offset }; };


#define _1BIT_TO_MASK(reg, pos) ((uint32_t)1 << std::remove_reference<decltype(reg)>::type::pos)
#define SET(reg_,pos)           (reg_.reg  |=  _1BIT_TO_MASK(reg_, pos))
#define CLEAR(reg_,pos)         (reg_.reg  &= ~_1BIT_TO_MASK(reg_, pos))
#define IS_CLEAR(reg_,pos)      ((reg_.reg &   _1BIT_TO_MASK(reg_, pos)) == 0)
#define IS_SET(reg_,pos)        ((reg_.reg &   _1BIT_TO_MASK(reg_, pos)) != 0)
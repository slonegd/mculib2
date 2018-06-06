#pragma once

#if defined(STM32F030x6)
   #include "stm32f0xx.h"
#elif defined(STM32F405xx)
   #include "stm32f4xx.h"
   #include "bitbanding.h"
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


template<class Bits, uint32_t n = sizeof(Bits)/4>
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


#define _1BIT_TO_MASK(reg, pos) ((uint32_t)0b1         << std::remove_reference<decltype(reg)>::type::pos)
#define _2BIT_TO_MASK(reg, pos) ((uint32_t)0b11        << std::remove_reference<decltype(reg)>::type::pos)
#define _3BIT_TO_MASK(reg, pos) ((uint32_t)0b111       << std::remove_reference<decltype(reg)>::type::pos)
#define _4BIT_TO_MASK(reg, pos) ((uint32_t)0b1111      << std::remove_reference<decltype(reg)>::type::pos)
#define _6BIT_TO_MASK(reg, pos) ((uint32_t)0b111111    << std::remove_reference<decltype(reg)>::type::pos)
#define _9BIT_TO_MASK(reg, pos) ((uint32_t)0b111111111 << std::remove_reference<decltype(reg)>::type::pos)
#define SHIFT_TO_0(reg_, pos)   (reg_.reg >> std::remove_reference<decltype(reg_)>::type::pos)
#define _2BIT_READ(reg, pos)    (0b11        & SHIFT_TO_0(reg, pos))
#define _3BIT_READ(reg, pos)    (0b111       & SHIFT_TO_0(reg, pos))
#define _4BIT_READ(reg, pos)    (0b1111      & SHIFT_TO_0(reg, pos))
#define _6BIT_READ(reg, pos)    (0b111111    & SHIFT_TO_0(reg, pos))
#define _9BIT_READ(reg, pos)    (0b111111111 & SHIFT_TO_0(reg, pos))
#define VAL_TO_MASK(reg, pos, val) ((uint32_t)val << std::remove_reference<decltype(reg)>::type::pos)
#define SET(reg_,pos)           (reg_.reg  |=  _1BIT_TO_MASK(reg_, pos))
#define CLEAR(reg_,pos)         (reg_.reg  &= ~_1BIT_TO_MASK(reg_, pos))
#define IS_CLEAR(reg_,pos)      ((reg_.reg &   _1BIT_TO_MASK(reg_, pos)) == 0)
#define IS_SET(reg_,pos)        ((reg_.reg &   _1BIT_TO_MASK(reg_, pos)) != 0)


/// эта ерунда не работает на этапе компиляции, потому не использовать!!!
#define POSITHION_OF(reg_,pos) [](){ \
   typename std::decay<decltype(reg_)>::type reg; \
   reg.bits.pos = static_cast<typename std::decay<decltype(reg.bits.pos)>::type>(1); \
   size_t res = 0; \
   while (reg.reg != 1) { \
      reg.reg >> 1; \
      res++; \
   } \
   return res; \
   }()


#define _1BIT_TO_MASK_(reg, pos) ((uint32_t)0b1 << POSITHION_OF(reg, pos))
#define SET_(reg_,pos)           (reg_.reg  |=  _1BIT_TO_MASK_(reg_, pos))
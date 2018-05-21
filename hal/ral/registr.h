#pragma once

#if defined(STM32F030x6)
   #include "stm32f0xx.h"
#elif defined(STM32F405xx)
   #include "stm32f4xx.h"
#endif

template<class Bits>
struct BitsRegistr {
   union {
      __IO Bits     bits;
      __IO uint32_t reg;
   };
};
struct DataRegistr {
   __IO uint32_t reg;
};
template <uint32_t offset>
struct Offset_t { enum { Offset = offset }; };
#pragma once

#if defined(STM32F030x6)
   #include "stm32f0xx.h"
#elif defined(STM32F405xx)
   #include "stm32f4xx.h"
#endif

#include <type_traits>

/// определение типа регистра (одиночный или массив) по размеру Bits
namespace Magic {
   template<class Bits, class T = typename std::enable_if<sizeof(Bits) == 4>::type>
   auto type() { uint32_t res; return res; }

   template<class Bits, class T = typename std::enable_if<sizeof(Bits) != 4>::type, class U = void>
   auto type() { static uint32_t res[sizeof(Bits)]; return res; }

   template<class Bits>
   using T = decltype(type<Bits>());
}



template<class Bits>
struct BitsRegistr {
   union {
      __IO Bits           bits;
      __IO Magic::T<Bits> reg;
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
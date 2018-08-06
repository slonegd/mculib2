/**
 * структура работы с пинами как с вариадиком
 */
#pragma once

#include "pin.h"

template<class First, class...Other>
struct Pins
{
   template<PinConf_t val>
   static void configure()
   {
      First::template configure<val>();
      Pins<Other...>::template configure<val>();
   }

   static constexpr std::size_t qty() { return 1 + sizeof...(Other); }

};

template<class Last>
struct Pins<Last>
{
   template<PinConf_t val>
   static void configure()
   {
      Last::template configure<val>();
   }

   static constexpr std::size_t qty() { return 1; }

};


#define TYPE(...) __VA_ARGS__

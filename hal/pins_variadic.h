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
};

template<class Last>
struct Pins<Last>
{
   template<PinConf_t val>
   static void configure()
   {
      Last::template configure<val>();
   }
};
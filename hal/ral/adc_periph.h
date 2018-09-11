#pragma once

#include "registr.h"
#include "ADC_common.h"
#include "DMA.h"

namespace ADC_detail {
   template<class T> struct DefaultStream_impl { using type = void; };
   template<class T>
   using DefaultStream_t = typename DefaultStream_impl<T>::type;
}

#if defined(STM32F0)
   #include "adc_f0.h"
#elif defined(STM32F4)
   #include "adc_f4.h"
#endif
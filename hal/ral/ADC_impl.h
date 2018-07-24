#pragma once

#include "pin.h"
#include "DMA.h"
#include "meta.h"
#include <type_traits>

namespace ADC_ral {

   template <class ADC_> struct DefaultStream;
#if defined(STM32F405xx)
   template<> struct DefaultStream<ADC1> { using Type = DMA1stream0; };
   template<> struct DefaultStream<ADC2> { using Type = DMA1stream2; };
   template<> struct DefaultStream<ADC3> { using Type = DMA1stream0; };
#elif defined(STM32F030x6)
   template<> struct DefaultStream<ADC1> { using Type = DMA1channel1; };
#endif

#if defined(STM32F405xx)
   template <class ADC_> constexpr auto DMAchannel() { return
      IS_SAME(ADC_,ADC1) ? ADC_::Channels::_0 :
      IS_SAME(ADC_,ADC2) ? ADC_::Channels::_1 :
      IS_SAME(ADC_,ADC3) ? ADC_::Channels::_2 : ADC_::Channels::_0;
   }
#endif


   template <class ADC_, class Pin> constexpr uint8_t ADCchannel() { return
      IS_SAME(ADC_,ADC1)
#if defined(STM32F405xx)
      or IS_SAME(ADC_,ADC2)
#endif       
       ? (
            IS_SAME(Pin,PA0) ? 0  : 
            IS_SAME(Pin,PA1) ? 1  :
            IS_SAME(Pin,PA2) ? 2  :
            IS_SAME(Pin,PA3) ? 3  :
            IS_SAME(Pin,PA4) ? 4  :
            IS_SAME(Pin,PA5) ? 5  :
            IS_SAME(Pin,PA6) ? 6  :
            IS_SAME(Pin,PA7) ? 7  :
            IS_SAME(Pin,PB0) ? 8  :
            IS_SAME(Pin,PB1) ? 9  :
            IS_SAME(Pin,PC0) ? 10 :
            IS_SAME(Pin,PC1) ? 11 :
            IS_SAME(Pin,PC2) ? 12 :
            IS_SAME(Pin,PC3) ? 13 :
            IS_SAME(Pin,PC4) ? 14 :
            IS_SAME(Pin,PC5) ? 15 : 255 ) : 
#if defined(STM32F405xx)         
      IS_SAME(ADC_,ADC3) ? (
            IS_SAME(Pin,PA0)  ? 0  :
            IS_SAME(Pin,PA1)  ? 1  :
            IS_SAME(Pin,PA2)  ? 2  :
            IS_SAME(Pin,PA3)  ? 3  :
            IS_SAME(Pin,PF6)  ? 4  :
            IS_SAME(Pin,PF7)  ? 5  :
            IS_SAME(Pin,PF8)  ? 6  :
            IS_SAME(Pin,PF9)  ? 7  :
            IS_SAME(Pin,PF10) ? 8  :
            IS_SAME(Pin,PF3)  ? 9  :
            IS_SAME(Pin,PC0)  ? 10 :
            IS_SAME(Pin,PC1)  ? 11 :
            IS_SAME(Pin,PC2)  ? 12 :
            IS_SAME(Pin,PC3)  ? 13 :
            IS_SAME(Pin,PF4)  ? 14 :
            IS_SAME(Pin,PF5)  ? 15 : 255 ) :
#endif
      255;
   }



   template <class ADC_, class Pin> constexpr bool PinEnabled() {
      return ADCchannel<ADC_,Pin>() != 255;
   }

#if defined(STM32F405xx)   
   template <class ADC_, class DMA_> constexpr bool DMAenabled()
   {
      return 
         ( IS_SAME(ADC_,ADC1) 
           and (IS_SAME(DMA_,DMA1stream0) or IS_SAME(DMA_,DMA1stream4))
         ) or (
           IS_SAME(ADC_,ADC2) 
           and (IS_SAME(DMA_,DMA1stream2) or IS_SAME(DMA_,DMA1stream3))
         ) or (
           IS_SAME(ADC_,ADC3) 
           and (IS_SAME(DMA_,DMA1stream0) or IS_SAME(DMA_,DMA1stream1))
         );
   }
#elif defined(STM32F030x6)
   template <class ADC_, class DMA_> constexpr bool DMAenabled()
   {
      return IS_SAME(ADC_, ADC1)  and IS_SAME(DMA_, DMA1channel1);
   }
#endif


} // namespace ADC_ral {

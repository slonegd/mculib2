#pragma once

#include <type_traits>
#include "pin.h"

// тут ещё не про все таймеры написано
template<class TIM_, class Pin_> constexpr uint8_t Channel() { return
   std::is_same<TIM_,TIM1>::value ? (  std::is_same<Pin_,PA8>::value  ? 1 :
                                       std::is_same<Pin_,PA9>::value  ? 2 :
                                       std::is_same<Pin_,PA10>::value ? 3 :
                                       std::is_same<Pin_,PA11>::value ? 4 :
#if defined(STM32F405xx)
                                       std::is_same<Pin_,PE9>::value  ? 1 :
                                       std::is_same<Pin_,PE11>::value ? 2 :
                                       std::is_same<Pin_,PE13>::value ? 3 :
                                       std::is_same<Pin_,PE14>::value ? 4 :
#endif
   0 ) :
#if defined(STM32F405xx)
   std::is_same<TIM_,TIM2>::value ? (  std::is_same<Pin_,PA0>::value  ? 1 :
                                       std::is_same<Pin_,PA1>::value  ? 2 :
                                       std::is_same<Pin_,PA2>::value  ? 3 :
                                       std::is_same<Pin_,PA3>::value  ? 4 :
                                       std::is_same<Pin_,PA5>::value  ? 1 :
                                       std::is_same<Pin_,PA15>::value ? 1 :
                                       std::is_same<Pin_,PB3>::value  ? 2 :
                                       std::is_same<Pin_,PB10>::value ? 3 :
                                       std::is_same<Pin_,PB11>::value ? 4 :

   0 ) :
#endif
   std::is_same<TIM_,TIM3>::value ? (  std::is_same<Pin_,PA6>::value  ? 1 :
                                       std::is_same<Pin_,PA7>::value  ? 2 :
                                       std::is_same<Pin_,PB0>::value  ? 3 :
                                       std::is_same<Pin_,PB1>::value  ? 4 :
                                       std::is_same<Pin_,PB4>::value  ? 1 :
                                       std::is_same<Pin_,PB5>::value  ? 2 :
                                       std::is_same<Pin_,PC6>::value  ? 1 :
                                       std::is_same<Pin_,PC7>::value  ? 2 :
                                       std::is_same<Pin_,PC8>::value  ? 3 :
                                       std::is_same<Pin_,PC9>::value  ? 4 :
   0 ) :
#if defined(STM32F405xx)
   std::is_same<TIM_,TIM4>::value ? (  std::is_same<Pin_,PB6>::value  ? 1 :
                                       std::is_same<Pin_,PB7>::value  ? 2 :
                                       std::is_same<Pin_,PB8>::value  ? 3 :
                                       std::is_same<Pin_,PB9>::value  ? 4 :
                                       std::is_same<Pin_,PD12>::value ? 1 :
                                       std::is_same<Pin_,PD13>::value ? 2 :
                                       std::is_same<Pin_,PD14>::value ? 3 :
                                       std::is_same<Pin_,PD15>::value ? 4 :
   0 ) :
   std::is_same<TIM_,TIM5>::value ? (  std::is_same<Pin_,PA0>::value  ? 1 :
                                       std::is_same<Pin_,PA1>::value  ? 2 :
                                       std::is_same<Pin_,PA2>::value  ? 3 :
                                       std::is_same<Pin_,PA3>::value  ? 4 :
   0 ) :
   std::is_same<TIM_,TIM8>::value ? (  std::is_same<Pin_,PA5>::value  ? 1 :
                                       std::is_same<Pin_,PA7>::value  ? 1 :
                                       std::is_same<Pin_,PB0>::value  ? 2 :
                                       std::is_same<Pin_,PB1>::value  ? 3 :
                                       std::is_same<Pin_,PB14>::value ? 2 :
                                       std::is_same<Pin_,PB15>::value ? 3 :
                                       std::is_same<Pin_,PC6>::value  ? 1 :
                                       std::is_same<Pin_,PC7>::value  ? 2 :
                                       std::is_same<Pin_,PC8>::value  ? 3 :
                                       std::is_same<Pin_,PC9>::value  ? 4 :
   0 ) :
#endif
   0;
}


template<class TIM_, class Pin_> constexpr AFR_t::AF AltFunc() {
   return
 #if defined(STM32F030x6)
   std::is_same<TIM_,TIM1>::value ? AFR_t::AF::_2 :
   std::is_same<TIM_,TIM3>::value ? (  std::is_same<Pin_,PA6>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PB4>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PC6>::value ? AFR_t::AF::_0 :
                                       std::is_same<Pin_,PA7>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PB5>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PC7>::value ? AFR_t::AF::_0 :
                                       std::is_same<Pin_,PB0>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PC8>::value ? AFR_t::AF::_0 :
                                       std::is_same<Pin_,PB1>::value ? AFR_t::AF::_1 :
                                       std::is_same<Pin_,PC9>::value ? AFR_t::AF::_0 : AFR_t::AF::_0 ) :
   std::is_same<TIM_,TIM14>::value ? ( std::is_same<Pin_,PA4>::value ? AFR_t::AF::_4 :
                                       std::is_same<Pin_,PA7>::value ? AFR_t::AF::_4 :
                                       std::is_same<Pin_,PB1>::value ? AFR_t::AF::_0 : AFR_t::AF::_0 ) :
   std::is_same<TIM_,TIM16>::value ? ( std::is_same<Pin_,PA6>::value ? AFR_t::AF::_5 :
                                       std::is_same<Pin_,PB8>::value ? AFR_t::AF::_2 : AFR_t::AF::_0 ) :
   std::is_same<TIM_,TIM17>::value ? ( std::is_same<Pin_,PA7>::value ? AFR_t::AF::_5 :
                                       std::is_same<Pin_,PB9>::value ? AFR_t::AF::_2 : AFR_t::AF::_0 ) :
   AFR_t::AF::_0;
#elif defined(STM32F405xx)
   std::is_same<TIM_,TIM1>::value  ? AFR_t::AF::_1 :
   std::is_same<TIM_,TIM2>::value  ? AFR_t::AF::_1 :
   std::is_same<TIM_,TIM3>::value  ? AFR_t::AF::_2 :
   std::is_same<TIM_,TIM4>::value  ? AFR_t::AF::_2 :
   std::is_same<TIM_,TIM5>::value  ? AFR_t::AF::_2 :
   std::is_same<TIM_,TIM8>::value  ? AFR_t::AF::_3 :
   std::is_same<TIM_,TIM9>::value  ? AFR_t::AF::_3 :
   std::is_same<TIM_,TIM10>::value ? AFR_t::AF::_3 :
   std::is_same<TIM_,TIM11>::value ? AFR_t::AF::_3 : AFR_t::AF::_0;
#endif
}




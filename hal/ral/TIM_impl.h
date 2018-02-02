#pragma once

#include <type_traits>
#include "pin_hal.h"

// тут ещё не про все таймеры написано
template<class Timer, class Pin> constexpr uint8_t PWMchannel() { return
   std::is_same<Timer,TIM1>::value ? ( std::is_same<Pin,PA8>::value  ? 1 :
                                       std::is_same<Pin,PA9>::value  ? 2 :
                                       std::is_same<Pin,PA10>::value ? 3 :
                                       std::is_same<Pin,PA11>::value ? 4 :
#if defined(STM32F405xx)
                                       std::is_same<Pin,PE9>::value  ? 1 :
                                       std::is_same<Pin,PE11>::value ? 2 :
                                       std::is_same<Pin,PE13>::value ? 3 :
                                       std::is_same<Pin,PE14>::value ? 4 :
#endif
   0 ) :
#if defined(STM32F405xx)
   std::is_same<Timer,TIM2>::value ? ( std::is_same<Pin,PA0>::value  ? 1 :
                                       std::is_same<Pin,PA1>::value  ? 2 :
                                       std::is_same<Pin,PA2>::value  ? 3 :
                                       std::is_same<Pin,PA3>::value  ? 4 :
                                       std::is_same<Pin,PA5>::value  ? 1 :
                                       std::is_same<Pin,PA15>::value ? 1 :
                                       std::is_same<Pin,PB3>::value  ? 2 :
                                       std::is_same<Pin,PB10>::value ? 3 :
                                       std::is_same<Pin,PB11>::value ? 4 :

   0 ) :
#endif
   std::is_same<Timer,TIM3>::value ? ( std::is_same<Pin,PA6>::value  ? 1 :
                                       std::is_same<Pin,PA7>::value  ? 2 :
                                       std::is_same<Pin,PB0>::value  ? 3 :
                                       std::is_same<Pin,PB1>::value  ? 4 :
                                       std::is_same<Pin,PB4>::value  ? 1 :
                                       std::is_same<Pin,PB5>::value  ? 2 :
                                       std::is_same<Pin,PC6>::value  ? 1 :
                                       std::is_same<Pin,PC7>::value  ? 2 :
                                       std::is_same<Pin,PC8>::value  ? 3 :
                                       std::is_same<Pin,PC9>::value  ? 4 :
   0 ) :
#if defined(STM32F405xx)
   std::is_same<Timer,TIM4>::value ? ( std::is_same<Pin,PB6>::value  ? 1 :
                                       std::is_same<Pin,PB7>::value  ? 2 :
                                       std::is_same<Pin,PB8>::value  ? 3 :
                                       std::is_same<Pin,PB9>::value  ? 4 :
                                       std::is_same<Pin,PD12>::value ? 1 :
                                       std::is_same<Pin,PD13>::value ? 2 :
                                       std::is_same<Pin,PD14>::value ? 3 :
                                       std::is_same<Pin,PD15>::value ? 4 :
   0 ) :
   std::is_same<Timer,TIM5>::value ? ( std::is_same<Pin,PA0>::value  ? 1 :
                                       std::is_same<Pin,PA1>::value  ? 2 :
                                       std::is_same<Pin,PA2>::value  ? 3 :
                                       std::is_same<Pin,PA3>::value  ? 4 :
   0 ) :
   std::is_same<Timer,TIM8>::value ? ( std::is_same<Pin,PA5>::value  ? 1 :
                                       std::is_same<Pin,PA7>::value  ? 1 :
                                       std::is_same<Pin,PB0>::value  ? 2 :
                                       std::is_same<Pin,PB1>::value  ? 3 :
                                       std::is_same<Pin,PB14>::value ? 2 :
                                       std::is_same<Pin,PB15>::value ? 3 :
                                       std::is_same<Pin,PC6>::value  ? 1 :
                                       std::is_same<Pin,PC7>::value  ? 2 :
                                       std::is_same<Pin,PC8>::value  ? 3 :
                                       std::is_same<Pin,PC9>::value  ? 4 : 
   0 ) :
#endif
   0;
}
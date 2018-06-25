#pragma once

   #include "RCC.h"
   #include "FLASH.h"
   #include "GPIO.h"
   #include "DMA.h"
   #include "TIM.h"
   #include "SysTick_.h"
#if defined(STM32F030x6)
   #include "SPI.h"
   #include "ADC.h"
#elif defined(STM32F405xx)
   #include "USART.h"
#endif


#define MAKE_VAR(name) __IO auto name##_d = (name*) name::Base

__IO auto RCC_d    = RCC   ::create();
__IO auto GPIOA_d  = PA    ::Create();
__IO auto GPIOB_d  = PB    ::Create();
__IO auto GPIOC_d  = PC    ::Create();
__IO auto GPIOD_d  = PD    ::Create();
__IO auto GPIOF_d  = PF    ::Create();
__IO auto FLASH_d  = FLASH ::create();
__IO auto USART1_d = USART1::create();
MAKE_VAR(DMA1);
MAKE_VAR(TIM1);
MAKE_VAR(TIM3);
__IO auto SysTick_d = (SysTick_t*) SysTick;
#if defined(STM32F030x6)
   __IO auto SPI1_d = SPI1::create();
   MAKE_VAR(DMA1channel1);
   MAKE_VAR(DMA1channel2);
   MAKE_VAR(DMA1channel3);
   MAKE_VAR(DMA1channel4);
   MAKE_VAR(DMA1channel5);
   MAKE_VAR(ADC1);
#elif defined(STM32F405xx)
    __IO auto GPIOE_d = PE::Create();
    MAKE_VAR(TIM2);
    MAKE_VAR(TIM4);
    MAKE_VAR(TIM5);
    MAKE_VAR(TIM8);
    __IO auto USART2_d = USART2::create();
    __IO auto USART3_d = USART3::create();
    __IO auto USART6_d = USART6::create();
    MAKE_VAR(DMA1stream0);
    MAKE_VAR(DMA1stream1);
    MAKE_VAR(DMA1stream2);
    MAKE_VAR(DMA1stream3);
    MAKE_VAR(DMA1stream4);
    MAKE_VAR(DMA1stream5);
    MAKE_VAR(DMA1stream6);
    MAKE_VAR(DMA1stream7);
    MAKE_VAR(DMA2stream0);
    MAKE_VAR(DMA2stream1);
    MAKE_VAR(DMA2stream2);
    MAKE_VAR(DMA2stream3);
    MAKE_VAR(DMA2stream4);
    MAKE_VAR(DMA2stream5);
    MAKE_VAR(DMA2stream6);
    MAKE_VAR(DMA2stream7);
    MAKE_VAR(DMA2);
#endif

#undef MAKE_VAR

inline void makeDebugVar (void)
{
    RCC_d->doSome();
    FLASH_d->doSome();
    USART1_d->doSome();
    GPIOA_d->makeDebugVar();
    GPIOB_d->makeDebugVar();
    // GPIOC_d->makeDebugVar();
    // почему то с ним не работает ЭО86
   //  GPIOD_d->makeDebugVar();
    GPIOF_d->makeDebugVar();
    DMA1_d->makeDebugVar();
    TIM1_d->makeDebugVar();
    TIM3_d->makeDebugVar();
    SysTick_d->VAL_t::reg = 0;
#if defined(STM32F030x6)
    SPI1_d->doSome();
    DMA1channel1_d->makeDebugVar();
    DMA1channel2_d->makeDebugVar();
    DMA1channel3_d->makeDebugVar();
    DMA1channel4_d->makeDebugVar();
    DMA1channel5_d->makeDebugVar();
    ADC1_d->makeDebugVar();
#elif defined(STM32F405xx)
    GPIOE_d->makeDebugVar();
    TIM2_d->makeDebugVar();
    TIM4_d->makeDebugVar();
    TIM5_d->makeDebugVar();
    TIM8_d->makeDebugVar();
    
    USART2_d->doSome();
    USART3_d->doSome();
    USART6_d->doSome();
    DMA1stream0_d->makeDebugVar();
    DMA1stream1_d->makeDebugVar();
    DMA1stream2_d->makeDebugVar();
    DMA1stream3_d->makeDebugVar();
    DMA1stream4_d->makeDebugVar();
    DMA1stream5_d->makeDebugVar();
    DMA1stream6_d->makeDebugVar();
    DMA1stream7_d->makeDebugVar();
    DMA2stream0_d->makeDebugVar();
    DMA2stream1_d->makeDebugVar();
    DMA2stream2_d->makeDebugVar();
    DMA2stream3_d->makeDebugVar();
    DMA2stream4_d->makeDebugVar();
    DMA2stream5_d->makeDebugVar();
    DMA2stream6_d->makeDebugVar();
    DMA2stream7_d->makeDebugVar();
    DMA2_d->makeDebugVar();

#endif

}


#undef MAKE_VAR
#pragma once

#include <stdint.h>
#include "defines.h"
#if defined(STM32F405xx)
    #include "stm32f4xx.h"
#elif defined(STM32F030x6)
    #include "stm32f0xx.h"
#endif


template <uint16_t ms>
inline void InitSysTimerInt (void)
{
    constexpr uint32_t val = F_CPU/(1000*ms)-1;
    static_assert (
       val <= 0xFFFFFF,
       "число должно быть 24-битное"
    );
    SysTick->LOAD = val;				            //Загрузка значения
    SysTick->VAL = val;				                //Обнуляем таймеры и флаги 

    SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk 		//processor clock
                    | SysTick_CTRL_TICKINT_Msk;     //разрешение прерывания
    
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  	    //запускает таймер
}
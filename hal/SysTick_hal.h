#pragma once

#include <stdint.h>
#include "defines.h"
#include "stm32f4xx.h"

template <uint16_t ms>
inline void InitSysTimerInt (void)
{
    constexpr uint32_t val = F_CPU/(1000*ms)-1;
    SysTick->LOAD = val;				            //Загрузка значения
    SysTick->VAL = val;				                //Обнуляем таймеры и флаги 

    SysTick->CTRL =	SysTick_CTRL_CLKSOURCE_Msk 		//processor clock
                    | SysTick_CTRL_TICKINT_Msk;     //разрешение прерывания
    
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  	    //запускает таймер
}
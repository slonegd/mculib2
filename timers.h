/**
 * шаблон класса аппаратных таймеров
 * параметр шаблона - количество таймеров
 * каждый отдельный таймер и методы работы с ним
 * в отдельном массиве
 * 
 */

#pragma once

#include <stdint.h>
#include "SysTick.h"

struct Timer
{
    volatile bool enable;
    // устанавливается в true, если дотикал
    volatile bool counted;
    // время работы в мс до установки counted
    volatile uint32_t timeSet;
    // прошедшее время в мс
    volatile uint32_t timePassed;	

    inline void setTimeAndStart (uint32_t ms)
    {
        timeSet = ms;
        enable = true;
    }
    inline void setTime (uint32_t ms) { timeSet = ms; }
    // возвращает true, если таймер натикал и перезапускает его
    inline bool event()
    {
        if (counted) {
            counted = false;
            timePassed = 0;
            return (true);
        } else {
            return (false);
        }
    }
    // возвращает true, если таймер натикал и НЕ перезапускает его
    inline bool done()   { return counted; }
    inline void pause()  { enable = false; }
    inline void start()  { enable = true;  }
    inline void stop()
    {
        counted = false;
        enable = false; 
        timePassed = 0;
    }
};

template<uint8_t qty>
class Timers
{
private:
    // служебная переменная, подсчёт милисекунд
    volatile uint16_t TickCount = 0;
public:
    Timer all[qty];
public:
    // инициализация и включение прерываний аппаратного таймера каждую мс
    Timers (void)
    {
        InitSysTimerInt<1> ();
    }
    // должно вызываться в прерывании аппаратного таймера
    inline void tick (void)
    {
        TickCount++;
    }
    // обновляет все созданные структуры Timer, если необходимо
    inline void update (void)
    {
        if (TickCount > 0) {
            for (uint8_t i = 0; i < qty; i++) {
                if (all[i].enable && !all[i].counted) {
                    all[i].timePassed = all[i].timePassed+TickCount;
                    all[i].counted = all[i].timePassed >= all[i].timeSet;
                }
            }
            TickCount = 0;
        }
    }
};




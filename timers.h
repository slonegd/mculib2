#pragma once

#include <stdint.h>
#include "SysTick.h"


struct TimersSubcriber;


class Timer
{
public:
   Timer();

   void setTime (uint32_t ms);
   void start   (uint32_t ms); /// запускает счёт с текущего значения счётчика, устанавливает время
   bool event();   /// возвращает true, если таймер натикал и перезапускает его
   template<class function>
   void event(function); /// выполняет function, когда дотикал и перезапускает таймер
   bool done();    /// возвращает true, если таймер натикал и НЕ перезапускает его
   void pause();   /// останавливает счёт, но не сбрасывает счётчик
   void start();   /// запускает счёт с текущего значения счётчика
   void stop();    /// останавливает счёт и сбрасывает счётчик
   bool isGreater (uint32_t val); /// возвращает true, если счётчик натикал больше значения val
   bool isCount(); /// возвращает true если считает, но не досчитал



private:
   volatile bool     enable;
   volatile bool     counted;
   volatile uint32_t timeSet;
   volatile uint32_t timePassed;	

   Timer* next;
   friend TimersSubcriber;

   void init();

};


struct TimersSubcriber
{
   Timer* first {nullptr};
   TimersSubcriber() { InitSysTimerInt<1> (); }
   /// обновляет значения счётчикаов каждого таймера, начиная с first
   void update();
} timers;


extern "C" void SysTick_Handler()
{
   timers.update();
}



void TimersSubcriber::update()
{
   auto p = this->first;
   while (p) {
      if (p->enable && !p->counted) {
         p->timePassed++;
         p->counted = p->timePassed >= p->timeSet;
      }
      p = p->next;
   }
}



Timer::Timer() : next {nullptr}
{
   init();
}


void Timer::init()
{
   auto p = timers.first;
   if (p) {
      while (p->next)
         p = p->next;
      p->next = this;
   } else {
      timers.first = this;
   }
} 


void Timer::start (uint32_t ms)
{
   timeSet = ms;
   enable = true;
}


void Timer::setTime (uint32_t ms)
{
   timeSet = ms;
}


bool Timer::event()
{
   if (counted) {
      counted = false;
      timePassed = 0;
      return (true);
   } else {
      return (false);
   }
}


template<class function>
void Timer::event(function f)
{
   if (counted) {
      counted = false;
      timePassed = 0;
      f();
   }
}


void Timer::stop()
{
   counted = false;
   enable = false; 
   timePassed = 0;
}


bool Timer::done()   { return counted; }
void Timer::pause()  { enable = false; }
void Timer::start()  { enable = true;  }
bool Timer::isGreater (uint32_t val) { return timePassed > val; }
bool Timer::isCount() { return enable and !counted; }
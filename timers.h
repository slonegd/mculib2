#pragma once

#include <stdint.h>
#include "SysTick.h"
#include "subscriber.h"


struct TickUpdater : Publisher
{
#if not defined(TEST) 
   TickUpdater() { InitSysTimerInt<1>(); }
#endif
} tickUpdater;

extern "C" void SysTick_Handler()
{
   tickUpdater.notify();
}

using TickSubscriber = Subscriber;



class Timer : TickSubscriber
{
public:
   Timer() { tickUpdater.subscribe (this); }
   void     start   (uint32_t ms); /// запускает счёт с текущего значения счётчика, устанавливает время
   bool     event();   /// возвращает true, если таймер натикал и перезапускает его
   bool     done();    /// возвращает true, если таймер натикал и НЕ перезапускает его
   void     pause();   /// останавливает счёт, но не сбрасывает счётчик
   void     start();   /// запускает счёт с текущего значения счётчика
   void     stop();    /// останавливает счёт и сбрасывает счётчик
   bool     isGreater (uint32_t val); /// возвращает true, если счётчик натикал больше значения val
   bool     isCount(); /// возвращает true если считает, но не досчитал
   uint32_t timePassed(); /// возвращает сколько натикал
   uint32_t timeLeft();   /// возвращает сколько осталось
   template<class function>
   void     event (function); /// выполняет function, когда дотикал и перезапускает таймер



   volatile uint32_t timeSet {0};
private:
   volatile bool     enable  {false};
   volatile bool     counted {false};
   volatile uint32_t timePassed_ {0};	

   void notify() override;

};




void Timer::notify()
{
   if (enable and not counted) {
      timePassed_++;
      counted = timePassed_ >= timeSet;
   }
}








void Timer::start (uint32_t ms)
{
   timeSet = ms;
   enable = true;
}


bool Timer::event()
{
   if (counted) {
      counted = false;
      timePassed_ = 0;
      return (true);
   } else {
      return (false);
   }
}


template<class function>
void Timer::event (function f)
{
   if (counted) {
      counted = false;
      timePassed_ = 0;
      f();
   }
}


void Timer::stop()
{
   counted = false;
   enable = false; 
   timePassed_ = 0;
}


bool     Timer::done()       { return counted; }
void     Timer::pause()      { enable = false; }
void     Timer::start()      { enable = true;  }
bool     Timer::isCount()    { return enable and !counted; }
uint32_t Timer::timePassed() { return timePassed_; }
uint32_t Timer::timeLeft(  ) { return timeSet - timePassed_; }
bool     Timer::isGreater (uint32_t val) { return timePassed_ > val; }
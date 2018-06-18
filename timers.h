#pragma once

#include <stdint.h>
#include "SysTick.h"


struct TickUpdater;
/// интерфейс для подписывания на вызов tick каждый тик
struct ItickSubscribed
{
   virtual void tick() = 0;
   ItickSubscribed* next {nullptr};
};


class Timer
{
public:
   Timer();

   // void     setTime (uint32_t ms);
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

   Timer* next {nullptr};
   friend TickUpdater;

   void init();

};


struct TickUpdater
{
   Timer* firstTimer {nullptr};
   ItickSubscribed* firstObserver {nullptr};
   TickUpdater() { InitSysTimerInt<1> (); }
   /// обновляет значения счётчиков каждого таймера, начиная с firstTimer
   void update();
   /// подписывает на выполнение tick каждый тик
   void subscribe (ItickSubscribed* ps);
} tickUpdater;


extern "C" void SysTick_Handler()
{
   tickUpdater.update();
}

/// можно определить у себя и добавить выполнение на каждый тик
// extern void doEveryTick() __attribute__((weak));

void TickUpdater::update()
{
   auto pt = this->firstTimer;
   while (pt) {
      if (pt->enable && !pt->counted) {
         pt->timePassed_++;
         pt->counted = pt->timePassed_ >= pt->timeSet;
      }
      pt = pt->next;
   }
   auto po = this->firstObserver;
   while (po) {
      po->tick();
      po = po->next;
   }
}


void TickUpdater::subscribe (ItickSubscribed* ps)
{
   auto p = firstObserver;
   if (p) {
      while (p->next)
         p = p->next;
      p->next = ps;
   } else {  
      firstObserver = ps;
   } 
}



Timer::Timer()
{
   init();
}


void Timer::init()
{
   auto p = tickUpdater.firstTimer;
   if (p) {
      while (p->next)
         p = p->next;
      p->next = this;
   } else {
      tickUpdater.firstTimer = this;
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
#pragma once

#include "USART.h"
#include "DMA.h"
#include "tim_periph.h"


/// интерфейс для подписки на прерывания
struct Interrupting
{
   Interrupting* next {nullptr};
   virtual void interrupt() = 0;
};


/// для каждой переферии свой класс, к которому можно подписаться
/// метод interrupt вызывается в соответсвующей функции прерывания
/// в файле interrupts.h
template<class Periph>
struct Interrupt
{
   /// список поддерживаемой переферии
   static_assert (
   #if defined(STM32F405xx)
         std::is_same<Periph, DMA1stream0>::value
      or std::is_same<Periph, DMA1stream1>::value
      or std::is_same<Periph, DMA1stream2>::value
      or std::is_same<Periph, DMA1stream3>::value
      or std::is_same<Periph, DMA1stream4>::value
      or std::is_same<Periph, DMA1stream5>::value
      or std::is_same<Periph, DMA1stream6>::value
      or std::is_same<Periph, DMA1stream7>::value
      or std::is_same<Periph, DMA2stream0>::value
      or std::is_same<Periph, DMA2stream1>::value
      or std::is_same<Periph, DMA2stream2>::value
      or std::is_same<Periph, DMA2stream3>::value
      or std::is_same<Periph, DMA2stream4>::value
      or std::is_same<Periph, DMA2stream5>::value
      or std::is_same<Periph, DMA2stream6>::value
      or std::is_same<Periph, DMA2stream7>::value
      or std::is_same<Periph, USART1     >::value
      or std::is_same<Periph, USART2     >::value
      or std::is_same<Periph, USART3     >::value
      or std::is_same<Periph, TIM1       >::value
      or std::is_same<Periph, TIM2       >::value
      or std::is_same<Periph, TIM3       >::value
      or std::is_same<Periph, TIM4       >::value
      or std::is_same<Periph, TIM5       >::value
      or std::is_same<Periph, TIM6       >::value
      or std::is_same<Periph, TIM7       >::value
      or std::is_same<Periph, TIM8       >::value
      or std::is_same<Periph, TIM9       >::value
      or std::is_same<Periph, TIM10      >::value
      or std::is_same<Periph, TIM11      >::value
      or std::is_same<Periph, TIM12      >::value
      or std::is_same<Periph, TIM13      >::value
      or std::is_same<Periph, TIM14      >::value
   #elif defined(STM32F030x6)
         std::is_same<Periph, DMA1channel1>::value
      or std::is_same<Periph, DMA1channel2>::value
      or std::is_same<Periph, DMA1channel3>::value
      or std::is_same<Periph, DMA1channel4>::value
      or std::is_same<Periph, DMA1channel5>::value
      or std::is_same<Periph, USART1      >::value
      or std::is_same<Periph, TIM1        >::value
      or std::is_same<Periph, TIM3        >::value
      or std::is_same<Periph, TIM14       >::value
      or std::is_same<Periph, TIM16       >::value
      or std::is_same<Periph, TIM17       >::value
   #else
      false
   #endif
      , "переферия не поддерживает прерывания"
   );


   static Interrupting* first;


   static void subscribe(Interrupting* ps)
   {
      auto p = first;
      if (p) {
         while (p->next)
            p = p->next;
         p->next = ps;
      } else {  
         first = ps;
      } 
   }


   static void interrupt()
   {
      auto p = first;
      while (p) {
         p->interrupt();
         p = p->next;
      }
      Periph::clearInterruptFlags();
   }
};

template<class Periph>
Interrupting* Interrupt<Periph>::first {nullptr};





/// макрос помощник на случай, если в классе надо подписаться на несколько прерываний
/// создаёт структуру внутри класса и подписывает её на нужное прерывание
/// при этом методы interrupt разных прерываний не конфликтуют,
/// поскольку в разных структурах помощниках
/// в классе должен быть определён type - тип самого класса
#define SUBSCRIBE_INTERRUPT(name, periph, function) struct name##_t : Interrupting { \
   type& up; \
   name##_t (type& up) : up(up) { \
      Interrupt<periph>::subscribe (this); \
   } \
   void interrupt() override { up.function(); } \
} name {*this}



#include "interrupts.h"
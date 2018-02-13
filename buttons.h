/******************************************************************************
 * 
 * Класс работы с кнопками
 * 
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "timers.h"
#include "literals.h"


// Types - это список пинов всех кнопок
template<class ... Types>
class Buttons
{
public:
   static const uint8_t MinPressed = 10_ms;
   static const uint8_t LongPressed = 1_s;


   Buttons (Timer& timer)
      : pushHandeledFlag(false),
        longPushHandeledFlag(false),
        timer(timer)
   {
      timer.setTime (100_s);
   }


   // запускает/останавливает таймер отслеживания времени нажатия
   // должна периодически вызываться
   void operator () ()
   {
      // (Types::IsSet() or ... ); - аналог в 17 стандарте
      if ( List<Types...>::IsAnyPush() ) {
         timer.start();
      } else {
         timer.stop();
         pushHandeledFlag = false;
         longPushHandeledFlag = false;
      }
   }


   // определяет событие нажатия кнопки (или кнопок если их несколько)
   template<class ... Buttons_> bool push()
   {
      bool tmp;
      if (pushHandeledFlag) {
         tmp = false;
      } else {
         // (Buttons_::IsSet() and ... ); - аналог в 17 стандарте
         tmp = List<Buttons_...>::IsAllPush() and timer.timePassed > MinPressed;
         if (tmp)
            pushHandeledFlag = true;
      }
      return tmp;
   }


   // определяет событие долгого нажатия кнопки (или кнопок если их несколько)
   template<class ... Buttons_> bool longPush()
   {
      bool tmp;
      if (longPushHandeledFlag) {
         tmp = false;
      } else {
         tmp = List<Buttons_...>::IsAllPush() and timer.timePassed > LongPressed;
         if (tmp)
            longPushHandeledFlag = true;
      }
      return tmp;
   }



private:
   bool pushHandeledFlag;
   bool longPushHandeledFlag;
   Timer& timer;


   // всю эту рекурсивную бяку можно/нужно заменить на fold expression 17 стандарта
   template<class T, class ... Ts> struct List { 
      static bool IsAnyPush() { return T::IsSet() or List<Ts...>::IsAnyPush(); }
      static bool IsAllPush() { return T::IsSet() and List<Ts...>::IsAllPush(); }
   };
   template<class T> struct List<T> {
      static bool IsAnyPush() { return T::IsSet(); }
      static bool IsAllPush() { return T::IsSet(); }
   };

};



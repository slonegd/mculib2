/******************************************************************************
 * 
 * Класс работы с кнопками
 * 
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "timers.h"
#include "meta.h"



template<class ... Types>
class Buttons
{
public:
   static const uint8_t MinPressed = 10_ms;
   static const uint8_t LongPressed = 1_s;


   Buttons (Timer& timer)
      : pressedButtons(), timer(timer)
   {
      timer.setTime (100_s);
   }


   // запускает/останавливает таймер отслеживания времени нажатия
   // должна периодически вызываться
   void operator () ()
   {
      bool tmp = true;
      for (auto but : pressedButtons)
         tmp &= but;
      if (tmp)
         timer.start();
      else
         timer.stop();
   }


   template<class Button> bool push()
   {
      return updateBut<Button>()
             && timer.timePassed > MinPressed 
             && timer.timePassed < LongPressed;
   }


   template<class Button> bool longPush()
   {
      return updateBut<Button>()
             && timer.timePassed > LongPressed;
   }



private:
   static const uint8_t qty = QtyTypes<Types...>::value;

   bool pressedButtons[qty];
   Timer& timer;


   template<class Button> bool updateBut()
   {
      const uint8_t n = Position<Button, Types...>::value;
      static_assert (n != 0, "такого типа нет в списке кнопок");
      bool tmp = Button::IsSet();
      pressedButtons[n-1] = tmp;
      return tmp;
   }

};
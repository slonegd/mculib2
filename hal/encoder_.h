#pragma once

#include "tim_periph.h"
#include "pin.h"
#include "pins_variadic.h"
#include "interrupt.h"
#include <type_traits>

template<class TIM_, class PinA, class PinB, bool inverted = false>
class Encoder : Interrupt<TIM_>
{
public:
   Encoder ();
   Encoder& withInterrupt();
   void subscribe(Interrupting* p) {Interrupt<TIM_>::subscribe(p);}
   void enableInterrupt ();
   void disableInterrupt();
   void setCompare(int16_t);
   int16_t operator=   (int16_t);
   int16_t operator!=  (int16_t);
   int16_t operator+   (int16_t);
   int16_t operator-   (int16_t);
   bool    operator>   (int16_t);
   bool    operator<   (int16_t);
   bool    operator>=  (int16_t);
   bool    operator<=  (int16_t);
           operator    int16_t();
};

template<class TIM_, class PinA, class PinB, bool inverted>
Encoder<TIM_, PinA, PinB, inverted>::Encoder()
{
   static constexpr auto pinAchannel = TIM_::template channel<PinA>();
   static constexpr auto pinBchannel = TIM_::template channel<PinB>();
   static_assert (
      pinAchannel == 1 or pinAchannel == 2,
      "PinA вывод контроллера не поддерживает функцию энкодера с этим таймером" 
   );
   static_assert (
      pinBchannel == 1 or pinBchannel == 2,
      "PinB вывод контроллера не поддерживает функцию энкодера с этим таймером" 
   );
   static_assert (
      pinAchannel != pinBchannel,
      "PinA и PinB не должны принадлежать одному каналу таймера" 
   );

   static constexpr auto altFuncPinA = TIM_::template AltFunc<PinA>();
   static constexpr auto altFuncPinB = TIM_::template AltFunc<PinB>();
   PinA::template configureAltFunction<altFuncPinA>();
   PinB::template configureAltFunction<altFuncPinB>();

   TIM_::clockEnable();
   TIM_::template compareEnable<TIM_::Channel::_3>();
//    TIM_::template compareEnable<pinBchannel>();
   TIM_::template set<TIM_::SlaveMode::Encoder3>();
   TIM_::template set<TIM_::CompareMode::ActiveOnMatch, TIM_::Channel::_3>();
//    TIM_::template set<TIM_::CompareMode::ActiveOnMatch, pinBchannel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::Input, pinAchannel>();
   TIM_::template selectCompareMode<TIM_::SelectionCompareMode::Input, pinBchannel>();

   if (inverted) {
      TIM_::template set<TIM_::Polarity::falling, pinAchannel>();
   }
   TIM_::clearCounter();
//    TIM_::mainOutputEnable();
   TIM_::counterEnable();
}

template<class TIM_, class PinA, class PinB, bool inverted>
Encoder<TIM_, PinA, PinB, inverted>& Encoder<TIM_, PinA, PinB, inverted>::withInterrupt ()
{
   NVIC_EnableIRQ (TIM_::IRQn());
   return *this;
}

template<class TIM_, class PinA, class PinB, bool inverted>
void Encoder<TIM_,PinA,PinB, inverted>::enableInterrupt()
{
   TIM_::compareInterruptEnable();
}

template<class TIM_, class PinA, class PinB, bool inverted>
void Encoder<TIM_, PinA, PinB, inverted>::disableInterrupt()
{
   TIM_::compareInterruptDisable();
}

template<class TIM_, class PinA, class PinB, bool inverted>
void Encoder<TIM_, PinA, PinB, inverted>::setCompare(int16_t v)
{
   TIM_::setCompare(v);
}

template<class TIM_, class PinA, class PinB, bool inverted>
int16_t Encoder<TIM_, PinA, PinB, inverted>::operator= (int16_t v)
{
   TIM_::setCounter(v);
   return v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
int16_t Encoder<TIM_, PinA, PinB, inverted>::operator!= (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) != v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
int16_t Encoder<TIM_, PinA, PinB, inverted>::operator+ (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) + v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
int16_t Encoder<TIM_, PinA, PinB, inverted>::operator- (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) - v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
bool Encoder<TIM_, PinA, PinB, inverted>::operator> (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) > v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
bool Encoder<TIM_, PinA, PinB, inverted>::operator< (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) < v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
bool Encoder<TIM_, PinA, PinB, inverted>::operator>= (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) >= v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
bool Encoder<TIM_, PinA, PinB, inverted>::operator<= (int16_t v)
{
   return static_cast<int16_t>(TIM_::getCounter()) <= v;
}

template<class TIM_, class PinA, class PinB, bool inverted>
Encoder<TIM_, PinA, PinB, inverted>::operator int16_t()
{
   return static_cast<int16_t>(TIM_::getCounter());
}

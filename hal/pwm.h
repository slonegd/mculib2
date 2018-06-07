#pragma once

#include "TIM.h"

#include "pin.h"
#include "literals.h"


template <class TIM_, class Pin_>
class PWM
{
public:
   /// отдельные классы параметров, так как изменения влияют на другие параметры
   /// частота в Гц
   class Freq {
   public:
      Freq  (PWM<TIM_,Pin_>& up);
            operator uint16_t();
      Freq& operator=  (uint16_t val);
      Freq& operator+= (int val);
      /// задаёт значениe, ничего не пересчитывая
      void  update     (uint16_t val);
   private:
      uint16_t        freq;
      PWM<TIM_,Pin_>& up;
   } freq;

   /// коэффициент заполения в от 0 до 1000
   class FillRatio {
   public:
      FillRatio  (PWM<TIM_,Pin_>& up);
                 operator uint16_t();
      FillRatio& operator=  (uint16_t val);
      FillRatio& operator+= (int val);
      void       update();
   private:
      uint16_t        fillRatio;
      PWM<TIM_,Pin_>& up;
   } fillRatio;

   /// значение при котором счётчик сбрасывается 
   class CountTo {
   public:
      CountTo  (PWM<TIM_,Pin_>& up);
               operator uint16_t();
      CountTo& operator=  (uint16_t val);
      CountTo& operator+= (int val);
      /// задаёт значениe, ничего не пересчитывая
      void     update     (uint16_t val);
   private:
      uint16_t countTo;
      PWM<TIM_,Pin_>& up;
   } countTo;


   PWM();

   /// следующие 4 метода управляют выходом ШИМ
   void outEnable()   { TIM_::template compareEnable  <channel>(); }
   void outDisable()  { TIM_::template compareDisable <channel>(); }
   void outToggle()   { TIM_::template compareToggle  <channel>(); }
   bool isOutEnable() { return TIM_::template isCompareEnable<channel>(); }

   static constexpr uint8_t  channel = Channel<TIM_,Pin_>();
   static constexpr uint32_t minFreq = F_CPU / 0xFFFF;
   
};
















template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::PWM() : freq(*this), fillRatio(*this), countTo(*this)
{
   static_assert (
      channel != 0,
      "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
   );

   Pin_::Port::clockEnable();
   Pin_::configure ( Pin_::Mode::Alternate,
                     Pin_::OutType::PushPull,
                     Pin_::OutSpeed::High,
                     Pin_::PullResistor::No);
   Pin_::template SetAltFunc <AltFunc<TIM_,Pin_>()> ();

   TIM_::clockEnable();
   TIM_::template setCompareMode <TIM_::CompareMode::PWMmode, channel> ();
   TIM_::template preloadEnable <channel> ();
   TIM_::autoReloadEnable();
   TIM_::mainOutputEnable();
   TIM_::counterEnable();

   freq = minFreq;
   fillRatio = 0;
}


///////////////////////////////////////////////////////////////////////////////
// ЧАСТОТА
///////////////////////////////////////////////////////////////////////////////
template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::Freq::Freq (PWM<TIM_,Pin_>& up) : up(up)
{

}


template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::Freq::operator uint16_t()
{
   return freq;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::Freq& PWM<TIM_,Pin_>::Freq::operator= (uint16_t val)
{
   if ( (val != freq) and (val > minFreq) ) {
      freq = val;
      up.countTo.update (F_CPU / freq - 1);
   }
   return *this;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::Freq& PWM<TIM_,Pin_>::Freq::operator+= (int val)
{
   return operator= (freq + val);
}


template <class TIM_, class Pin_>
void PWM<TIM_,Pin_>::Freq::update (uint16_t val)
{
   freq = val;
}


///////////////////////////////////////////////////////////////////////////////
// Коэффициент заполнения
///////////////////////////////////////////////////////////////////////////////
template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::FillRatio::FillRatio (PWM<TIM_,Pin_>& up) : up(up)
{

}


template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::FillRatio::operator uint16_t()
{
   return fillRatio;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::FillRatio& PWM<TIM_,Pin_>::FillRatio::operator= (uint16_t val)
{
   if ( (val != fillRatio) and (val >= 0) and (val <= 1000) ) {
      fillRatio = val;
      update();
   }
   return *this;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::FillRatio& PWM<TIM_,Pin_>::FillRatio::operator+= (int val)
{
   return this->operator= (fillRatio + val);
}


template <class TIM_, class Pin_>
void PWM<TIM_,Pin_>::FillRatio::update()
{
   TIM_::template setCompareValue <channel> (up.countTo * fillRatio / 1000);
}


///////////////////////////////////////////////////////////////////////////////
// СБРОС СЧЁТЧИКА
///////////////////////////////////////////////////////////////////////////////
template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::CountTo::CountTo (PWM<TIM_,Pin_>& up) : countTo{0}, up(up)
{

}


template <class TIM_, class Pin_>
PWM<TIM_,Pin_>::CountTo::operator uint16_t()
{
   return countTo;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::CountTo& PWM<TIM_,Pin_>::CountTo::operator= (uint16_t val)
{
   if ( (val != countTo) and (countTo >= 0) and (countTo <= 0xFFFF) ) {
      countTo = val;
      update (countTo);
      up.freq.update (F_CPU / (countTo + 1));
   }
   return *this;
}


template <class TIM_, class Pin_>
typename PWM<TIM_,Pin_>::CountTo& PWM<TIM_,Pin_>::CountTo::operator+= (int val)
{
   return operator= (countTo + val);
}


template <class TIM_, class Pin_>
void PWM<TIM_,Pin_>::CountTo::update (uint16_t val)
{
   countTo = val;
   TIM_::setAutoReloadValue (val);
   up.fillRatio.update();
}
#pragma once

#include "tim_periph.h"

#include "pin.h"
#include "literals.h"


template <class TIM_, class Pin_, uint16_t maxFill = 500_from1000>
class PWM
{
public:
   /// отдельные классы параметров, так как изменения влияют на другие параметры
   /// частота в Гц
   class Freq {
   public:
      Freq  (PWM<TIM_,Pin_,maxFill>& up);
            operator uint16_t();
      Freq& operator=  (uint16_t val);
      Freq& operator+= (int val);
      /// задаёт значениe, ничего не пересчитывая
      void  update     (uint16_t val);
   private:
      uint16_t        freq;
      PWM<TIM_,Pin_,maxFill>& up;
   } freq;

   /// коэффициент заполения в от 0 до 1000
   class FillRatio {
   public:
      FillRatio  (PWM<TIM_,Pin_,maxFill>& up);
                 operator uint16_t();
      FillRatio& operator=  (uint16_t val);
      FillRatio& operator+= (int val);
      void       update();
   private:
      uint16_t        fillRatio;
      PWM<TIM_,Pin_,maxFill>& up;
   } fillRatio;

   /// значение при котором счётчик сбрасывается 
   class CountTo {
   public:
      CountTo  (PWM<TIM_,Pin_,maxFill>& up);
               operator uint16_t();
      CountTo& operator=  (uint16_t val);
      CountTo& operator+= (int val);
      /// задаёт значениe, ничего не пересчитывая
      void     update     (uint16_t val);
   private:
      uint16_t countTo;
      PWM<TIM_,Pin_,maxFill>& up;
   } countTo;


   PWM();

   /// следующие 4 метода управляют выходом ШИМ
   void outEnable()   { TIM_::template compareEnable  <channel>(); }
   void outDisable()  { TIM_::template compareDisable <channel>(); }
   void outToggle()   { TIM_::template compareToggle  <channel>(); }
   bool isOutEnable() { return TIM_::template isCompareEnable<channel>(); }

   static constexpr typename TIM_::Channel channel = TIM_::template channel<Pin_>();
   static constexpr uint32_t minFreq = F_CPU / 0xFFFF;
   
};
















template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::PWM() : freq(*this), fillRatio(*this), countTo(*this)
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
   Pin_::template SetAltFunc <TIM_::template AltFunc<Pin_>()> ();

   TIM_::clockEnable();
   TIM_::template set <TIM_::CompareMode::PWMmode, channel> ();
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
template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::Freq::Freq (PWM<TIM_,Pin_,maxFill>& up) : up(up)
{

}


template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::Freq::operator uint16_t()
{
   return freq;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::Freq& PWM<TIM_,Pin_,maxFill>::Freq::operator= (uint16_t val)
{
   if ( (val != freq) and (val >= minFreq) ) {
      freq = val;
      up.countTo.update (F_CPU / freq - 1);
   }
   return *this;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::Freq& PWM<TIM_,Pin_,maxFill>::Freq::operator+= (int val)
{
   return operator= (freq + val);
}


template <class TIM_, class Pin_, uint16_t maxFill>
void PWM<TIM_,Pin_,maxFill>::Freq::update (uint16_t val)
{
   freq = val;
}


///////////////////////////////////////////////////////////////////////////////
// Коэффициент заполнения
///////////////////////////////////////////////////////////////////////////////
template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::FillRatio::FillRatio (PWM<TIM_,Pin_,maxFill>& up) : up(up)
{

}


template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::FillRatio::operator uint16_t()
{
   return fillRatio;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::FillRatio& PWM<TIM_,Pin_,maxFill>::FillRatio::operator= (uint16_t val)
{
   if ( (val != fillRatio) and (val > 0) and (val <= maxFill) ) {
      fillRatio = val;
      update();
   }
   return *this;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::FillRatio& PWM<TIM_,Pin_,maxFill>::FillRatio::operator+= (int val)
{
   return operator= (fillRatio + val);
}


template <class TIM_, class Pin_, uint16_t maxFill>
void PWM<TIM_,Pin_,maxFill>::FillRatio::update()
{
   TIM_::template setCompareValue <channel> (up.countTo * fillRatio / 1000);
}


///////////////////////////////////////////////////////////////////////////////
// СБРОС СЧЁТЧИКА
///////////////////////////////////////////////////////////////////////////////
template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::CountTo::CountTo (PWM<TIM_,Pin_,maxFill>& up) : countTo{0}, up(up)
{

}


template <class TIM_, class Pin_, uint16_t maxFill>
PWM<TIM_,Pin_,maxFill>::CountTo::operator uint16_t()
{
   return countTo;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::CountTo& PWM<TIM_,Pin_,maxFill>::CountTo::operator= (uint16_t val)
{
   if ( (val != countTo) and (countTo >= 0) and (countTo <= 0xFFFF) ) {
      countTo = val;
      update (countTo);
      up.freq.update (F_CPU / (countTo + 1));
   }
   return *this;
}


template <class TIM_, class Pin_, uint16_t maxFill>
typename PWM<TIM_,Pin_,maxFill>::CountTo& PWM<TIM_,Pin_,maxFill>::CountTo::operator+= (int val)
{
   return operator= (countTo + val);
}


template <class TIM_, class Pin_, uint16_t maxFill>
void PWM<TIM_,Pin_,maxFill>::CountTo::update (uint16_t val)
{
   countTo = val;
   TIM_::setAutoReloadValue (val);
   up.fillRatio.update();
}

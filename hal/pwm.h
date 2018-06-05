/**     Работа с ШИМ
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер-пин конкретезируются путём инициализации константы channel для пары
 *      При неверном задании пары таймер-пин не компилируеться
 */

#pragma once

#include "TIM.h"

#include "pin.h"
#include "literals.h"


template <class TIM_, class Pin_>
class PWM
{
public:
   PWM () : d(0), freq(*this)
   {
      static_assert (
         channel != 0,
         "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
      );
      init();
   }
   inline void outEnable ()  { TIM_::template compareEnable  <channel>(); }
   inline void outDisable () { TIM_::template compareDisable <channel>(); }
   inline void outToggle ()  { TIM_::template compareToggle  <channel>(); }
   inline bool isOutEnable ()    { return TIM_::template isCompareEnable<channel>(); }
   inline void setFreq (uint32_t val)
   {
      extern const uint32_t fCPU;
      if ( (val != this->freq) and (val != 0) ) {
         this->freq = val;
         countTo = fCPU / val - 1;
         TIM_::setAutoReloadValue (countTo);
         setD (d);
      }
   }
   
   // d - в процентах
   inline void setD (uint8_t d)
   {
      this->d = d;
      TIM_::template setCompareValue <channel> (countTo * d / 100);
   }




   // частота в Гц
   class Freq
   {
   public:
      Freq(PWM<TIM_,Pin_>& up) : up(up) {}
      operator uint16_t() { return freq; }
      uint16_t& operator= (uint16_t val) { return freq = val; }
      uint16_t& operator+= (int val)
      {
         up.countTo -= val;
         TIM_::setAutoReloadValue (up.countTo);
         up.setD (up.d);
         extern const uint32_t fCPU;
         freq = fCPU / (up.countTo + 1);
         return freq;
      }
   private:
      uint16_t freq;
      PWM<TIM_,Pin_>& up;
   } freq;


   // коэффициент заполнения в процентах
   uint16_t d;
   // таймер считает до, зависит от частоты
   uint32_t countTo;

   // номер канала таймера
   static const uint8_t channel = Channel<TIM_,Pin_>();//PWM_HAL::Channel<TIM_,Pin>().val;
   // static const AFR_t::AF altFun = AltFunc<Timer,Pin>();
   void init (void)
   {
      Pin_::Port::ClockEnable();
      TIM_::clockEnable();


      
      Pin_::Configure ( Pin_::Mode::Alternate,
                        Pin_::OutType::PushPull,
                        Pin_::OutSpeed::High,
                        Pin_::PullResistor::No);
      Pin_::template SetAltFunc <AltFunc<TIM_,Pin_>()> ();

      TIM_::template setCompareMode <TIM_::CompareMode::PWMmode, channel> ();
      TIM_::template preloadEnable <channel> ();
      TIM_::autoReloadEnable();
      TIM_::mainOutputEnable();
      TIM_::counterEnable();
   }

};







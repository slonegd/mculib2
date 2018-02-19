/**     Работа с ШИМ
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер-пин конкретезируются путём инициализации константы channel для пары
 *      При неверном задании пары таймер-пин не компилируеться
 */

#pragma once

#include "TIM_ral.h"
#include "pin_hal.h"
#include "literals.h"


template <class Timer, class Pin>
class PWM
{
public:
    PWM () : d(0)
    {
        static_assert (
            channel != 0,
            "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
        );
        init();
    }
    inline void outEnable ()  { Timer::template CompareEnable  <channel>(); }
    inline void outDisable () { Timer::template CompareDisable <channel>(); }
    inline void outToggle ()  { Timer::template CompareToggle  <channel>(); }
    inline bool isOutEnable ()    { return Timer::template IsCompareEnable<channel>(); }
    inline void setFreq (uint32_t f)
    {
        extern const uint32_t fCPU;
        if ( (f != this->freq) && (f != 0) ) {
            this->freq = f;
            countTo = fCPU / f - 1;
            Timer::SetAutoReloadValue (countTo);
            setD (d);
        }
    }
    
    // d - в процентах
    inline void setD (uint8_t d)
    {
        this->d = d;
        Timer::template SetCompareValue <channel> (countTo * d / 100);
    }



private:
    // частота в Гц
    uint16_t freq;
    // коэффициент заполнения в процентах
    uint16_t d;
    // таймер считает до, зависит от частоты
    uint32_t countTo;

    // номер канала таймера
    static const uint8_t channel = PWMchannel<Timer,Pin>();//PWM_HAL::Channel<Timer,Pin>().val;

    void init (void)
    {
        Pin::Port::ClockEnable();
        Timer::ClockEnable();

        Pin::Configure ( Pin::Mode::Alternate,
                         Pin::OutType::PushPull,
                         Pin::OutSpeed::High,
                         Pin::PullResistor::No);
        Pin::template SetAltFunc <Timer::AltFunc> ();
         
        Timer::template SetCompareMode <Timer::CompareMode::PWMmode, channel> ();
        Timer::template PreloadEnable <channel> ();
        Timer::AutoReloadEnable();
        Timer::MainOutputEnable();
        Timer::CounterEnable();
    }

};







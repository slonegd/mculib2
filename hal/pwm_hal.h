/**     Работа с ШИМ
 *      При объявление требует параметры шаблонов
 *          статический класс аппаратного таймера
 *          статический класс пина
 *      Конструктор инициализирует пин и таймер
 *      Пары таймер-пин конкретезируются путём инициализации константы channel для пары
 *      При неверном задании пары таймер-пин не компилируеться
 *      В этом файле конкретизируються только таймеры
 *          TIM2_t, TIM3_t, TIM4_t
 *      Если нужны другие, то необходимо дописать инициализацию channel
 */

#pragma once

#include <stdint.h>
#include "TIM_ral.h"
#include "pin_hal.h"
#include "constDef.h"
#include "literals.h"

namespace PWM_HAL {
    using ChannelDef = ConstDef<uint8_t>;
    template<class Timer, class Pin> constexpr PWM_HAL::ChannelDef Channel() { return {0, false}; }

    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA0>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA1>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA2>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA3>()  { return {4, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA5>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PA15>() { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PB3>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PB10>() { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM2_t,PB11>() { return {4, true}; }

    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PA6>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PA7>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PB0>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PB1>()  { return {4, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PB4>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PB5>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PC6>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PC7>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PC8>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM3_t,PC9>()  { return {4, true}; }

    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PB6>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PB7>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PB8>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PB9>()  { return {4, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PD12>() { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PD13>() { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PD14>() { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM4_t,PD15>() { return {4, true}; }

    template<> constexpr PWM_HAL::ChannelDef Channel<TIM5_t,PA0>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM5_t,PA1>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM5_t,PA2>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM5_t,PA3>()  { return {4, true}; }


    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PA5>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PA7>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PB0>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PB1>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PB14>() { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PB15>() { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PC6>()  { return {1, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PC7>()  { return {2, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PC8>()  { return {3, true}; }
    template<> constexpr PWM_HAL::ChannelDef Channel<TIM8_t,PC9>()  { return {4, true}; }

 

}



template <class Timer, class Pin>
class PWM
{
public:
    PWM () : d(0)
    {
        static_assert (
            PWM_HAL::Channel<Timer,Pin>().defined,
            "Вывод контроллера не поддерживает функцию ШИМ с этим таймером"
        );
        init();
    }
    inline void outEnable (void)  { Timer::template CompareEnable <channel>(); }
    inline void outDisable (void) { Timer::template CompareDisable <channel>(); }
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

    // номер канала таймера
    static const uint8_t channel = PWM_HAL::Channel<Timer,Pin>().val;

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
        Timer::AutoReloadEnable();
        Timer::CounterEnable();
    }

private:
    // частота в Гц
    uint16_t freq;
    // коэффициент заполнения в процентах
    uint16_t d;
    // таймер считает до, зависит от частоты
    uint32_t countTo;



};


////////////////////////////////////////////////////
// конкретизация 
////////////////////////////////////////////////////







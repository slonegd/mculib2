/*****************************************************************************
 * дл€ того, чтобы кирилица вместилась в char этот файл должен быть
 * в кодировке cp1251
 * 
 *      переделал чужую библиотеку под свою систему
 *      вариант через дма не закончен (HD44780_hal_.h)
 * 
 *////////////////////////////////////////////////////////////////////////////

#pragma once

#include "pin.h"
#include "pinlist.h"
#include "SysTick_.h"


namespace HD44780_HAL {

    const char convert_HD44780[] = {
        0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
        0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
        0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,
        0xAC,0xE2,0xAD,0xAE,0xAD,0xAF,0xB0,0xB1,
        0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,
        0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
        0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,
        0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
    };

}

// D4-D7 тут не об€зательно одного порта
template <class RS,
          class RW,
          class E, 
          class D4,
          class D5,
          class D6,
          class D7
> class HD44780
{
public:

    HD44780()
    {
        init();
    }

    // устанавливает string в строке LineN LCD
    // если размер string меньше размера строки LCD
    // заполн€ет до конца пробелами
    template <uint8_t n>
    void setLine (const char ( &string )[n], uint8_t LineN)
    {
        LineN == 0 ? sendByte (0b1000000 + 0x00) : 
                     sendByte (0b1000000 + 0x40);
        delay<40>();
        RS::Set();
        sendLine (string, n - 1);
        RS::Clear();
    }


private:

    using DataPins = PinList<D4,D5,D6,D7>;

    void init()
    {
        // OpenDrain - дл€ слвемстимости с 5 ¬
        RS::Port::ClockEnable();
        RS::Configure ( RS::Mode::Output,
                        RS::OutType::OpenDrain,
                        RS::OutSpeed::Low,
                        RS::PullResistor::No
        );
        RW::Port::ClockEnable();
        RW::Configure ( RW::Mode::Output,
                        RW::OutType::OpenDrain,
                        RW::OutSpeed::Low,
                        RW::PullResistor::No
        );
        E::Configure ( E::Mode::Output,
                       E::OutType::OpenDrain, 
                       E::OutSpeed::Low,
                       E::PullResistor::No
        );
        D4::Port::ClockEnable();
        D4::Configure ( D4::Mode::Output,
                        D4::OutType::OpenDrain, 
                        D4::OutSpeed::Low,
                        D4::PullResistor::No
        );
        D5::Configure ( D5::Mode::Output,
                        D5::OutType::OpenDrain,
                        D5::OutSpeed::Low,
                        D5::PullResistor::No
        );
        D6::Configure ( D6::Mode::Output,
                        D6::OutType::OpenDrain,
                        D6::OutSpeed::Low,
                        D6::PullResistor::No
        );
        D7::Configure ( D7::Mode::Output,
                        D7::OutType::OpenDrain,
                        D7::OutSpeed::Low,
                        D7::PullResistor::No
        );

        E::Set();
        RS::Clear();
        RW::Clear();
        delay<20000>();  
        sendNibble (0b11);
        delay<40>();     
        sendNibble (0b11);
        delay<40>();
        sendNibble (0b11);
        delay<40>();
        sendNibble (0b10);
        delay<40>();
        // установка интерфейса 4 бита и страницы 0
        sendByte (0x28);
        delay<40>();
        // установка отсутсви€ видимого курсора
        sendByte (0x08);
        delay<40>();
        // очистка экрана и курсор в начало
        sendByte (0x08);
        delay<1500>();
        // установка сдвига курсора вправо и запрет сдвига экрана
        sendByte (0x06);
        delay<40>();
    } // init()

    template <uint32_t us> void delay ()
    {
        // с 7 тактами получилось 40 мкс 168ћ latency = 7
        // а вот 1 мкс не получилась совсем
        constexpr uint32_t end = us * FCPU() / 7 / 1000000 + 1; 
	    for (volatile uint32_t i = 0; i < end; i++ ) { }
    }

    void delayTick (uint32_t tickQty)
    {
        volatile uint32_t tmp = SysTick_::get() - tickQty;
        while (tmp < SysTick_::get()) { }
    }

    void sendNibble (char data)
    {
        constexpr uint32_t tickQty1us = FCPU() / 1000000;
        DataPins::Write (data);
        delayTick (tickQty1us);
        E::Clear();
        delayTick (tickQty1us);
        E::Set();
    }

    void sendByte (char val)
    {
        sendNibble (val >> 4);
        sendNibble (val);
    }

    // отправл€ет строку до size, после size пробелы до конца экрана
    void sendLine (const char* string, uint8_t size)
    __attribute__((noinline))
    {
        for (uint8_t i = 0; i < size; ++i) {
            sendByte ( convert (string[i]) );
        }
        for (uint8_t i = size; i < 16; ++i) {
            sendByte (0x20); // пробел
        }
    }

    uint8_t convert (uint8_t ch)
    {
        if (ch > 'ј') {
            ch -= 'A';
            ch = *(HD44780_HAL::convert_HD44780 + ch);
        }
        return ch;
    }
    
};
/**
 * Вся эта муть - переосмысление библиотеки
 * https://github.com/KonstantinChizhov/Mcucpp
 * http://easyelectronics.ru/rabota-s-portami-vvoda-vyvoda-mikrokontrollerov-na-si.html
 */

#pragma once

#include "loki/Typelist.h"
#include <stdint.h>
#include "pinlistfunc.h"

using NullType = Loki::NullType;

////////////////////////////////////////////////////////////////////////////////
// класс с методами работы со списком пинов, наследуеться при объявлении
////////////////////////////////////////////////////////////////////////////////
template <class PinList>
class PinListfunc
{
private:
    using PinsToPorts = typename GetPorts<PinList>::Result;
    using Ports = typename Loki::TL::NoDuplicates<PinsToPorts>::Result;
    static const uint16_t PortMask = GetPortMask<PinList>::value;
public:
	static void Write(uint16_t value)
	{
		PortWriteIterator<Ports, PinList>::Write(value);
	}

    // работает только для пинлиста одного порта
    // возвращает значение, которое необходимо отправить в регистр GPIO->BSRR
    // чтобы утсановить значение параметра шаблона как выход пинлиста
    template <uint16_t val> static uint32_t BSRvalue() {
        return ((PortMask & val) | ((uint32_t)(PortMask & ~val) << 16));
    }
};

////////////////////////////////////////////////////////////////////////////////
// класс для объявления списка пинов
//  Пример
//      using Pins = PinList<PA1, PC2, PD0, PA3>;
////////////////////////////////////////////////////////////////////////////////
template <
    typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
    typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
    typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
    typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
    typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
    typename T16 = NullType, typename T17 = NullType, typename T18 = NullType,
    typename T19 = NullType, typename T20 = NullType, typename T21 = NullType,
    typename T22 = NullType, typename T23 = NullType, typename T24 = NullType,
    typename T25 = NullType, typename T26 = NullType, typename T27 = NullType,
    typename T28 = NullType, typename T29 = NullType, typename T30 = NullType,
    typename T31 = NullType, typename T32 = NullType, typename T33 = NullType
>
struct PinList : public PinListfunc <
        typename MakePinList <
        	0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
            T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
            T26, T27, T28, T29, T30, T31, T32, T33
        >::Result
    >
{	};
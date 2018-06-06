/**
 * Вся эта муть - переосмысление библиотеки
 * https://github.com/KonstantinChizhov/Mcucpp
 * http://easyelectronics.ru/rabota-s-portami-vvoda-vyvoda-mikrokontrollerov-na-si.html
 */

#pragma once

#include "loki/Typelist.h"
#include <stdint.h>
#include "pin.h"

//using namespace Loki;
using NullType = Loki::NullType;

////////////////////////////////////////////////////////////////////////////////
// структура чтобы сохранить позицию в pinlist \/
////////////////////////////////////////////////////////////////////////////////
template<class TPIN, uint8_t p>
struct PinPositionHolder
{
   typedef TPIN Pin;
   enum { Position = p };
};

////////////////////////////////////////////////////////////////////////////////
// создаёт список типов с сохранённой позицией типа в списке \/
////////////////////////////////////////////////////////////////////////////////
template
<
   int Position,
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
struct MakePinList
{
private:
   using TailResult = typename MakePinList < Position + 1,
      T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33
   >::Result;
   enum { PositionInList = Position };
public:
   using Result = Loki::Typelist< PinPositionHolder<T1, PositionInList>, TailResult>;
};

template<int Position>
struct MakePinList<Position>
{
   using Result = NullType;
};

////////////////////////////////////////////////////////////////////////////////
// преобразует список пинов в список портов этих пинов \/
////////////////////////////////////////////////////////////////////////////////
template <class TList> struct GetPorts;
// пустая специализация
template <> struct GetPorts<NullType>
{
   using Result = NullType;
};

template <class Head, class Tail>
struct GetPorts< Loki::Typelist<Head, Tail> >
{
private:
   using Port = typename Head::Pin::Port;
   using L1 = typename GetPorts<Tail>::Result;
public:
   using Result = Loki::Typelist<Port, L1>;
};

////////////////////////////////////////////////////////////////////////////////
// создает список пинов конкретного порта \/
////////////////////////////////////////////////////////////////////////////////
template <class TList, class Port> struct GetPinsWithPort;

// для пустого списка результат – пустой тип (т.е. тоже пустой список)
template <class Port>
struct GetPinsWithPort<NullType, Port>
{
   typedef NullType Result;
};
// если TList это список типов, голова в котором 
// это PinPositionHolder<Pin_t<Port, pin>, PositionInList>,
// т.е. линия в заданном порту Port (pin и PositionInList неважно какие)
// то вставляем её в голову нового списка. Рекурсивно обрабатываем хвост.
template <class Port, class Tail, uint8_t pin, uint8_t PositionInList>
struct GetPinsWithPort<Loki::Typelist<PinPositionHolder<Pin_t<Port, pin>, PositionInList>, Tail>, Port>
{
   typedef Loki::Typelist<PinPositionHolder<Pin_t<Port, pin>, PositionInList>, 
   typename GetPinsWithPort<Tail, Port>::Result> Result;
};
// если голова списка - любой другой тип, то вставляем на её место рекурсивно обработанный хвост.
template <class Head, class Tail, class Port>
struct GetPinsWithPort<Loki::Typelist<Head, Tail>, Port>
{
   typedef typename GetPinsWithPort<Tail, Port>::Result Result;
};

////////////////////////////////////////////////////////////////////////////////
// определяет битовую маску для порта 
// список пинов должен быть только этого порта (см GetPinsWithPort) \/
////////////////////////////////////////////////////////////////////////////////
template <class TList> struct GetPortMask;
// Для пустого списка возвращаем 0.
template <> struct GetPortMask<NullType>
{
   enum { value = 0 };
};
 
template <class Head, class Tail>
struct GetPortMask< Loki::Typelist<Head, Tail> >
{	
   //value =	битовая маска для головы  | битовая маска оставшейся части списка
   enum {
      value = (1 << Head::Pin::Number) | GetPortMask<Tail>::value
   };
};

////////////////////////////////////////////////////////////////////////////////
// проецируем биты из входного значения в соответствующие биты порта
////////////////////////////////////////////////////////////////////////////////
// Tlist – список линий принадлежащих одному порту
template <class TList> struct PinWriteIterator;
// специализация для пустого списка – возвращаем 0
template <> struct PinWriteIterator<NullType>
{
   static uint8_t UppendValue(const uint16_t &value)
   {
      return 0; 
   }
};
 
// специализация для непустого списка
template <class Head, class Tail>
struct PinWriteIterator< Loki::Typelist<Head, Tail> >
{
   static inline uint16_t UppendValue(const uint16_t &value)
   {
      // проверяем, если линии в порту расположены последовательно
      // если часть линий в середине списка будет расположена последовательно, то 
      // это условие не выполнется, так, что есть ещё простор для оптимизации.
/* Эту часть пока не понял, поэтому закомментировал
      if(IsSerial<Typelist<Head, Tail> >::value)
      {	
         // сдвигаем значение на нужное число бит и накладываем не него маску
         if((int)Head::Position > (int)Head::Pin::Number)
            return (value >> ((int)Head::Position - (int)Head::Pin::Number)) & 
               GetPortMask<Typelist<Head, Tail> >::value;
         else
            return (value << ((int)Head::Pin::Number - (int)Head::Position)) & 
               GetPortMask<Typelist<Head, Tail> >::value;
      }
  
      uint16_t result = 0;
   
      if ((int)Head::Position == (int)Head::Pin::Number) {
         result |= value & (1 << Head::Position);
      } else {
         // это условие будет вычисляться во время выполнения программы
         if (value & (1 << Head::Position)) {
            result |= (1 << Head::Pin::Number);
         }
      }
*/      
      uint16_t result = 0;
      // это условие будет вычисляться во время выполнения программы
      if (value & (1 << Head::Position)) {
         result |= (1 << Head::Pin::Number);
      }
      // рекурсивно обрабатываем оставшиеси линии в списке
      return result | PinWriteIterator<Tail>::UppendValue(value);
   }
};
 
////////////////////////////////////////////////////////////////////////////////
// определяет операции с портами
////////////////////////////////////////////////////////////////////////////////
template <class PortList, class PinList> struct PortWriteIterator;

   // пустая специализация
   template <class PinList> struct PortWriteIterator<NullType, PinList>
   {
      static void Write(uint32_t) { }
   };

   template <class Head, class Tail, class PinList>
   struct PortWriteIterator< Loki::Typelist<Head, Tail>, PinList>
   {
      using CurPort = Head;
      using Pins = typename GetPinsWithPort<PinList, CurPort>::Result;
      static const uint16_t PortMask = GetPortMask<Pins>::value;

      static void Write(uint16_t value)
      {   
         // проецируем биты из входного значения в соответствующие биты порта
         // как это реализованно увидим дальше
         uint16_t result = PinWriteIterator<Pins>::UppendValue(value);
         CurPort::clearAndSet(PortMask, result);
         // рекурсивно обрабатываем остальные порты в списке
         PortWriteIterator<Tail, PinList>::Write(value);
      }

      static uint32_t Read()
      {
         return 0;    
      }
   };





// ДАЛЕЕ УЖЕ МОЁ ТВОРЧЕСТВО


////////////////////////////////////////////////////////////////////////////////
// выдаёт значение регистра bsr для пинлиста одного порта в зависимости
// от значения
////////////////////////////////////////////////////////////////////////////////

template <class PinList, uint16_t val> struct BSRValue
{
   static const uint16_t PortMask = GetPortMask<PinList>::value;
   static const uint32_t Get = (PortMask & val | ((uint32_t)(PortMask & ~val) << 16));
};

/*
////////////////////////////////////////////////////////////////////////////////
// итератор по пин листу так и не придумал
////////////////////////////////////////////////////////////////////////////////
template <class PinList, class func> struct Iterator;
template <class func> struct Iterator<NullType, func>
{
   static func f;

}
template <> struct Iterator<NullType> { using Result }
template <class function> forechIterator<NullType, function> (function f)
{ };
template <class function> forechIterator<HEAD, TAIL, function> (function f)
{
   HEAD::f();
   forechIterator<TAIL, function> (function f);
}*/
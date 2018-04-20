/*****************************************************************************
 *
 *      Задание значения одного бита переферии
 *      Может использоваться в классах, у которых должен быть определён
 *      адрес в переменной base/
 *      Работает только со структурами Rstruct у которых 
 *      есть поле Offset относительно Base
 * 
 *      вообще пришлось это сделать, поскольку не все регистры
 *      позволяют работать с собой побайтно, а компилятор
 *      при работе с битовыми полями именно так и работает
 *      потому вылезали в хардфолт, если задавать
 *      с помощью битовых полей
 * 
 *      в дальнейшем битовые поля надо перевести на чисто информационные
 *      русла для отладки
 * 
 *////////////////////////////////////////////////////////////////////////////

#pragma once


#include "stm32f4xx.h"
#include <type_traits>

#define BITBAND_SET(Rstruct, Bit, Val) (*((volatile uint32_t*)(PERIPH_BB_BASE + (Base-PERIPH_BASE + Rstruct.Offset)*32 + Bit*4)) = Val)
//#define BITBAND_VAL(Rstruct, Bit) *((volatile uint32_t*)(PERIPH_BB_BASE + (Base-PERIPH_BASE + Rstruct.Offset)*32 + Bit*4))
//#define BITBAND_ADR(Rstruct, Bit) (volatile uint32_t*)(PERIPH_BB_BASE + (Base-PERIPH_BASE + Rstruct.Offset)*32 + Bit*4)

// почему тут работает с Rstruct.Offset, а не с Rstruct::Offset
// для меня пока загадка, ведь Offset это член перечисления

#define BIT2BAND_SET(Rstruct, Bit, Val) BITBAND_SET(Rstruct, Bit, Val & 0b1); BITBAND_SET(Rstruct, Bit+1, (Val>>1) & 0b1)
#define BIT3BAND_SET(Rstruct, Bit, Val) BIT2BAND_SET(Rstruct, Bit, Val & 0b1); BITBAND_SET(Rstruct, Bit+2, (Val>>2) & 0b1)

// из-за преобразования указателя эта функция не будет выполнятся точно во время компиляции
constexpr volatile uint32_t& bitBand (uint32_t base, uint32_t offset, uint32_t bit)
{
    return (volatile uint32_t&)*((volatile uint32_t*)(PERIPH_BB_BASE + (base-PERIPH_BASE + offset)*32 + bit*4));
}

// а вот эта будет
template<uint32_t base, uint32_t offset, uint32_t bit>
constexpr uint32_t bitBandAdr() { return 
   PERIPH_BB_BASE + (base-PERIPH_BASE + offset)*32 + bit*4;
}

// макрос для упрощения работы с предыдущей функцией
#define BB_REG(reg, bit) *(uint32_t*)bitBandAdr<Base, std::remove_reference<decltype(reg)>::type::Offset, std::remove_reference<decltype(reg)>::type::bit>()

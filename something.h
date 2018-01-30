#pragma once

// определяет размер строки в значащих символах (без \n)
template <uint8_t n> uint8_t size (const char ( &string )[n]) { return n - 1; }

// AssertyTypeEq<T1, T2>::type is defined iff T1 and T2 are the same
// type.  This can be used as a compile-time assertion to ensure that
// two types are equal.
template <typename T1, typename T2> struct AssertTypeEq;

template <typename T> struct AssertTypeEq<T, T> { };

template <typename T1, typename T2> bool StaticAssertTypeEq() {
    (void)AssertTypeEq<T1, T2>();
    return true;
}

// определить позицию бита по маске (часто надо)
constexpr uint8_t pos (uint32_t mask)
{
    uint16_t res = 0;
    while (mask != 0) {
        if ((mask & 1) == 1)
            break;
        res++;
        mask >>= 1;
    };
    return res;
}

// определить позицию по битовому полю





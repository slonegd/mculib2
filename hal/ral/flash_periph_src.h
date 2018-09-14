#pragma once

///////////////////////////////////////////////////////////////////////////////
//  0000000
//  00   00
//  00   00
//  00   00
//  00   00
//  0000000
///////////////////////////////////////////////////////////////////////////////
#if defined(STM32F0)


template<class Pointer>
void template_FLASH<Pointer>::unlock()
{
   static constexpr uint32_t Key1 = 0x45670123;
   static constexpr uint32_t Key2 = 0xCDEF89AB;
   if ( is_lock() ) {
      Pointer::get()->KEYR = Key1;
      IF_TEST_WAIT_MS(10);
      Pointer::get()->KEYR = Key2;
   }
}

template<class Pointer>
template <typename template_FLASH<Pointer>::Sector s>
void template_FLASH<Pointer>::startErase()
{
   Pointer::get()->CR.PER = true;
   IF_TEST_WAIT_MS(10);
   Pointer::get()->AR = address<s>();
   IF_TEST_WAIT_MS(10);
   Pointer::get()->CR.STRT = true;
}

template<class Pointer>
template <typename template_FLASH<Pointer>::Sector s>
constexpr uint32_t template_FLASH<Pointer>::address()
{
   return 0x08000000 + 1024 * s;
}





///////////////////////////////////////////////////////////////////////////////
//  00   00
//  00   00
//  00   00
//  0000000
//       00
//       00
///////////////////////////////////////////////////////////////////////////////
#elif defined(STM32F4)

template<class Pointer>
void template_FLASH<Pointer>::unlock()
{
   static constexpr uint32_t Key1 = 0x45670123;
   static constexpr uint32_t Key2 = 0xCDEF89AB;
   if ( is_lock() ) {
      Pointer::get()->KEYR = Key1;
      IF_TEST_WAIT_MS(10);
      Pointer::get()->KEYR = Key2;
   }
}

template<class Pointer>
template <typename template_FLASH<Pointer>::Sector v>
void template_FLASH<Pointer>::startErase()
{
      Pointer::get()->CR.SER  = true;
      IF_TEST_WAIT_MS(1);
      Pointer::get()->CR.SNB  = v;
      IF_TEST_WAIT_MS(1);
      Pointer::get()->CR.STRT = true;
}

template<class Pointer>
template <typename template_FLASH<Pointer>::Sector s>
constexpr uint32_t template_FLASH<Pointer>::address()
{
   return 
      s == Sector::_0  ? 0x08000000 :
      s == Sector::_1  ? 0x08004000 :
      s == Sector::_2  ? 0x08008000 :
      s == Sector::_3  ? 0x0800C000 :
      s == Sector::_4  ? 0x08010000 :
      s == Sector::_5  ? 0x08020000 :
      s == Sector::_6  ? 0x08040000 :
      s == Sector::_7  ? 0x08060000 :
      s == Sector::_8  ? 0x08080000 :
      s == Sector::_9  ? 0x080A0000 :
      s == Sector::_10 ? 0x080C0000 :
                         0x080E0000; // s == Sector::_11
}

#endif

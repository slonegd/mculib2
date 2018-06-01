#pragma once

#include <type_traits>

#if defined(STM32F405xx) or defined(STM32F030x6)

uint32_t RCC_t::getAPBclock(APBprescaler val)
{
   return val == RCC_ral::APBprescaler::APBnotdiv ? fCPU     :
          val == RCC_ral::APBprescaler::APBdiv2   ? fCPU / 2 :
          val == RCC_ral::APBprescaler::APBdiv4   ? fCPU / 4 :
          val == RCC_ral::APBprescaler::APBdiv8   ? fCPU / 8 :
                                                    fCPU / 16;
}


void RCC_t::setAHBprescaler (AHBprescaler val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_3BIT_TO_MASK(conf(), HPRE);
   tmp |= VAL_TO_MASK(conf(), HPRE, val);
   conf().reg = tmp;
}


void RCC_t::systemClockSwitch (SystemClockSwitch val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_2BIT_TO_MASK(conf(), SW);
   tmp |= VAL_TO_MASK(conf(), SW, val);
   conf().reg = tmp;
}

#endif


#if defined(STM32F405xx)

void RCC_t::HSEon()
{
   BIT_BAND(clockContr(), HSEON) = true;
}


void RCC_t::waitHSEready()
{
   while (!BIT_BAND(clockContr(), HSERDY)) { }
}


void RCC_t::PLLon()
{
   BIT_BAND(clockContr(), PLLON) = true;
}


void RCC_t::waitPLLready()
{
   while (!BIT_BAND(clockContr(), PLLRDY)) { }
}


void RCC_t::setPLLsource (PLLsource val)
{
   BIT_BAND(pllConf(), PLLSRC) = val;
}


uint32_t RCC_t::getAPB2clock()
{
   auto tmp = static_cast<APBprescaler>(_3BIT_READ(conf(), PPRE2));
   return getAPBclock (tmp);
}


void RCC_t::setAPB1prescaler (APBprescaler val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_3BIT_TO_MASK(conf(), PPRE1);
   tmp |= VAL_TO_MASK(conf(), PPRE1, val);
   conf().reg = tmp;
}


void RCC_t::setAPB2prescaler (APBprescaler val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_3BIT_TO_MASK(conf(), PPRE2);
   tmp |= VAL_TO_MASK(conf(), PPRE2, val);
   conf().reg = tmp;
}


uint32_t RCC_t::getAPB1clock()
{
   auto tmp = static_cast<APBprescaler>(_3BIT_READ(conf(), PPRE1));
   return getAPBclock (tmp);
}


void RCC_t::setPLLP (PLLPdiv val)
{
   uint32_t tmp = pllConf().reg;
   tmp &= ~_2BIT_TO_MASK(pllConf(), PLLP);
   tmp |= VAL_TO_MASK(pllConf(), PLLP, val);
   pllConf().reg = tmp;
}


template <uint8_t val>
void RCC_t::setPLLM()
{
   static_assert (
      val >= 2 && val <= 63,
      "значение множителя должно быть в диапазоне 2-63"
   );
   uint32_t tmp = pllConf().reg;
   tmp &= ~_6BIT_TO_MASK(pllConf(), PLLM);
   tmp |= VAL_TO_MASK(pllConf(), PLLM, val);
   pllConf().reg = tmp;
}


template <uint16_t val>
void RCC_t::setPLLN()
{
   static_assert (
      val >= 50 && val <= 432,
      "значение множителя должно быть в диапазоне 50-432"
   );
   uint32_t tmp = pllConf().reg;
   tmp &= ~_9BIT_TO_MASK(pllConf(), PLLN);
   tmp |= VAL_TO_MASK(pllConf(), PLLN, val);
   pllConf().reg = tmp;
}


template <uint8_t val>
void RCC_t::setPLLQ()
{
   static_assert (
      val >= 2 && val <= 15,
      "значение множителя должно быть в диапазоне 2-15"
   );
   uint32_t tmp = pllConf().reg;
   tmp &= ~_4BIT_TO_MASK(pllConf(), PLLQ);
   tmp |= VAL_TO_MASK(pllConf(), PLLQ, val);
   pllConf().reg = tmp;
}






#elif defined(STM32F030x6)

void RCC_t::HSEon()
{
   SET(clockContr(), HSEON);
}


void RCC_t::waitHSEready()
{
   while (IS_CLEAR(clockContr(), HSERDY)) { }
}


void RCC_t::PLLon()
{
   SET(clockContr(), PLLON);
}


void RCC_t::waitPLLready()
{
   while (IS_CLEAR(clockContr(), PLLRDY)) { }
}


void RCC_t::setPLLsource (PLLsource val)
{
   if (val)
      SET(conf(), PLLSRC);
   else
      CLEAR(conf(), PLLSRC);
}


uint32_t RCC_t::getAPB2clock()
{
   auto tmp = static_cast<APBprescaler>(_3BIT_READ(conf(), PPRE));
   return getAPBclock (tmp);
}


void RCC_t::setAPBprecsaler (APBprescaler val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_3BIT_TO_MASK(conf(), PPRE);
   tmp |= VAL_TO_MASK(conf(), PPRE, val);
   conf().reg = tmp;
}


void RCC_t::setPLLmultiplier (PLLmultiplier val)
{
   uint32_t tmp = conf().reg;
   tmp &= ~_4BIT_TO_MASK(conf(), PLLMUL);
   tmp |= VAL_TO_MASK(conf(), PLLMUL, val);
   conf().reg = tmp;
}


#endif

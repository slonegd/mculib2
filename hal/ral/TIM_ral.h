/******************************************************************************
 * 
 * Пока для general purpose биты
 * соответсвенно созданы только general purpose и advanced control типы
 * для STM32F0 не проверял соответствия, но основная структура идентична
 * 
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TIM_bits.h"
#include "RCC_ral.h"
#include "GPIO_ral.h"
#if defined(STM32F405xx)
#include "bitbanding.h"
#endif

/* STM32F4 STM32F0
typedef struct
{
   __IO uint32_t CR1;   // TIM control register 1,              Address offset: 0x00
   __IO uint32_t CR2;   // TIM control register 2,              Address offset: 0x04
   __IO uint32_t SMCR;  // TIM slave mode control register,     Address offset: 0x08
   __IO uint32_t DIER;  // TIM DMA/interrupt enable register,   Address offset: 0x0C
   __IO uint32_t SR;    // TIM status register,                 Address offset: 0x10
   __IO uint32_t EGR;   // TIM event generation register,       Address offset: 0x14
   __IO uint32_t CCMR1; // TIM capture/compare mode register 1, Address offset: 0x18
   __IO uint32_t CCMR2; // TIM capture/compare mode register 2, Address offset: 0x1C
   __IO uint32_t CCER;  // TIM capture/compare enable register, Address offset: 0x20
   __IO uint32_t CNT;   // TIM counter register,                Address offset: 0x24
   __IO uint32_t PSC;   // TIM prescaler,                       Address offset: 0x28
   __IO uint32_t ARR;   // TIM auto-reload register,            Address offset: 0x2C
   __IO uint32_t RCR;   // TIM repetition counter register,     Address offset: 0x30
   __IO uint32_t CCR1;  // TIM capture/compare register 1,      Address offset: 0x34
   __IO uint32_t CCR2;  // TIM capture/compare register 2,      Address offset: 0x38
   __IO uint32_t CCR3;  // TIM capture/compare register 3,      Address offset: 0x3C
   __IO uint32_t CCR4;  // TIM capture/compare register 4,      Address offset: 0x40
   __IO uint32_t BDTR;  // TIM break and dead-time register,    Address offset: 0x44
   __IO uint32_t DCR;   // TIM DMA control register,            Address offset: 0x48
   __IO uint32_t DMAR;  // TIM DMA address for full transfer,   Address offset: 0x4C
   __IO uint32_t OR;    // TIM option register,                 Address offset: 0x50
} TIM_TypeDef;
*/


template <uint32_t TIMbaseAdr>
class TIM : private TIM_ral::CR1_t,
            private TIM_ral::CR2_t,
            private TIM_ral::SMCR_t,
            private TIM_ral::DIER_t,
            private TIM_ral::SR_t,
            private TIM_ral::EGR_t,
            private TIM_ral::CCMR_t,
            private TIM_ral::CCER_t,
            private TIM_ral::CNT_t,
            private TIM_ral::PSC_t,
            private TIM_ral::ARR_t,
            private TIM_ral::RCR_t,
            private TIM_ral::CCR_t
{
public:
   using CompareMode = TIM_ral::CCMR_t::CompareMode;
   using AF = AFR_t::AF;

   static const uint32_t Base = TIMbaseAdr;
   static constexpr AF AltFunc = 
      Base == TIM1_BASE ? AF::_1 :
#if defined(STM32F405xx)
      Base == TIM2_BASE ? AF::_1 :
#endif
      Base == TIM3_BASE ? AF::_2 :
#if defined(STM32F405xx)
      Base == TIM4_BASE ? AF::_2 :
      Base == TIM5_BASE ? AF::_2 :
      Base == TIM8_BASE ? AF::_3 :
#endif
                          AF::_0;

   void makeDebugVar() { conf1().bits.res = 0; }

   template <CompareMode val, uint8_t channel>
   static void  SetCompareMode ()
   {
      // 0 для каналов 1,2; 1 для каналов 3,4
      constexpr uint8_t regN = channel / 3;
      // 4 для каналов 1,3; 12 для каналов 2,4
      constexpr uint8_t offset = 4 + 8 * (channel / (regN*2 + 2));
      constexpr uint32_t ClearMask = (uint32_t) 0b111 << offset;
      constexpr uint32_t SetMask = (uint32_t) val << offset;
      MODIFY_REG (captureMode().regs[regN], ClearMask, SetMask);
   }
   template <uint8_t channel>
   static void CompareEnable ()   { captureEn().reg |= (uint16_t)1 << (channel-1)*4; }
   template <uint8_t channel>
   static void CompareDisable ()  { captureEn().reg &= ~( (uint16_t)1 << (channel-1)*4 ); }
   template <uint8_t channel>
   static void CompareToggle ()  { captureEn().reg ^= (uint16_t)1 << (channel-1)*4; }
   template <uint8_t channel>
   static bool IsCompareEnable () { return ( (captureEn().reg & ((uint16_t)1 << (channel-1)*4)) != 0); }
   template <uint8_t channel>
   static void SetCompareValue (uint32_t val) { capture().regs[channel-1] = val; }
   static void SetAutoReloadValue (uint32_t val) { autoReload().reg = val; }
   static void SetPrescaller (uint32_t val)      { prescaler().reg = val; }
   
#if defined(STM32F405xx)
   // включает тактирование таймера
   static void ClockEnable()
   {
      ClkEnableBit() = true;
      while ( !ClkEnableBit() ) { };
   }
   static void CounterEnable()    { bitBand(Base, conf1().Offset, CEN) = true; }
   static bool IsCount()          { return bitBand(Base, conf1().Offset, CEN); }
   static void CounterDisable()   { bitBand(Base, conf1().Offset, CEN) = false; }
   static void AutoReloadEnable() { bitBand(Base, conf1().Offset, ARPE) = true; }
#elif defined(STM32F030x6)
   // включает тактирование таймера
   static void ClockEnable()
   {
      ClockEnReg() |= ClockEnMask;
      while ( (ClockEnReg() & ClockEnMask) == 0 ) { };
   }
   static void CounterEnable()    { conf1().reg |= TIM_CR1_CEN_Msk; }
   static bool IsCount()          { return (conf1().reg & TIM_CR1_CEN_Msk) != 0; }
   static void CounterDisable()   { conf1().reg &= ~TIM_CR1_CEN_Msk; }
   static void AutoReloadEnable() { conf1().reg |= TIM_CR1_ARPE_Msk; }
#endif



protected:
#define MakeRef(Reg,Ref) TIM_ral::Reg& Ref() { return (TIM_ral::Reg&) *(uint32_t*)(Base + TIM_ral::Reg::Offset); }
   static volatile MakeRef (CR1_t,  conf1       );
   static volatile MakeRef (CR1_t,  conf2       );
   static volatile MakeRef (CCMR_t, captureMode );
   static volatile MakeRef (CCER_t, captureEn   );
   static volatile MakeRef (PSC_t,  prescaler   );
   static volatile MakeRef (ARR_t,  autoReload  );
   static volatile MakeRef (CCR_t,  capture     );
#undef MakeRef



private:
#if defined(STM32F405xx)
   static constexpr volatile uint32_t& ClkEnableBit() { return
      Base == TIM1_BASE ? bitBand(RCC_BASE, RCC_ral::APB2ENR_t::Offset, RCC_APB2ENR_TIM1EN_Pos) :
      Base == TIM2_BASE ? bitBand(RCC_BASE, RCC_ral::APB1ENR_t::Offset, RCC_APB1ENR_TIM2EN_Pos) :
      Base == TIM3_BASE ? bitBand(RCC_BASE, RCC_ral::APB1ENR_t::Offset, RCC_APB1ENR_TIM3EN_Pos) :
      Base == TIM4_BASE ? bitBand(RCC_BASE, RCC_ral::APB1ENR_t::Offset, RCC_APB1ENR_TIM4EN_Pos) :
      Base == TIM5_BASE ? bitBand(RCC_BASE, RCC_ral::APB1ENR_t::Offset, RCC_APB1ENR_TIM5EN_Pos) :
      Base == TIM8_BASE ? bitBand(RCC_BASE, RCC_ral::APB2ENR_t::Offset, RCC_APB2ENR_TIM8EN_Pos) :
                          bitBand(RCC_BASE, RCC_ral::APB2ENR_t::Offset, RCC_APB2ENR_TIM1EN_Pos);
   }
#elif defined(STM32F030x6)
   static constexpr uint32_t& ClockEnReg() { return
      Base == TIM1_BASE ? (uint32_t&)RCC->APB2ENR :
      Base == TIM3_BASE ? (uint32_t&)RCC->APB1ENR : (uint32_t&)RCC->APB2ENR;
   }
   static constexpr uint32_t ClockEnMask =
      Base == TIM1_BASE ? RCC_APB2ENR_TIM1EN_Msk :
      Base == TIM3_BASE ? RCC_APB1ENR_TIM3EN_Msk : RCC_APB2ENR_TIM1EN_Msk;
#endif
};




#undef TIM1
using TIM1 = TIM<TIM1_BASE>;
#undef TIM3
using TIM3 = TIM<TIM3_BASE>;

#if defined(STM32F405xx)
   #undef TIM2
   using TIM2 = TIM<TIM2_BASE>;
   #undef TIM4
   using TIM4 = TIM<TIM4_BASE>;
   #undef TIM5
   using TIM5 = TIM<TIM5_BASE>;
   #undef TIM8
   using TIM8 = TIM<TIM8_BASE>;
#endif




#include "TIM_impl.h"


#pragma once

#include "TIM_bits.h"
#include "RCC.h"
#include "GPIO.h"
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

template<uint32_t adr>
struct TIMx {
   TIM_ral::CR1_t   CR1;
   TIM_ral::CR2_t   CR2;
   TIM_ral::SMCR_t  SMCR;
   TIM_ral::DIER_t  DIER;
   TIM_ral::SR_t    SR;
   TIM_ral::EGR_t   EGR;
   TIM_ral::CCMR_t  CCMR;
   TIM_ral::CCER_t  CCER;
   TIM_ral::CNT_t   CNT;
   TIM_ral::PSC_t   PSC;
   TIM_ral::ARR_t   ARR;
   TIM_ral::RCR_t   RCR;
   TIM_ral::CCR_t   CCR;
   TIM_ral::BDTR_t  BDTR;


  using OnePulseMode            = TIM_ral::CR1_t::OnePulseMode;
  using Trigger                 = TIM_ral::SMCR_t::Trigger;
  using SlaveMode               = TIM_ral::SMCR_t::SlaveMode;
  using ExternalTriggerPolarity = TIM_ral::SMCR_t::ExternalTriggerPolarity;
  using SelectionCompareMode    = TIM_ral::CCMR_t::SelectionCompareMode;
  using CompareMode             = TIM_ral::CCMR_t::CompareMode;
  using OutputPolarity          = TIM_ral::CCER_t::OutputPolarity;

 // using AF = AFR_t::AF;

  static const uint32_t Base = adr;
  

  void makeDebugVar() { controlRegister1().bits.res = 0; }


   static void     counterEnable();
   static void     counterDisable();
   static bool     isCount();
   static void     autoReloadEnable();
   static void     clockEnable();
   template<SelectionCompareMode value, uint8_t channel>
   static void     selectCompareMode();
   template<CompareMode value, uint8_t channel>
   static void     setCompareMode();
   template<uint8_t channel>
   static void     preloadEnable();
   template<uint8_t channel>
   static void     preloadDisable();
   static uint16_t getCounter();
   static uint16_t clearCounter();
   template<SlaveMode value>
   static void     setSlaveMode();
   template<OutputPolarity value, uint8_t channel>
   static void     setOutputPolarity();
   template<Trigger value>
   static void     setTrigger ();
   template<OnePulseMode value>
   static void     setOnePulseMode();
   template<ExternalTriggerPolarity value>
   static void     setExternalTriggerPolarity();
   static void     externalClockEnable();
   static void     externalClockDisable();
   template <uint8_t channel>
   static void     compareEnable ();   
   template <uint8_t channel>
   static void     compareDisable (); 
   template <uint8_t channel>
   static void     compareToggle ();  
   template <uint8_t channel>
   static bool     isCompareEnable ();
   template <uint8_t channel>
   static void     setCompareValue (uint32_t val);
   static void     setAutoReloadValue (uint32_t val);
   static void     setPrescaller (uint32_t val);
   static void     mainOutputEnable();




  #define MAKE_REG(Type, name) static Type& name() { return *((Type *)(adr + Type::Offset));}
  MAKE_REG(TIM_ral::CCMR_t, captureCompareMode)
  MAKE_REG(TIM_ral::SMCR_t, slaveModeControl)
  MAKE_REG(TIM_ral::CR1_t,  controlRegister1)
  MAKE_REG(TIM_ral::CCER_t, captureCompareEnable)
  MAKE_REG(TIM_ral::CNT_t,  count)
  MAKE_REG(TIM_ral::CCR_t,  captureCompareRegister)
  MAKE_REG(TIM_ral::PSC_t,  prescaler)
  MAKE_REG(TIM_ral::ARR_t,  autoReload)
  MAKE_REG(TIM_ral::BDTR_t, breakAndDeathTime)
  #undef MAKE_REG



};

#undef TIM1
using TIM1 = TIMx<TIM1_BASE>;
#undef TIM3
using TIM3 = TIMx<TIM3_BASE>;

#undef TIM14
using TIM14 = TIMx<TIM14_BASE>;
#if defined (STM32F030x6)
#undef TIM16
using TIM16 = TIMx<TIM16_BASE>;
#undef TIM17
using TIM17 = TIMx<TIM17_BASE>;
#elif defined(STM32F405xx)
#undef TIM2
using TIM2 = TIMx<TIM2_BASE>;
#undef TIM4
using TIM4 = TIMx<TIM4_BASE>;
#undef TIM5
using TIM5 = TIMx<TIM5_BASE>;
#undef TIM6
using TIM6 = TIMx<TIM6_BASE>;
#undef TIM7
using TIM7 = TIMx<TIM7_BASE>;
#undef TIM8
using TIM8 = TIMx<TIM8_BASE>;
#undef TIM9
using TIM9 = TIMx<TIM9_BASE>;
#undef TIM10
using TIM10 = TIMx<TIM10_BASE>;
#undef TIM11
using TIM11 = TIMx<TIM11_BASE>;
#undef TIM12
using TIM12 = TIMx<TIM12_BASE>;
#undef TIM13
using TIM13 = TIMx<TIM13_BASE>;
#endif 


#include "TIM_src.h"

#include "TIM_impl.h"


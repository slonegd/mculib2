#pragma once

#include "TIM_bits.h"
#include "RCC.h"
#include "GPIO.h"


template<uint32_t adr>
class TIMx
{
public:
   using OnePulseMode         = TIM_ral::OnePulseMode;
   using Trigger              = TIM_ral::Trigger;
   using SlaveMode            = TIM_ral::SlaveMode;
   using ExtTriggerPolarity   = TIM_ral::ExtTriggerPolarity;
   using SelectionCompareMode = TIM_ral::SelectionCompareMode;
   using CompareMode          = TIM_ral::CompareMode;
   using Polarity             = TIM_ral::Polarity;

   static const uint32_t Base = adr;

   void makeDebugVar() { controlRegister1().bits.res = 0; }

   static void     counterEnable();
   static void     counterDisable();
   static bool     isCount();
   static void     autoReloadEnable();
   static void     clockEnable();
   static uint16_t getCounter();
   static void     clearCounter();
   static void     externalClockEnable(); 
   static void     externalClockDisable();
   static void     setAutoReloadValue (uint32_t val);
   static void     setPrescaller (uint32_t val);
   static void     mainOutputEnable();


   template<uint8_t channel>          static void preloadEnable();
   template<uint8_t channel>          static void preloadDisable();
   template<uint8_t channel>          static void compareEnable ();   
   template<uint8_t channel>          static void compareDisable (); 
   template<uint8_t channel>          static void compareToggle ();  
   template<uint8_t channel>          static bool isCompareEnable ();
   template<uint8_t channel>          static void setCompareValue (uint32_t val);
   template<SlaveMode value>          static void setSlaveMode();
   template<Trigger value>            static void setTrigger ();
   template<OnePulseMode value>       static void setOnePulseMode();
   template<ExtTriggerPolarity value> static void setExternalTriggerPolarity();

   template<SelectionCompareMode value, uint8_t channel> static void selectCompareMode();
   template<CompareMode value,          uint8_t channel> static void setCompareMode();
   template<Polarity value,             uint8_t channel> static void setPolarity();


protected:
  #define MAKE_REG(Type, name) __IO static Type& name() { return *((Type *)(adr + Type::Offset));}
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

private:
   TIM_ral::CR1_t  CR1;  // TIM control register 1
   TIM_ral::CR2_t  CR2;  // TIM control register 2
   TIM_ral::SMCR_t SMCR; // TIM slave mode control register
   TIM_ral::DIER_t DIER; // TIM DMA/interrupt enable register
   TIM_ral::SR_t   SR;   // TIM status register
   TIM_ral::EGR_t  EGR;  // TIM event generation register
   TIM_ral::CCMR_t CCMR; // TIM capture/compare mode register 1
   TIM_ral::CCER_t CCER; // TIM capture/compare enable register
   TIM_ral::CNT_t  CNT;  // TIM counter register
   TIM_ral::PSC_t  PSC;  // TIM prescaler
   TIM_ral::ARR_t  ARR;  // TIM auto-reload register
   TIM_ral::RCR_t  RCR;  // TIM repetition counter register
   TIM_ral::CCR_t  CCR;  // TIM capture/compare register
   TIM_ral::BDTR_t BDTR; // TIM break and dead-time register
   TIM_ral::DCR_t  DCR;  // TIM DMA control registerGPIO_ral
/* STM32F4 STM32F0
typedef struct
{
   __IO uint32_t DCR;   // TIM DMA control register,            Address offset: 0x48
   __IO uint32_t DMAR;  // TIM DMA address for full transfer,   Address offset: 0x4C
   __IO uint32_t OR;    // TIM option register,                 Address offset: 0x50
} TIM_TypeDef;
*/

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


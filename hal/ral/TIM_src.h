#include <stddef.h>


template<uint32_t adr>
void TIMx<adr>::clockEnable()
{ 
   constexpr uint32_t ClockEnAdr = RCC_BASE +
      (adr == TIM1_BASE  ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM3_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM14_BASE ? offsetof(RCC_TypeDef, APB1ENR) :
   #if defined(STM32F030x6)
       adr == TIM16_BASE ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM17_BASE ? offsetof(RCC_TypeDef, APB2ENR) : 
   #elif defined(STM32F405xx)    
       adr == TIM2_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM4_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM5_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM6_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM7_BASE  ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM8_BASE  ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM9_BASE  ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM10_BASE ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM11_BASE ? offsetof(RCC_TypeDef, APB2ENR) :
       adr == TIM12_BASE ? offsetof(RCC_TypeDef, APB1ENR) :
       adr == TIM13_BASE ? offsetof(RCC_TypeDef, APB1ENR) :
   #endif 
      0);

   constexpr uint32_t mask = adr == TIM1_BASE  ? RCC_APB2ENR_TIM1EN_Msk :
                             adr == TIM3_BASE  ? RCC_APB1ENR_TIM3EN_Msk :
                             adr == TIM14_BASE ? RCC_APB1ENR_TIM14EN_Msk :
   #if defined(STM32F030x6)
                             adr == TIM16_BASE ? RCC_APB2ENR_TIM16EN_Msk :
                             adr == TIM17_BASE ? RCC_APB2ENR_TIM17EN_Msk : 
   #elif defined(STM32F405xx)    
                             adr == TIM2_BASE  ? RCC_APB1ENR_TIM2EN_Msk :
                             adr == TIM4_BASE  ? RCC_APB1ENR_TIM4EN_Msk :
                             adr == TIM5_BASE  ? RCC_APB1ENR_TIM5EN_Msk :
                             adr == TIM6_BASE  ? RCC_APB1ENR_TIM6EN_Msk :
                             adr == TIM7_BASE  ? RCC_APB1ENR_TIM7EN_Msk :
                             adr == TIM8_BASE  ? RCC_APB2ENR_TIM8EN_Msk :
                             adr == TIM9_BASE  ? RCC_APB2ENR_TIM9EN_Msk :
                             adr == TIM10_BASE ? RCC_APB2ENR_TIM10EN_Msk :
                             adr == TIM11_BASE ? RCC_APB2ENR_TIM11EN_Msk :
                             adr == TIM12_BASE ? RCC_APB1ENR_TIM12EN_Msk :
                             adr == TIM13_BASE ? RCC_APB1ENR_TIM13EN_Msk :
   #endif 

      0;

   *(reinterpret_cast<uint32_t*>(ClockEnAdr)) |= mask;
   // WRITE_MASK_ON_ADDRESS(ClockEnAdr, mask);
}

template<uint32_t adr>
template<TIM_ral::CCMR_t::SelectionCompareMode value, uint8_t channel>
void TIMx<adr>::SelectCompareMode()
{
    constexpr uint8_t regN = channel == (1 | 2) ? 0:
                             channel == (3 | 4) ? 1: 0;
    constexpr uint8_t position = channel == (1 | 3) ? 0:
                                 channel == (2 | 4) ? 8: 0;
    uint32_t tmp = captureCompareMode().regs[regN];
    tmp &= ~((uint32_t)0b11 << position);
    tmp |= ((uint32_t)value << position);
    captureCompareMode().regs[regN] = tmp;
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::PreloadEnable()
{
   constexpr uint8_t regN = channel == (1 | 2) ? 0:
                            channel == (3 | 4) ? 1: 0;
   constexpr uint8_t position = channel == (1 | 3) ? 3:
                                channel == (2 | 4) ? 11: 3;
   captureCompareMode().regs[regN] |= ((uint32_t)0b1 << position);
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::PreloadDisable()
{
   constexpr uint8_t regN = channel == (1 | 2) ? 0:
                            channel == (3 | 4) ? 1: 0;
   constexpr uint8_t position = channel == (1 | 3) ? 3:
                                channel == (2 | 4) ? 11: 3;
   captureCompareMode().regs[regN] &= ~((uint32_t)0b1 << position);
}
template<uint32_t adr>
template <TIM_ral::CCMR_t::CompareMode value, uint8_t channel>
void TIMx<adr>::SetCompareMode()
{
   constexpr uint8_t regN = channel == (1 | 2) ? 0:
                            channel == (3 | 4) ? 1: 0;
   constexpr uint8_t position = channel == (1 | 3) ? 4:
                                channel == (2 | 4) ? 12: 3;
   uint32_t tmp = captureCompareMode().regs[regN];
   tmp &= ~((uint32_t)0b111 << position);
   tmp |=  ((uint32_t)value << position);
   captureCompareMode().regs[regN] = tmp;

}

template<uint32_t adr>
uint16_t TIMx<adr>::getCounter() { return count().reg; }

template<uint32_t adr>
uint16_t TIMx<adr>::clearCounter() { return  count().reg = 0; }



template<uint32_t adr>
template<TIM_ral::SMCR_t::Trigger value>
void TIMx<adr>::setTrigger ()
{
   uint32_t tmp = slaveModeControl().reg;
   tmp &= ~((uint32_t)0b111 << TIM_ral::SMCR_t::TS);
   tmp |= ((uint32_t)value << TIM_ral::SMCR_t::TS);
   slaveModeControl().reg = tmp;    
}

template<uint32_t adr>
template<TIM_ral::SMCR_t::SlaveMode value>
void TIMx<adr>::setSlaveMode()
{
   uint32_t tmp = slaveModeControl().reg;
   tmp &= ~((uint32_t)0b111 << TIM_ral::SMCR_t::SMS);
   tmp |= ((uint32_t)value << TIM_ral::SMCR_t::SMS);
   slaveModeControl().reg = tmp;
}


template<uint32_t adr>
template<TIM_ral::CCER_t::OutputPolarity value, uint8_t channel>
void TIMx<adr>::setOutputPolarity()
{
   uint32_t tmp = captureCompareEnable().reg;
   tmp &= ~((uint32_t)OutputPolarity::reset << (channel - 1) * 4 );
   tmp |= ((uint32_t)value << (channel - 1) * 4 ); 
   captureCompareEnable().reg = tmp;
}


template<uint32_t adr>
template<TIM_ral::CR1_t::OnePulseMode value>
void TIMx<adr>::setOnePulseMode()
{
    uint32_t tmp = controlRegister1().reg;
    tmp &= ~((uint32_t)OnePulseMode::notStopped << TIM_ral::CR1_t::OPM);
    tmp |= ((uint32_t)value << TIM_ral::CR1_t::OPM);
    controlRegister1().reg = tmp;
}


template<uint32_t adr>
template<TIM_ral::SMCR_t::ExternalTriggerPolarity value>
void TIMx<adr>::setExternalTriggerPolarity()
{
    uint32_t tmp = slaveModeControl().reg;
    tmp &= ~((uint32_t)ExternalTriggerPolarity::notInverted << TIM_ral::SMCR_t::ETP);
    tmp |= ((uint32_t)value << TIM_ral::SMCR_t::ETP);
    slaveModeControl().reg = tmp;
}



template<uint32_t adr>
void TIMx<adr>::ExternalClockEnable()
{
   slaveModeControl().reg |= TIM_SMCR_ECE_Msk;
} 

template<uint32_t adr>
void TIMx<adr>::ExternalClockDisable() 
{
   slaveModeControl().reg &= ~TIM_SMCR_ECE_Msk;
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::CompareEnable()
{
   captureCompareEnable().reg |= (uint16_t)1 << (channel-1)*4; 
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::CompareDisable()
{
   captureCompareEnable().reg &= ~( (uint16_t)1 << (channel-1)*4 ); 
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::CompareToggle()
{
   captureCompareEnable().reg ^= (uint16_t)1 << (channel-1)*4;
}

template<uint32_t adr>
template<uint8_t channel>
bool TIMx<adr>::IsCompareEnable()
{
   return ( (captureCompareEnable().reg & ((uint16_t)1 << (channel-1)*4)) != 0);
}

template<uint32_t adr>
template<uint8_t channel>
void TIMx<adr>::SetCompareValue (uint32_t val) 
{
    captureCompareRegister().regs[channel-1] = val; 
}

template<uint32_t adr>
void TIMx<adr>::SetAutoReloadValue (uint32_t val) 
{
    autoReload().reg = val;  
}

template<uint32_t adr>
void TIMx<adr>::SetPrescaller (uint32_t val) 
{
    prescaler().reg = val;
}

template<uint32_t adr>
void TIMx<adr>::MainOutputEnable () 
{
    bdtr().reg |= TIM_BDTR_MOE_Msk;
}
#if defined(STM32F030x6)
   template<uint32_t adr>
   void TIMx<adr>::CounterEnable()
   {
      controlRegister1().reg |= TIM_CR1_CEN_Msk;
   } 

   template<uint32_t adr>
   void TIMx<adr>::CounterDisable() 
   {
      controlRegister1().reg &= ~TIM_CR1_CEN_Msk;
   }

   template<uint32_t adr>
   bool TIMx<adr>::IsCount()
   {
   return (controlRegister1().reg & TIM_CR1_CEN_Msk) != 0;
   }

   template<uint32_t adr>
   void TIMx<adr>::AutoReloadEnable ()
   {
      controlRegister1().reg |= TIM_CR1_ARPE_Msk;
   }
#elif defined(STM32F405xx)
   template<uint32_t adr>
   void TIMx<adr>::CounterEnable()
   {
       BB_REG(controlRegister1(), CEN) = true;
   } 

   template<uint32_t adr>
   void TIMx<adr>::CounterDisable() 
   {
      BB_REG(controlRegister1(), CEN) = false;
   }

   template<uint32_t adr>
   bool TIMx<adr>::IsCount()
   {
      return BB_REG(controlRegister1(), CEN); 
   }

   template<uint32_t adr>
   void TIMx<adr>::AutoReloadEnable ()
   {
      BB_REG(controlRegister1(), ARPE) = true;
   }
#endif
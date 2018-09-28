#define STM32F405xx

#include "RCC.h"
#include "tim_periph.h"
#include <iostream>
#include <type_traits>
#include <thread>

struct MockPointer
{
   static TIM1::CMSIS_type* p;
   static auto get() { return reinterpret_cast<TIM1::periph_type*>(p); }
};
TIM1::CMSIS_type mock;
TIM1::CMSIS_type* MockPointer::p = &mock;
using TTIM = template_TIM<0, MockPointer>;

bool counterEnable()
{
   mock.CR1 = 0;
   TTIM::counterEnable();
   return mock.CR1 & TIM_CR1_CEN_Msk;
}

bool counterDisable()
{
   mock.CR1 |= TIM_CR1_CEN_Msk;
   TTIM::counterDisable();
   return not (mock.CR1 & TIM_CR1_CEN_Msk);
}

bool isCount()
{
   bool good {true};
   mock.CR1 = 0;
   good &= not TTIM::isCount();

   mock.CR1 |= TIM_CR1_CEN_Msk;
   good &= TTIM::isCount();

   return good;
}

bool autoReloadEnable()
{
   mock.CR1 = 0;
   TTIM::autoReloadEnable();
   return mock.CR1 & TIM_CR1_ARPE_Msk;
}

bool getCounter()
{
   mock.CNT = 0;
   mock.CNT = 0xFFFF;
   return mock.CNT & TTIM::getCounter();
}

bool clearCounter()
{
   mock.CNT = 0x1234;
   TTIM::clearCounter();
   return mock.CNT == 0;
}

bool externalClockEnable()
{
   mock.SMCR = 0;
   TTIM::externalClockEnable();
   return mock.SMCR & TIM_SMCR_ECE_Msk;
}

bool externalClockDisable()
{
   mock.SMCR |= TIM_SMCR_ECE_Msk;
   TTIM::externalClockDisable();
   return not (mock.SMCR & TIM_SMCR_ECE_Msk);
}

bool setAutoReloadValue()
{
   TTIM::setAutoReloadValue(0xFFFF);
   return mock.ARR & 0xFFFF;
}

bool setPrescaller()
{
   TTIM::setPrescaller(0xFFFF);
   return mock.PSC & 0xFFFF;
}

bool mainOutputEnable()
{
   mock.BDTR = 0;
   TTIM::mainOutputEnable();
   return mock.BDTR & TIM_BDTR_MOE_Msk;
}

bool preloadEnable()
{
   mock.CCMR1 = 0;
   mock.CCMR2 = 0;

   bool good {true};
   TTIM::preloadEnable<TTIM::Channel::_1>();
   good &= bool (mock.CCMR1 & TIM_CCMR1_OC1PE_Msk);
   TTIM::preloadEnable<TTIM::Channel::_2>();
   good &= bool (mock.CCMR1 & TIM_CCMR1_OC2PE_Msk);
   TTIM::preloadEnable<TTIM::Channel::_3>();
   good &= bool (mock.CCMR2 & TIM_CCMR2_OC3PE_Msk);
   TTIM::preloadEnable<TTIM::Channel::_4>();
   good &= bool (mock.CCMR2 & TIM_CCMR2_OC4PE_Msk);
   return good;
}

bool preloadDisable()
{
   mock.CCMR1 |= TIM_CCMR1_OC1PE_Msk | TIM_CCMR1_OC2PE_Msk;
   mock.CCMR2 |= TIM_CCMR2_OC3PE_Msk | TIM_CCMR2_OC4PE_Msk;

   bool good {true};
   TTIM::preloadDisable<TTIM::Channel::_1>();
   good &= not (mock.CCR1 & TIM_CCMR1_OC1PE_Msk);
   TTIM::preloadDisable<TTIM::Channel::_2>();
   good &= not (mock.CCR1 & TIM_CCMR1_OC2PE_Msk);
   TTIM::preloadDisable<TTIM::Channel::_3>();
   good &= not (mock.CCR2 & TIM_CCMR2_OC3PE_Msk);
   TTIM::preloadDisable<TTIM::Channel::_4>();
   good &= not (mock.CCR2 & TIM_CCMR2_OC4PE_Msk);
   return good;
}

bool compareEnable()
{
   mock.CCER = 0;

   bool good {true};
   TTIM::compareEnable<TTIM::Channel::_1>();
   good &= bool (mock.CCER & TIM_CCER_CC1E_Msk);
   TTIM::compareEnable<TTIM::Channel::_2>();
   good &= bool (mock.CCER & TIM_CCER_CC2E_Msk);
   TTIM::compareEnable<TTIM::Channel::_3>();
   good &= bool (mock.CCER & TIM_CCER_CC3E_Msk);
   TTIM::compareEnable<TTIM::Channel::_4>();
   good &= bool (mock.CCER & TIM_CCER_CC4E_Msk);
   return good;
}

bool compareDisable()
{
   mock.CCER |= TIM_CCER_CC1E_Msk | TIM_CCER_CC2E_Msk | TIM_CCER_CC3E_Msk | TIM_CCER_CC4E_Msk;

   bool good {true};
   TTIM::compareDisable<TTIM::Channel::_1>();
   good &= not (mock.CCER & TIM_CCER_CC1E_Msk);
   TTIM::compareDisable<TTIM::Channel::_2>();
   good &= not (mock.CCER & TIM_CCER_CC2E_Msk);
   TTIM::compareDisable<TTIM::Channel::_3>();
   good &= not (mock.CCER & TIM_CCER_CC3E_Msk);
   TTIM::compareDisable<TTIM::Channel::_4>();
   good &= not (mock.CCER & TIM_CCER_CC4E_Msk);
   return good;
}

bool compareToggle()
{
   mock.CCER = 0;
   
   bool good {true};
   TTIM::compareToggle<TTIM::Channel::_1>();
   good &= bool (mock.CCER & TIM_CCER_CC1E_Msk);
   TTIM::compareToggle<TTIM::Channel::_1>();
   good &= not (mock.CCER & TIM_CCER_CC1E_Msk);
   TTIM::compareToggle<TTIM::Channel::_2>();
   good &= bool (mock.CCER & TIM_CCER_CC2E_Msk);
   TTIM::compareToggle<TTIM::Channel::_2>();
   good &= not (mock.CCER & TIM_CCER_CC2E_Msk);
   TTIM::compareToggle<TTIM::Channel::_3>();
   good &= bool (mock.CCER & TIM_CCER_CC3E_Msk);
   TTIM::compareToggle<TTIM::Channel::_3>();
   good &= not (mock.CCER & TIM_CCER_CC3E_Msk);
   TTIM::compareToggle<TTIM::Channel::_4>();
   good &= bool (mock.CCER & TIM_CCER_CC4E_Msk);
   TTIM::compareToggle<TTIM::Channel::_4>();
   good &= not (mock.CCER & TIM_CCER_CC4E_Msk);
   return good;
}

bool isCompareEnable()
{
   mock.CCER = 0;

   bool good {true};
   mock.CCER |= TIM_CCER_CC1E_Msk;
   good &= TTIM::isCompareEnable<TTIM::Channel::_1>();
   mock.CCER |= TIM_CCER_CC2E_Msk;
   good &= TTIM::isCompareEnable<TTIM::Channel::_2>();
   mock.CCER |= TIM_CCER_CC3E_Msk;
   good &= TTIM::isCompareEnable<TTIM::Channel::_3>();
   mock.CCER |= TIM_CCER_CC4E_Msk;
   good &= TTIM::isCompareEnable<TTIM::Channel::_4>();
   return good;
}

bool setCompareValue()
{
   bool good {true};
   TTIM::setCompareValue<TTIM::Channel::_1>(0xFFFF);
   good &= (mock.CCR1 & 0xFFFF);
   TTIM::setCompareValue<TTIM::Channel::_2>(0xFFFF);
   good &= (mock.CCR2 & 0xFFFF);
   TTIM::setCompareValue<TTIM::Channel::_3>(0xFFFF);
   good &= (mock.CCR3 & 0xFFFF);
   TTIM::setCompareValue<TTIM::Channel::_4>(0xFFFF);
   good &= (mock.CCR4 & 0xFFFF);
   return good;
}

bool setSlaveMode()
{
   bool good {true};
   mock.SMCR = 0;

   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::ExternalClock>();
   good &=     bool (mock.SMCR & TIM_SMCR_SMS_0)
       and     bool (mock.SMCR & TIM_SMCR_SMS_1)
       and     bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::TriggerMode>();
   good &= not bool (mock.SMCR & TIM_SMCR_SMS_0)
       and     bool (mock.SMCR & TIM_SMCR_SMS_1)
       and     bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::Gated>();
   good &=     bool (mock.SMCR & TIM_SMCR_SMS_0)
       and not bool (mock.SMCR & TIM_SMCR_SMS_1)
       and     bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::Reset>();
   good &= not bool (mock.SMCR & TIM_SMCR_SMS_0)
       and not bool (mock.SMCR & TIM_SMCR_SMS_1)
       and     bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::Encoder3>();
   good &=     bool (mock.SMCR & TIM_SMCR_SMS_0)
       and     bool (mock.SMCR & TIM_SMCR_SMS_1)
       and not bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::Encoder2>();
   good &= not bool (mock.SMCR & TIM_SMCR_SMS_0)
       and     bool (mock.SMCR & TIM_SMCR_SMS_1)
       and not bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::Encoder1>();
   good &=     bool (mock.SMCR & TIM_SMCR_SMS_0)
       and not bool (mock.SMCR & TIM_SMCR_SMS_1)
       and not bool (mock.SMCR & TIM_SMCR_SMS_2);
   TTIM::set<TIM_detail::SMCR_bits::SlaveMode::SMDisabled>();
   good &= not bool (mock.SMCR & TIM_SMCR_SMS_0)
       and not bool (mock.SMCR & TIM_SMCR_SMS_1)
       and not bool (mock.SMCR & TIM_SMCR_SMS_2);

   return good;
}

bool setTrigger()
{
   bool good {true};
   mock.SMCR = 0;

   TTIM::set<TIM_detail::SMCR_bits::Trigger::External>();
   good &=     bool (mock.SMCR & TIM_SMCR_TS_0)
       and     bool (mock.SMCR & TIM_SMCR_TS_1)
       and     bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::FiltrTI2>();
   good &= not bool (mock.SMCR & TIM_SMCR_TS_0)
       and     bool (mock.SMCR & TIM_SMCR_TS_1)
       and     bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::FiltrTI1>();
   good &=     bool (mock.SMCR & TIM_SMCR_TS_0)
       and not bool (mock.SMCR & TIM_SMCR_TS_1)
       and     bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::TI1edge>();
   good &= not bool (mock.SMCR & TIM_SMCR_TS_0)
       and not bool (mock.SMCR & TIM_SMCR_TS_1)
       and     bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::_3>();
   good &=     bool (mock.SMCR & TIM_SMCR_TS_0)
       and     bool (mock.SMCR & TIM_SMCR_TS_1)
       and not bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::_2>();
   good &= not bool (mock.SMCR & TIM_SMCR_TS_0)
       and     bool (mock.SMCR & TIM_SMCR_TS_1)
       and not bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::_1>();
   good &=     bool (mock.SMCR & TIM_SMCR_TS_0)
       and not bool (mock.SMCR & TIM_SMCR_TS_1)
       and not bool (mock.SMCR & TIM_SMCR_TS_2);
   TTIM::set<TIM_detail::SMCR_bits::Trigger::_0>();
   good &= not bool (mock.SMCR & TIM_SMCR_TS_0)
       and not bool (mock.SMCR & TIM_SMCR_TS_1)
       and not bool (mock.SMCR & TIM_SMCR_TS_2);

   return good;
}

bool setOnePulseMode()
{
   bool good {true};
   mock.CR1 = 0;

   TTIM::set<TIM_detail::CR1_bits::OnePulseMode::counterStop>();
   good &= bool (mock.CR1 & TIM_CR1_OPM_Msk);
   TTIM::set<TIM_detail::CR1_bits::OnePulseMode::notStopped >();
   good &= not bool (mock.CR1 & TIM_CR1_OPM_Msk);

   return good;
}

bool setExtTriggerPolarity()
{
   bool good {true};
   mock.SMCR = 0;

   TTIM::set<TIM_detail::SMCR_bits::ExtTriggerPolarity::inverted>();
   good &= bool (mock.SMCR & TIM_SMCR_ETP_Msk);
   TTIM::set<TIM_detail::SMCR_bits::ExtTriggerPolarity::notInverted>();
   good &= not bool (mock.SMCR & TIM_SMCR_ETP_Msk);

   return good;
}

bool selectCompareMode()
{
   bool good {true};
   mock.CCMR1 = 0;
   mock.CCMR2 = 0;

   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputTRC, TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_CC1S_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_CC1S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputALT, TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_CC1S_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_CC1S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Input,    TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_CC1S_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_CC1S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Output,   TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_CC1S_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_CC1S_1);

   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputTRC, TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_CC2S_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_CC2S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputALT, TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_CC2S_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_CC2S_0);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Input,    TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_CC2S_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_CC2S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Output,   TTIM::Channel::_2>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_CC2S_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_CC2S_1);

   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputTRC, TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC3S_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_CC3S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputALT, TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC3S_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC3S_0);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Input,    TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC3S_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC3S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Output,   TTIM::Channel::_3>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_CC3S_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC3S_1);

   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputTRC, TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC4S_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_CC4S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::InputALT, TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC4S_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC4S_0);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Input,    TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_CC4S_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC4S_1);
   TTIM::selectCompareMode<TIM_detail::SelectionCompareMode::Output,   TTIM::Channel::_4>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_CC4S_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_CC4S_1);

   return good;
}

bool setCompareMode ()
{
   bool good {true};
   mock.CCMR1 = 0;
   mock.CCMR2 = 0;

   TTIM::set<TIM_detail::Output_bits::CompareMode::InvertedPWMmode, TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::PWMmode,         TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceActive,     TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceInactive,   TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ToggleOnMatch,   TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::InactiveOnMatch, TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ActiveOnMatch,   TTIM::Channel::_1>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::Off,             TTIM::Channel::_1>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC1M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC1M_2);

   TTIM::set<TIM_detail::Output_bits::CompareMode::InvertedPWMmode, TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::PWMmode,         TTIM::Channel::_2>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceActive,     TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceInactive,   TTIM::Channel::_2>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ToggleOnMatch,   TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::InactiveOnMatch, TTIM::Channel::_2>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and     bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ActiveOnMatch,   TTIM::Channel::_2>();
   good &=     bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::Off,             TTIM::Channel::_2>();
   good &= not bool (mock.CCMR1 & TIM_CCMR1_OC2M_0)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_1)
       and not bool (mock.CCMR1 & TIM_CCMR1_OC2M_2);

   TTIM::set<TIM_detail::Output_bits::CompareMode::InvertedPWMmode, TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::PWMmode,         TTIM::Channel::_3>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceActive,     TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceInactive,   TTIM::Channel::_3>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ToggleOnMatch,   TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::InactiveOnMatch, TTIM::Channel::_3>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ActiveOnMatch,   TTIM::Channel::_3>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::Off,             TTIM::Channel::_3>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC3M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC3M_2);

   TTIM::set<TIM_detail::Output_bits::CompareMode::InvertedPWMmode, TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::PWMmode,         TTIM::Channel::_4>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceActive,     TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ForceInactive,   TTIM::Channel::_4>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ToggleOnMatch,   TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::InactiveOnMatch, TTIM::Channel::_4>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and     bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::ActiveOnMatch,   TTIM::Channel::_4>();
   good &=     bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);
   TTIM::set<TIM_detail::Output_bits::CompareMode::Off,             TTIM::Channel::_4>();
   good &= not bool (mock.CCMR2 & TIM_CCMR2_OC4M_0)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_1)
       and not bool (mock.CCMR2 & TIM_CCMR2_OC4M_2);

   return good;
}

bool setPolarity()
{
   bool good {true};
   mock.CCER = 0;

   TTIM::set<TIM_detail::CCER_bits::Polarity::both,    TTIM::Channel::_1>();
   good &=     bool (mock.CCER & TIM_CCER_CC1P_Msk)
       and     bool (mock.CCER & TIM_CCER_CC1NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::falling, TTIM::Channel::_1>();
   good &=     bool (mock.CCER & TIM_CCER_CC1P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC1NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::rising,  TTIM::Channel::_1>();
   good &= not bool (mock.CCER & TIM_CCER_CC1P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC1NP_Msk);

   TTIM::set<TIM_detail::CCER_bits::Polarity::both,    TTIM::Channel::_2>();
   good &=     bool (mock.CCER & TIM_CCER_CC2P_Msk)
       and     bool (mock.CCER & TIM_CCER_CC2NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::falling, TTIM::Channel::_2>();
   good &=     bool (mock.CCER & TIM_CCER_CC2P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC2NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::rising,  TTIM::Channel::_2>();
   good &= not bool (mock.CCER & TIM_CCER_CC2P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC2NP_Msk);

   TTIM::set<TIM_detail::CCER_bits::Polarity::both,    TTIM::Channel::_3>();
   good &=     bool (mock.CCER & TIM_CCER_CC3P_Msk)
       and     bool (mock.CCER & TIM_CCER_CC3NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::falling, TTIM::Channel::_3>();
   good &=     bool (mock.CCER & TIM_CCER_CC3P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC3NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::rising,  TTIM::Channel::_3>();
   good &= not bool (mock.CCER & TIM_CCER_CC3P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC3NP_Msk);

   TTIM::set<TIM_detail::CCER_bits::Polarity::both,    TTIM::Channel::_4>();
   good &=     bool (mock.CCER & TIM_CCER_CC4P_Msk)
       and     bool (mock.CCER & TIM_CCER_CC4NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::falling, TTIM::Channel::_4>();
   good &=     bool (mock.CCER & TIM_CCER_CC4P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC4NP_Msk);
   TTIM::set<TIM_detail::CCER_bits::Polarity::rising,  TTIM::Channel::_4>();
   good &= not bool (mock.CCER & TIM_CCER_CC4P_Msk)
       and not bool (mock.CCER & TIM_CCER_CC4NP_Msk);

   return good;
}
bool channel()
{
   return (TIM1::channel<PA8> () == TIM1::Channel::_1)
      and (TIM1::channel<PE9> () == TIM1::Channel::_1)
      and (TIM1::channel<PA9> () == TIM1::Channel::_2)
      and (TIM1::channel<PE11>() == TIM1::Channel::_2)
      and (TIM1::channel<PA10>() == TIM1::Channel::_3)
      and (TIM1::channel<PE13>() == TIM1::Channel::_3)
      and (TIM1::channel<PA11>() == TIM1::Channel::_4)
      and (TIM1::channel<PE14>() == TIM1::Channel::_4)
      // and (TIM1::channel<PA6> () == TIM1::Channel::_4) // warning [-Wreturn-type]

      and (TIM2::channel<PA15>() == TIM2::Channel::_1)
      and (TIM2::channel<PA1> () == TIM2::Channel::_2)
      and (TIM2::channel<PB3> () == TIM2::Channel::_2)
      and (TIM2::channel<PA2> () == TIM2::Channel::_3)
      and (TIM2::channel<PB10>() == TIM2::Channel::_3)
      and (TIM2::channel<PA3> () == TIM2::Channel::_4)
      and (TIM2::channel<PB11>() == TIM2::Channel::_4)
      // and (TIM2::channel<PA6> () == TIM1::Channel::_4) // warning [-Wreturn-type]

      and (TIM3::channel<PA6> () == TIM3::Channel::_1)
      and (TIM3::channel<PB4> () == TIM3::Channel::_1)
      and (TIM3::channel<PC6> () == TIM3::Channel::_1)
      and (TIM3::channel<PA7> () == TIM3::Channel::_2)
      and (TIM3::channel<PB5> () == TIM3::Channel::_2)
      and (TIM3::channel<PC7> () == TIM3::Channel::_2)
      and (TIM3::channel<PC8> () == TIM3::Channel::_3)
      and (TIM3::channel<PC9> () == TIM3::Channel::_4)
      // and (TIM3::channel<PA1> () == TIM3::Channel::_4) // warning [-Wreturn-type]

      and (TIM4::channel<PB6> () == TIM4::Channel::_1)
      and (TIM4::channel<PD12>() == TIM4::Channel::_1)
      and (TIM4::channel<PB7> () == TIM4::Channel::_2)
      and (TIM4::channel<PD13>() == TIM4::Channel::_2)
      and (TIM4::channel<PB8> () == TIM4::Channel::_3)
      and (TIM4::channel<PD14>() == TIM4::Channel::_3)
      and (TIM4::channel<PB9> () == TIM4::Channel::_4)
      and (TIM4::channel<PD15>() == TIM4::Channel::_4)
      // and (TIM4::channel<PA1> () == TIM3::Channel::_4) // warning [-Wreturn-type]

      and (TIM5::channel<PA0> () == TIM5::Channel::_1)
      and (TIM5::channel<PH10>() == TIM5::Channel::_1)
      and (TIM5::channel<PA1> () == TIM5::Channel::_2)
      and (TIM5::channel<PH11>() == TIM5::Channel::_2)
      and (TIM5::channel<PA2> () == TIM5::Channel::_3)
      and (TIM5::channel<PH12>() == TIM5::Channel::_3)
      and (TIM5::channel<PA3> () == TIM5::Channel::_4)
      and (TIM5::channel<PI0> () == TIM5::Channel::_4)
      // and (TIM5::channel<PA6> () == TIM3::Channel::_4) // warning [-Wreturn-type]

      and (TIM8::channel<PC6> () == TIM8::Channel::_1)
      and (TIM8::channel<PI5> () == TIM8::Channel::_1)
      and (TIM8::channel<PC7> () == TIM8::Channel::_2)
      and (TIM8::channel<PI6> () == TIM8::Channel::_2)
      and (TIM8::channel<PC8> () == TIM8::Channel::_3)
      and (TIM8::channel<PI7> () == TIM8::Channel::_3)
      and (TIM8::channel<PC9> () == TIM8::Channel::_4)
      and (TIM8::channel<PI2> () == TIM8::Channel::_4)
      // and (TIM8::channel<PA6> () == TIM3::Channel::_4) // warning [-Wreturn-type]

      and (TIM9::channel<PA2>() == TIM9::Channel::_1)
      and (TIM9::channel<PE5>() == TIM9::Channel::_1)
      and (TIM9::channel<PA3>() == TIM9::Channel::_2)
      and (TIM9::channel<PE6>() == TIM9::Channel::_2)
      // and (TIM9::channel<PA1>() == TIM9::Channel::_2) // warning [-Wreturn-type]

      and (TIM10::channel<PB8>() == TIM10::Channel::_1)
      and (TIM10::channel<PF6>() == TIM10::Channel::_1)
      // and (TIM10::channel<PA1>() == TIM10::Channel::_1) // warning [-Wreturn-type]

      and (TIM11::channel<PB9>() == TIM11::Channel::_1)
      and (TIM11::channel<PF7>() == TIM11::Channel::_1);
      // and (TIM11::channel<PA1>() == TIM10::Channel::_1); // warning [-Wreturn-type]
}

bool AltFunc ()
{
   return (TIM1::AltFunc<PA8> () == GPIO_ral::AF::_1)
      and (TIM2::AltFunc<PA1> () == GPIO_ral::AF::_1)
      and (TIM3::AltFunc<PA6> () == GPIO_ral::AF::_2)
      and (TIM4::AltFunc<PB6> () == GPIO_ral::AF::_2)
      and (TIM5::AltFunc<PA0> () == GPIO_ral::AF::_2)
      and (TIM8::AltFunc<PC6> () == GPIO_ral::AF::_3)
      and (TIM9::AltFunc<PC7> () == GPIO_ral::AF::_3)
      and (TIM10::AltFunc<PB9>() == GPIO_ral::AF::_3)
      and (TIM11::AltFunc<PB9>() == GPIO_ral::AF::_3);
      // and (TIM9::AltFunc<PC1> () == GPIO_ral::AF::_1); // тест провален

}

int main()
{
   std::cout << '\n'
             << "Тесты класса TIM для STM32F4:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

  
   test ("TIM::counterEnable         ", counterEnable);
   test ("TIM::counterDisable        ", counterDisable);
   test ("TIM::isCount               ", isCount);
   test ("TIM::autoReloadEnable      ", autoReloadEnable);
   test ("TIM::getCounter            ", getCounter);
   test ("TIM::clearCounter          ", clearCounter);
   test ("TIM::externalClockEnable   ", externalClockEnable);
   test ("TIM::externalClockDisable  ", externalClockDisable);
   test ("TIM::setAutoReloadValue    ", setAutoReloadValue);
   test ("TIM::setPrescaller         ", setPrescaller);
   test ("TIM::mainOutputEnable      ", mainOutputEnable);
   test ("TIM::preloadEnable         ", preloadEnable);
   test ("TIM::preloadDisable        ", preloadDisable);
   test ("TIM::compareEnable         ", compareEnable);
   test ("TIM::compareDisable        ", compareDisable);
   test ("TIM::compareToggle         ", compareToggle);
   test ("TIM::isCompareEnable       ", isCompareEnable);
   test ("TIM::setCompareValue       ", setCompareValue);
   test ("TIM::setSlaveMode          ", setSlaveMode);
   test ("TIM::setTrigger            ", setTrigger);
   test ("TIM::setOnePulseMode       ", setOnePulseMode);
   test ("TIM::setExtTriggerPolarity ", setExtTriggerPolarity);
   test ("TIM::selectCompareMode     ", selectCompareMode);
   test ("TIM::setCompareMode        ", setCompareMode);
   test ("TIM::setPolarity           ", setPolarity);
   test ("TIM::channel               ", channel);
   test ("TIM::AltFunc               ", AltFunc);
   
   std::cout << std::endl;
}
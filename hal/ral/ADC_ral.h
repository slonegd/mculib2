#pragma once

#if defined(STM32F030x6)
#include "ADC_F0_bits.h"
#elif defined(STM32F405xx)
#include "ADC_F4_bits.h"
#include "bitbanding.h"
#endif



template <uint32_t ADCadr>
class ADCx : private ADC_ral::SR_t,
#if defined(STM32F405xx)
             private ADC_ral::CR1_t,
             private ADC_ral::CR2_t,
             private ADC_ral::SMPR1_t,
             private ADC_ral::SMPR2_t,
             private ADC_ral::JOFR1_t,
             private ADC_ral::JOFR2_t,
             private ADC_ral::JOFR3_t,
             private ADC_ral::JOFR4_t,
             private ADC_ral::HTR_t,
             private ADC_ral::LTR_t,
             private ADC_ral::SQR1_t,
             private ADC_ral::SQR2_t,
             private ADC_ral::SQR3_t,
             private ADC_ral::JSQR_t,
             private ADC_ral::JDR1_t,
             private ADC_ral::JDR2_t,
             private ADC_ral::JDR3_t,
             private ADC_ral::JDR4_t,
#elif defined(STM32F030x6)
             private ADC_ral::IER_t,
             private ADC_ral::CR_t,
             private ADC_ral::CFGR1_t,
             private ADC_ral::CFGR2_t,
             private ADC_ral::SMPR_t,
             private ADC_ral::Reserved<2>,
             private ADC_ral::TR_t,
             private ADC_ral::Reserved<1>,
             private ADC_ral::CHSELR_t,
             private ADC_ral::Reserved<5>,
#endif
             private ADC_ral::DR_t
{
public:
   static const uint32_t Base = ADCadr;

   using Channels = DMA_ral::CR_t::Channels;


   void makeDebugVar() { status().bits.res1 = 0; }
   static void ClockEnable() { RCC->APB2ENR |= ClkEnMask; }



protected:
#define MakeRef(Reg,Ref) ADC_ral::Reg& Ref() { return (ADC_ral::Reg&) *(uint32_t*)(Base + ADC_ral::Reg::Offset); }
   static volatile MakeRef(SR_t,    status);
/*   static volatile MakeRef(CR1_t,   conf1);
   static volatile MakeRef(CR2_t,   conf2);
   static volatile MakeRef(SMPR1_t, sampleTime1);
   static volatile MakeRef(SMPR2_t, sampleTime2);
   static volatile MakeRef(JOFR1_t, jof1);
   static volatile MakeRef(JOFR2_t, jof2);
   static volatile MakeRef(JOFR3_t, jof3);
   static volatile MakeRef(JOFR4_t, jof4);
   static volatile MakeRef(HTR_t,   ht);
   static volatile MakeRef(LTR_t,   lt);
   static volatile MakeRef(SQR1_t,  sq1);
   static volatile MakeRef(SQR2_t,  sq2);
   static volatile MakeRef(SQR3_t,  sq3);
   static volatile MakeRef(JDR1_t,  jd1);
   static volatile MakeRef(JDR2_t,  jd2);
   static volatile MakeRef(JDR3_t,  jd3);
   static volatile MakeRef(JDR4_t,  jd4);
   static volatile MakeRef(DR_t,    data);
*/
#undef MakeRef


private:
#if defined(STM32F405xx)
   static constexpr uint32_t ClkEnMask =
      Base == ADC1_BASE ? RCC_APB2ENR_ADC1EN_Msk :
      Base == ADC2_BASE ? RCC_APB2ENR_ADC2EN_Msk :
      Base == ADC3_BASE ? RCC_APB2ENR_ADC3EN_Msk : 0;
#elif defined(STM32F030x6)
   static constexpr uint32_t ClkEnMask = RCC_APB2ENR_ADCEN_Msk;
#endif
};



#undef ADC1
using ADC1 = ADCx<ADC1_BASE>;

#if defined(STM32F405xx)
   #undef ADC2
   using ADC2 = ADCx<ADC2_BASE>;
   #undef ADC3
   using ADC3 = ADCx<ADC3_BASE>;
#endif





#include "ADC_impl.h"


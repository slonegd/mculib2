/******************************************************************************
 *    ADCaverage постоянно шлёт в буфер по DMA значения с АЦП
 *    метод compute вычисляет сумму буфера
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ADC_ral.h"
#include "DMA_ral.h"
#include "constDef.h"



template<class ADC_, class PIN, uint16_t bufSize,
         class DMA_ = typename ADC_ral::DefaultStream<ADC_>::Type >
class ADCaverage : ADC_
{
public:
   using Channels = DMA_ral::CR_t::Channels;


   inline void Enable() {}
   inline void Disable() {}
   inline uint32_t compute()
   {
      sum = 0;
      for (uint16_t i = 0; i < bufSize; i++)
         sum += buf[i];
      return sum;
   }
   inline uint32_t get() { return sum; }
   ADCaverage() : buf{0}
   {
      static_assert (
         ADC_ral::PinEnabled<ADC_,PIN>(),
         "Вывод контроллера не поддерживает функцию АЦП"
      );
      static_assert (
         ADC_ral::DMAenabled<ADC_,DMA_>(),
         "Поток ДМА не работает с этим АЦП"
      );
      ADC_::ClockEnable();
   }



private:
   uint16_t buf[bufSize];
   uint32_t sum;
   //static const Channels channel = ADC_ral::DMAchannel<ADC_>();
   static const int8_t ADCin = ADC_ral::ADCin<ADC_,PIN>();
   
};






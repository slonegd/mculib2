/******************************************************************************
 *    ADCaverageFull постоянно шлёт в буфер по DMA значения с АЦП
 *    DoubleFiltrADC складывает среднее в новый буфер, у которого тоже 
 *       считает среднее
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <iterator>
#include "adc_periph.h"
#include "DMA.h"
#include "interrupt.h"
#include "pins_variadic.h"
#include "meta.h"
#include "ring_buffer.h"


// класс, который по DMA шлёт данные с АЦП в буфер постоянно циклически
// ADC_ - конкретный ADC класс,
// PIN - выводы микроконтроллера, с которого преобразование
// bufSize - размер буфера в word (2 байта)
// DMA_ - поток ДМА (параметр опционный)
template <
   class ADC_,
   uint16_t bufSize = 16,
   class DMA_ = typename ADC_::DefaultStream,
   class ... PIN
>
class ADCaverageFull : Interrupting
{
   uint16_t buf[bufSize * sizeof...(PIN)];
   uint32_t sum[sizeof...(PIN)];
   uint32_t avg[sizeof...(PIN)];
   uint32_t mul;
   uint32_t div;
public:
   using Clock      = typename ADC_::Clock;
   using Resolution = typename ADC_::Resolution;
   using SampleTime = typename ADC_::SampleTime;
   using DMAstream  = DMA_;

 
   ADCaverageFull (
      uint32_t mul = 1, // mul - множитель для вычисления среднего
      uint32_t div = 1, // div - частное для вычисления среднего
      Clock clock = Clock::PCLKdiv4,
      Resolution resolution = Resolution::_12bits,
      SampleTime sampleTime = SampleTime::Default
   );
   ADCaverageFull& withMultipler    (uint32_t);
   ADCaverageFull& withDivider      (uint32_t);
   ADCaverageFull& changeResolution (Resolution);
   ADCaverageFull& changeSampleTime (SampleTime);
   ADCaverageFull& withInterrupt();

   /// для единственного входа
   auto get() const { return avg[0]; }
   operator uint32_t() const { return avg[0]; }

   /// если входов несколько
   template <class PIN_>
   auto get() const;

   void computeSum();
   void computeAvg();
   

private:
   void init (Clock, Resolution, SampleTime);
   void interrupt() override
   {
      ADC_::disable();
      computeSum();
      computeAvg();
      ADC_::enable();
      ADC_::start();
   }
  //  static constexpr int8_t channel = ADC_ral::ADCchannel<ADC_,PIN>();
};


/// хелперы, чтоб не указывать значения по умолчанию
template <class ADC_, class ... PIN>
using ADCaverage = ADCaverageFull<ADC_, 16, typename ADC_::DefaultStream, PIN...>;

template <uint16_t bufSize, class ADC_, class ... PIN>
using ADCaverageSized = ADCaverageFull<ADC_, bufSize, typename ADC_::DefaultStream, PIN...>;





/// дполнительно к прошлому классу добавляет фильтрацию среднего скользящего
template<class ADC_, std::size_t n, class ... PIN>
class DoubleFiltrADC : Interrupting
{
   using ValueType = uint16_t;
   SumRingBuffer<n, ValueType> buffer [sizeof...(PIN)];
   ValueType                   avg    [sizeof...(PIN)];
   using ADCavg = ADCaverage<ADC_,PIN...>;
   ADCavg adc {};
public:
   DoubleFiltrADC()
   {
      adc.withInterrupt();
      // adc.changeSampleTime (ADCavg::SampleTime::_3CLK);
      Interrupt<typename ADCavg::DMAstream>::subscribe (this);
   }
   auto     get()       { return buffer[0].getAvg(); }   
   operator ValueType() { return buffer[0].getAvg(); }

   template <class PIN_>
   auto get() { return buffer[position_v<PIN_, PIN...> - 1].getAvg(); }
   
private:
   void interrupt() override
   {
      ( buffer [position_v<PIN, PIN...> - 1]
         .pushAndCompute (adc.template get<PIN>())
        , ...
      );
   }
};




#include "adc_src.h"
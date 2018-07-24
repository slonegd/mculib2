/******************************************************************************
 *    ADCaverage постоянно шлёт в буфер по DMA значения с АЦП
 *    метод computeSum вычисляет сумму буфера
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ADC.h"
#include "DMA.h"


// класс, который по DMA шлёт данные с АЦП в буфер постоянно циклически
// ADC_ - конкретный ADC класс,
// PIN - вывод микроконтроллера, с которого преобразование
// bufSize - размер буфера в word (2 байта)
// DMA_ - поток ДМА (параметр опционный)
template <
   class ADC_,
   class PIN,
   uint16_t bufSize = 16,
   class DMA_ = typename ADC_ral::DefaultStream<ADC_>::Type
>
class ADCaverage// : private ADC_
{
public:
   using Clock      = typename ADC_::Clock;
   using Resolution = typename ADC_::Resolution;
   using SampleTime = typename ADC_::SampleTime;
   // using Channels   = typename DMA_ral::Channels;

   // mul - множитель для вычисления среднего
   // div - частное для вычисления среднего
   ADCaverage (uint32_t mul = 1, uint32_t div = 1,
               Clock clock = Clock::PCLKdiv4,
               Resolution resolution = Resolution::_12bits,
               SampleTime sampleTime = SampleTime::Default);
   ADCaverage& withMultipler (uint32_t val) { mul = val; return this; }
   ADCaverage& withDivider   (uint32_t val) { div = val; return this; }
   ADCaverage& changeResolution (Resolution val)
   {
      ADC_::disable();
      ADC_::setResolution (val);
      ADC_::enable();
      return this;
   }
   ADCaverage& changeSampleTime (SampleTime val)
   {
      ADC_::disable();
      ADC_::setSampleTime (val);
      ADC_::enable();
      return this;
   }
   // расчитывает сумму всех элементов буфера
   uint32_t computeSum();
   // возвращает ранее рассчитаную сумму буфера
   uint32_t getSum()         { return sum; }
   uint32_t computeAverage() { avg = computeSum() * mul / div / bufSize; return avg; }
   uint32_t getAverage()     { return avg; }



private:
   uint16_t buf[bufSize];
   uint32_t sum;
   uint32_t avg;
   uint32_t mul;
   uint32_t div;
   static constexpr int8_t channel = ADC_ral::ADCchannel<ADC_,PIN>();
   void init (Clock clock, Resolution resolution, SampleTime sampleTime);
};







// PUBLIC
template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
ADCaverage<ADC_, PIN, bufSize, DMA_>::
ADCaverage (uint32_t mul, uint32_t div, Clock clock, Resolution resolution, SampleTime sampleTime)
   : buf{0}, avg(0), mul(mul), div(div)

{
   static_assert (
      ADC_ral::PinEnabled<ADC_,PIN>(),
      "Вывод контроллера не поддерживает функцию АЦП"
   );
   static_assert (
      ADC_ral::DMAenabled<ADC_,DMA_>(),
      "Поток ДМА не работает с этим АЦП"
   );
   init(clock, resolution, sampleTime);
}




template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
uint32_t ADCaverage<ADC_, PIN, bufSize, DMA_>::computeSum()
{
   sum = 0;
   for (const auto n : buf)
      sum += n;
   return sum;
}




// PRIVATE
template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
void ADCaverage<ADC_, PIN, bufSize, DMA_>::
init(Clock clock, Resolution resolution, SampleTime sampleTime)
{
   CONFIGURE_PIN (PIN, AnalogInput);

   ADC_::clockEnable();
   ADC_::setClock (clock);
   ADC_::setResolution (resolution);
   #if defined(STM32F030x6)
      ADC_::setSampleTime (sampleTime);
   #elif defined(STM32F405xx)
      ADC_::template setSampleTime<channel> (sampleTime);
   #endif
   ADC_::setContinuousMode();
   #if defined(STM32F030x6)
      ADC_::setChannel (channel);
   #endif
   ADC_::DMAenable();
   ADC_::setCircularDMA();

   DMA_::ClockEnable();
   DMA_::SetMemoryAdr ( (uint32_t)buf );
   DMA_::SetPeriphAdr ( ADC_::getDataAdr() );
   DMA_::SetQtyTransactions (bufSize);
   typename DMA_::Configure_t conf;
   conf.dataDir = DMA_::DataDirection::PerToMem;
   conf.memSize = DMA_::DataSize::word16;
   conf.perSize = DMA_::DataSize::word16;
   conf.memInc = true;
   conf.perInc = false;
   conf.circularMode = true;
   #if defined(STM32F405xx)
      conf.channel = ADC_::DMAchannel();
   #endif
   DMA_::Configure (conf);

   DMA_::Enable();
   ADC_::enable();
   ADC_::start();
}


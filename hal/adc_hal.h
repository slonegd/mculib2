/******************************************************************************
 *    ADCaverage постоянно шлёт в буфер по DMA значения с АЦП
 *    метод compute вычисляет сумму буфера
 */////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ADC_ral.h"
#include "DMA_ral.h"


// класс, который по DMA шлёт данные с АЦП в буфер постоянно циклически
// ADC_ - конкретный ADC класс,
// PIN - вывод микроконтроллера, с которого преобразование
// bufSize - размер буфера в word (2 байта)
// DMA_ - поток ДМА (параметр опционный)
template<class ADC_, class PIN, uint16_t bufSize,
         class DMA_ = typename ADC_ral::DefaultStream<ADC_>::Type >
class ADCaverage : private ADC_
{
public:
   using Channels = DMA_ral::CR_t::Channels;
   using Clock = typename ADC_::Clock;
   using Resolution = typename ADC_::Resolution;
   using SampleTime = typename ADC_::SampleTime;

   // mul - множитель для вычисления среднего
   // div - частное для вычисления среднего
   ADCaverage (uint32_t mul = 1, uint32_t div = 1,
               Clock clock = Clock::PCLKdiv4,
               Resolution resolution = Resolution::_12bits,
               SampleTime sampleTime = SampleTime::_239_5_ADCclockCicle);
   void Enable();
   void Disable();
   // расчитывает сумму всех элементов буфера
   uint32_t computeSum();
   // возвращает ранее рассчитаную сумму буфера
   uint32_t getSum()    { return sum; }
   uint32_t computeAverage() { avg = computeSum() * mul / div / bufSize; return avg; }
   uint32_t getAverage()     { return avg; }



private:
   uint16_t buf[bufSize];
   uint32_t sum;
   uint32_t avg;
   uint32_t mul;
   uint32_t div;
   static const int8_t ADCin = ADC_ral::ADCin<ADC_,PIN>();
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
void ADCaverage<ADC_, PIN, bufSize, DMA_>::Enable()
{
   if (ADC_::IsReady())
      ADC_::SetBusy();
   ADC_::Enable();
   while ( !ADC_::IsReady() ) { }
}


template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
void ADCaverage<ADC_, PIN, bufSize, DMA_>::Disable()
{
   ADC_::Stop();
   while ( ADC_::IsStoping() ) { }
   ADC_::Disable();
   while ( !ADC_::IsDisable() ) { }
}


template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
uint32_t ADCaverage<ADC_, PIN, bufSize, DMA_>::computeSum()
{
   sum = 0;
   for (uint16_t i = 0; i < bufSize; i++)
      sum += buf[i];
   return sum;
}




// PRIVATE
template<class ADC_, class PIN, uint16_t bufSize, class DMA_>
void ADCaverage<ADC_, PIN, bufSize, DMA_>::
init(Clock clock, Resolution resolution, SampleTime sampleTime)
{
   PIN::Port::ClockEnable();
   CONFIGURE_PIN (PIN, AnalogInput);

   ADC_::ClockEnable();
   ADC_::SetClock (clock);
   ADC_::SetResolution (resolution);
   ADC_::SetSampleTime (sampleTime);
   ADC_::SetContinuousMode();
   ADC_::SetChannel (ADCin);
   ADC_::DMAenable();
   ADC_::SetCircularDMA();

   DMA_::ClockEnable();
   DMA_::SetMemoryAdr ( (uint32_t)buf );
   DMA_::SetPeriphAdr ( (uint32_t) &(ADC_::data()) );
   DMA_::SetQtyTransactions (bufSize);
   typename DMA_::Configure_t conf;
   conf.dataDir = DMA_::DataDirection::PerToMem;
   conf.memSize = DMA_::DataSize::word16;
   conf.perSize = DMA_::DataSize::word16;
   conf.memInc = true;
   conf.perInc = false;
   conf.circularMode = true;
   DMA_::Configure (conf);

   Enable();
   ADC_::Start();
   DMA_::Enable();
}









#include "adc.h"


///////////////////////////////////////////////////////////////////////////////
//
//    ADCaverageFull
//
///////////////////////////////////////////////////////////////////////////////

// PUBLIC
template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::
ADCaverageFull (uint32_t mul, uint32_t div, Clock clock, Resolution resolution, SampleTime sampleTime)
   : buf{0}, avg{0}, mul{mul}, div{div}

{
   static_assert (
      (ADC_ral::PinEnabled<ADC_,PIN>() and ...),
      "Вывод контроллера не поддерживает функцию АЦП"
   );
   static_assert (
      ADC_ral::DMAenabled<ADC_,DMA_>(),
      "Поток ДМА не работает с этим АЦП"
   );
   init(clock, resolution, sampleTime);
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>& 
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::withMultipler (uint32_t val)
{
   mul = val;
   return *this;
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>&
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::withDivider (uint32_t val)
{
   div = val;
   return *this;
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>&
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::
changeResolution (Resolution val)
{
   ADC_::disable();
   ADC_::setResolution (val);
   ADC_::enable();
   return *this;
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>&
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::
changeSampleTime (SampleTime val)
{
   ADC_::disable();
   ADC_::setSampleTime (val);
   ADC_::enable();
   return *this;
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>&
ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::withInterrupt()
{
   Interrupt<DMA_>::subscribe (this);
   DMA_::EnableTransferCompleteInterrupt();
   NVIC_EnableIRQ (DMA_::IRQn());
   return *this;
}


template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
template <class PIN_>
auto ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::get() const
{
   static_assert (
      position_v<PIN_, PIN...> != -1,
      "указанный вывод не из списка шаблонных параметров класса"
   );
   return avg[position_v<PIN_, PIN...>];
}




template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
void ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::computeSum()
{
   std::fill (std::begin(sum), std::end(sum), 0);
   for (std::size_t i {0}; i < std::size(buf); ++i)
      sum [i % sizeof...(PIN)] += buf[i];
}



template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
void ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::computeAvg()
{
   for (std::size_t i {0}; i < std::size(sum); ++i)
      avg[i] = sum[i] / bufSize * mul / div;
}




// PRIVATE
template<class ADC_, uint16_t bufSize, class DMA_, class ... PIN>
void ADCaverageFull<ADC_, bufSize, DMA_, PIN...>::
init(Clock clock, Resolution resolution, SampleTime sampleTime)
{
   (PIN::template configure <PinConf_t::AnalogInput> () , ...);

   ADC_::clockEnable();
   ADC_::setClock (clock);
   ADC_::setResolution (resolution);
   #if defined(STM32F0)
      ADC_::setSampleTime (sampleTime);
   #elif defined(STM32F4)
      (ADC_::template setSampleTime<ADC_ral::ADCchannel<ADC_,PIN>()> (sampleTime) , ...);
   #endif
   ADC_::setContinuousMode();
   #if defined(STM32F0)
      (ADC_::setChannel (ADC_ral::ADCchannel<ADC_,PIN>()) , ...);
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
   #if defined(STM32F4)
      conf.channel = ADC_::DMAchannel();
   #endif
   DMA_::Configure (conf);

   DMA_::Enable();
   ADC_::enable();
   ADC_::start();
}



///////////////////////////////////////////////////////////////////////////////
//
//    DoubleFiltrADC
//
///////////////////////////////////////////////////////////////////////////////

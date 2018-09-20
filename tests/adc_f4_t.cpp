#define STM32F405xx

#include "RCC.h"
#include "adc_periph.h"
#include <iostream>
#include <type_traits>

struct MockPointer
{
   static ADC1::CMSIS_type* p;
   static auto get() { return reinterpret_cast<ADC1::periph_type*>(p); }
};
ADC1::CMSIS_type mock;
ADC1::CMSIS_type* MockPointer::p = &mock;
using TADC = template_ADC<0, MockPointer>;

// тесты возвращают true, если прошли
bool enable()
{
   mock.CR2 = 0;
   TADC::enable();
   return mock.CR2 & ADC_CR2_ADON_Msk; 
}


bool disable()
{
   mock.CR2 |= ADC_CR2_ADON_Msk;
   TADC::disable();
   return (mock.CR2 & ADC_CR2_ADON_Msk) == 0; 
}

bool is_disable()
{
   bool good {true};
   mock.CR2 = 0;
   good &= TADC::is_disable();
   mock.CR2 |= ADC_CR2_ADON_Msk;
   good &= not TADC::is_disable();

   return good; 
}

bool start()
{
   mock.CR2 = 0;
   TADC::start();
   return mock.CR2 & ADC_CR2_SWSTART_Msk;
}

bool DMAenable()
{
   mock.CR2 = 0;
   TADC::DMAenable();
   return mock.CR2 & ADC_CR2_DMA_Msk;
}

bool setCircularDMA()
{
   mock.CR2 = 0;
   TADC::setCircularDMA();
   return mock.CR2 & ADC_CR2_DDS_Msk;
}

bool setContinuousMode()
{
   mock.CR2 = 0;
   TADC::setContinuousMode();
   return mock.CR2 & ADC_CR2_CONT_Msk;
}

bool setResolution()
{
   bool good {true};
   mock.CR1 = 0;
   TADC::set (TADC::Resolution::_6bits);
   good &= mock.CR1 == (ADC_CR1_RES_0 | ADC_CR1_RES_1);
   TADC::set (TADC::Resolution::_12bits);
   good &= mock.CR1 == 0;
   TADC::set (TADC::Resolution::_8bits);
   good &= mock.CR1 == ADC_CR1_RES_1;
   TADC::set (TADC::Resolution::_10bits);
   good &= mock.CR1 == ADC_CR1_RES_0;
   return good;
}

bool getDataAdr()
{
   return TADC::getDataAdr() == reinterpret_cast<size_t>(&mock.DR);
}

bool setSampleTime()
{
   bool good {true};
   mock.SMPR1 = 0;
   mock.SMPR2 = 0;

   TADC::set<0>(TADC::SampleTime::_15CLK);
   good &=     (mock.SMPR2 & ADC_SMPR2_SMP0_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP0_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP0_2);

   TADC::set<1>(TADC::SampleTime::_28CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and     (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::set<1>(TADC::SampleTime::_84CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and     (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::set<1>(TADC::SampleTime::_3CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::set<2>(TADC::SampleTime::_56CLK);
   good &=     (mock.SMPR2 & ADC_SMPR2_SMP2_0)
       and     (mock.SMPR2 & ADC_SMPR2_SMP2_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP2_2);

   TADC::set<10>(TADC::SampleTime::_112CLK);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP10_0)
       and not (mock.SMPR1 & ADC_SMPR1_SMP10_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP10_2);

   TADC::set<11>(TADC::SampleTime::_144CLK);
   good &= not (mock.SMPR1 & ADC_SMPR1_SMP11_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP11_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP11_2);

   TADC::set<12>(TADC::SampleTime::_480CLK);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP12_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_2);

   TADC::set<18>(TADC::SampleTime::Default);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP12_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_2);

   // TADC::set<19>(TADC::SampleTime::Default); // ошибка компиляции

   return good;
}


bool setRegularSequenceOrder()
{
   bool good {true};
   mock.SQR1 = 0;
   mock.SQR2 = 0;
   mock.SQR3 = 0;

   TADC::setRegularSequenceOrder<1,0>();
   good &= not (mock.SQR3 & ADC_SQR3_SQ1_0)
       and not (mock.SQR3 & ADC_SQR3_SQ1_1)
       and not (mock.SQR3 & ADC_SQR3_SQ1_2)
       and not (mock.SQR3 & ADC_SQR3_SQ1_3)
       and not (mock.SQR3 & ADC_SQR3_SQ1_4);

   TADC::setRegularSequenceOrder<1,1>();
   good &=     (mock.SQR3 & ADC_SQR3_SQ1_0)
       and not (mock.SQR3 & ADC_SQR3_SQ1_1)
       and not (mock.SQR3 & ADC_SQR3_SQ1_2)
       and not (mock.SQR3 & ADC_SQR3_SQ1_3)
       and not (mock.SQR3 & ADC_SQR3_SQ1_4);

   TADC::setRegularSequenceOrder<1,2>();
   good &= not (mock.SQR3 & ADC_SQR3_SQ1_0)
       and     (mock.SQR3 & ADC_SQR3_SQ1_1)
       and not (mock.SQR3 & ADC_SQR3_SQ1_2)
       and not (mock.SQR3 & ADC_SQR3_SQ1_3)
       and not (mock.SQR3 & ADC_SQR3_SQ1_4);

   TADC::setRegularSequenceOrder<10,3>();
   good &=     (mock.SQR2 & ADC_SQR2_SQ10_0)
       and     (mock.SQR2 & ADC_SQR2_SQ10_1)
       and not (mock.SQR2 & ADC_SQR2_SQ10_2)
       and not (mock.SQR2 & ADC_SQR2_SQ10_3)
       and not (mock.SQR2 & ADC_SQR2_SQ10_4);

   TADC::setRegularSequenceOrder<13,4>();
   good &= not (mock.SQR1 & ADC_SQR1_SQ13_0)
       and not (mock.SQR1 & ADC_SQR1_SQ13_1)
       and     (mock.SQR1 & ADC_SQR1_SQ13_2)
       and not (mock.SQR1 & ADC_SQR1_SQ13_3)
       and not (mock.SQR1 & ADC_SQR1_SQ13_4);

   // TADC::setRegularSequenceOrder<0,0>();  // ошибка компиляции
   // TADC::setRegularSequenceOrder<17,0>(); // ошибка компиляции
   // TADC::setRegularSequenceOrder<1,19>(); // ошибка компиляции

   return good;
}

bool setRegularSequenceLength()
{
   bool good {true};
   mock.SQR1 = 0;
   TADC::setRegularSequenceLength<2>();
   good &=     (mock.SQR1 & ADC_SQR1_L_0)
       and not (mock.SQR1 & ADC_SQR1_L_1)
       and not (mock.SQR1 & ADC_SQR1_L_2)
       and not (mock.SQR1 & ADC_SQR1_L_3);

   TADC::setRegularSequenceLength<1>();
   good &= not (mock.SQR1 & ADC_SQR1_L_0)
       and not (mock.SQR1 & ADC_SQR1_L_1)
       and not (mock.SQR1 & ADC_SQR1_L_2)
       and not (mock.SQR1 & ADC_SQR1_L_3);

   TADC::setRegularSequenceLength<16>();
   good &=     (mock.SQR1 & ADC_SQR1_L_0)
       and     (mock.SQR1 & ADC_SQR1_L_1)
       and     (mock.SQR1 & ADC_SQR1_L_2)
       and     (mock.SQR1 & ADC_SQR1_L_3);

   // TADC::setRegularSequenceLength<0>();  // ошибка компиляции
   // TADC::setRegularSequenceLength<17>(); // ошибка компиляции

   return good;
}

bool setScanMode()
{
   mock.CR1 = 0;
   TADC::setScanMode();
   return mock.CR1 & ADC_CR1_SCAN_Msk;
}

bool DefaultStream()
{
   return std::is_same_v <ADC1::DefaultStream, DMA2stream0>
      and std::is_same_v <ADC2::DefaultStream, DMA2stream2>
      and std::is_same_v <ADC3::DefaultStream, DMA2stream1>;
}

bool DMAenabled()
{
   return     ADC1::DMAenabled<DMA2stream0>()
      and     ADC1::DMAenabled<DMA2stream4>()
      and not ADC1::DMAenabled<DMA2stream1>()
      and not ADC1::DMAenabled<DMA1stream0>()
      and     ADC2::DMAenabled<DMA2stream2>()
      and     ADC2::DMAenabled<DMA2stream3>()
      and not ADC2::DMAenabled<DMA2stream0>()
      and not ADC2::DMAenabled<DMA1stream2>()
      and     ADC3::DMAenabled<DMA2stream0>()
      and     ADC3::DMAenabled<DMA2stream1>()
      and not ADC3::DMAenabled<DMA2stream2>()
      and not ADC3::DMAenabled<DMA1stream0>();
}

bool channel()
{
   return ADC1::channel<PA0>() == 0
      and ADC1::channel<PA1>() == 1
      and ADC1::channel<PA2>() == 2
      and ADC1::channel<PA3>() == 3
      and ADC1::channel<PA4>() == 4
      and ADC1::channel<PA5>() == 5
      and ADC1::channel<PA6>() == 6
      and ADC1::channel<PA7>() == 7
      and ADC1::channel<PB0>() == 8
      and ADC1::channel<PB1>() == 9
      and ADC1::channel<PC0>() == 10
      and ADC1::channel<PC1>() == 11
      and ADC1::channel<PC2>() == 12
      and ADC1::channel<PC3>() == 13
      and ADC1::channel<PC4>() == 14
      and ADC1::channel<PC5>() == 15
      and ADC1::channel<PC6>() == 255

      and ADC2::channel<PA0>() == 0
      and ADC2::channel<PA1>() == 1
      and ADC2::channel<PA2>() == 2
      and ADC2::channel<PA3>() == 3
      and ADC2::channel<PA4>() == 4
      and ADC2::channel<PA5>() == 5
      and ADC2::channel<PA6>() == 6
      and ADC2::channel<PA7>() == 7
      and ADC2::channel<PB0>() == 8
      and ADC2::channel<PB1>() == 9
      and ADC2::channel<PC0>() == 10
      and ADC2::channel<PC1>() == 11
      and ADC2::channel<PC2>() == 12
      and ADC2::channel<PC3>() == 13
      and ADC2::channel<PC4>() == 14
      and ADC2::channel<PC5>() == 15
      and ADC2::channel<PA8>() == 255

      and ADC3::channel<PA0>() == 0
      and ADC3::channel<PA1>() == 1
      and ADC3::channel<PA2>() == 2
      and ADC3::channel<PA3>() == 3
      and ADC3::channel<PF6>() == 4
      and ADC3::channel<PF7>() == 5
      and ADC3::channel<PF8>() == 6
      and ADC3::channel<PF9>() == 7
      and ADC3::channel<PF10>()== 8
      and ADC3::channel<PF3>() == 9
      and ADC3::channel<PC0>() == 10
      and ADC3::channel<PC1>() == 11
      and ADC3::channel<PC2>() == 12
      and ADC3::channel<PC3>() == 13
      and ADC3::channel<PF4>() == 14
      and ADC3::channel<PF5>() == 15
      and ADC3::channel<PA4>() == 255;
}

bool PINenabled()
{
   return     ADC1::PINenabled<PA0>()
      and not ADC1::PINenabled<PC6>()
      and     ADC2::PINenabled<PB0>()
      and not ADC2::PINenabled<PA8>()
      and     ADC3::PINenabled<PF5>()
      and not ADC3::PINenabled<PA4>();
}

bool DMAchannel()
{
   return ADC1::DMAchannel() == ADC1::Channels::_0
      and ADC2::DMAchannel() == ADC1::Channels::_1
      and ADC3::DMAchannel() == ADC1::Channels::_2
      and TADC::DMAchannel() == ADC1::Channels::_0;
}




int main()
{
   std::cout << '\n'
             << "Тесты класса ADC для STM32F4:" << std::endl;

   auto test = [](auto s, auto f){
      std::cout << s << (f() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   };

   test ("ADC::enable                  ", enable);
   test ("ADC::disable                 ", disable);
   test ("ADC::is_disable              ", is_disable);
   test ("ADC::start                   ", start);
   test ("ADC::DMAenable               ", DMAenable);
   test ("ADC::setCircularDMA          ", setCircularDMA);
   test ("ADC::setContinuousMode       ", setContinuousMode);
   test ("ADC::setResolution           ", setResolution);
   test ("ADC::getDataAdr              ", getDataAdr);
   test ("ADC::setSampleTime           ", setSampleTime);
   test ("ADC::setRegularSequenceOrder ", setRegularSequenceOrder);
   test ("ADC::setScanMode             ", setScanMode);
   test ("ADC::DefaultStream           ", DefaultStream);
   test ("ADC::channel                 ", channel);
   test ("ADC::PINenabled              ", PINenabled);
   test ("ADC::DMAenabled              ", DMAenabled);
   std::cout << std::endl;
}
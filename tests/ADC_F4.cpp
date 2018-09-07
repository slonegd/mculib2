#define STM32F405xx

#include "RCC.h"
#include "ADC.h"
#include <iostream>
#include <type_traits>

struct MockPointer
{
   static ADC_TypeDef * p;
   static auto get() { return reinterpret_cast<ADC_t<0>*>(p); }
};
ADC_TypeDef mock;
ADC_TypeDef* MockPointer::p = &mock;
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

bool is_disable_1()
{
   mock.CR2 = 0;
   return TADC::is_disable(); 
}

bool is_disable_2()
{
   mock.CR2 |= ADC_CR2_ADON_Msk;
   return not TADC::is_disable();
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
   TADC::setResolution (TADC::Resolution::_6bits);
   good &= mock.CR1 == (ADC_CR1_RES_0 | ADC_CR1_RES_1);
   TADC::setResolution (TADC::Resolution::_12bits);
   good &= mock.CR1 == 0;
   TADC::setResolution (TADC::Resolution::_8bits);
   good &= mock.CR1 == ADC_CR1_RES_1;
   TADC::setResolution (TADC::Resolution::_10bits);
   good &= mock.CR1 == ADC_CR1_RES_0;
   return good;
}

bool getDataAdr()
{
   return TADC::getDataAdr() == reinterpret_cast<size_t>(&mock.DR);
}

static_assert ( std::is_same_v <ADC1::DefaultStream, DMA2stream0> );
static_assert ( std::is_same_v <ADC2::DefaultStream, DMA2stream2> );
static_assert ( std::is_same_v <ADC3::DefaultStream, DMA2stream1> );

static_assert ( ADC1::DMAenabled<DMA2stream0>() );
static_assert ( ADC1::DMAenabled<DMA2stream4>() );
static_assert ( not ADC1::DMAenabled<DMA2stream1>() );
static_assert ( not ADC1::DMAenabled<DMA1stream0>() );

static_assert ( ADC2::DMAenabled<DMA2stream2>() );
static_assert ( ADC2::DMAenabled<DMA2stream3>() );
static_assert ( not ADC2::DMAenabled<DMA2stream0>() );
static_assert ( not ADC2::DMAenabled<DMA1stream2>() );

static_assert ( ADC3::DMAenabled<DMA2stream0>() );
static_assert ( ADC3::DMAenabled<DMA2stream1>() );
static_assert ( not ADC3::DMAenabled<DMA2stream2>() );
static_assert ( not ADC3::DMAenabled<DMA1stream0>() );

static_assert ( ADC1::ADCchannel<PA0>() == 0  );
static_assert ( ADC1::ADCchannel<PA1>() == 1  );
static_assert ( ADC1::ADCchannel<PA2>() == 2  );
static_assert ( ADC1::ADCchannel<PA3>() == 3  );
static_assert ( ADC1::ADCchannel<PA4>() == 4  );
static_assert ( ADC1::ADCchannel<PA5>() == 5  );
static_assert ( ADC1::ADCchannel<PA6>() == 6  );
static_assert ( ADC1::ADCchannel<PA7>() == 7  );
static_assert ( ADC1::ADCchannel<PB0>() == 8  );
static_assert ( ADC1::ADCchannel<PB1>() == 9  );
static_assert ( ADC1::ADCchannel<PC0>() == 10 );
static_assert ( ADC1::ADCchannel<PC1>() == 11 );
static_assert ( ADC1::ADCchannel<PC2>() == 12 );
static_assert ( ADC1::ADCchannel<PC3>() == 13 );
static_assert ( ADC1::ADCchannel<PC4>() == 14 );
static_assert ( ADC1::ADCchannel<PC5>() == 15 );

static_assert ( ADC2::ADCchannel<PA0>() == 0  );
static_assert ( ADC2::ADCchannel<PA1>() == 1  );
static_assert ( ADC2::ADCchannel<PA2>() == 2  );
static_assert ( ADC2::ADCchannel<PA3>() == 3  );
static_assert ( ADC2::ADCchannel<PA4>() == 4  );
static_assert ( ADC2::ADCchannel<PA5>() == 5  );
static_assert ( ADC2::ADCchannel<PA6>() == 6  );
static_assert ( ADC2::ADCchannel<PA7>() == 7  );
static_assert ( ADC2::ADCchannel<PB0>() == 8  );
static_assert ( ADC2::ADCchannel<PB1>() == 9  );
static_assert ( ADC2::ADCchannel<PC0>() == 10 );
static_assert ( ADC2::ADCchannel<PC1>() == 11 );
static_assert ( ADC2::ADCchannel<PC2>() == 12 );
static_assert ( ADC2::ADCchannel<PC3>() == 13 );
static_assert ( ADC2::ADCchannel<PC4>() == 14 );
static_assert ( ADC2::ADCchannel<PC5>() == 15 );

static_assert ( ADC3::ADCchannel<PA0>() == 0  );
static_assert ( ADC3::ADCchannel<PA1>() == 1  );
static_assert ( ADC3::ADCchannel<PA2>() == 2  );
static_assert ( ADC3::ADCchannel<PA3>() == 3  );
static_assert ( ADC3::ADCchannel<PF6>() == 4  );
static_assert ( ADC3::ADCchannel<PF7>() == 5  );
static_assert ( ADC3::ADCchannel<PF8>() == 6  );
static_assert ( ADC3::ADCchannel<PF9>() == 7  );
static_assert ( ADC3::ADCchannel<PF10>()== 8  );
static_assert ( ADC3::ADCchannel<PF3>() == 9  );
static_assert ( ADC3::ADCchannel<PC0>() == 10 );
static_assert ( ADC3::ADCchannel<PC1>() == 11 );
static_assert ( ADC3::ADCchannel<PC2>() == 12 );
static_assert ( ADC3::ADCchannel<PC3>() == 13 );
static_assert ( ADC3::ADCchannel<PF4>() == 14 );
static_assert ( ADC3::ADCchannel<PF5>() == 15 );

static_assert ( ADC1::ADCchannel<PC6>() == 255 );
static_assert ( ADC2::ADCchannel<PA8>() == 255 );
static_assert ( ADC3::ADCchannel<PA4>() == 255 );

static_assert ( ADC1::PINenabled<PA0>() );
static_assert ( not ADC1::PINenabled<PC6>() );

static_assert ( ADC2::PINenabled<PB0>() );
static_assert ( not ADC2::PINenabled<PA8>() );

static_assert ( ADC3::PINenabled<PF5>() );
static_assert ( not ADC3::PINenabled<PA4>() );

bool setSampleTime()
{
   bool good {true};
   mock.SMPR1 = 0;
   mock.SMPR2 = 0;

   TADC::setSampleTime<0>(TADC::SampleTime::_15CLK);
   good &=     (mock.SMPR2 & ADC_SMPR2_SMP0_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP0_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP0_2);

   TADC::setSampleTime<1>(TADC::SampleTime::_28CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and     (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::setSampleTime<1>(TADC::SampleTime::_84CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and     (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::setSampleTime<1>(TADC::SampleTime::_3CLK);
   good &= not (mock.SMPR2 & ADC_SMPR2_SMP1_0)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP1_2);

   TADC::setSampleTime<2>(TADC::SampleTime::_56CLK);
   good &=     (mock.SMPR2 & ADC_SMPR2_SMP2_0)
       and     (mock.SMPR2 & ADC_SMPR2_SMP2_1)
       and not (mock.SMPR2 & ADC_SMPR2_SMP2_2);

   TADC::setSampleTime<10>(TADC::SampleTime::_112CLK);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP10_0)
       and not (mock.SMPR1 & ADC_SMPR1_SMP10_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP10_2);

   TADC::setSampleTime<11>(TADC::SampleTime::_144CLK);
   good &= not (mock.SMPR1 & ADC_SMPR1_SMP11_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP11_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP11_2);

   TADC::setSampleTime<12>(TADC::SampleTime::_480CLK);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP12_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_2);

   TADC::setSampleTime<18>(TADC::SampleTime::Default);
   good &=     (mock.SMPR1 & ADC_SMPR1_SMP12_0)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_1)
       and     (mock.SMPR1 & ADC_SMPR1_SMP12_2);

   // TADC::setSampleTime<19>(TADC::SampleTime::Default); // ошибка компиляции

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

static_assert ( ADC1::DMAchannel() == ADC1::Channels::_0 );
static_assert ( ADC2::DMAchannel() == ADC1::Channels::_1 );
static_assert ( ADC3::DMAchannel() == ADC1::Channels::_2 );
static_assert ( TADC::DMAchannel() == ADC1::Channels::_0 );



int main()
{
   std::cout << '\n' << "Тесты класса ADC для STM32F4:" << std::endl;

   // \033[32mТЕКСТ\033[0m - для цвета
   std::cout << "ADC::enable                  " << (enable()                  ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::disable                 " << (disable()                 ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::is_disable_1            " << (is_disable_1()            ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::is_disable_2            " << (is_disable_2()            ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::start                   " << (start()                   ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::DMAenable               " << (DMAenable()               ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setCircularDMA          " << (setCircularDMA()          ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setContinuousMode       " << (setContinuousMode()       ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setResolution           " << (setResolution()           ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::getDataAdr              " << (getDataAdr()              ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setSampleTime           " << (setSampleTime()           ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setRegularSequenceOrder " << (setRegularSequenceOrder() ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << "ADC::setScanMode             " << (setScanMode()             ? "\033[32mпрошёл\033[0m" : "\033[31mпровален\033[0m") << std::endl;
   std::cout << std::endl;
}


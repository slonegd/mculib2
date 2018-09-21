#define STM32F030x6

#include "RCC.h"
#include "adc_periph.h"
#include <iostream>
#include <type_traits>
#include <thread>

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
   mock.CR = 0;
   std::thread{TADC::enable}.detach();
   while ((mock.CR & ADC_CR_ADEN_Msk) == 0)
   {
   }
   return true;
}

bool disable()
{
   mock.CR = 0;
   std::thread{TADC::disable}.detach();
   while ((mock.CR & ADC_CR_ADSTP_Msk) == 0)
   {
   }
   mock.CR &= ~ADC_CR_ADSTP_Msk;
   while ((mock.CR & ADC_CR_ADDIS_Msk) == 0)
   {
   }
   return true;
}

bool is_disable()
{
   bool good {true};
   mock.CR = 0;
   good &= not TADC::is_disable();
   mock.CR |= ADC_CR_ADDIS_Msk;
   good &= TADC::is_disable();

   return good;
}

bool start()
{
   mock.CR = 0;
   TADC::start();
   return mock.CR & ADC_CR_ADSTART_Msk;
}

bool DMAenable()
{
   mock.CFGR1 = 0;
   TADC::DMAenable();
   return mock.CFGR1 & ADC_CFGR1_DMAEN_Msk;
}

bool setCircularDMA()
{
   mock.CFGR1 = 0;
   TADC::setCircularDMA();
   return mock.CFGR1 & ADC_CFGR1_DMACFG_Msk;
}

bool setContinuousMode()
{
   mock.CFGR1 = 0;
   TADC::setContinuousMode();
   return mock.CFGR1 & ADC_CFGR1_CONT_Msk;
}


bool setClock()
{
   mock.CFGR2 = 0;
   bool good {true};

   TADC::set (TADC::Clock::PCLKdiv4);
   good &= not (mock.CFGR2 & ADC_CFGR2_CKMODE_0)
       and     (mock.CFGR2 & ADC_CFGR2_CKMODE_1);

   TADC::set (TADC::Clock::PCLKdiv2);
   good &=     (mock.CFGR2 & ADC_CFGR2_CKMODE_0)
       and not (mock.CFGR2 & ADC_CFGR2_CKMODE_1);

   TADC::set (TADC::Clock::Dedicated14MHzClock);
   good &= not (mock.CFGR2 & ADC_CFGR2_CKMODE_0)
       and not (mock.CFGR2 & ADC_CFGR2_CKMODE_1);
   return good;
}

bool setResolution()
{
   mock.CFGR1 = 0;
   bool good {true};

   TADC::set (TADC::Resolution::_6bits);
   good &=     (mock.CFGR1 & ADC_CFGR1_RES_0)
       and     (mock.CFGR1 & ADC_CFGR1_RES_1);

   TADC::set (TADC::Resolution::_8bits);
   good &= not (mock.CFGR1 & ADC_CFGR1_RES_0)
       and     (mock.CFGR1 & ADC_CFGR1_RES_1);

   TADC::set (TADC::Resolution::_10bits);
   good &=     (mock.CFGR1 & ADC_CFGR1_RES_0)
       and not (mock.CFGR1 & ADC_CFGR1_RES_1);

   TADC::set (TADC::Resolution::_12bits);
   good &= not (mock.CFGR1 & ADC_CFGR1_RES_0)
       and not (mock.CFGR1 & ADC_CFGR1_RES_1);

   return good;
}

bool setSampleTime()
{
   mock.SMPR = 0;
   bool good {true};

   TADC::set (TADC::SampleTime::_239_5CLOCK);
   good &=     (mock.SMPR & ADC_SMPR_SMP_0)
       and     (mock.SMPR & ADC_SMPR_SMP_1)
       and     (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_71_5CLOCK);
   good &= not (mock.SMPR & ADC_SMPR_SMP_0)
       and     (mock.SMPR & ADC_SMPR_SMP_1)
       and     (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_55_5CLOCK);
   good &=     (mock.SMPR & ADC_SMPR_SMP_0)
       and not (mock.SMPR & ADC_SMPR_SMP_1)
       and     (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_41_5CLOCK);
   good &= not (mock.SMPR & ADC_SMPR_SMP_0)
       and not (mock.SMPR & ADC_SMPR_SMP_1)
       and     (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_28_5CLOCK);
   good &=     (mock.SMPR & ADC_SMPR_SMP_0)
       and     (mock.SMPR & ADC_SMPR_SMP_1)
       and not (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_13_5CLOCK);
   good &= not (mock.SMPR & ADC_SMPR_SMP_0)
       and     (mock.SMPR & ADC_SMPR_SMP_1)
       and not (mock.SMPR & ADC_SMPR_SMP_2);
 
   TADC::set (TADC::SampleTime::_7_5CLOCK);
   good &=     (mock.SMPR & ADC_SMPR_SMP_0)
       and not (mock.SMPR & ADC_SMPR_SMP_1)
       and not (mock.SMPR & ADC_SMPR_SMP_2);

   TADC::set (TADC::SampleTime::_1_5CLOCK);
   good &= not (mock.SMPR & ADC_SMPR_SMP_0)
       and not (mock.SMPR & ADC_SMPR_SMP_1)
       and not (mock.SMPR & ADC_SMPR_SMP_2);

   static_assert ( TADC::SampleTime::Default == TADC::SampleTime::_239_5CLOCK );

   return good;
}

bool is_ready()
{
   bool good {true};
   mock.ISR = 0;
   good &= not TADC::is_ready();

   mock.ISR |= ADC_ISR_ADRDY_Msk;
   good &= TADC::is_ready();

   return good;
}


bool setBusy()
{
   mock.ISR = 0;
   TADC::setBusy();
   return mock.ISR & ADC_ISR_ADRDY_Msk;
}

bool stop()
{
   mock.CR = 0;
   TADC::stop();
   return mock.CR & ADC_CR_ADSTP_Msk;
}

bool is_stoping()
{
   bool good {true};
   mock.CR = 0;
   good &= not TADC::is_stoping();

   mock.CR |= ADC_CR_ADSTP_Msk;
   good &= TADC::is_stoping();

   return good;
}

bool getDataAdr()
{
   return TADC::getDataAdr() == reinterpret_cast<size_t>(&mock.DR);
}

bool setChannel()
{
   bool good {true};
   mock.CHSELR = 0;
   TADC::setChannel<0>();
   good &=     (mock.CHSELR & ADC_CHSELR_CHSEL0_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL1_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL2_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL3_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL4_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL5_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL6_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL7_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL8_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL9_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL10_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL11_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL12_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL13_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL14_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL15_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL16_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL17_Msk);

   TADC::setChannel<5>();
   good &=     (mock.CHSELR & ADC_CHSELR_CHSEL0_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL1_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL2_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL3_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL4_Msk)
       and     (mock.CHSELR & ADC_CHSELR_CHSEL5_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL6_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL7_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL8_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL9_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL10_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL11_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL12_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL13_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL14_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL15_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL16_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL17_Msk);

   TADC::setChannel<17>();
   good &=     (mock.CHSELR & ADC_CHSELR_CHSEL0_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL1_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL2_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL3_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL4_Msk)
       and     (mock.CHSELR & ADC_CHSELR_CHSEL5_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL6_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL7_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL8_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL9_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL10_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL11_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL12_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL13_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL14_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL15_Msk)
       and not (mock.CHSELR & ADC_CHSELR_CHSEL16_Msk)
       and     (mock.CHSELR & ADC_CHSELR_CHSEL17_Msk);

   // TADC::setChannel<18>(); // ошибка компиляции

   return good;

}

bool DefaultStream()
{
    return std::is_same_v <ADC1::DefaultStream, DMA1channel1>;
}

bool channel()
{
    return
            ADC1::channel<PA0>() == 0  
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

        and ADC1::channel<PC6>() == 255;
}

bool PINenabled()
{
    return      ADC1::PINenabled<PC5>()
        and not ADC1::PINenabled<PC6>();
}

bool DMAenabled()
{
    return      ADC1::DMAenabled<DMA1channel1>()
        and not ADC1::DMAenabled<DMA1channel2>();
}





int main()
{
   std::cout << '\n'
             << "Тесты класса ADC для STM32F0:" << std::endl;

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
   test ("ADC::setClock                ", setClock);
   test ("ADC::setResolution           ", setResolution);
   test ("ADC::setSampleTime           ", setSampleTime);
   test ("ADC::is_ready                ", is_ready);
   test ("ADC::setBusy                 ", setBusy);
   test ("ADC::stop                    ", stop);
   test ("ADC::is_stoping              ", is_stoping);
   test ("ADC::getDataAdr              ", getDataAdr);
   test ("ADC::setChannel              ", setChannel);
   test ("ADC::DefaultStream           ", DefaultStream);
   test ("ADC::channel                 ", channel);
   test ("ADC::PINenabled              ", PINenabled);
   test ("ADC::DMAenabled              ", DMAenabled);
   std::cout << std::endl;
}

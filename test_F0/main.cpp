// #include "init.h"
// #include "meta.h"
#include "init.h"
#include "pin_hal.h"
#include "pwm_hal.h"
#include "TIM.h"
#include "inputCounter.h"


#include "GPIO_ral.h"

using BlueLed = PC9;

// volatile auto RCC_d   = (RCC_t*)RCC_BASE;


// volatile auto TIM1_d = reinterpret_cast<TIM1*>(TIM1::Base);

auto counter = InputCounter<TIM1, PA9> (counterTimer);

PWM<TIM3, PA6> pwm;

void InitAll()
{
  CONFIGURE_PIN (BlueLed, OutputPushPullLowSpeedNoResistor);
}

volatile uint32_t f;

int main(void)
{
  TIM1_d->CNT.reg = 0;
  RCC_d->CR_t::bits.dcb1 = 0;
  InitAll();

  pwm.setFreq(2000_Hz);
  pwm.setD(50_percent);
  pwm.outEnable();
  
  
  ledTimer.setTimeAndStart (100_ms);
  
  while (1)
  {
    
    counter();

    f = counter.getFrequency();
    timers.update();
    if (ledTimer.event())
      BlueLed::Toggle();
  }
}



  
extern "C" void SysTick_Handler()
{
  timers.tick();
  
}



// int main(void)
// {
//     makeDebugVar();


//     //RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
//     //GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;
//     CONFIGURE_PIN (Led, OutputPushPullLowSpeedNoResistor);
//     //Led::Port::Enable();
//     //Led::Configure<Led::PinConf_t::OutputPushPullLowSpeedNoResistor>();

//     //test
    
//     auto& onTimer = timers.all[0];
//     auto& offTimer = timers.all[1];
//     offTimer.setTimeAndStart (1000);
//     spiTimer.setTimeAndStart (100);

//     // тест метапрограммирования на вариадиках
//     static_assert (QtyTypes<PA0,PA1,PA3>::value == 3, "");
//     using Test = At<3,PA0,PA1,PA3>::Result;
//     static_assert (std::is_same<Test,PA3>::value, "");
//     static_assert (Position<PA1,PA0,PA1,PA3>::value == 2, "");

//     buttons.push<But1>();

//     while (1)
//     {
//         timers.update();
//         zoomer();
//         buttons();

//         if (offTimer.event()) {
//             Led::Set();
//             offTimer.stop();
//             onTimer.setTimeAndStart(1000);
//             zoomer.beep (100_ms, 2_cnt);
//         };
//         if (onTimer.event()) {
//             Led::Clear();
//             onTimer.stop();
//             offTimer.setTimeAndStart(1000);
//         };


//         if ( spiTimer.event() ) {
//             flash.update();
//             spi.data.time++;
//             spi.startTx();
//         }
   
//     }

// }
// extern "C" void SysTick_Handler()
// {
//     timers.tick();
// }

#include "timers.h"
#include "init.h"

const uint8_t timersQty = 2;
Timers<timersQty> timers;

using Led = PC8;

int main(void)
{
    makeDebugVar();

    SPI1_::SetAsMaster();


    //RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    //GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;
    Led::Port::Enable();
    Led::Configure<Led::PinConf_t::OutputPushPullLowSpeedNoResistor>();


    
    auto& onTimer = timers.all[0];
    auto& offTimer = timers.all[1];

    offTimer.setTimeAndStart(1000);

    while (1)
    {
        timers.update();
        flash.update();
        if (offTimer.event()) {
            Led::Set();
            offTimer.stop();
            onTimer.setTimeAndStart(1000);    
        };
        if (onTimer.event()) {
            Led::Clear();
            onTimer.stop();
            offTimer.setTimeAndStart(1000);
        };
   
    }

}
extern "C" void SysTick_Handler()
{
    timers.tick();
}

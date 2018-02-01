#include "init.h"

const uint8_t timersQty = 3;
Timers<timersQty> timers;
auto& onTimer  = timers.all[0];
auto& offTimer = timers.all[1];
auto& spiTimer = timers.all[2];

using Led = PC8;


int main(void)
{
    makeDebugVar();

    SPI1::SetAsMaster();


    //RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    //GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;
    CONFIGURE (Led, OutputPushPullLowSpeedNoResistor);
    //Led::Port::Enable();
    //Led::Configure<Led::PinConf_t::OutputPushPullLowSpeedNoResistor>();

    offTimer.setTimeAndStart (1000);
    spiTimer.setTimeAndStart (100);

    while (1)
    {
        timers.update();

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


        if ( spiTimer.event() ) {
            flash.update();
            spi.data.time++;
            spi.startTx();
        }
   
    }

}
extern "C" void SysTick_Handler()
{
    timers.tick();
}

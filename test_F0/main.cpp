#include "init.h"




int main(void)
{
    makeDebugVar();


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
        zoomer();

        if (offTimer.event()) {
            Led::Set();
            offTimer.stop();
            onTimer.setTimeAndStart(1000);
            zoomer.beep (100_ms, 2_cnt);
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

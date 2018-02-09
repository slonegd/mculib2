#include "init.h"
#include "meta.h"



int main(void)
{
    makeDebugVar();


    //RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    //GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;
    CONFIGURE (Led, OutputPushPullLowSpeedNoResistor);
    //Led::Port::Enable();
    //Led::Configure<Led::PinConf_t::OutputPushPullLowSpeedNoResistor>();

    //test
    
    auto& onTimer = timers.all[0];
    auto& offTimer = timers.all[1];
    offTimer.setTimeAndStart (1000);
    spiTimer.setTimeAndStart (100);

    // тест метапрограммирования на вариадиках
    static_assert (QtyTypes<PA0,PA1,PA3>::value == 3, "");
    using Test = At<3,PA0,PA1,PA3>::Result;
    static_assert (std::is_same<Test,PA3>::value, "");
    static_assert (Position<PA1,PA0,PA1,PA3>::value == 2, "");

    buttons.push<But1>();

    while (1)
    {
        timers.update();
        zoomer();
        buttons();

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

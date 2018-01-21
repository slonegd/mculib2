#include "timers.h"
#include "init.h"

const uint8_t timersQty = 2;
Timers<timersQty> timers;

int main(void)
{
    
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0) ;


    
    auto& onTimer = timers.all[0];
    auto& offTimer = timers.all[1];

    offTimer.setTimeAndStart(1000);

    while (1)
    {
        timers.update();
        //flash.update();
        if (offTimer.event()) {
            GPIOC->ODR |= GPIO_ODR_8;
            offTimer.stop();
            onTimer.setTimeAndStart(1000);    
        };
        if (onTimer.event()) {
            GPIOC->ODR &= ~GPIO_ODR_8;
            onTimer.stop();
            offTimer.setTimeAndStart(1000);
        };
   
    }

}
extern "C" void SysTick_Handler()
{
    timers.tick();
}

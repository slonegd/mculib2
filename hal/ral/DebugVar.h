#pragma once

#include "RCC_ral.h"
#include "FLASH_ral.h"
#include "GPIO_ral.h"
#include "SPI_ral.h"
#if defined(STM32F405xx)
#include "TIM_ral.h"
#include "USART_ral.h"
#include "ADC_ral.h"
#include "DMA_ral.h"
#include "SysTick_ral.h"
#endif


volatile auto RCC_d = (RCC_t*) RCC;
volatile auto GPIOA_d = (GPIO_t*) GPIOA;
volatile auto GPIOB_d = (GPIO_t*) GPIOB;
volatile auto GPIOC_d = (GPIO_t*) GPIOC;
volatile auto GPIOD_d = (GPIO_t*) GPIOD;
volatile auto GPIOF_d = (GPIO_t*) GPIOF;
volatile auto FLASH_d = (FLASH_t*) FLASH;
volatile auto SPI1_d = (SPI1_*)SPI1_::Base;
#if defined(STM32F405xx)
volatile auto GPIOE_d = (GPIO_t*) GPIOE;
volatile auto TIM2_d = (TIM_t*) TIM2;
volatile auto TIM3_d = (TIM_t*) TIM3;
volatile auto TIM4_d = (TIM_t*) TIM4;
volatile auto USART1_d = (USART_t*) USART1;
volatile auto USART2_d = (USART_t*) USART2;
volatile auto USART3_d = (USART_t*) USART3;
volatile auto USART6_d = (USART_t*) USART6;
volatile auto ADC1_d = (ADC_t*) ADC1;
volatile auto ADC2_d = (ADC_t*) ADC2;
volatile auto ADC3_d = (ADC_t*) ADC3;
volatile auto DMA1Stream0_d = (DMAstream_t*) DMA1_Stream0;
volatile auto DMA1Stream1_d = (DMAstream_t*) DMA1_Stream1;
volatile auto DMA1Stream2_d = (DMAstream_t*) DMA1_Stream2;
volatile auto DMA1Stream3_d = (DMAstream_t*) DMA1_Stream3;
volatile auto DMA1Stream4_d = (DMAstream_t*) DMA1_Stream4;
volatile auto DMA1Stream5_d = (DMAstream_t*) DMA1_Stream5;
volatile auto DMA1Stream6_d = (DMAstream_t*) DMA1_Stream6;
volatile auto DMA1Stream7_d = (DMAstream_t*) DMA1_Stream7;
volatile auto DMA2Stream0_d = (DMAstream_t*) DMA2_Stream0;
volatile auto DMA2Stream1_d = (DMAstream_t*) DMA2_Stream1;
volatile auto DMA2Stream2_d = (DMAstream_t*) DMA2_Stream2;
volatile auto DMA2Stream3_d = (DMAstream_t*) DMA2_Stream3;
volatile auto DMA2Stream4_d = (DMAstream_t*) DMA2_Stream4;
volatile auto DMA2Stream5_d = (DMAstream_t*) DMA2_Stream5;
volatile auto DMA2Stream6_d = (DMAstream_t*) DMA2_Stream6;
volatile auto DMA2Stream7_d = (DMAstream_t*) DMA2_Stream7;
volatile auto DMA1_d = (DMA_t*) DMA1;
volatile auto DMA2_d = (DMA_t*) DMA2;
volatile auto SysTick_d = (SysTick_t*) SysTick;
#endif


inline void makeDebugVar (void)
{
    RCC_d->CR_t::bits.dcb1 = 0;
    FLASH_d->makeDebugVar();
    GPIOA_d->BSRR_t::reg = 0;
    GPIOB_d->BSRR_t::reg = 0;
    GPIOC_d->BSRR_t::reg = 0;
    GPIOD_d->BSRR_t::reg = 0;
    GPIOF_d->BSRR_t::reg = 0;
    SPI1_d->makeDebugVar();
#if defined(STM32F405xx)
    GPIOE_d->BSRR_t::reg = 0;
    TIM2_d->CR1_t::bits.dcb = 0;
    TIM3_d->CR1_t::bits.dcb = 0;
    TIM4_d->CR1_t::bits.dcb = 0;
    USART1_d->CR1_t::bits.dcb1 = 0;
    USART2_d->CR1_t::bits.dcb1 = 0;
    USART3_d->CR1_t::bits.dcb1 = 0;
    USART6_d->CR1_t::bits.dcb1 = 0;
    ADC1_d->SR_t::bits.dcb1 = 0;
    ADC2_d->SR_t::bits.dcb1 = 0;
    ADC3_d->SR_t::bits.dcb1 = 0;
    DMA1Stream0_d->CR_t::bits.dcb1 = 0;
    DMA1Stream1_d->CR_t::bits.dcb1 = 0;
    DMA1Stream2_d->CR_t::bits.dcb1 = 0;
    DMA1Stream3_d->CR_t::bits.dcb1 = 0;
    DMA1Stream4_d->CR_t::bits.dcb1 = 0;
    DMA1Stream5_d->CR_t::bits.dcb1 = 0;
    DMA1Stream6_d->CR_t::bits.dcb1 = 0;
    DMA1Stream7_d->CR_t::bits.dcb1 = 0;
    DMA2Stream0_d->CR_t::bits.dcb1 = 0;
    DMA2Stream1_d->CR_t::bits.dcb1 = 0;
    DMA2Stream2_d->CR_t::bits.dcb1 = 0;
    DMA2Stream3_d->CR_t::bits.dcb1 = 0;
    DMA2Stream4_d->CR_t::bits.dcb1 = 0;
    DMA2Stream5_d->CR_t::bits.dcb1 = 0;
    DMA2Stream6_d->CR_t::bits.dcb1 = 0;
    DMA2Stream7_d->CR_t::bits.dcb1 = 0;
    DMA1_d->LIFCR_t::bits.dcb1 = 0;
    DMA2_d->LIFCR_t::bits.dcb1 = 0;
    SysTick_d->VAL_t::reg = 0;
#endif

}
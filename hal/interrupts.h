#pragma once
#include "interrupt.h"

#if defined(STM32F405xx) || defined(STM32F030x6)

extern "C" void USART1_IRQHandler()       { Interrupt<USART1>     ::interrupt(); }

#endif

#if defined(STM32F405xx)

// список прерываний, которые не описаны
extern "C" void WWDG_IRQHandler               () { while(1) {} }
extern "C" void PVD_IRQHandler                () { while(1) {} }
extern "C" void TAMP_STAMP_IRQHandler         () { while(1) {} }
extern "C" void RTC_WKUP_IRQHandler           () { while(1) {} }
extern "C" void FLASH_IRQHandler              () { while(1) {} }
extern "C" void RCC_IRQHandler                () { while(1) {} }
extern "C" void EXTI0_IRQHandler              () { while(1) {} }
extern "C" void EXTI1_IRQHandler              () { while(1) {} }
extern "C" void EXTI2_IRQHandler              () { while(1) {} }
extern "C" void EXTI3_IRQHandler              () { while(1) {} }
extern "C" void EXTI4_IRQHandler              () { while(1) {} }
extern "C" void ADC_IRQHandler                () { while(1) {} }
extern "C" void CAN1_TX_IRQHandler            () { while(1) {} }
extern "C" void CAN1_RX0_IRQHandler           () { while(1) {} }
extern "C" void CAN1_RX1_IRQHandler           () { while(1) {} }
extern "C" void CAN1_SCE_IRQHandler           () { while(1) {} }
extern "C" void EXTI9_5_IRQHandler            () { while(1) {} }
extern "C" void I2C1_EV_IRQHandler            () { while(1) {} }
extern "C" void I2C1_ER_IRQHandler            () { while(1) {} }
extern "C" void I2C2_EV_IRQHandler            () { while(1) {} }
extern "C" void I2C2_ER_IRQHandler            () { while(1) {} }
extern "C" void SPI1_IRQHandler               () { while(1) {} }
extern "C" void SPI2_IRQHandler               () { while(1) {} }
extern "C" void EXTI15_10_IRQHandler          () { while(1) {} }
extern "C" void RTC_Alarm_IRQHandler          () { while(1) {} }
extern "C" void OTG_FS_WKUP_IRQHandler        () { while(1) {} }
extern "C" void FSMC_IRQHandler               () { while(1) {} }
extern "C" void SDIO_IRQHandler               () { while(1) {} }
extern "C" void SPI3_IRQHandler               () { while(1) {} }
extern "C" void UART4_IRQHandler              () { while(1) {} }
extern "C" void UART5_IRQHandler              () { while(1) {} }
extern "C" void CAN2_TX_IRQHandler            () { while(1) {} }
extern "C" void CAN2_RX0_IRQHandler           () { while(1) {} }
extern "C" void CAN2_RX1_IRQHandler           () { while(1) {} }
extern "C" void CAN2_SCE_IRQHandler           () { while(1) {} }
extern "C" void OTG_FS_IRQHandler             () { while(1) {} }
extern "C" void USART6_IRQHandler             () { while(1) {} }
extern "C" void I2C3_EV_IRQHandler            () { while(1) {} }
extern "C" void I2C3_ER_IRQHandler            () { while(1) {} }
extern "C" void OTG_HS_EP1_OUT_IRQHandler     () { while(1) {} }
extern "C" void OTG_HS_EP1_IN_IRQHandler      () { while(1) {} }
extern "C" void OTG_HS_WKUP_IRQHandler        () { while(1) {} }
extern "C" void OTG_HS_IRQHandler             () { while(1) {} }
extern "C" void HASH_RNG_IRQHandler           () { while(1) {} }
extern "C" void FPU_IRQHandler                () { while(1) {} }

extern "C" void TIM1_BRK_TIM9_IRQHandler      () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM1_UP_TIM10_IRQHandler      () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM1_CC_IRQHandler            () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM2_IRQHandler               () { Interrupt<TIM2>::interrupt(); }
extern "C" void TIM3_IRQHandler               () { Interrupt<TIM3>::interrupt(); }
extern "C" void TIM4_IRQHandler               () { Interrupt<TIM4>::interrupt(); }
extern "C" void TIM5_IRQHandler               () { Interrupt<TIM5>::interrupt(); }
extern "C" void TIM6_DAC_IRQHandler           () { Interrupt<TIM6>::interrupt(); }
extern "C" void TIM7_IRQHandler               () { Interrupt<TIM7>::interrupt(); }
extern "C" void TIM8_BRK_TIM12_IRQHandler     () { Interrupt<TIM8>::interrupt(); }
extern "C" void TIM8_UP_TIM13_IRQHandler      () { Interrupt<TIM8>::interrupt(); }
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler () { Interrupt<TIM8>::interrupt(); }
extern "C" void TIM8_CC_IRQHandler            () { Interrupt<TIM8>::interrupt(); }

extern "C" void DMA1_Stream0_IRQHandler() { Interrupt<DMA1stream0>::interrupt(); }
extern "C" void DMA1_Stream1_IRQHandler() { Interrupt<DMA1stream1>::interrupt(); }
extern "C" void DMA1_Stream2_IRQHandler() { Interrupt<DMA1stream2>::interrupt(); }
extern "C" void DMA1_Stream3_IRQHandler() { Interrupt<DMA1stream3>::interrupt(); }
extern "C" void DMA1_Stream4_IRQHandler() { Interrupt<DMA1stream4>::interrupt(); }
extern "C" void DMA1_Stream5_IRQHandler() { Interrupt<DMA1stream5>::interrupt(); }
extern "C" void DMA1_Stream6_IRQHandler() { Interrupt<DMA1stream6>::interrupt(); }
extern "C" void DMA1_Stream7_IRQHandler() { Interrupt<DMA1stream7>::interrupt(); }
extern "C" void DMA2_Stream0_IRQHandler() { Interrupt<DMA2stream0>::interrupt(); }
extern "C" void DMA2_Stream1_IRQHandler() { Interrupt<DMA2stream1>::interrupt(); }
extern "C" void DMA2_Stream2_IRQHandler() { Interrupt<DMA2stream2>::interrupt(); }
extern "C" void DMA2_Stream3_IRQHandler() { Interrupt<DMA2stream3>::interrupt(); }
extern "C" void DMA2_Stream4_IRQHandler() { Interrupt<DMA2stream4>::interrupt(); }
extern "C" void DMA2_Stream5_IRQHandler() { Interrupt<DMA2stream5>::interrupt(); }
extern "C" void DMA2_Stream6_IRQHandler() { Interrupt<DMA2stream6>::interrupt(); }
extern "C" void DMA2_Stream7_IRQHandler() { Interrupt<DMA2stream7>::interrupt(); }
extern "C" void USART2_IRQHandler()       { Interrupt<USART2>     ::interrupt(); }
extern "C" void USART3_IRQHandler()       { Interrupt<USART3>     ::interrupt(); }

#endif


#if defined(STM32F030x6)

extern "C" void TIM1_BRK_TIM9_IRQHandler      () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM1_CC_IRQHandler            () { Interrupt<TIM1>::interrupt(); }
extern "C" void TIM3_IRQHandler               () { Interrupt<TIM3>::interrupt(); }
extern "C" void TIM14_IRQHandler              () { Interrupt<TIM14>::interrupt(); }
extern "C" void TIM16_IRQHandler              () { Interrupt<TIM16>::interrupt(); }
extern "C" void TIM17_IRQHandler              () { Interrupt<TIM17>::interrupt(); }

extern "C" void DMA1_Channel1_IRQHandler()   { Interrupt<DMA1channel1>::interrupt(); }
extern "C" void DMA1_Channel2_3_IRQHandler() { Interrupt<DMA1channel2>::interrupt();
                                               Interrupt<DMA1channel3>::interrupt(); }
extern "C" void DMA1_Channel4_5_IRQHandler() { Interrupt<DMA1channel4>::interrupt();
                                               Interrupt<DMA1channel5>::interrupt(); }

#endif // 

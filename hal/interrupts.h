#pragma once
#include "interrupt.h"

#if defined(STM32F405xx) || defined(STM32F030x6)

extern "C" void USART1_IRQHandler()       { Interrupt<USART1>     ::interrupt(); }

#endif

#if defined(STM32F405xx)
/**
 * список прерываний, которые не описаны
 * 
 * WWDG_IRQHandler
 * PVD_IRQHandler
 * TAMP_STAMP_IRQHandler
 * RTC_WKUP_IRQHandler
 * FLASH_IRQHandler
 * RCC_IRQHandler
 * EXTI0_IRQHandler
 * EXTI1_IRQHandler
 * EXTI2_IRQHandler
 * EXTI3_IRQHandler
 * EXTI4_IRQHandler
 * ADC_IRQHandler
 * CAN1_TX_IRQHandler
 * CAN1_RX0_IRQHandler
 * CAN1_RX1_IRQHandler
 * CAN1_SCE_IRQHandler
 * EXTI9_5_IRQHandler
 * TIM1_BRK_TIM9_IRQHandler
 * TIM1_UP_TIM10_IRQHandler
 * TIM1_TRG_COM_TIM11_IRQHandler
 * TIM1_CC_IRQHandler
 * TIM2_IRQHandler
 * TIM3_IRQHandler
 * TIM4_IRQHandler
 * I2C1_EV_IRQHandler
 * I2C1_ER_IRQHandler
 * I2C2_EV_IRQHandler
 * I2C2_ER_IRQHandler
 * SPI1_IRQHandler
 * SPI2_IRQHandler
 * EXTI15_10_IRQHandler
 * RTC_Alarm_IRQHandler
 * OTG_FS_WKUP_IRQHandler
 * TIM8_BRK_TIM12_IRQHandler
 * TIM8_UP_TIM13_IRQHandler
 * TIM8_TRG_COM_TIM14_IRQHandler
 * TIM8_CC_IRQHandler
 * FSMC_IRQHandler
 * SDIO_IRQHandler
 * TIM5_IRQHandler
 * SPI3_IRQHandler
 * UART4_IRQHandler
 * UART5_IRQHandler
 * TIM6_DAC_IRQHandler
 * TIM7_IRQHandler
 * CAN2_TX_IRQHandler 
 * CAN2_RX0_IRQHandler
 * CAN2_RX1_IRQHandler
 * CAN2_SCE_IRQHandler
 * OTG_FS_IRQHandler
 * USART6_IRQHandler
 * I2C3_EV_IRQHandler
 * I2C3_ER_IRQHandler
 * OTG_HS_EP1_OUT_IRQHandler
 * OTG_HS_EP1_IN_IRQHandler
 * OTG_HS_WKUP_IRQHandler
 * OTG_HS_IRQHandler
 * HASH_RNG_IRQHandler
 * FPU_IRQHandler
 **/

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

extern "C" void DMA1_Channel1_IRQHandler()   { Interrupt<DMA1channel1>::interrupt(); }
extern "C" void DMA1_Channel2_3_IRQHandler() { Interrupt<DMA1channel2>::interrupt();
                                               Interrupt<DMA1channel3>::interrupt(); }
extern "C" void DMA1_Channel4_5_IRQHandler() { Interrupt<DMA1channel4>::interrupt();
                                               Interrupt<DMA1channel5>::interrupt(); }

#endif // 

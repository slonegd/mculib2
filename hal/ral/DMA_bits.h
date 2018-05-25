#pragma once

#include "registr.h"



namespace DMA_ral {


struct ISRbits {
#if defined(STM32F405xx)
   __IO bool     FEIF0  :1; // Bits 22, 16, 6, 0 FEIFx: Stream x FIFO error interrupt flag (x=3..0)
   __IO uint32_t res1   :1; // Bits 23, 17, 7, 1 Reserved, must be kept at reset value
   __IO bool     DMEIF0 :1; // Bits 24, 18, 8, 2 DMEIFx: Stream x direct mode error interrupt flag (x=3..0)
   __IO bool     TEIF0  :1; // Bits 25, 19, 9, 3 TEIFx: Stream x transfer error interrupt flag (x=3..0)
   __IO bool     HTIF0  :1; // Bits 26, 20, 10, 4 HTIFx: Stream x half transfer interrupt flag (x=3..0)
   __IO bool     TCIF0  :1; // Bits 27, 21, 11, 5 TCIFx: Stream x transfer complete interrupt flag (x = 3..0)
   __IO bool     FEIF1  :1;
   __IO uint32_t res2   :1;
   __IO bool     DMEIF1 :1;
   __IO bool     TEIF1  :1;
   __IO bool     HTIF1  :1;
   __IO bool     TCIF1  :1;
   __IO uint32_t res3   :4; // Bits 31:28, 15:12 Reserved, must be kept at reset value.
   __IO bool     FEIF2  :1;
   __IO uint32_t res4   :1;
   __IO bool     DMEIF2 :1;
   __IO bool     TEIF2  :1;
   __IO bool     HTIF2  :1;
   __IO bool     TCIF2  :1;
   __IO bool     FEIF3  :1;
   __IO uint32_t res5   :1;
   __IO bool     DMEIF3 :1;
   __IO bool     TEIF3  :1;
   __IO bool     HTIF3  :1;
   __IO bool     TCIF3  :1;
   __IO uint32_t res6   :4;
   __IO bool     FEIF4  :1;
   __IO uint32_t res7   :1;
   __IO bool     DMEIF4 :1;
   __IO bool     TEIF4  :1;
   __IO bool     HTIF4  :1;
   __IO bool     TCIF4  :1;
   __IO bool     FEIF5  :1;
   __IO uint32_t res8   :1;
   __IO bool     DMEIF5 :1;
   __IO bool     TEIF5  :1;
   __IO bool     HTIF5  :1;
   __IO bool     TCIF5  :1;
   __IO uint32_t res9   :4;
   __IO bool     FEIF6  :1;
   __IO uint32_t res10  :1;
   __IO bool     DMEIF6 :1;
   __IO bool     TEIF6  :1;
   __IO bool     HTIF6  :1;
   __IO bool     TCIF6  :1;
   __IO bool     FEIF7  :1;
   __IO uint32_t res11  :1;
   __IO bool     DMEIF7 :1;
   __IO bool     TEIF7  :1;
   __IO bool     HTIF7  :1;
   __IO bool     TCIF7  :1;
   __IO uint32_t res12  :4;
#elif defined(STM32F030x6)
   __IO bool     GIF1  :1; // Bits 16, 12, 8, 4, 0 GIFx: Channel x global interrupt flag (x = 1..5)
   __IO bool     TCIF1 :1; // Bits 17, 13, 9, 5, 1 TCIFx: Channel x transfer complete flag (x = 1..5)
   __IO bool     HTIF1 :1; // Bits 18, 14, 10, 6, 2 HTIFx: Channel x half transfer flag (x = 1..5)
   __IO bool     TEIF1 :1; // Bits 19, 15, 11, 7, 3 TEIFx: Channel x transfer error flag (x = 1..5)
   __IO bool     GIF2  :1;
   __IO bool     TCIF2 :1;
   __IO bool     HTIF2 :1;
   __IO bool     TEIF2 :1;
   __IO bool     GIF3  :1;
   __IO bool     TCIF3 :1;
   __IO bool     HTIF3 :1;
   __IO bool     TEIF3 :1;
   __IO bool     GIF4  :1;
   __IO bool     TCIF4 :1;
   __IO bool     HTIF4 :1;
   __IO bool     TEIF4 :1;
   __IO bool     GIF5  :1;
   __IO bool     TCIF5 :1;
   __IO bool     HTIF5 :1;
   __IO bool     TEIF5 :1;
   __IO uint32_t res1 :12;
#endif
};

#if defined(STM32F405xx)
struct ISR_t   : BitsRegistrs<ISRbits>, Offset_t<0x00> {};
struct IFCR_t  : BitsRegistrs<ISRbits>, Offset_t<0x08> {};
#elif defined(STM32F030x6)
struct ISR_t   : BitsRegistr<ISRbits> , Offset_t<0x00> {};
struct IFCR_t  : BitsRegistr<ISRbits> , Offset_t<0x04> {};
#endif




} // namespace DMA_ral {
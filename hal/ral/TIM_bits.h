#pragma once

#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif

/* STM32F4 STM32F0
typedef struct
{
   __IO uint32_t CR1;   // TIM control register 1,              Address offset: 0x00
   __IO uint32_t CR2;   // TIM control register 2,              Address offset: 0x04
   __IO uint32_t SMCR;  // TIM slave mode control register,     Address offset: 0x08
   __IO uint32_t DIER;  // TIM DMA/interrupt enable register,   Address offset: 0x0C
   __IO uint32_t SR;    // TIM status register,                 Address offset: 0x10
   __IO uint32_t EGR;   // TIM event generation register,       Address offset: 0x14
   __IO uint32_t CCMR1; // TIM capture/compare mode register 1, Address offset: 0x18
   __IO uint32_t CCMR2; // TIM capture/compare mode register 2, Address offset: 0x1C
   __IO uint32_t CCER;  // TIM capture/compare enable register, Address offset: 0x20
   __IO uint32_t CNT;   // TIM counter register,                Address offset: 0x24
   __IO uint32_t PSC;   // TIM prescaler,                       Address offset: 0x28
   __IO uint32_t ARR;   // TIM auto-reload register,            Address offset: 0x2C
   __IO uint32_t RCR;   // TIM repetition counter register,     Address offset: 0x30
   __IO uint32_t CCR1;  // TIM capture/compare register 1,      Address offset: 0x34
   __IO uint32_t CCR2;  // TIM capture/compare register 2,      Address offset: 0x38
   __IO uint32_t CCR3;  // TIM capture/compare register 3,      Address offset: 0x3C
   __IO uint32_t CCR4;  // TIM capture/compare register 4,      Address offset: 0x40
   __IO uint32_t BDTR;  // TIM break and dead-time register,    Address offset: 0x44
   __IO uint32_t DCR;   // TIM DMA control register,            Address offset: 0x48
   __IO uint32_t DMAR;  // TIM DMA address for full transfer,   Address offset: 0x4C
   __IO uint32_t OR;    // TIM option register,                 Address offset: 0x50
} TIM_TypeDef;
*/

namespace TIM_ral {

   struct CR1_t {
      enum { Offset = 0x00 };
      struct Bits {
         // Bit 0 CEN: Counter enable
         volatile bool CEN        :1;
         // Bit 1 UDIS: Update disable
         volatile uint32_t UDIS   :1;
         // Bit 2 URS: Update request source
         volatile uint32_t URS    :1;
         // Bit 3 OPM: One-pulse mode
         volatile uint32_t OPM    :1;
         // Bit 4 DIR: Direction
         // 0: Counter used as upcounter
         // 1: Counter used as downcounter
         volatile uint32_t DIR    :1;
         // Bits 6:5 CMS: Center-aligned mode selection
         volatile uint32_t CMS    :2;
         // Bit 7 ARPE: Auto-reload preload enable
         volatile bool ARPE       :1;
         // Bits 9:8 CKD: Clock division
         // 00: t DTS = t CK_INT
         // 01: t DTS = 2 × t CK_INT
         // 10: t DTS = 4 × t CK_INT
         volatile uint32_t CKD    :2;
         // Bits 15:10 Reserved, must be kept at reset value.
         volatile uint32_t res    :22;
      };
      enum {
         CEN = 0, UDIS, URS, OPM, DIR, CMS, ARPE = 7, CKD
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CR2_t {
      enum { Offset = 0x04 };
      struct Bits {
         // Bits 2:0 Reserved, must be kept at reset value.
         volatile uint32_t res1  :3;
         // Bit 3 CCDS: Capture/compare DMA selection
         volatile uint32_t CCDS  :1;
         // Bits 6:4 MMS[2:0]: Master mode selection
         volatile uint32_t MMS   :3;
         // Bit 7 TI1S: TI1 selection
         volatile uint32_t TI1S  :1;
         // Bits 15:8 Reserved, must be kept at reset value.
         volatile uint32_t res2  :24;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct SMCR_t {
      enum { Offset = 0x08 };
      uint32_t reg;
   };



   struct DIER_t {
      enum { Offset = 0x0C };
      struct Bits {
         // Bit 0 UIE: Update interrupt enable
         volatile bool UIE       :1;
         // Bit 1 CC1IE: Capture/Compare 1 interrupt enable
         volatile bool CC1IE     :1;
         // Bit 2 CC2IE: Capture/Compare 2 interrupt enable
         volatile bool CC2IE     :1;
         // Bit 3 CC2IE: Capture/Compare 3 interrupt enable
         volatile bool CC3IE     :1;
         // Bit 4 CC2IE: Capture/Compare 4 interrupt enable
         volatile bool CC4IE     :1;
         // Bit 5 Reserved, must be kept at reset value.
         volatile uint32_t res1  :1;
         // Bit 6 TIE: Trigger interrupt enable
         volatile bool TIE       :1;
         // Bit 7 Reserved, must be kept at reset value.
         volatile uint32_t res2  :1;
         // Bit 8 UDE: Update DMA request enable
         volatile bool UDE       :1;
         // Bit 9 CC1DE: Capture/Compare 1 DMA request enable
         volatile bool CC1DE     :1;
         // Bit 10 CC1DE: Capture/Compare 2 DMA request enable
         volatile bool CC2DE     :1;
         // Bit 11 CC1DE: Capture/Compare 3 DMA request enable
         volatile bool CC3DE     :1;
         // Bit 12 CC1DE: Capture/Compare 4 DMA request enable
         volatile bool CC4DE     :1;
         // Bit 13 Reserved, always read as 0.
         volatile uint32_t res3  :1;
         // Bit 14 TDE: Trigger DMA request enable
         volatile bool TDE       :1;
         // Bit 15 Reserved, must be kept at reset value.
         volatile uint32_t res4  :17;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct SR_t {
      enum { Offset = 0x10 };
      uint32_t reg;
   };



   struct EGR_t {
      enum { Offset = 0x14 };
      uint32_t reg;
   };



   struct CCMR_t {
      enum { Offset = 0x18 };
      enum CompareMode {
         Off             = 0b000,
         ActiveOnMatch   = 0b001,
         InactiveOnMatch = 0b010,
         ToggleOnMatch   = 0b011,
         ForceInactive   = 0b100,
         ForceActive     = 0b101,
         PWMmode         = 0b110,
         InvertedPWMmode = 0b111
      };
      struct Bits {
         // Bits 1:0 CC1S: Capture/Compare 1 selection
         volatile uint32_t CC1S      :2;
         // Bit 2 OC1FE: Output compare 1 fast enable
         volatile bool OC1FE         :1;
         // Bit 3 OC1PE: Output compare 1 preload enable
         volatile bool OC1PE         :1;
         // Bits 6:4 OC1M: Output compare 1 mode
         volatile CompareMode OC1M   :3;
         // Bit 7 OC1CE: Output compare 1 clear enable
         volatile bool OC1CE         :1;
         volatile uint32_t CC2S      :2;
         volatile bool OC2FE         :1;
         volatile bool OC2PE         :1;
         volatile CompareMode OC2M   :3;
         volatile bool OC2CE         :1;
         uint32_t res1               :16;
         volatile uint32_t CC3S      :2;
         volatile bool OC3FE         :1;
         volatile bool OC3PE         :1;
         volatile CompareMode OC3M   :3;
         volatile bool OC3CE         :1;
         volatile uint32_t CC4S      :2;
         volatile bool OC4FE         :1;
         volatile bool OC4PE         :1;
         volatile CompareMode OC4M   :3;
         volatile bool OC4CE         :1;
         uint32_t res2               :16;
      };
      union {
         volatile Bits bits;
         volatile uint32_t regs[2];   
      };
   };



   struct CCER_t {
      enum { Offset = 0x20 };
      struct Bits {
         // Bit 0 CC1E: Capture/Compare 1 output enable.
         volatile bool CC1E      :1;
         // Bit 1 CC1P: Capture/Compare 1 output Polarity.
         volatile uint32_t CC1P  :1;
         // Bit 2 Reserved, must be kept at reset value.
         volatile uint32_t res1  :1;
         // Bit 3 CC1NP: Capture/Compare 1 output Polarity.
         volatile uint32_t CC1NP :1;
         volatile bool CC2E      :1;
         volatile uint32_t CC2P  :1;
         volatile uint32_t res2  :1;
         volatile uint32_t CC2NP :1;
         volatile bool CC3E      :1;
         volatile uint32_t CC3P  :1;
         volatile uint32_t res3  :1;
         volatile uint32_t CC3NP :1;
         volatile bool CC4E      :1;
         volatile uint32_t CC4P  :1;
         volatile uint32_t res4  :1;
         volatile uint32_t CC4NP :1;
         volatile uint32_t res5  :16;
      };
      union {
         volatile Bits bits;
         volatile uint16_t reg;
      };
   };



   struct CNT_t {
      enum { Offset = 0x24 };
      volatile uint32_t reg;
   };



   struct PSC_t {
      enum { Offset = 0x28 };
      volatile uint32_t reg;
   };



   struct ARR_t {
      enum { Offset = 0x2C };
      volatile uint32_t reg;
   };



   struct RCR_t {
      enum { Offset = 0x30 };
      volatile uint32_t reg;
   };



   struct CCR_t {
      enum { Offset = 0x34 };
      volatile uint32_t regs[4];
   };



   struct BDTR_t {
      enum { Offset = 0x44 };
      struct Bits {
         // Bits 7:0 DTG[7:0]: Dead-time generator setup
         volatile uint32_t DTG :8;
         // Bits 9:8 LOCK[1:0]: Lock configuration
         volatile uint32_t LOCK :2;
         // Bit 10 OSSI: Off-state selection for Idle mode
         volatile uint32_t OSSI :1;
         // Bit 11 OSSR: Off-state selection for Run mode
         volatile uint32_t OSSR :1;
         // Bit 12 BKE: Break enable
         volatile bool BKE      :1;
         // Bit 13 BKP: Break polarity
         volatile uint32_t BKP  :1;
         // Bit 14 AOE: Automatic output enable
         volatile uint32_t AOE  :1;
         // Bit 15 MOE: Main output enable
         volatile bool MOE      :1;
         volatile uint32_t res1 :16; 
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };
}


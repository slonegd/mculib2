#pragma once

#include "stm32f0xx.h"

/*
typedef struct
{
  __IO uint32_t ISR;          //ADC interrupt and status register,        offset: 0x00
  __IO uint32_t IER;          //ADC interrupt enable register,            offset: 0x04
  __IO uint32_t CR;           //ADC control register,                     offset: 0x08
  __IO uint32_t CFGR1;        //ADC configuration register 1,             offset: 0x0C
  __IO uint32_t CFGR2;        //ADC configuration register 2,             offset: 0x10
  __IO uint32_t SMPR;         //ADC sampling time register,               offset: 0x14
       uint32_t RESERVED1;    //Reserved,                                 0x18
       uint32_t RESERVED2;    //Reserved,                                 0x1C
  __IO uint32_t TR;           //ADC analog watchdog 1 threshold register, offset: 0x20
       uint32_t RESERVED3;    //Reserved,                                 0x24
  __IO uint32_t CHSELR;       //ADC group regular sequencer register,     offset: 0x28
       uint32_t RESERVED4[5]; //Reserved,                                 0x2C
  __IO uint32_t DR;           //ADC group regular data register,          offset: 0x40
} ADC_TypeDef;
*/

namespace ADC_ral {

   struct SR_t {
      enum { Offset = 0x00 };
      struct Bits {
         // Bit 0 ADRDY: ADC ready
         volatile bool ADRDY     :1;
         // Bit 1 EOSMP: End of sampling flag
         volatile bool EOSMP     :1;
         // Bit 2 EOC: End of conversion flag
         volatile bool EOC       :1;
         // Bit 3 EOSEQ: End of sequence flag
         volatile bool EOSEQ     :1;
         // Bit 4 OVR: ADC overrun
         volatile bool OVR       :1;
         // Bit 6:5 Reserved, must be kept at reset value.
         volatile uint32_t res1  :2;
         // Bit 7 AWD: Analog watchdog flag
         volatile bool AWD       :1;
         // Bits 31:8 Reserved, must be kept at reset value.
         volatile uint32_t res2  :24;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct IER_t {
      enum { Offset = 0x04 };
      struct Bits {
         // Bits 0 ADRDYIE: ADC ready interrupt enable
         volatile bool ADRDYIE   :1;
         // Bit 1 EOSMPIE: End of sampling flag interrupt enable
         volatile bool EOSMPIE   :1;
         // Bit 2 EOCIE: End of conversion interrupt enable
         volatile bool EOCIE     :1;
         // Bit 3 EOSEQIE: End of conversion sequence interrupt enable
         volatile bool EOSEQIE   :1;
         // Bit 4 OVRIE: Overrun interrupt enable
         volatile bool OVRIE     :1;
         // Bit 6:5 Reserved, must be kept at reset value.
         volatile uint32_t res1  :1;
         // Bit 7 AWDIE: Analog watchdog interrupt enable
         volatile bool AWDIE     :1;
         // Bits 31:8 Reserved, must be kept at reset value.
         volatile uint32_t res2  :24;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CR_t {
      enum { Offset = 0x08 };
      struct Bits {
         // Bit 0 ADEN: ADC enable command
         volatile bool ADEN     :1;
         // Bit 1 ADDIS: ADC disable command
         volatile bool ADDIS    :1;
         // Bit 2 ADSTART: ADC start conversion command
         volatile bool ADSTART  :1;
         // Bit 3 Reserved, must be kept at reset value.
         volatile uint32_t res1 :1;
         // Bit 4 ADSTP: ADC stop conversion command
         volatile bool ADSTP    :1;
         // Bits 30:5 Reserved, must be kept at reset value.
         volatile uint32_t res2 :26;
         // Bit 31 ADCAL: ADC calibration
         volatile bool ADCAL    :1;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CFGR1_t {
      enum { Offset = 0x0C };
      enum Resolution { _12bits = 0b00, _10bits, _8bits, _6bits }; 
      enum Trigger { _0 = 0b000, _1, _2, _3, _4, _5, _6, _7 };
      enum TriggerEn { Disable = 0b00, RisingEdge, FallingEdge, BothEdge };
      struct Bits {
         // Bit 0 DMAEN: Direct memory access enable
         volatile bool DMAEN        :1;
         // Bit 1 DMACFG: Direct memory access configuration
         volatile uint32_t DMACFG   :1;
         // Bit 2 SCANDIR: Scan sequence direction
         volatile uint32_t SCANDIR  :1;
         // Bit 4:3 RES[1:0]: Data resolution
         volatile Resolution RES    :2;
         // Bits 8:6 EXTSEL[2:0]: External trigger selection
         volatile Trigger EXTSEL    :3;
         // Bits 11:10 EXTEN[1:0]: External trigger enable and polarity selection
         volatile TriggerEn EXTEN   :2;
         // Bit 12 OVRMOD: Overrun management mode
         volatile uint32_t OVRMOD   :1;
         // Bit 13 CONT: Single / continuous conversion mode
         volatile bool CONT         :1;
         // Bit 14 WAIT: Wait conversion mode
         volatile bool WAIT         :1;
         // Bit 15 AUTOFF: Auto-off mode
         volatile bool AUTOFF       :1;
         // Bit 16 DISCEN: Discontinuous mode
         volatile bool DISCEN       :1;
         // Bits 21:17 Reserved, must be kept at reset value.
         volatile uint32_t res1     :5;
         // Bit 22 AWDSGL: Enable the watchdog on a single channel or on all channels
         volatile uint32_t AWDSGL   :1;
         // Bit 23 AWDEN: Analog watchdog enable
         volatile bool AWDEN        :1;
         // Bits 25:24 Reserved, must be kept at reset value.
         volatile uint32_t res2     :2;
         // Bits 30:26 AWDCH[4:0]: Analog watchdog channel selection
         volatile uint32_t AWDCH    :5;
         // Bit 31 Reserved, must be kept at reset value.
         volatile uint32_t res3     :1;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CFGR2_t {
      enum { Offset = 0x10 };
      enum ADCclockDiv { ADCCLK = 0b00, PCLKdiv2, PCLKdiv4 };
      struct Bits {
         // Bits 29:0 Reserved, must be kept at reset value.
         volatile uint32_t res1        :30;
         // Bits 31:30 CKMODE[1:0]: ADC clock mode
         volatile ADCclockDiv CKMODE   :2;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct SMPR_t {
      enum { Offset = 0x14 };
      enum SampleTime { 
         _1_5_ADCclockCycles = 0b000, _7_5_ADCclockCycles,
         _13_5_ADCclockCycles, _28_5_ADCclockCycles, _41_5_ADCclockCycles,
         _55_5_ADCclockCicle, _71_5_ADCclockCicle, _239_5_ADCclockCicle
      };
      struct Bits {
         // Bits 2:0 SMP[2:0]: Sampling time selection
         volatile SampleTime SMP :3;
         // Bits 31:3 Reserved, must be kept at reset value.
         volatile uint32_t res1  :29;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct TR_t {
      enum { Offset = 0x20 };
      struct Bits {
         // Bit 11:0 LT[11:0]: Analog watchdog lower threshold
         volatile uint32_t LT    :12;
         // Bits 15:12 Reserved, must be kept at reset value.
         volatile uint32_t res1  :4;
         // Bit 27:16 HT[11:0]: Analog watchdog higher threshold
         volatile uint32_t HT    :12;
         // Bits 31:28 Reserved, must be kept at reset value.
         volatile uint32_t res2  :4;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct CHSELR_t {
      enum { Offset = 0x28 };
      struct Bits {
         // Bits 17:0 CHSELx: Channel-x selection
         volatile bool CHSEL0   :1;
         volatile bool CHSEL1   :1;
         volatile bool CHSEL2   :1;
         volatile bool CHSEL3   :1;
         volatile bool CHSEL4   :1;
         volatile bool CHSEL5   :1;
         volatile bool CHSEL6   :1;
         volatile bool CHSEL7   :1;
         volatile bool CHSEL8   :1;
         volatile bool CHSEL9   :1;
         volatile bool CHSEL10  :1;
         volatile bool CHSEL11  :1;
         volatile bool CHSEL12  :1;
         volatile bool CHSEL13  :1;
         volatile bool CHSEL14  :1;
         volatile bool CHSEL15  :1;
         volatile bool CHSEL16  :1;
         // Bits 31:18 Reserved, must be kept at reset value.
         volatile uint32_t res1 :14;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };



   struct DR_t {
      enum { Offset = 0x40 };
      volatile uint32_t reg;
   };


   template<uint8_t n>
   struct Reserved {
      uint32_t reg[n];
   };

} // namespace ADC_ral {

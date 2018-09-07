#pragma once

#include "registr.h"


namespace ADC_detail {

struct SR_bits {
   bool     ADRDY :1; // Bit 0 ADRDY: ADC ready
   bool     EOSMP :1; // Bit 1 EOSMP: End of sampling flag
   bool     EOC   :1; // Bit 2 EOC: End of conversion flag
   bool     EOSEQ :1; // Bit 3 EOSEQ: End of sequence flag
   bool     OVR   :1; // Bit 4 OVR: ADC overrun
   uint32_t res1  :2; // Bit 6:5 Reserved, must be kept at reset value.
   bool     AWD   :1; // Bit 7 AWD: Analog watchdog flag
   uint32_t res2  :24; // Bits 31:8 Reserved, must be kept at reset value.
};


struct IER_bits {
   bool     ADRDYIE :1; // Bits 0 ADRDYIE: ADC ready interrupt enable
   bool     EOSMPIE :1; // Bit 1 EOSMPIE: End of sampling flag interrupt enable
   bool     EOCIE   :1; // Bit 2 EOCIE: End of conversion interrupt enable
   bool     EOSEQIE :1; // Bit 3 EOSEQIE: End of conversion sequence interrupt enable
   bool     OVRIE   :1; // Bit 4 OVRIE: Overrun interrupt enable
   uint32_t res1    :1; // Bit 6:5 Reserved, must be kept at reset value.
   bool     AWDIE   :1; // Bit 7 AWDIE: Analog watchdog interrupt enable
   uint32_t res2    :24; // Bits 31:8 Reserved, must be kept at reset value.
};


struct CR_bits {
   bool     ADEN    :1; // Bit 0 ADEN: ADC enable command
   bool     ADDIS   :1; // Bit 1 ADDIS: ADC disable command
   bool     ADSTART :1; // Bit 2 ADSTART: ADC start conversion command
   uint32_t res1    :1; // Bit 3 Reserved, must be kept at reset value.
   bool     ADSTP   :1; // Bit 4 ADSTP: ADC stop conversion command
   uint32_t res2    :26; // Bits 30:5 Reserved, must be kept at reset value.
   bool     ADCAL   :1;  // Bit 31 ADCAL: ADC calibration
};


struct CFGR1_bits {
   enum Resolution { _12bits = 0b00, _10bits, _8bits, _6bits }; 
   enum Trigger { _0 = 0b000, _1, _2, _3, _4, _5, _6, _7 };
   enum TriggerEn { Disable = 0b00, RisingEdge, FallingEdge, BothEdge };
   enum DMAmode { OneShot = 0b0, Circular };
   bool       DMAEN   :1; // Bit 0 DMAEN: Direct memory access enable
   DMAmode    DMACFG  :1; // Bit 1 DMACFG: Direct memory access configuration
   uint32_t   SCANDIR :1; // Bit 2 SCANDIR: Scan sequence direction
   Resolution RES     :2; // Bit 4:3 RES[1:0]: Data resolution
   Trigger    EXTSEL  :3; // Bits 8:6 EXTSEL[2:0]: External trigger selection
   TriggerEn  EXTEN   :2; // Bits 11:10 EXTEN[1:0]: External trigger enable and polarity selection
   uint32_t   OVRMOD  :1; // Bit 12 OVRMOD: Overrun management mode
   bool       CONT    :1; // Bit 13 CONT: Single / continuous conversion mode
   bool       WAIT    :1; // Bit 14 WAIT: Wait conversion mode
   bool       AUTOFF  :1; // Bit 15 AUTOFF: Auto-off mode
   bool       DISCEN  :1; // Bit 16 DISCEN: Discontinuous mode
   uint32_t   res1    :5; // Bits 21:17 Reserved, must be kept at reset value.
   uint32_t   AWDSGL  :1; // Bit 22 AWDSGL: Enable the watchdog on a single channel or on all channels
   bool       AWDEN   :1; // Bit 23 AWDEN: Analog watchdog enable
   uint32_t   res2    :2; // Bits 25:24 Reserved, must be kept at reset value.
   uint32_t   AWDCH   :5; // Bits 30:26 AWDCH[4:0]: Analog watchdog channel selection
   uint32_t   res3    :1; // Bit 31 Reserved, must be kept at reset value.
};


struct CFGR2_bits {
   enum Clock { Dedicated14MHzClock = 0b00, PCLKdiv2, PCLKdiv4 };
   uint32_t res1   :30; // Bits 29:0 Reserved, must be kept at reset value.
   Clock    CKMODE :2;  // Bits 31:30 CKMODE[1:0]: ADC clock mode
};


struct SMPR_bits {
   enum SampleTime { _1_5CLOCK = 0b000, _7_5CLOCK, _13_5CLOCK, _28_5CLOCK, _41_5CLOCK,
      _55_5CLOCK, _71_5CLOCK, _239_5CLOCK, Default = _239_5CLOCK
   };
   SampleTime SMP  :3;  // Bits 2:0 SMP[2:0]: Sampling time selection
   uint32_t   res1 :29; // Bits 31:3 Reserved, must be kept at reset value.
};


struct TR_bits {
   uint32_t LT    :12; // Bit 11:0 LT[11:0]: Analog watchdog lower threshold
   uint32_t res1  :4;  // Bits 15:12 Reserved, must be kept at reset value.
   uint32_t HT    :12; // Bit 27:16 HT[11:0]: Analog watchdog higher threshold
   uint32_t res2  :4;  // Bits 31:28 Reserved, must be kept at reset value.
};


struct CHSELR_bits {
   bool     CHSEL0  :1; // Bits 17:0 CHSELx: Channel-x selection
   bool     CHSEL1  :1;
   bool     CHSEL2  :1;
   bool     CHSEL3  :1;
   bool     CHSEL4  :1;
   bool     CHSEL5  :1;
   bool     CHSEL6  :1;
   bool     CHSEL7  :1;
   bool     CHSEL8  :1;
   bool     CHSEL9  :1;
   bool     CHSEL10 :1;
   bool     CHSEL11 :1;
   bool     CHSEL12 :1;
   bool     CHSEL13 :1;
   bool     CHSEL14 :1;
   bool     CHSEL15 :1;
   bool     CHSEL16 :1;
   bool     CHSEL17 :1;
   uint32_t res1    :14; // Bits 31:18 Reserved, must be kept at reset value.
};

} // namespace ADC_detail {

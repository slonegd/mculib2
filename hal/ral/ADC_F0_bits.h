#pragma once

#include "registr.h"


namespace ADC_ral {

struct SRbits {
   __IO bool     ADRDY :1; // Bit 0 ADRDY: ADC ready
   __IO bool     EOSMP :1; // Bit 1 EOSMP: End of sampling flag
   __IO bool     EOC   :1; // Bit 2 EOC: End of conversion flag
   __IO bool     EOSEQ :1; // Bit 3 EOSEQ: End of sequence flag
   __IO bool     OVR   :1; // Bit 4 OVR: ADC overrun
   __IO uint32_t res1  :2; // Bit 6:5 Reserved, must be kept at reset value.
   __IO bool     AWD   :1; // Bit 7 AWD: Analog watchdog flag
   __IO uint32_t res2  :24; // Bits 31:8 Reserved, must be kept at reset value.
};

struct IERbits {
   __IO bool     ADRDYIE :1; // Bits 0 ADRDYIE: ADC ready interrupt enable
   __IO bool     EOSMPIE :1; // Bit 1 EOSMPIE: End of sampling flag interrupt enable
   __IO bool     EOCIE   :1; // Bit 2 EOCIE: End of conversion interrupt enable
   __IO bool     EOSEQIE :1; // Bit 3 EOSEQIE: End of conversion sequence interrupt enable
   __IO bool     OVRIE   :1; // Bit 4 OVRIE: Overrun interrupt enable
   __IO uint32_t res1    :1; // Bit 6:5 Reserved, must be kept at reset value.
   __IO bool     AWDIE   :1; // Bit 7 AWDIE: Analog watchdog interrupt enable
   __IO uint32_t res2    :24; // Bits 31:8 Reserved, must be kept at reset value.
};

struct CRbits {
   __IO bool     ADEN    :1; // Bit 0 ADEN: ADC enable command
   __IO bool     ADDIS   :1; // Bit 1 ADDIS: ADC disable command
   __IO bool     ADSTART :1; // Bit 2 ADSTART: ADC start conversion command
   __IO uint32_t res1    :1; // Bit 3 Reserved, must be kept at reset value.
   __IO bool     ADSTP   :1; // Bit 4 ADSTP: ADC stop conversion command
   __IO uint32_t res2    :26; // Bits 30:5 Reserved, must be kept at reset value.
   __IO bool     ADCAL   :1;  // Bit 31 ADCAL: ADC calibration
};

enum Resolution { _12bits = 0b00, _10bits, _8bits, _6bits }; 
enum Trigger { _0 = 0b000, _1, _2, _3, _4, _5, _6, _7 };
enum TriggerEn { Disable = 0b00, RisingEdge, FallingEdge, BothEdge };
enum DMAmode { OneShot = 0b0, Circular };

struct CFGR1bits {
   __IO bool       DMAEN   :1; // Bit 0 DMAEN: Direct memory access enable
   __IO DMAmode    DMACFG  :1; // Bit 1 DMACFG: Direct memory access configuration
   __IO uint32_t   SCANDIR :1; // Bit 2 SCANDIR: Scan sequence direction
   __IO Resolution RES     :2; // Bit 4:3 RES[1:0]: Data resolution
   __IO Trigger    EXTSEL  :3; // Bits 8:6 EXTSEL[2:0]: External trigger selection
   __IO TriggerEn  EXTEN   :2; // Bits 11:10 EXTEN[1:0]: External trigger enable and polarity selection
   __IO uint32_t   OVRMOD  :1; // Bit 12 OVRMOD: Overrun management mode
   __IO bool       CONT    :1; // Bit 13 CONT: Single / continuous conversion mode
   __IO bool       WAIT    :1; // Bit 14 WAIT: Wait conversion mode
   __IO bool       AUTOFF  :1; // Bit 15 AUTOFF: Auto-off mode
   __IO bool       DISCEN  :1; // Bit 16 DISCEN: Discontinuous mode
   __IO uint32_t   res1    :5; // Bits 21:17 Reserved, must be kept at reset value.
   __IO uint32_t   AWDSGL  :1; // Bit 22 AWDSGL: Enable the watchdog on a single channel or on all channels
   __IO bool       AWDEN   :1; // Bit 23 AWDEN: Analog watchdog enable
   __IO uint32_t   res2    :2; // Bits 25:24 Reserved, must be kept at reset value.
   __IO uint32_t   AWDCH   :5; // Bits 30:26 AWDCH[4:0]: Analog watchdog channel selection
   __IO uint32_t   res3    :1; // Bit 31 Reserved, must be kept at reset value.
};

enum Clock { Dedicated14MHzClock = 0b00, PCLKdiv2, PCLKdiv4 };

struct CFGR2bits {
   __IO uint32_t res1   :30; // Bits 29:0 Reserved, must be kept at reset value.
   __IO Clock    CKMODE :2; // Bits 31:30 CKMODE[1:0]: ADC clock mode
};

enum SampleTime { _1_5_ADCclockCycles = 0b000, _7_5_ADCclockCycles,
   _13_5_ADCclockCycles, _28_5_ADCclockCycles, _41_5_ADCclockCycles,
   _55_5_ADCclockCicle, _71_5_ADCclockCicle, _239_5_ADCclockCicle
};

struct SMPRbits {
   __IO SampleTime SMP  :3; // Bits 2:0 SMP[2:0]: Sampling time selection
   __IO uint32_t   res1 :29; // Bits 31:3 Reserved, must be kept at reset value.
};

struct TRbits {
   __IO uint32_t LT    :12; // Bit 11:0 LT[11:0]: Analog watchdog lower threshold
   __IO uint32_t res1  :4; // Bits 15:12 Reserved, must be kept at reset value.
   __IO uint32_t HT    :12; // Bit 27:16 HT[11:0]: Analog watchdog higher threshold
   __IO uint32_t res2  :4; // Bits 31:28 Reserved, must be kept at reset value.
};

struct CHSELRbits {
   __IO bool     CHSEL0  :1; // Bits 17:0 CHSELx: Channel-x selection
   __IO bool     CHSEL1  :1;
   __IO bool     CHSEL2  :1;
   __IO bool     CHSEL3  :1;
   __IO bool     CHSEL4  :1;
   __IO bool     CHSEL5  :1;
   __IO bool     CHSEL6  :1;
   __IO bool     CHSEL7  :1;
   __IO bool     CHSEL8  :1;
   __IO bool     CHSEL9  :1;
   __IO bool     CHSEL10 :1;
   __IO bool     CHSEL11 :1;
   __IO bool     CHSEL12 :1;
   __IO bool     CHSEL13 :1;
   __IO bool     CHSEL14 :1;
   __IO bool     CHSEL15 :1;
   __IO bool     CHSEL16 :1;
   __IO bool     CHSEL17 :1;
   __IO uint32_t res1    :14; // Bits 31:18 Reserved, must be kept at reset value.
};

struct SR_t     : BitsRegistr<SRbits>,     Offset_t<0x00> {};
struct IER_t    : BitsRegistr<IERbits>,    Offset_t<0x04> {};
struct CR_t     : BitsRegistr<CRbits>,     Offset_t<0x08> {};
struct CFGR1_t  : BitsRegistr<CFGR1bits>,  Offset_t<0x0C> {};
struct CFGR2_t  : BitsRegistr<CFGR2bits>,  Offset_t<0x10> {};
struct SMPR_t   : BitsRegistr<SMPRbits>,   Offset_t<0x14> {};
struct TR_t     : BitsRegistr<TRbits>,     Offset_t<0x20> {};
struct CHSELR_t : BitsRegistr<CHSELRbits>, Offset_t<0x28> {};
struct DR_t     : DataRegistr,             Offset_t<0x40> {};



} // namespace ADC_ral {

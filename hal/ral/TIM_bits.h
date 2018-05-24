#pragma once

#include "registr.h"

namespace TIM_ral {

enum OnePulseMode { notStopped  = 0b0, counterStop };
enum Direction { up  = 0b0, down };

struct CR1bits {
   __IO bool CEN         :1; // Bit 0 CEN: Counter enable
   __IO uint32_t UDIS    :1; // Bit 1 UDIS: Update disable
   __IO uint32_t URS     :1; // Bit 2 URS: Update request source
   __IO OnePulseMode OPM :1; // Bit 3 OPM: One-pulse mode
   __IO Direction DIR    :1; // Bit 4 DIR: Direction
   __IO uint32_t CMS     :2; // Bits 6:5 CMS: Center-aligned mode selection
   __IO bool ARPE        :1; // Bit 7 ARPE: Auto-reload preload enable
   __IO uint32_t CKD     :2; // Bits 9:8 CKD: Clock division
   __IO uint32_t res     :22; // Bits 31:10 Reserved, must be kept at reset value.
};

struct CR1position {
   enum { CEN = 0, UDIS, URS, OPM, DIR, CMS, ARPE = 7, CKD };
};

struct CR2bits {
   __IO uint32_t res1  :3; // Bits 2:0 Reserved, must be kept at reset value.
   __IO uint32_t CCDS  :1; // Bit 3 CCDS: Capture/compare DMA selection
   __IO uint32_t MMS   :3; // Bits 6:4 MMS[2:0]: Master mode selection
   __IO uint32_t TI1S  :1; // Bit 7 TI1S: TI1 selection
   __IO uint32_t res2  :24; // Bits 15:8 Reserved, must be kept at reset value.
};

enum ExternalTriggerPolarity { notInverted = 0b0, inverted };
enum Trigger { _0 = 0b000, _1, _2, _3, TI1edge, FiltrTI1, FiltrTI2, External };
enum SlaveMode { SMDisabled = 0b000, Encoder1, Encoder2, Encoder3, Reset, Gated, TriggerMode, ExternalClock };

struct SMCRbits {
   __IO SlaveMode               SMS  :3; // Bits 2:0 SMS: Slave mode selection
   __IO uint32_t                OCCS :1; // Bit 3 OCCS: OCREF clear selection.
   __IO Trigger                 TS   :3; // Bits 6:4 TS[2:0]: Trigger selection
   __IO uint32_t                MSM  :1; // Bit 7 MSM: Master/slave mode
   __IO uint32_t                ETF  :4; // Bits 11:8 ETF[3:0]: External trigger filter
   __IO uint32_t                ETPS :2; // Bits 13:12 ETPS[1:0]: External trigger prescaler
   __IO uint32_t                ECE  :1; // Bit 14 ECE: External clock enable
   __IO ExternalTriggerPolarity ETP  :1; // Bit 15 ETP: External trigger polarity
   __IO uint32_t                res1 :16;
};

struct SMCRposition {
   enum { SMS, OCCS = 3, TS, MSM = 7, ETF = 8, ETPS = 12, ECE = 14, ETP };
};

struct DIERbits {
   __IO bool     UIE   :1; // Bit 0 UIE: Update interrupt enable
   __IO bool     CC1IE :1; // Bit 1 CC1IE: Capture/Compare 1 interrupt enable
   __IO bool     CC2IE :1; // Bit 2 CC2IE: Capture/Compare 2 interrupt enable
   __IO bool     CC3IE :1; // Bit 3 CC2IE: Capture/Compare 3 interrupt enable
   __IO bool     CC4IE :1; // Bit 4 CC2IE: Capture/Compare 4 interrupt enable
   __IO uint32_t res1  :1; // Bit 5 Reserved, must be kept at reset value.
   __IO bool     TIE   :1; // Bit 6 TIE: Trigger interrupt enable
   __IO uint32_t res2  :1; // Bit 7 Reserved, must be kept at reset value.
   __IO bool     UDE   :1; // Bit 8 UDE: Update DMA request enable
   __IO bool     CC1DE :1; // Bit 9 CC1DE: Capture/Compare 1 DMA request enable
   __IO bool     CC2DE :1; // Bit 10 CC1DE: Capture/Compare 2 DMA request enable
   __IO bool     CC3DE :1; // Bit 11 CC1DE: Capture/Compare 3 DMA request enable
   __IO bool     CC4DE :1; // Bit 12 CC1DE: Capture/Compare 4 DMA request enable
   __IO uint32_t res3  :1; // Bit 13 Reserved, always read as 0.
   __IO bool     TDE   :1; // Bit 14 TDE: Trigger DMA request enable
   __IO uint32_t res4  :17; // Bit 15 Reserved, must be kept at reset value.
};

enum CompareMode { Off = 0b000, ActiveOnMatch, InactiveOnMatch, ToggleOnMatch,
   ForceInactive, ForceActive, PWMmode, InvertedPWMmode
};
enum SelectionCompareMode { Output, InputTIFirst, InputTISecond, InputTRC };  

struct CCMRbits {
   __IO SelectionCompareMode CC1S     :2; // Bits 1:0 CC1S: Capture/Compare 1 selection
   __IO bool                 OC1FE    :1; // Bit 2 OC1FE: Output compare 1 fast enable
   __IO bool                 OC1PE    :1; // Bit 3 OC1PE: Output compare 1 preload enable
   __IO CompareMode          OC1M     :3; // Bits 6:4 OC1M: Output compare 1 mode
   __IO bool                 OC1CE    :1; // Bit 7 OC1CE: Output compare 1 clear enable
   __IO SelectionCompareMode CC2S     :2;
   __IO bool                 OC2FE    :1;
   __IO bool                 OC2PE    :1;
   __IO CompareMode          OC2M     :3;
   __IO bool                 OC2CE    :1;
   __IO uint32_t             res1     :16;
   __IO SelectionCompareMode CC3S     :2;
   __IO bool                 OC3FE    :1;
   __IO bool                 OC3PE    :1;  
   __IO CompareMode          OC3M     :3;
   __IO bool                 OC3CE    :1;
   __IO SelectionCompareMode CC4S     :2;
   __IO bool                 OC4FE    :1;
   __IO bool                 OC4PE    :1;
   __IO CompareMode          OC4M     :3;
   __IO bool                 OC4CE    :1;
   __IO uint32_t             res2     :16;
};

/// CC1P и CC1NP в CCERbits без смещения
enum  OutputPolarity { rising = 0b0000, faling = 0b0010, both = 0b1010, reset = 0b1010 };

struct CCERbits {
   __IO bool     CC1E  :1; // Bit 0 CC1E: Capture/Compare 1 output enable.
   __IO uint32_t CC1P  :1; // Bit 1 CC1P: Capture/Compare 1 output Polarity.
   __IO uint32_t res1  :1; // Bit 2 Reserved, must be kept at reset value.
   __IO uint32_t CC1NP :1; // Bit 3 CC1NP: Capture/Compare 1 output Polarity.
   __IO bool     CC2E  :1;
   __IO uint32_t CC2P  :1;
   __IO uint32_t res2  :1;
   __IO uint32_t CC2NP :1;
   __IO bool     CC3E  :1;
   __IO uint32_t CC3P  :1;
   __IO uint32_t res3  :1;
   __IO uint32_t CC3NP :1;
   __IO bool     CC4E  :1;
   __IO uint32_t CC4P  :1;
   __IO uint32_t res4  :1;
   __IO uint32_t CC4NP :1;
   __IO uint32_t res5  :16;
};


struct BDTRbits {
   __IO uint32_t DTG  :8; // Bits 7:0 DTG[7:0]: Dead-time generator setup
   __IO uint32_t LOCK :2; // Bits 9:8 LOCK[1:0]: Lock configuration
   __IO uint32_t OSSI :1; // Bit 10 OSSI: Off-state selection for Idle mode
   __IO uint32_t OSSR :1; // Bit 11 OSSR: Off-state selection for Run mode
   __IO bool     BKE  :1; // Bit 12 BKE: Break enable
   __IO uint32_t BKP  :1; // Bit 13 BKP: Break polarity
   __IO uint32_t AOE  :1; // Bit 14 AOE: Automatic output enable
   __IO bool     MOE  :1; // Bit 15 MOE: Main output enable__IO uint32_t res1 :16; 
};

struct DCRbits {
   __IO uint32_t DBA  :5; // Bits 4:0 DBA[4:0]: DMA base address
   __IO uint32_t res1 :3; // Bits 7:5 Reserved, must be kept at reset value.
   __IO uint32_t DBL  :5; // Bits 12:8 DBL[4:0]: DMA burst length
   __IO uint32_t res2 :19; // Bits 31:13 Reserved, must be kept at reset value.
};

struct CR1_t  : BitsRegistr<CR1bits>,   Offset_t<0x00>, CR1position {};
struct CR2_t  : BitsRegistr<CR2bits>,   Offset_t<0x04> {};
struct SMCR_t : BitsRegistr<SMCRbits>,  Offset_t<0x08>, SMCRposition {};
struct DIER_t : BitsRegistr<DIERbits>,  Offset_t<0x0C> {};
struct SR_t   : DataRegistr,            Offset_t<0x10> {};
struct EGR_t  : DataRegistr,            Offset_t<0x14> {};
struct CCMR_t : BitsRegistrs<CCMRbits>, Offset_t<0x18> {};
struct CCER_t : BitsRegistr<CCERbits>,  Offset_t<0x20> {};
struct CNT_t  : DataRegistr,            Offset_t<0x24> {};
struct PSC_t  : DataRegistr,            Offset_t<0x28> {};
struct ARR_t  : DataRegistr,            Offset_t<0x2C> {};
struct RCR_t  : DataRegistr,            Offset_t<0x30> {};
struct CCR_t  : ArrayDataRegistr<4>,    Offset_t<0x34> {};
struct BDTR_t : BitsRegistr<BDTRbits>,  Offset_t<0x44> {};
struct DCR_t  : BitsRegistr<DCRbits>,   Offset_t<0x48> {};
struct DMAR_t : DataRegistr,            Offset_t<0x4C> {};

} // namespace


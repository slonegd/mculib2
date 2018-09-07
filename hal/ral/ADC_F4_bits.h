#pragma once

#include "registr.h"

namespace ADC_detail {

struct SR_bits {
   bool     AWD   :1;  // Bit 0 AWD: Analog watchdog flag
   bool     EOC   :1;  // Bit 1 EOC: Regular channel end of conversion
   bool     JEOC  :1;  // Bit 2 JEOC: Injected channel end of conversion
   bool     JSTRT :1;  // Bit 3 JSTRT: Injected channel start flag
   bool     STRT  :1;  // Bit 4 STRT: Regular channel start flag
   bool     OVR   :1;  // Bit 5 OVR: Overrun
   uint32_t res1  :26; // Bits 31:6 Reserved, must be kept at reset value.
};

struct CR1_bits {
   enum Resolution { _12bits  = 0b00, _10bits, _8bits, _6bits };
   uint32_t   AWDCH   :5; // Bits 4:0 AWDCH[4:0]: Analog watchdog channel select bits
   bool       EOCIE   :1; // Bit 5 EOCIE: Interrupt enable for EOC
   bool       AWDIE   :1; // Bit 6 AWDIE: Analog watchdog interrupt enable
   bool       JEOCIE  :1; // Bit 7 JEOCIE: Interrupt enable for injected channels
   bool       SCAN    :1; // Bit 8 SCAN: Scan mode
   uint32_t   AWDSGL  :1; // Bit 9 AWDSGL: Enable the watchdog on a single channel in scan mode
   bool       JAUTO   :1; // Bit 10 JAUTO: Automatic injected group conversion
   bool       DISCEN  :1; // Bit 11 DISCEN: Discontinuous mode on regular channels
   bool       JDISCEN :1; // Bit 12 JDISCEN: Discontinuous mode on injected channels
   uint32_t   DISCNUM :3; // Bits 15:13 DISCNUM[2:0]: Discontinuous mode channel count
   uint32_t   res1    :6; // Bits 21:16 Reserved, must be kept at reset value.
   bool       JAWDEN  :1; // Bit 22 JAWDEN: Analog watchdog enable on injected channels
   bool       AWDEN   :1; // Bit 23 AWDEN: Analog watchdog enable on regular channels
   Resolution RES     :2; // Bits 25:24 RES[1:0]: Resolution
   bool       OVRIE   :1; // Bit 26 OVRIE: Overrun interrupt enable
   uint32_t   res2    :5; // Bits 31:27 Reserved, must be kept at reset value.
};

struct CR2_bits {
   enum EventsInjected {
      iTimer1CC4 = 0b0000,
      iTimer1TRGO,
      iTimer2CC1, iTimer2TRGO,
      iTimer3CC2, iTimer3CC4, 
      iTimer4CC1, iTimer4CC2, iTimer4CC3, iTimer4TRGO,
      iTimer5CC4, iTimer5TRGO,
      iTimer8CC2, iTimer8CC3, iTimer8CC4,
      iEXTI15
   };
   enum TriggerEn { Disable = 0b00, RisingEdge, FallingEdge, BothEdge };
   enum EventsRegular {
      rTimer1CC1 = 0b0000,
      rTimer1CC2, rTimer1CC3,
      rTimer2CC2, rTimer2CC3, rTimer2CC4, rTimer2TRGO,
      rTimer3CC1, rTimer3TRGO,
      rTimer4CC4,
      rTimer5CC1, rTimer5CC2, rTimer5CC3,
      rTimer8CC1, rTimer8TRG0,
      rEXTI11
   };
   bool           ADON     :1; // Bit 0 ADON: A/D Converter ON / OFF
   bool           CONT     :1; // Bit 1 CONT: Continuous conversion
   uint32_t       res1     :6; // Bits 7:2 Reserved, must be kept at reset value.
   bool           DMA      :1; // Bit 8 DMA: Direct memory access mode (for single ADC mode)
   bool           DDS      :1; // Bit 9 DDS: DMA disable selection (for single ADC mode)
   bool           EOCS     :1; // Bit 10 EOCS: End of conversion selection
   uint32_t       ALIGN    :1; // Bit 11 ALIGN: Data alignment
   uint32_t       res2     :4; // Bits 15:12 Reserved, must be kept at reset value.
   EventsInjected JEXTSEL  :4; // Bits 19:16 JEXTSEL[3:0]: External event select for injected group
   TriggerEn      JEXTEN   :2; // Bits 21:20 JEXTEN: External trigger enable for injected channels
   bool           JSWSTART :1; // Bit 22 JSWSTART: Start conversion of injected channels
   uint32_t       res3     :1; // Bit 23 Reserved, must be kept at reset value.
   EventsRegular  EXTSEL   :4; // Bits 27:24 EXTSEL[3:0]: External event select for regular group
   TriggerEn      EXTEN    :2; // Bits 29:28 EXTEN: External trigger enable for regular channels
   bool           SWSTART  :1; // Bit 30 SWSTART: Start conversion of regular channels
   bool           res4     :1; // Bit 31 Reserved, must be kept at reset value.
};



struct SMPR_bits {
   enum SampleTime { _3CLK = 0b000, _15CLK = 0b001, _28CLK = 0b010, _56CLK = 0b011, _84CLK = 0b100,
      _112CLK = 0b101, _144CLK = 0b110, _480CLK = 0b111, Default = _480CLK
   };
   // какой-то адский глюк, не принимает SampleTime, считает его размер более 3 бит
   uint32_t SMP10 :3; // Bits 26:0 SMPx[2:0]: Channel x sampling time selection
   uint32_t SMP11 :3;
   uint32_t SMP12 :3;
   uint32_t SMP13 :3;
   uint32_t SMP14 :3;
   uint32_t SMP15 :3;
   uint32_t SMP16 :3;
   uint32_t SMP17 :3;
   uint32_t SMP18 :3;
   uint32_t res1  :5; // Bits 31: 27 Reserved, must be kept at reset value.
   uint32_t SMP0  :3; // Bits 29:0 SMPx[2:0]: Channel x sampling time selection
   uint32_t SMP1  :3;
   uint32_t SMP2  :3;
   uint32_t SMP3  :3;
   uint32_t SMP4  :3;
   uint32_t SMP5  :3;
   uint32_t SMP6  :3;
   uint32_t SMP7  :3;
   uint32_t SMP8  :3;
   uint32_t SMP9  :3;
   uint32_t res2  :2; // Bits 31:30 Reserved, must be kept at reset value.
};

struct SQR_bits {
   uint32_t SQ13 :5; // Bits 4:0 SQ13[4:0]: 13th conversion in regular sequence
   uint32_t SQ14 :5;
   uint32_t SQ15 :5;
   uint32_t SQ16 :5;
   uint32_t L    :4; // Bits 23:20 L[3:0]: Regular channel sequence length
   uint32_t res1 :8;
   uint32_t SQ7  :5; // Bits 4:0 SQ7[4:0]: 7th conversion in regular sequence
   uint32_t SQ8  :5;
   uint32_t SQ9  :5;
   uint32_t SQ10 :5;
   uint32_t SQ11 :5;
   uint32_t SQ12 :5; 
   uint32_t res2 :2;
   uint32_t SQ1  :5; // Bits 4:0 SQ1[4:0]: 1st conversion in regular sequence
   uint32_t SQ2  :5;
   uint32_t SQ3  :5;
   uint32_t SQ4  :5;
   uint32_t SQ5  :5;
   uint32_t SQ6  :5; 
   uint32_t res3 :2;
};

} // namespace ADC_detail {

   
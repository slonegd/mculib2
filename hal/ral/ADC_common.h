#pragma once
#include "registr.h"

#if defined(STM32F405xx)

namespace ADC_ral {

struct CSRbits {
   __IO bool    AWD   :1; // Bit 0 AWD: Analog watchdog flag
   __IO bool    EOC   :1; // Bit 1 EOC1: End of conversion
   __IO bool    JEOC  :1; // Bit 2 JEOC1: Injected channel end of conversion
   __IO bool    JSTRT :1; // Bit 3 JSTRT1: Injected channel Start flag
   __IO bool    STRT  :1; // Bit 4 STRT1: Regular channel Start flag
   __IO bool    OVR   :1; // Bit 5 OVR1: Overrun flag
   __IO uint8_t res1  :2; // Bits 7:6 Reserved, must be kept at reset value.
};

enum Delay { CLKx5 = 0b0000, CLKx6, CLKx7, CLKx8, CLKx9, CLKx10, CLKx11, CLKx12,
   CLKx13, CLKx14, CLKx15, CLKx16, CLKx17, CLKx18, CLKx19, CLKx20
};
enum Clock { PCLKdiv2 = 0b00, PCLKdiv4, PCLKdiv6, PCLKdiv8 };

struct CCRbits {
   __IO uint32_t MULTI   :5; // Bits 4:0 MULTI[4:0]: Multi ADC mode selection
   __IO uint32_t res1    :3; // Bits 7:5 Reserved, must be kept at reset value.
   __IO Delay    DELAY   :4; // Bits 11:8 DELAY: Delay between 2 sampling phases
   __IO uint32_t res2    :1; // Bit 12 Reserved, must be kept at reset value.
   __IO bool     DDS     :1; // Bit 13 DDS: DMA disable selection (for multi-ADC mode)
   __IO uint32_t DMA     :2; // Bits 15:14 DMA: Direct memory access mode for multi ADC mode
   __IO Clock    ADCPRE  :2; // Bits 17:16 ADCPRE: ADC prescaler
   __IO uint32_t res3    :4; // Bits 21:18 Reserved, must be kept at reset value.
   __IO bool     VBATE   :1; // Bit 22 VBATE: V BAT enable
   __IO bool     TSVREFE :1; // Bit 23 TSVREFE: Temperature sensor and V REFINT enable
   __IO uint32_t res4    :8; // Bits 31:24 Reserved, must be kept at reset value.
};

struct CCRposition {
   enum { MULTI = 0, DELAY = 8, DDS = 13, DMA, ADCPRE = 16, VBATE = 22, TSVREFE };
};

struct CSR_t : BitsRegistrs<CSRbits, uint8_t>, Offset_t<0x00> {};
struct CCR_t : BitsRegistr<CCRbits>          , Offset_t<0x04>, CCRposition {};
struct CDR_t : DataRegistr                   , Offset_t<0x08> {};

} // namespace ADC_ral {




class ADCC
{
public:
   using Clock = ADC_ral::Clock;


   static constexpr uint32_t Base = ADC1_BASE + 0x300;

   ADCC() = delete;
   void makeDebugVar() { control().bits.res1 = 0; }

   static void setClock (Clock val)
   {
      uint32_t tmp = control().reg;
      tmp &= ~_2BIT_TO_MASK(control(), ADCPRE);
      tmp |= VAL_TO_MASK(control(), ADCPRE, val);
      control().reg = tmp;
   }



protected:
#define MakeRef(Reg,Ref) ADC_ral::Reg& Ref() { return (ADC_ral::Reg&) *(uint32_t*)(Base + ADC_ral::Reg::Offset); }
   static volatile MakeRef(CSR_t, status );
   static volatile MakeRef(CCR_t, control);
   static volatile MakeRef(CDR_t, data   );
#undef MakeRef
private:
   ADC_ral::CSR_t CSR; // ADC Common status register
   Reserve_t<1, uint8_t> reserve1;
   ADC_ral::CCR_t CCR; // ADC common control register
   ADC_ral::CDR_t CDR; // DC common regular data register for dual AND triple modes
};


#endif
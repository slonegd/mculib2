#pragma once

#include "registr.h"
#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif

namespace GPIO_ral {
   enum  Mode_t {Input = 0b00, Output = 0b01, Alternate = 0b10, Analog = 0b11};

struct MODERbits {
   __IO Mode_t MODER0	:2;
   __IO Mode_t MODER1	:2;
   __IO Mode_t MODER2	:2;
   __IO Mode_t MODER3	:2;
   __IO Mode_t MODER4	:2;
   __IO Mode_t MODER5	:2;
   __IO Mode_t MODER6	:2;
   __IO Mode_t MODER7	:2;
   __IO Mode_t MODER8	:2;
   __IO Mode_t MODER9	:2;
   __IO Mode_t MODER10	:2;
   __IO Mode_t MODER11	:2;
   __IO Mode_t MODER12	:2;
   __IO Mode_t MODER13	:2;
   __IO Mode_t MODER14	:2;
   __IO Mode_t MODER15	:2;        
};


enum  OutType_t {PushPull = 0b0, OpenDrain = 0b1};

struct OTYPERbits {
   __IO OutType_t OT0	:1;
   __IO OutType_t OT1	:1;
   __IO OutType_t OT2	:1;
   __IO OutType_t OT3	:1;
   __IO OutType_t OT4	:1;
   __IO OutType_t OT5	:1;
   __IO OutType_t OT6	:1;
   __IO OutType_t OT7	:1;
   __IO OutType_t OT8	:1;
   __IO OutType_t OT9	:1;
   __IO OutType_t OT10	:1;
   __IO OutType_t OT11	:1;
   __IO OutType_t OT12	:1;
   __IO OutType_t OT13	:1;
   __IO OutType_t OT14	:1;
   __IO OutType_t OT15	:1;
   // Bits 31:16 Reserved, must be kept at reset value.
   uint32_t dcb1	:16;
};

enum OutSpeed_t {
   Low	    = 0b00,
   Medium	 = 0b01,
   High	    = 0b10,
#if defined(STM32F405xx)
   VeryHigh	 = 0b11
#endif
};
struct OSPEEDRbits{
   __IO OutSpeed_t OSPEEDR0	:2;
   __IO OutSpeed_t OSPEEDR1	:2;
   __IO OutSpeed_t OSPEEDR2	:2;
   __IO OutSpeed_t OSPEEDR3	:2;
   __IO OutSpeed_t OSPEEDR4	:2;
   __IO OutSpeed_t OSPEEDR5	:2;
   __IO OutSpeed_t OSPEEDR6	:2;
   __IO OutSpeed_t OSPEEDR7	:2;
   __IO OutSpeed_t OSPEEDR8	:2;
   __IO OutSpeed_t OSPEEDR9	:2;
   __IO OutSpeed_t OSPEEDR10	:2;
   __IO OutSpeed_t OSPEEDR11	:2;
   __IO OutSpeed_t OSPEEDR12	:2;
   __IO OutSpeed_t OSPEEDR13	:2;
   __IO OutSpeed_t OSPEEDR14	:2;
   __IO OutSpeed_t OSPEEDR15	:2;
};

enum PullResistor_t {
   No	  = 0b00,
   Up   = 0b01,
   Down = 0b10
};
struct PUPDRbits {
   __IO PullResistor_t PUPDR0	   :2;
   __IO PullResistor_t PUPDR1	   :2;
   __IO PullResistor_t PUPDR2	   :2;
   __IO PullResistor_t PUPDR3	   :2;
   __IO PullResistor_t PUPDR4	   :2;
   __IO PullResistor_t PUPDR5	   :2;
   __IO PullResistor_t PUPDR6	   :2;
   __IO PullResistor_t PUPDR7	   :2;
   __IO PullResistor_t PUPDR8	   :2;
   __IO PullResistor_t PUPDR9	   :2;
   __IO PullResistor_t PUPDR10   :2;
   __IO PullResistor_t PUPDR11   :2;
   __IO PullResistor_t PUPDR12   :2;
   __IO PullResistor_t PUPDR13   :2;
   __IO PullResistor_t PUPDR14   :2;
   __IO PullResistor_t PUPDR15   :2;
};

struct IDRbits {
   __IO bool _0  :1;
   __IO bool _1  :1;
   __IO bool _2  :1;
   __IO bool _3  :1;
   __IO bool _4  :1;
   __IO bool _5  :1;
   __IO bool _6  :1;
   __IO bool _7  :1;
   __IO bool _8  :1;
   __IO bool _9  :1;
   __IO bool _10 :1;
   __IO bool _11 :1;
   __IO bool _12 :1;
   __IO bool _13 :1;
   __IO bool _14 :1;
   __IO bool _15 :1;
   __IO uint32_t res1 :16;
};
 
enum AF {
   _0 = 0b0000, _1, _2, _3, _4, _5, _6, _7,
#if defined(STM32F405xx)
   _8, _9, _10, _11, _12, _13, _14, _15
#endif
   };
struct AFRbits {
   __IO AF AFR0    : 4;
   __IO AF AFR1    : 4;
   __IO AF AFR2    : 4;
   __IO AF AFR3    : 4;
   __IO AF AFR4    : 4;
   __IO AF AFR5    : 4;
   __IO AF AFR6    : 4;
   __IO AF AFR7    : 4;
   __IO AF AFR8    : 4;
   __IO AF AFR9    : 4;
   __IO AF AFR10   : 4;
   __IO AF AFR11   : 4;
   __IO AF AFR12   : 4;
   __IO AF AFR13   : 4;
   __IO AF AFR14   : 4;
   __IO AF AFR15   : 4;
};
 


struct MODER_t    : BitsRegistr<MODERbits>,     Offset_t<0x00>{};
struct OTYPER_t   : BitsRegistr<OTYPERbits>,    Offset_t<0x04>{};
struct OSPEEDR_t  : BitsRegistr<OSPEEDRbits>,   Offset_t<0x08>{};
struct PUPDR_t    : BitsRegistr<PUPDRbits>,     Offset_t<0x0C>{};
struct IDR_t      : BitsRegistr<IDRbits>,       Offset_t<0x10>{};
struct ODR_t      : DataRegistr,                Offset_t<0x14>{};
struct BSRR_t     : DataRegistr,                Offset_t<0x18>{};
struct LCKR_t     : DataRegistr,                Offset_t<0x1C>{};
struct AFR_t      : ArrayDataRegistr<2>,       Offset_t<0x20>{};

};



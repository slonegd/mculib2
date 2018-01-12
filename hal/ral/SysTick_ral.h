#pragma once
/*
#include <stdint.h>
#include <stdbool.h>*/
#include "stm32f4xx.h"

namespace SysTick_ral {

    struct CTRL_t {
        enum { Offset = 0x00 };
        volatile uint32_t reg;
    };

    struct LOAD_t {
        enum { Offset = 0x04 };
        volatile uint32_t reg;
    };

    struct VAL_t {
        enum { Offset = 0x08 };
        volatile uint32_t reg;
    };

    struct CALIB_t {
        enum { Offset = 0x0C };
        volatile uint32_t reg;
    };

}

/*
typedef struct
{
  __IOM uint32_t CTRL;  //Offset: 0x000 (R/W)  SysTick Control and Status Register 
  __IOM uint32_t LOAD;  //Offset: 0x004 (R/W)  SysTick Reload Value Register 
  __IOM uint32_t VAL;   //Offset: 0x008 (R/W)  SysTick Current Value Register 
  __IM  uint32_t CALIB; //Offset: 0x00C (R/ )  SysTick Calibration Register 
} SysTick_Type;
*/

struct SysTick_t : public SysTick_ral::CTRL_t,
                   public SysTick_ral::LOAD_t,
                   public SysTick_ral::VAL_t,
                   public SysTick_ral::CALIB_t
{ };

class SysTick_ : SysTick_t
{
public:
    static uint32_t get() { return value().reg; } 
protected:
    static volatile SysTick_ral::CTRL_t   &control()     
    { return (SysTick_ral::CTRL_t &)   (*(SysTick_Type*)SysTick_BASE).CTRL;   }

    static volatile SysTick_ral::LOAD_t   &load()  
    { return (SysTick_ral::LOAD_t &)   (*(SysTick_Type*)SysTick_BASE).LOAD;   }

    static volatile SysTick_ral::VAL_t    &value()
    { return (SysTick_ral::VAL_t &)    (*(SysTick_Type*)SysTick_BASE).VAL;    }

    static volatile SysTick_ral::CALIB_t  &calib()
    { return (SysTick_ral::CALIB_t &)  (*(SysTick_Type*)SysTick_BASE).CALIB;  }
     
};

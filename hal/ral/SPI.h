#pragma once


#if defined(STM32F030x6)
#include "SPI_F0_bits.h"
#endif
#include "DMA.h"

#if defined(STM32F030x6)



template<uint32_t adr>
class SPIx
{
public:
   using Div      = SPI_ral::Div;
   using DataSize = SPI_ral::DataSize;
   using DMAtx    = DMA1channel3;

   static constexpr uint32_t Base = adr;

   SPIx() = delete;
   static SPIx<adr>* create() { return reinterpret_cast<SPIx<adr>*>(Base); } 
   void doSome() { conf1().bits.res1 = 0; }

   static uint32_t getDataAdr();
   static void     clockEnable();
   static void     setAsMaster();
   static void     slaveSelectEnable();
   static void     txDMAenable();
   static void     enable();
   static void     slaveSelectPulseEnable();
   template<Div>      static void setBoudRate();
   template<DataSize> static void setDataSize();



protected:
#define MakeRef(Reg,Ref) SPI_ral::Reg& Ref() { return (SPI_ral::Reg&) *(uint32_t*)(Base + SPI_ral::Reg::Offset); }
   static __IO MakeRef (CR1_t,    conf1      );
   static __IO MakeRef (CR2_t,    conf2      );
   static __IO MakeRef (SR_t,     status     );
   static __IO MakeRef (DR_t,     data       );
   static __IO MakeRef (CRCPR_t,  CRCpolinom );
   static __IO MakeRef (RXCRCR_t, CRCrx      );
   static __IO MakeRef (TXCRCR_t, CRCtx      );
#undef MakeRef



private:
   SPI_ral::CR1_t     CR1;     // Control register 1 (not used in I2S mode)
   SPI_ral::CR2_t     CR2;     // Control register 2
   SPI_ral::SR_t      SR;      // Status register
   SPI_ral::DR_t      DR;      // data register
   SPI_ral::CRCPR_t   CRCPR;   // CRC polynomial register (not used in I2S mode)
   SPI_ral::RXCRCR_t  RXCRCR;  // Rx CRC register (not used in I2S mode)
   SPI_ral::TXCRCR_t  TXCRCR;  // Tx CRC register (not used in I2S mode)
   SPI_ral::I2SCFGR_t I2SCFGR; // I2S configuration register
};


#undef SPI1
using SPI1 = SPIx<SPI1_BASE>;

#endif

// #if defined(STM32F405xx)

// #undef SPI2
// using SPI2 = SPIx<SPI2_BASE>;
// #undef SPI3
// using SPI3 = SPIx<SPI3_BASE>;

// #endif




#include "SPI_src.h"
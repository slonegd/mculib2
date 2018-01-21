/**
 * RAL над регистрами SPI
 */

#pragma once

#include <stdint.h>
#if defined(STM32F030x6)
#include "stm32f0xx.h"
#elif defined(STM32F405xx)
#include "stm32f4xx.h"
#endif


namespace SPI_ral {

   struct CR1_t {
      enum { Offset = 0x00 };
      enum Div {
         Div2 = 0b000, Div4, Div8, Div16, Div32, Div64, Div128, Div256
      };
      enum CRCLength {
         _8bits = 0b0, _16bits
      };
      struct Bits {
         // Bit 0 CPHA: Clock phase
         volatile uint32_t CPHA :1;
         // Bit1 CPOL: Clock polarity
         volatile uint32_t CPOL :1;
         // Bit 2 MSTR: Master selection
         volatile bool MSTR     :1;
         // Bits 5:3 BR[2:0]: Baud rate control
         volatile Div BR        :3;
         // Bit 6 SPE: SPI enable
         volatile bool SPE      :1;
         // Bit 7 LSBFIRST: Frame format
         volatile bool LSBFIRST :1;
         // Bit 8 SSI: Internal slave select
         volatile uint32_t SSI  :1;
         // Bit 9 SSM: Software slave management
         volatile bool SSM      :1;
         // Bit 10 RXONLY: Receive only mode enabled.
         volatile bool RXONLY   :1;
         // Bit 11 CRCL: CRC length
         volatile CRCLength     :1;
         // Bit 12 CRCNEXT: Transmit CRC next
         volatile bool CRCNEXT  :1;
         // Bit 13 CRCEN: Hardware CRC calculation enable
         volatile bool CRCEN    :1;
         // Bit 14 BIDIOE: Output enable in bidirectional mode
         volatile bool BIDIOE   :1;
         // Bit 15 BIDIMODE: Bidirectional data mode enable.
         volatile bool BIDIMODE :1;
         volatile uint32_t res1 :16;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   }; 


   struct CR2_t {
      enum { Offset = 0x04 };
      enum Format {
         Motorolla = 0b0, TI
      };
      enum DataSize {
         _4bits = 0b0011, _5bits, _6bits, _7bits, _8bits, _10bits, _11bits, 
         _12bits, _13bits, _14bits, _15bits, _16bits
      };
      struct Bits {
         // Bit 0 RXDMAEN: Rx buffer DMA enable
         volatile bool RXDMAEN     :1;
         // Bit 1 TXDMAEN: Tx buffer DMA enable
         volatile bool TXDMAEN     :1;
         // Bit 2 SSOE: SS output enable
         volatile bool SSOE        :1;
         // Bit 3 NSSP : NSS pulse management
         volatile bool NSSP        :1;
         // Bit 4 FRF: Frame format
         volatile Format FRF       :1;
         // Bit 5 ERRIE: Error interrupt enable
         volatile bool ERRIE       :1;
         // Bit 6 RXNEIE: RX buffer not empty interrupt enable
         volatile bool RXNEIE      :1;
         // Bit 7 TXEIE: Tx buffer empty interrupt enable
         volatile bool TXEIE       :1;
         // Bits 11:8 DS [3:0]: Data size
         volatile DataSize DS      :4;
         // Bit 12 FRXTH: FIFO reception threshold
         volatile uint32_t FRXTH   :1;
         // Bit 13 LDMA_RX: Last DMA transfer for reception
         volatile uint32_t LDMA_RX :1;
         // Bit 14 LDMA_TX: Last DMA transfer for transmission
         volatile uint32_t LDMA_TX :1;
         // Bit 15 Reserved, must be kept at reset value.
         volatile uint32_t res1    :17; 
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };


   struct SR_t {
      enum { Offset = 0x08 };
      enum FIFOlevel {
         empty = 0b00, quarter, half, full 
      };
      struct Bits {
         // Bit 0 RXNE: Receive buffer not empty
         volatile bool RXNE       :1;
         // Bit 1 TXE: Transmit buffer empty
         volatile bool TXE        :1;
         // Bits 3:2 Reserved, must be kept at reset value.
         volatile uint32_t res1   :2;
         // Bit 4 CRCERR: CRC error flag
         volatile bool CRCERR     :1;
         // Bit 5 MODF: Mode fault
         volatile bool MODF       :1;
         // Bit 6 OVR: Overrun flag
         volatile bool OVR        :1;
         // Bit 7 BSY: Busy flag
         volatile bool BSY        :1;
         // Bit 8 FRE: Frame format error
         volatile bool FRE        :1;
         // Bits 10:9 FRLVL[1:0]: FIFO reception level
         volatile FIFOlevel FRLVL :2;
         // Bits 12:11 FTLVL[1:0]: FIFO Transmission Level
         volatile FIFOlevel FTLVL :2;
         // Bits 15:13 Reserved, must be kept at reset value.
         volatile uint32_t res2   :19;
      };
      union {
         volatile Bits bits;
         volatile uint32_t reg;
      };
   };


   struct DR_t {
      enum { Offset = 0x0C };
      struct {
         volatile uint16_t reg;
         volatile uint16_t reserve;
      };
   };


   struct CRCPR_t {
      enum { Offset = 0x10 };
      struct {
         volatile uint16_t reg;
         volatile uint16_t reserve;
      };
   };


   struct RXCRCR_t {
      enum { Offset = 0x14 };
      struct {
         volatile uint16_t reg;
         volatile uint16_t reserve;
      };
   };


   struct TXCRCR_t {
      enum { Offset = 0x18 };
      struct {
         volatile uint16_t reg;
         volatile uint16_t reserve;
      };
   };
} // namespace
/*
typedef struct
{
  __IO uint32_t CR1;     // SPI Control register 1 (not used in I2S mode),      Address offset: 0x00
  __IO uint32_t CR2;     // SPI Control register 2,                             Address offset: 0x04
  __IO uint32_t SR;      // SPI Status register,                                Address offset: 0x08
  __IO uint32_t DR;      // SPI data register,                                  Address offset: 0x0C
  __IO uint32_t CRCPR;   // SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10
  __IO uint32_t RXCRCR;  // SPI Rx CRC register (not used in I2S mode),         Address offset: 0x14
  __IO uint32_t TXCRCR;  // SPI Tx CRC register (not used in I2S mode),         Address offset: 0x18
  __IO uint32_t I2SCFGR; // SPI_I2S configuration register,                     Address offset: 0x1C
} SPI_TypeDef;
*/

template<uint32_t BaseAdr>
class SPI_ : private SPI_ral::CR1_t,
             private SPI_ral::CR2_t,
             private SPI_ral::SR_t,
             private SPI_ral::DR_t,
             private SPI_ral::CRCPR_t,
             private SPI_ral::RXCRCR_t,
             private SPI_ral::TXCRCR_t
{
public:
   static const uint32_t Base = BaseAdr;


   void makeDebugVar() { conf1().bits.res1 = 0; }
   static void SetAsMaster() { conf1().reg |= SPI_CR1_MSTR_Msk; }



protected:
#define MakeRef(Reg,Ref) SPI_ral::Reg& Ref() { return (SPI_ral::Reg&) *(uint32_t*)(Base + SPI_ral::Reg::Offset); }
   static volatile MakeRef(CR1_t, conf1);
   static volatile MakeRef(CR2_t, conf2);
   static volatile MakeRef(SR_t, status);
   static volatile MakeRef(DR_t, data);
   static volatile MakeRef(CRCPR_t, CRCpolinom);
   static volatile MakeRef(RXCRCR_t, CRCrx);
   static volatile MakeRef(TXCRCR_t, CRCtx);

};

using SPI1_ = SPI_<SPI1_BASE>;
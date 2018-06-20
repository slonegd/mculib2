#pragma once

#include "registr.h"

namespace SPI_ral {

enum Div { Div2 = 0b000, Div4, Div8, Div16, Div32, Div64, Div128, Div256 };
enum CRCLength { crc8 = 0b0, crc16 };

struct CR1bits {
   uint32_t  CPHA     :1; // Bit 0 CPHA: Clock phase
   uint32_t  CPOL     :1; // Bit1 CPOL: Clock polarity
   bool      MSTR     :1; // Bit 2 MSTR: Master selection
   Div       BR       :3; // Bits 5:3 BR[2:0]: Baud rate control
   bool      SPE      :1; // Bit 6 SPE: SPI enable
   bool      LSBFIRST :1; // Bit 7 LSBFIRST: Frame format
   uint32_t  SSI      :1; // Bit 8 SSI: Internal slave select
   bool      SSM      :1; // Bit 9 SSM: Software slave management
   bool      RXONLY   :1; // Bit 10 RXONLY: Receive only mode enabled.
   CRCLength CRCL     :1; // Bit 11 CRCL: CRC length
   bool      CRCNEXT  :1; // Bit 12 CRCNEXT: Transmit CRC next
   bool      CRCEN    :1; // Bit 13 CRCEN: Hardware CRC calculation enable
   bool      BIDIOE   :1; // Bit 14 BIDIOE: Output enable in bidirectional mode
   bool      BIDIMODE :1; // Bit 15 BIDIMODE: Bidirectional data mode enable.
   uint32_t  res1 :16;
};

struct CR1position {
   enum { CPHA = 0, CPOL, MSTR, BR, SPE = 6, LSBFIRST, SSI, SSM, RXONLY, CRCL, CRCNEXT, CRCEN, BIDIOE, BIDIMODE };
};

enum Format { Motorolla = 0b0, TI };
enum DataSize { _4bits = 0b0011, _5bits, _6bits, _7bits, _8bits, _10bits, _11bits, _12bits, _13bits, _14bits, _15bits, _16bits };

struct CR2bits {
   bool     RXDMAEN :1; // Bit 0 RXDMAEN: Rx buffer DMA enable
   bool     TXDMAEN :1; // Bit 1 TXDMAEN: Tx buffer DMA enable
   bool     SSOE    :1; // Bit 2 SSOE: SS output enable
   bool     NSSP    :1; // Bit 3 NSSP : NSS pulse management
   Format   FRF     :1; // Bit 4 FRF: Frame format
   bool     ERRIE   :1; // Bit 5 ERRIE: Error interrupt enable
   bool     RXNEIE  :1; // Bit 6 RXNEIE: RX buffer not empty interrupt enable
   bool     TXEIE   :1; // Bit 7 TXEIE: Tx buffer empty interrupt enable
   DataSize DS      :4; // Bits 11:8 DS [3:0]: Data size
   uint32_t FRXTH   :1; // Bit 12 FRXTH: FIFO reception threshold
   uint32_t LDMA_RX :1; // Bit 13 LDMA_RX: Last DMA transfer for reception
   uint32_t LDMA_TX :1; // Bit 14 LDMA_TX: Last DMA transfer for transmission
   uint32_t res1    :17; // Bit 15 Reserved, must be kept at reset value.
};

struct CR2position {
   enum { RXDMAEN = 0, TXDMAEN, SSOE, NSSP, FRF, ERRIE, RXNEIE, TXEIE, DS, FRXTH = 12, LDMA_RX, LDMA_TX };
};

enum FIFOlevel { empty = 0b00, quarter, half, full };

struct SRbits {
   bool      RXNE   :1; // Bit 0 RXNE: Receive buffer not empty
   bool      TXE    :1; // Bit 1 TXE: Transmit buffer empty
   uint32_t  res1   :2; // Bits 3:2 Reserved, must be kept at reset value.
   bool      CRCERR :1; // Bit 4 CRCERR: CRC error flag
   bool      MODF   :1; // Bit 5 MODF: Mode fault
   bool      OVR    :1; // Bit 6 OVR: Overrun flag
   bool      BSY    :1; // Bit 7 BSY: Busy flag
   bool      FRE    :1; // Bit 8 FRE: Frame format error
   FIFOlevel FRLVL  :2; // Bits 10:9 FRLVL[1:0]: FIFO reception level
   FIFOlevel FTLVL  :2; // Bits 12:11 FTLVL[1:0]: FIFO Transmission Level
   uint32_t  res2   :19; // Bits 15:13 Reserved, must be kept at reset value.
};

struct SRposition {
   enum { RXNE = 0, TXE, CRCERR = 4, MODF, OVR, BSY, FRE, FRLVL, FTLVL= 11 };
};


struct CR1_t     : BitsRegistr<CR1bits>, Offset_t<0x00>, CR1position {};
struct CR2_t     : BitsRegistr<CR2bits>, Offset_t<0x04>, CR2position {};
struct SR_t      : BitsRegistr<SRbits> , Offset_t<0x08>, SRposition  {};
struct DR_t      : DataRegistr         , Offset_t<0x0C>              {};
struct CRCPR_t   : DataRegistr         , Offset_t<0x10>              {};
struct RXCRCR_t  : DataRegistr         , Offset_t<0x14>              {};
struct TXCRCR_t  : DataRegistr         , Offset_t<0x18>              {};
struct I2SCFGR_t : DataRegistr         , Offset_t<0x1C>              {};

} // namespace SPI_ral {


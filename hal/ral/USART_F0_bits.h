#pragma once

#include "registr.h"

namespace USART_ral {

enum Parity     { even = 0b0, odd     };

struct CR1bits {
   bool     UE     :1; // Bit 0 UE: USART enable
   uint32_t res1   :1; // Bit 1 Reserved, must be kept at reset value.
   bool     RE     :1; // Bit 2 RE: Receiver enable
   bool     TE     :1; // Bit 3 TE: Transmitter enable
   bool     IDLEIE :1; // Bit 4 IDLEIE: IDLE interrupt enable
   bool     RXNEIE :1; // Bit 5 RXNEIE: RXNE interrupt enable
   bool     TCIE   :1; // Bit 6 TCIE: Transmission complete interrupt enable
   bool     TXEIE  :1; // Bit 7 TXEIE: interrupt enable
   bool     PEIE   :1; // Bit 8 PEIE: PE interrupt enable
   Parity   PS     :1; // Bit 9 PS: Parity selection
   bool     PCE    :1; // Bit 10 PCE: Parity control enable
   uint32_t WAKE   :1; // Bit 11 WAKE: Receiver wakeup method
   uint32_t M0     :1; // Bit 12 M0: Word length
   bool     MME    :1; // Bit 13 MME: Mute mode enable
   bool     CMIE   :1; // Bit 14 CMIE: Character match interrupt enable
   uint32_t OVER8  :1; // Bit 15 OVER8: Oversampling mode
   uint32_t DEDT   :5; // Bits 20:16 DEDT[4:0]: Driver Enable de-assertion time
   uint32_t DEAT   :5; // Bits 25:21 DEAT[4:0]: Driver Enable assertion time
   bool     RTOIE  :1; // Bit 26 RTOIE: Receiver timeout interrupt enable
   uint32_t res2   :1; // Bit 27
   uint32_t M1     :1; // Bit 28 M1: Word length
   uint32_t res3   :3; // Bits 31:29 Reserved, must be kept at reset value
};

struct CR1position {
   enum { UE = 0, RE = 2, TE, IDLEIE, RXNEIE, TCIE, TXEIE, PEIE, PS, PCE, WAKE,
      M0, MME, CMIE, OVER8, DEDT, DEAT = 21, RTOIE = 26, M1 = 28
   };
};

enum StopBits       { _1 = 0b00, _2 = 0b10 };

struct CR2bits {
   uint32_t res1     :4; // Bits 3:0 Reserved, must be kept at reset value.
   uint32_t ADDM7    :1; // Bit 4 ADDM7:7-bit Address Detection/4-bit Address Detection
   uint32_t res2     :3; // Bits 7:5 Reserved, must be kept at reset value.
   uint32_t LBCL     :1; // Bit 8 LBCL: Last bit clock pulse
   uint32_t CPHA     :1; // Bit 9 CPHA: Clock phase
   uint32_t CPOL     :1; // Bit 10 CPOL: Clock polarity
   bool     CLKEN    :1; // Bit 11 CLKEN: Clock enable
   StopBits STOP     :2; // Bits 13:12 STOP[1:0]: STOP bits
   uint32_t res3     :1; // Bit 14 Reserved, must be kept at reset value.
   uint32_t SWAP     :1; // Bit 15 SWAP: Swap TX/RX pins
   bool     RXINV    :1; // Bit 16 RXINV: RX pin active level inversion
   bool     TXINV    :1; // Bit 17 TXINV: TX pin active level inversion
   bool     DATAINV  :1; // Bit 18 DATAINV: Binary data inversion
   uint32_t MSBFIRST :1; // Bit 19 MSBFIRST: Most significant bit first
   bool     ABREN    :1; // Bit 20 ABREN: Auto baud rate enable
   uint32_t ABRMOD   :2; // Bits 22:21 ABRMOD[1:0]: Auto baud rate mode
   uint32_t RTOEN    :1; // Bit 23 RTOEN: Receiver timeout enable
   uint32_t ADD1     :4; // Bits 27:24 ADD[3:0]: Address of the USART node
   uint32_t ADD2     :4; // Bits 31:28 ADD[7:4]: Address of the USART node
};

struct CR2position {
   enum { ADDM7 = 4, LBCL = 8, CPHA, CPOL, CLKEN, STOP, SWAP = 15,
      RXINV, TXINV, DATAINV, MSBFIRST, ABREN, ABRMOD, RTOEN = 23, ADD1, ADD2 = 28
   };
};

struct CR3bits {
   bool     EIE    :1; // Bit 0 EIE: Error interrupt enable
   uint32_t res1   :2; // Bits 2:1 Reserved, must be kept at reset value.
   bool     HDSEL  :1; // Bit 3 HDSEL: Half-duplex selection
   uint32_t res2   :2; // Bits 5:4 Reserved, must be kept at reset value.
   bool     DMAR   :1; // Bit 6 DMAR: DMA enable receiver
   bool     DMAT   :1; // Bit 7 DMAT: DMA enable transmitter
   bool     RTSE   :1; // Bit 8 RTSE: RTS enable
   bool     CTSE   :1; // Bit 9 CTSE: CTS enable
   bool     CTSIE  :1; // Bit 10 CTSIE: CTS interrupt enable
   bool     ONEBIT :1; // Bit 11 ONEBIT: One sample bit method enable
   bool     OVRDIS :1; // Bit 12 OVRDIS: Overrun Disable
   bool     DDRE   :1; // Bit 13 DDRE: DMA Disable on Reception Error
   bool     DEM    :1; // Bit 14 DEM: Driver enable mode
   bool     DEP    :1; // Bit 15 DEP: Driver enable polarity selection
   uint32_t res3   :16; // Bits 31:16 Reserved, must be kept at reset value.
};

struct CR3position {
   enum { EIE = 0, HDSEL = 3, DMAR = 6, DMAT, RTSE, CTSE, CTSIE, ONEBIT, OVRDIS, DDRE, DEM, DEP };
};

struct RQRbits {
   uint32_t ABRRQ :1; // Bit 0 ABRRQ: Auto baud rate request
   uint32_t SBKRQ :1; // Bit 1 SBKRQ: Send break request
   uint32_t MMRQ  :1; // Bit 2 MMRQ: Mute mode request
   uint32_t RXFRQ :1; // Bit 3 RXFRQ: Receive data flush request
   uint32_t res1  :28; // Bits 31:4 Reserved, must be kept at reset value
};

struct SRbits {
   bool     PE    :1; // Bit 0 PE: Parity error
   bool     FE    :1; // Bit 1 FE: Framing error
   bool     NF    :1; // Bit 2 NF: START bit Noise detection flag
   bool     ORE   :1; // Bit 3 ORE: Overrun error
   bool     IDLE  :1; // Bit 4 IDLE: Idle line detected
   bool     RXNE  :1; // Bit 5 RXNE: Read data register not empty
   bool     TC    :1; // Bit 6 TC: Transmission complete
   bool     TXE   :1; // Bit 7 TXE: Transmit data register empty
   uint32_t res1  :1; // Bit 8 Reserved, must be kept at reset value.
   bool     CTSIF :1; // Bit 9 CTSIF: CTS interrupt flag
   bool     CTS   :1; // Bit 10 CTS: CTS flag
   bool     RTOF  :1; // Bit 11 RTOF: Receiver timeout
   uint32_t res2  :2; // Bits 13:12 Reserved, must be kept at reset value.
   bool     ABRE  :1; // Bit 14 ABRE: Auto baud rate error
   bool     ABRF  :1; // Bit 15 ABRF: Auto baud rate flag
   bool     BUSY  :1; // Bit 16 BUSY: Busy flag
   bool     CMF   :1; // Bit 17 CMF: Character match flag
   bool     SBKF  :1; // Bit 18 SBKF: Send break flag
   bool     RWU   :1; // Bit 19 RWU: Receiver wakeup from Mute mode
   uint32_t res3  :12; // Bits 31:20 Reserved, must be kept at reset value.
};

struct SRposition {
   enum { PE = 0, FE, NF, ORE, IDLE, RXNE, TC, TXE, CTSIF = 9,
      CTS, RTOF, ABRE = 14, ABRF, BUSY, CMF, SBKF, RWU
   };
};

struct ICRbits {
   bool     PECF   :1; // Bit 0 PECF: Parity error clear flag
   bool     FECF   :1; // Bit 1 FECF: Framing error clear flag
   bool     NCF    :1; // Bit 2 NCF: Noise detected clear flag
   bool     ORECF  :1; // Bit 3 ORECF: Overrun error clear flag
   bool     IDLECF :1; // Bit 4 IDLECF: Idle line detected clear flag
   uint32_t res1   :1; // Bit 5 Reserved, must be kept at reset value.
   bool     TCCF   :1; // Bit 6 TCCF: Transmission complete clear flag
   uint32_t res2   :2; // Bits 8:7 Reserved, must be kept at reset value.
   bool     CTSCF  :1; // Bit 9 CTSCF: CTS clear flag
   uint32_t res3   :1; // Bit 10 Reserved, must be kept at reset value.
   bool     RTOCF  :1; // Bit 11 RTOCF: Receiver timeout clear flag
   uint32_t res4   :5; // Bits 16:12 Reserved, must be kept at reset value.
   bool     CMCF   :1; // Bit 17 CMCF: Character match clear flag
   uint32_t res5   :14; // Bits 31:18 Reserved, must be kept at reset value.
};

struct ICRposition {
   enum { PECF = 0, FECF, NCF, ORECF, IDLECF, TCCF = 6, CTSCF = 9, RTOCF = 11, CMCF = 17 };
};


struct CR1_t  : BitsRegistr<CR1bits>, Offset_t<0x00>, CR1position {};
struct CR2_t  : BitsRegistr<CR2bits>, Offset_t<0x04>, CR2position {};
struct CR3_t  : BitsRegistr<CR3bits>, Offset_t<0x08>, CR3position {};
struct BRR_t  : DataRegistr,          Offset_t<0x0C>              {};
struct RTOR_t : DataRegistr,          Offset_t<0x14>              {};
struct RQR_t  : BitsRegistr<RQRbits>, Offset_t<0x18>              {};
struct SR_t   : BitsRegistr<SRbits>,  Offset_t<0x1C>, SRposition  {};
struct ICR_t  : BitsRegistr<ICRbits>, Offset_t<0x20>, ICRposition {};
struct RDR_t  : DataRegistr,          Offset_t<0x24>              {};
struct TDR_t  : DataRegistr,          Offset_t<0x28>              {};

} // namespace USART_ral


#pragma once

#include "registr.h"

namespace USART_ral {

enum Parity     { even = 0b0, odd     };

struct CR1bits {
   __IO bool     UE     :1; // Bit 0 UE: USART enable
   __IO bool     RE     :1; // Bit 2 RE: Receiver enable
   __IO bool     TE     :1; // Bit 3 TE: Transmitter enable
   __IO bool     IDLEIE :1; // Bit 4 IDLEIE: IDLE interrupt enable
   __IO bool     RXNEIE :1; // Bit 5 RXNEIE: RXNE interrupt enable
   __IO bool     TCIE   :1; // Bit 6 TCIE: Transmission complete interrupt enable
   __IO bool     TXEIE  :1; // Bit 7 TXEIE: interrupt enable
   __IO bool     PEIE   :1; // Bit 8 PEIE: PE interrupt enable
   __IO Parity   PS     :1; // Bit 9 PS: Parity selection
   __IO bool     PCE    :1; // Bit 10 PCE: Parity control enable
   __IO uint32_t WAKE   :1; // Bit 11 WAKE: Receiver wakeup method
   __IO uint32_t M0     :1; // Bit 12 M0: Word length
   __IO bool     MME    :1; // Bit 13 MME: Mute mode enable
   __IO bool     CMIE   :1; // Bit 14 CMIE: Character match interrupt enable
   __IO uint32_t OVER8  :1; // Bit 15 OVER8: Oversampling mode
   __IO uint32_t DEDT   :5; // Bits 20:16 DEDT[4:0]: Driver Enable de-assertion time
   __IO uint32_t DEAT   :5; // Bits 25:21 DEAT[4:0]: Driver Enable assertion time
   __IO bool     RTOIE  :1; // Bit 26 RTOIE: Receiver timeout interrupt enable
   __IO uint32_t res1   :1; // Bit 27
   __IO uint32_t M1     :1; // Bit 28 M1: Word length
   __IO uint32_t res2   :3; // Bits 31:29 Reserved, must be kept at reset value
};

enum StopBits       { _1 = 0b00, _2 = 0b10 };

struct CR2bits {
   __IO uint32_t res1     :4; // Bits 3:0 Reserved, must be kept at reset value.
   __IO uint32_t ADDM7    :1; // Bit 4 ADDM7:7-bit Address Detection/4-bit Address Detection
   __IO uint32_t res2     :3; // Bits 7:5 Reserved, must be kept at reset value.
   __IO uint32_t LBCL     :1; // Bit 8 LBCL: Last bit clock pulse
   __IO uint32_t CPHA     :1; // Bit 9 CPHA: Clock phase
   __IO uint32_t CPOL     :1; // Bit 10 CPOL: Clock polarity
   __IO bool     CLKEN    :1; // Bit 11 CLKEN: Clock enable
   __IO StopBits STOP     :2; // Bits 13:12 STOP[1:0]: STOP bits
   __IO uint32_t res3     :1; // Bit 14 Reserved, must be kept at reset value.
   __IO uint32_t SWAP     :1; // Bit 15 SWAP: Swap TX/RX pins
   __IO bool     RXINV    :1; // Bit 16 RXINV: RX pin active level inversion
   __IO bool     TXINV    :1; // Bit 17 TXINV: TX pin active level inversion
   __IO bool     DATAINV  :1; // Bit 18 DATAINV: Binary data inversion
   __IO uint32_t MSBFIRST :1; // Bit 19 MSBFIRST: Most significant bit first
   __IO bool     ABREN    :1; // Bit 20 ABREN: Auto baud rate enable
   __IO uint32_t ABRMOD   :2; // Bits 22:21 ABRMOD[1:0]: Auto baud rate mode
   __IO uint32_t RTOEN    :1; // Bit 23 RTOEN: Receiver timeout enable
   __IO uint32_t ADD1     :4; // Bits 27:24 ADD[3:0]: Address of the USART node
   __IO uint32_t ADD2     :4; // Bits 31:28 ADD[7:4]: Address of the USART node
};

struct CR3bits {
   __IO bool     EIE    :1; // Bit 0 EIE: Error interrupt enable
   __IO uint32_t res1   :2; // Bits 2:1 Reserved, must be kept at reset value.
   __IO bool     HDSEL  :1; // Bit 3 HDSEL: Half-duplex selection
   __IO uint32_t res2   :2; // Bits 5:4 Reserved, must be kept at reset value.
   __IO bool     DMAR   :1; // Bit 6 DMAR: DMA enable receiver
   __IO bool     DMAT   :1; // Bit 7 DMAT: DMA enable transmitter
   __IO bool     RTSE   :1; // Bit 8 RTSE: RTS enable
   __IO bool     CTSE   :1; // Bit 9 CTSE: CTS enable
   __IO bool     CTSIE  :1; // Bit 10 CTSIE: CTS interrupt enable
   __IO bool     ONEBIT :1; // Bit 11 ONEBIT: One sample bit method enable
   __IO bool     OVRDIS :1; // Bit 12 OVRDIS: Overrun Disable
   __IO bool     DDRE   :1; // Bit 13 DDRE: DMA Disable on Reception Error
   __IO bool     DEM    :1; // Bit 14 DEM: Driver enable mode
   __IO bool     DEP    :1; // Bit 15 DEP: Driver enable polarity selection
   __IO uint32_t res3   :16; // Bits 31:16 Reserved, must be kept at reset value.
};

struct RQRbits {
   __IO uint32_t ABRRQ :1; // Bit 0 ABRRQ: Auto baud rate request
   __IO uint32_t SBKRQ :1; // Bit 1 SBKRQ: Send break request
   __IO uint32_t MMRQ  :1; // Bit 2 MMRQ: Mute mode request
   __IO uint32_t RXFRQ :1; // Bit 3 RXFRQ: Receive data flush request
   __IO uint32_t res1  :28; // Bits 31:4 Reserved, must be kept at reset value
};

struct ISRbits {
   __IO bool     PE    :1; // Bit 0 PE: Parity error
   __IO bool     FE    :1; // Bit 1 FE: Framing error
   __IO bool     NF    :1; // Bit 2 NF: START bit Noise detection flag
   __IO bool     ORE   :1; // Bit 3 ORE: Overrun error
   __IO bool     IDLE  :1; // Bit 4 IDLE: Idle line detected
   __IO bool     RXNE  :1; // Bit 5 RXNE: Read data register not empty
   __IO bool     TC    :1; // Bit 6 TC: Transmission complete
   __IO bool     TXE   :1; // Bit 7 TXE: Transmit data register empty
   __IO uint32_t res1  :1; // Bit 8 Reserved, must be kept at reset value.
   __IO bool     CTSIF :1; // Bit 9 CTSIF: CTS interrupt flag
   __IO bool     CTS   :1; // Bit 10 CTS: CTS flag
   __IO bool     RTOF  :1; // Bit 11 RTOF: Receiver timeout
   __IO uint32_t res2  :2; // Bits 13:12 Reserved, must be kept at reset value.
   __IO bool     ABRE  :1; // Bit 14 ABRE: Auto baud rate error
   __IO bool     ABRF  :1; // Bit 15 ABRF: Auto baud rate flag
   __IO bool     BUSY  :1; // Bit 16 BUSY: Busy flag
   __IO bool     CMF   :1; // Bit 17 CMF: Character match flag
   __IO bool     SBKF  :1; // Bit 18 SBKF: Send break flag
   __IO bool     RWU   :1; // Bit 19 RWU: Receiver wakeup from Mute mode
   __IO uint32_t res3  :12; // Bits 31:20 Reserved, must be kept at reset value.
};

struct ICRbits {
   __IO bool     PECF   :1; // Bit 0 PECF: Parity error clear flag
   __IO bool     FECF   :1; // Bit 1 FECF: Framing error clear flag
   __IO bool     NCF    :1; // Bit 2 NCF: Noise detected clear flag
   __IO bool     ORECF  :1; // Bit 3 ORECF: Overrun error clear flag
   __IO bool     IDLECF :1; // Bit 4 IDLECF: Idle line detected clear flag
   __IO uint32_t res1   :1; // Bit 5 Reserved, must be kept at reset value.
   __IO bool     TCCF   :1; // Bit 6 TCCF: Transmission complete clear flag
   __IO uint32_t res2   :2; // Bits 8:7 Reserved, must be kept at reset value.
   __IO bool     CTSCF  :1; // Bit 9 CTSCF: CTS clear flag
   __IO uint32_t res3   :1; // Bit 10 Reserved, must be kept at reset value.
   __IO bool     RTOCF  :1; // Bit 11 RTOCF: Receiver timeout clear flag
   __IO uint32_t res4   :5; // Bits 16:12 Reserved, must be kept at reset value.
   __IO bool     CMCF   :1; // Bit 17 CMCF: Character match clear flag
   __IO uint32_t res5   :14; // Bits 31:18 Reserved, must be kept at reset value.
};

struct ICRposition {
   enum { PECF = 0, FECF, NCF, ORECF, IDLECF, TCCF = 6, CTSCF = 9, RTOCF = 11, CMCF = 17 };
};


struct CR1_t  : BitsRegistr<CR1bits>, Offset_t<0x00> {};
struct CR2_t  : BitsRegistr<CR2bits>, Offset_t<0x04> {};
struct CR3_t  : BitsRegistr<CR3bits>, Offset_t<0x08> {};
struct BRR_t  : DataRegistr,          Offset_t<0x0C> {};
struct RTOR_t : DataRegistr,          Offset_t<0x14> {};
struct RQR_t  : BitsRegistr<RQRbits>, Offset_t<0x18> {};
struct ISR_t  : BitsRegistr<ISRbits>, Offset_t<0x1C> {};
struct ICR_t  : BitsRegistr<ICRbits>, Offset_t<0x20>, ICRposition {};
struct RDR_t  : DataRegistr,          Offset_t<0x24> {};
struct TDR_t  : DataRegistr,          Offset_t<0x28> {};

} // namespace USART_ral


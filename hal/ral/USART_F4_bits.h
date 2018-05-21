#pragma once

#include "registr.h"

namespace USART_ral {

struct SRbits {
   __IO bool     PE   :1; // Bit 0 PE: Parity error
   __IO bool     FE   :1; // Bit 1 FE: Framing error
   __IO bool     NF   :1; // Bit 2 NF: Noise detected flag
   __IO bool     ORE  :1; // Bit 3 ORE: Overrun error
   __IO bool     IDLE :1; // Bit 4 IDLE: IDLE line detected
   __IO bool     RXNE :1; // Bit 5 RXNE: Read data register not empty
   __IO bool     TC   :1; // Bit 6 TC: Transmission complete
   __IO bool     TXE  :1; // Bit 7 TXE: Transmit data register empty
   __IO bool     LBD  :1; // Bit 8 LBD: LIN break detection flag
   __IO bool     CTS  :1; // Bit 9 CTS: CTS flag
   __IO uint32_t res1 :22; // Bits 31:10 Reserved, must be kept at reset value
};

enum Parity     { even = 0b0, odd     };
enum WakeMethod { idle = 0b0, address };
enum DataBits   { _8   = 0b0, _9      };
enum OverSample { by8  = 0b0, by16    };

struct CR1bits {
   __IO bool       SBK    :1; // Bit 0 SBK: Send break
   __IO bool       RWU    :1; // Bit 1 RWU: Receiver wakeup
   __IO bool       RE     :1; // Bit 2 RE: Receiver enable
   __IO bool       TE     :1; // Bit 3 TE: Transmitter enable
   __IO bool       IDLEIE :1; // Bit 4 IDLEIE: IDLE interrupt enable
   __IO bool       RXNEIE :1; // Bit 5 RXNEIE: RXNE interrupt enable
   __IO bool       TCIE   :1; // Bit 6 TCIE: Transmission complete interrupt enable
   __IO bool       TXEIE  :1; // Bit 7 TXEIE: TXE interrupt enable
   __IO bool       PEIE   :1; // Bit 8 PEIE: PE interrupt enable
   __IO Parity     PS     :1; // Bit 9 PS: Parity selection
   __IO bool       PCE    :1; // Bit 10 PCE: Parity control enable
   __IO WakeMethod WAKE   :1; // Bit 11 WAKE: Wakeup method
   __IO DataBits   M      :1; // Bit 12 M: Word length
   __IO bool       UE     :1; // Bit 13 UE: USART enable
   __IO uint32_t   res1   :1; // Bit 14 Reserved, must be kept at reset value
   __IO OverSample OVER8  :1; // Bit 15 OVER8: Oversampling mode
   __IO uint32_t   res2   :16; // Bits 31:16 Reserved, must be kept at reset value
};

struct CR1position {
   enum { SBK = 0, RWU, RE, TE, IDLEIE, RXNEIE, TCIE, TXEIE, PEIE,
      PS, PCE, WAKE, M, UE, OVER8 = 15
   };
};

enum BreakDetection { _10bit = 0b0, _11bit };
enum StopBits       { _1 = 0b00, _0_5, _2, _1_5 };

struct CR2bits {
   __IO uint32_t       ADD   :4; // Bits 3:0 ADD[3:0]: Address of the USART node
   __IO uint32_t       res1  :1; // Bit 4 Reserved, must be kept at reset value
   __IO BreakDetection LBDL  :1; // Bit 5 LBDL: lin break detection length
   __IO bool           LBDIE :1; // Bit 6 LBDIE: LIN break detection interrupt enable
   __IO bool           res2  :1; // Bit 7 Reserved, must be kept at reset value
   __IO uint32_t       LBCL  :1; // Bit 8 LBCL: Last bit clock pulse
   __IO uint32_t       CPHA  :1; // Bit 9 CPHA: Clock phase
   __IO uint32_t       CPOL  :1; // Bit 10 CPOL: Clock polarity
   __IO bool           CLKEN :1; // Bit 11 CLKEN: Clock enable
   __IO StopBits       STOP  :2; // Bits 13:12 STOP: STOP bits
   __IO bool           LINEN :1; // Bit 14 LINEN: LIN mode enable
   __IO uint32_t       res3  :17; // Bits 31:15 Reserved, must be kept at reset value
};

struct CR3bits {
   __IO bool     EIE    :1; // Bit 0 EIE: Error interrupt enable
   __IO bool     IREN   :1; // Bit 1 IREN: IrDA mode enable
   __IO bool     IRLP   :1; // Bit 2 IRLP: IrDA low-power
   __IO bool     HDSEL  :1; // Bit 3 HDSEL: Half-duplex selection
   __IO bool     NACK   :1; // Bit 4 NACK: Smartcard NACK enable
   __IO bool     SCEN   :1; // Bit 5 SCEN: Smartcard mode enable
   __IO bool     DMAR   :1; // Bit 6 DMAR: DMA enable receiver
   __IO bool     DMAT   :1; // Bit 7 DMAT: DMA enable transmitter
   __IO bool     RTSE   :1; // Bit 8 RTSE: RTS enable
   __IO bool     CTSE   :1; // Bit 9 CTSE: CTS enable
   __IO bool     CTSIE  :1; // Bit 10 CTSIE: CTS interrupt enable
   __IO bool     ONEBIT :1; // Bit 11 ONEBIT: One sample bit method enable
   __IO uint32_t res1   :20; // Bits 31:12 Reserved, must be kept at reset value
};


struct SR_t   : BitsRegistr<SRbits> , Offset_t<0x00> {};
struct DR_t   : DataRegistr         , Offset_t<0x04> {};
struct BRR_t  : DataRegistr         , Offset_t<0x08> {};
struct CR1_t  : BitsRegistr<CR1bits>, Offset_t<0x0C>, CR1position {};
struct CR2_t  : BitsRegistr<CR2bits>, Offset_t<0x10> {};
struct CR3_t  : BitsRegistr<CR3bits>, Offset_t<0x14> {};
struct GTPR_t : DataRegistr         , Offset_t<0x18> {};

} // namespace


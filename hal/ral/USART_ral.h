#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "DMA_ral.h"
#include "RCC_ral.h"
#include "bitbanding.h"

namespace USART_ral {

    struct SR_t {
        enum { Offset = 0x00 };
        struct Bits {
            // Bit 0 PE: Parity error
            volatile bool PE    :1;
            // Bit 1 FE: Framing error
            volatile bool FE    :1;
            // Bit 2 NF: Noise detected flag
            volatile bool NF    :1;
            // Bit 3 ORE: Overrun error
            volatile bool ORE   :1;
            // Bit 4 IDLE: IDLE line detected
            volatile bool IDLE  :1;
            // Bit 5 RXNE: Read data register not empty
            volatile bool RXNE  :1;
            // Bit 6 TC: Transmission complete
            volatile bool TC    :1;
            // Bit 7 TXE: Transmit data register empty
            volatile bool TXE   :1;
            // Bit 8 LBD: LIN break detection flag
            volatile bool LBD   :1;
            // Bit 9 CTS: CTS flag
            volatile bool CTS   :1;
            // Bits 31:10 Reserved, must be kept at reset value
            volatile uint32_t dcb1  :22;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct DR_t {
        enum { Offset = 0x04 };
        union {
            volatile uint32_t reg;
        };
    };

    struct BRR_t {
        enum { Offset = 0x08 };
        union {
            volatile uint32_t reg;
        };
    };

    struct CR1_t {
        enum { Offset = 0x0C };
        enum Parity {
            even = 0,
            odd  = 1
        };
        enum WakeupMethod {
            idle    = 0,
            address = 1
        };
        enum DataBits {
            _8bits = 0,
            _9bits = 1
        };
        enum OverSample {
            by8  = 0,
            by16 = 1
        };
        struct Bits {
            // Bit 0 SBK: Send break
            volatile bool SBK           :1;
            // Bit 1 RWU: Receiver wakeup
            volatile bool RWU           :1;
            // Bit 2 RE: Receiver enable
            volatile bool RE            :1;
            // Bit 3 TE: Transmitter enable
            volatile bool TE            :1;
            // Bit 4 IDLEIE: IDLE interrupt enable
            volatile bool IDLEIE        :1;
            // Bit 5 RXNEIE: RXNE interrupt enable
            volatile bool RXNEIE        :1;
            // Bit 6 TCIE: Transmission complete interrupt enable
            volatile bool TCIE          :1;
            // Bit 7 TXEIE: TXE interrupt enable
            volatile bool TXEIE         :1;
            // Bit 8 PEIE: PE interrupt enable
            volatile bool PEIE          :1;
            // Bit 9 PS: Parity selection
            volatile Parity PS          :1;
            // Bit 10 PCE: Parity control enable
            volatile bool PCE           :1;
            // Bit 11 WAKE: Wakeup method
            volatile WakeupMethod WAKE  :1;
            // Bit 12 M: Word length
            volatile DataBits M         :1;
            // Bit 13 UE: USART enable
            volatile bool UE            :1;
            // Bit 14 Reserved, must be kept at reset value
            volatile  uint32_t dcb1     :1;
            // Bit 15 OVER8: Oversampling mode
            volatile OverSample OVER8   :1;
            // Bits 31:16 Reserved, must be kept at reset value
            volatile uint32_t dcb2      :16;
        };
        enum {
            SBK = 0, RWU, RE, TE, IDLEIE, RXNEIE, TCIE, TXEIE, PEIE,
            PS, PCE, WAKE, M, UE, OVER8 = 15
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct CR2_t {
        enum { Offset = 0x10 };
        enum BreakDetection {
            _10bit = 0,
            _11bit = 1
        };
        enum StopBits {
            _1      = 0b00,
            _0_5    = 0b01,
            _2      = 0b10,
            _1_5    = 0b11
        };
        struct Bits {
            // Bits 3:0 ADD[3:0]: Address of the USART node
            volatile uint32_t ADD           :4;
            // Bit 4 Reserved, must be kept at reset value
            volatile uint32_t dcb1          :1;
            // Bit 5 LBDL: lin break detection length
            volatile BreakDetection LBDL    :1;
            // Bit 6 LBDIE: LIN break detection interrupt enable
            volatile bool LBDIE             :1;
            // Bit 7 Reserved, must be kept at reset value
            volatile bool dcb2              :1;
            // Bit 8 LBCL: Last bit clock pulse
            volatile uint32_t LBCL          :1;
            // Bit 9 CPHA: Clock phase
            volatile uint32_t CPHA          :1;
            // Bit 10 CPOL: Clock polarity
            volatile uint32_t CPOL          :1;
            // Bit 11 CLKEN: Clock enable
            volatile bool CLKEN             :1;
            // Bits 13:12 STOP: STOP bits
            volatile StopBits STOP          :2;
            // Bit 14 LINEN: LIN mode enable
            volatile bool LINEN             :1;
            // Bits 31:15 Reserved, must be kept at reset value
            volatile uint32_t dcb3          :17;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct CR3_t {
        enum { Offset = 0x14 };
        struct Bits {
            // Bit 0 EIE: Error interrupt enable
            volatile bool EIE           :1;
            // Bit 1 IREN: IrDA mode enable
            volatile bool IREN          :1;
            // Bit 2 IRLP: IrDA low-power
            volatile bool IRLP          :1;
            // Bit 3 HDSEL: Half-duplex selection
            volatile bool HDSEL         :1;
            // Bit 4 NACK: Smartcard NACK enable
            volatile bool NACK          :1;
            // Bit 5 SCEN: Smartcard mode enable
            volatile bool SCEN          :1;
            // Bit 6 DMAR: DMA enable receiver
            volatile bool DMAR          :1;
            // Bit 7 DMAT: DMA enable transmitter
            volatile bool DMAT          :1;
            // Bit 8 RTSE: RTS enable
            volatile bool RTSE          :1;
            // Bit 9 CTSE: CTS enable
            volatile bool CTSE          :1;
            // Bit 10 CTSIE: CTS interrupt enable
            volatile bool CTSIE         :1;
            // Bit 11 ONEBIT: One sample bit method enable
            volatile bool ONEBIT        :1;
            // Bits 31:12 Reserved, must be kept at reset value
            volatile uint32_t dcb1      :20;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };
    struct GTPR_t {
        enum { Offset = 0x18 };
        union {
            volatile uint32_t reg;
        };
    };

}


/*
typedef struct
{
  __IO uint32_t SR;         // USART Status register,                   Address offset: 0x00 
  __IO uint32_t DR;         // USART Data register,                     Address offset: 0x04 
  __IO uint32_t BRR;        // USART Baud rate register,                Address offset: 0x08 
  __IO uint32_t CR1;        // USART Control register 1,                Address offset: 0x0C 
  __IO uint32_t CR2;        // USART Control register 2,                Address offset: 0x10 
  __IO uint32_t CR3;        // USART Control register 3,                Address offset: 0x14 
  __IO uint32_t GTPR;       // USART Guard time and prescaler register, Address offset: 0x18 
} USART_TypeDef;
*/

struct USART_t : public USART_ral::SR_t,
                 public USART_ral::DR_t,
                 public USART_ral::BRR_t,
                 public USART_ral::CR1_t,
                 public USART_ral::CR2_t,
                 public USART_ral::CR3_t,
                 public USART_ral::GTPR_t
{

};

extern const uint32_t fCPU;

// ClkEnOffset оффсет для регистра из структуры RCC, разрешающий тактирование 
template <uint32_t USARTptr, class DMAstreamRX, class DMAstreamTX, uint32_t ClkEnMask>
class USARTx : USART_t
{
public:
    enum Boudrate {
        BR9600	 = 9600,
        BR14400	 = 14400,
        BR19200  = 19200,
        BR28800	 = 28800,
        BR38400  = 38400,
        BR57600	 = 57600,
        BR76800	 = 76800,
        BR115200 = 115200
    };
    using Parity = CR1_t::Parity;
    using StopBits = CR2_t::StopBits;
    using DMArx = DMAstreamRX;
    using DMAtx = DMAstreamTX;
    using Channels = DMA_ral::CR_t::Channels;

    static constexpr DMA_ral::CR_t::Channels DMAChannel = 
        USARTptr == USART6_BASE ? DMA_ral::CR_t::Channels::_5 :
                                  DMA_ral::CR_t::Channels::_4;
    static constexpr RCC_t::Bus bus =
        USARTptr == USART1_BASE ? RCC_t::Bus::APB2 :
        USARTptr == USART6_BASE ? RCC_t::Bus::APB2 :
                                  RCC_t::Bus::APB1;
    static const uint32_t Base = USARTptr;

    static constexpr IRQn_Type IRQn = 
        USARTptr == USART1_BASE ? USART1_IRQn :
        USARTptr == USART2_BASE ? USART2_IRQn :
        USARTptr == USART3_BASE ? USART3_IRQn :
        USARTptr == USART6_BASE ? USART6_IRQn :
                                  NonMaskableInt_IRQn;


    static void ClockEnable() { *((uint32_t*)(RCC_BASE + ClkEnOffset)) |= ClkEnMask; }
    static void Enable (bool val)      { BITBAND_SET(conf1(), UE, val); }
    static void RXenable (bool val)    { BITBAND_SET(conf1(), RE, val); }
    static void TXenable (bool val)    { BITBAND_SET(conf1(), TE, val); }
    static void DMAtxEnable() { conf3().bits.DMAT = true; }
    static void DMArxEnable() { conf3().bits.DMAR = true; }
    static void SetBoudRate (Boudrate val)
    {
        if (bus == RCC_t::Bus::APB1) {
            boudrate().reg = RCC_t::getAPB1clock() / val;
        } else if (bus == RCC_t::Bus::APB2) {
            boudrate().reg = RCC_t::getAPB2clock() / val;
        }
    }
    static void ParityEnable (bool val)    { BITBAND_SET(conf1(), PCE, val); }
    static void SetParity (Parity val)     { BITBAND_SET(conf1(), PS, val); }
    static void SetStopBits (StopBits val) { conf2().bits.STOP = val; }
    static void EnableIDLEinterrupt()      { BITBAND_SET(conf1(), IDLEIE, true); }
    static bool IDLEinterrupt()            { return status().bits.IDLE; }
    static void ClearIDLEinterruptFlag()
    {
        status().reg;
        data().reg;
    }
    static void sendByte (uint8_t val) { data().reg = val; }


protected:
    static volatile USART_ral::SR_t   &status()  
    { return (USART_ral::SR_t &)   (*(USART_TypeDef*)USARTptr).SR;   }
    static volatile USART_ral::DR_t   &data()     
    { return (USART_ral::DR_t &)   (*(USART_TypeDef*)USARTptr).DR;   }
    static volatile USART_ral::BRR_t  &boudrate() 
    { return (USART_ral::BRR_t &)  (*(USART_TypeDef*)USARTptr).BRR;  }
    static volatile USART_ral::CR1_t  &conf1()    
    { return (USART_ral::CR1_t &)  (*(USART_TypeDef*)USARTptr).CR1;  }
    static volatile USART_ral::CR2_t  &conf2()    
    { return (USART_ral::CR2_t &)  (*(USART_TypeDef*)USARTptr).CR2;  }
    static volatile USART_ral::CR3_t  &conf3()    
    { return (USART_ral::CR3_t &)  (*(USART_TypeDef*)USARTptr).CR3;  }
    static volatile USART_ral::GTPR_t &gtp()      
    { return (USART_ral::GTPR_t &) (*(USART_TypeDef*)USARTptr).GTPR; }


private:
    static constexpr uint32_t ClkEnOffset = 
        bus == RCC_t::Bus::APB1 ? RCC_ral::APB1ENR_t::Offset :
                                  RCC_ral::APB2ENR_t::Offset;


};

using USART1_t      = USARTx<USART1_BASE, DMA2stream5, DMA2stream7, RCC_APB2ENR_USART1EN_Msk>;
// альтернатива с другим потоком дма
using USART1alt_t   = USARTx<USART1_BASE, DMA2stream2, DMA2stream7, RCC_APB2ENR_USART1EN_Msk>;

using USART2_t      = USARTx<USART2_BASE, DMA1stream5, DMA1stream6, RCC_APB1ENR_USART2EN_Msk>;

using USART3_t      = USARTx<USART3_BASE, DMA1stream1, DMA1stream3, RCC_APB1ENR_USART3EN_Msk>;
// альтернатива с другим потоком дма
using USART3alt_t   = USARTx<USART3_BASE, DMA1stream1, DMA1stream4, RCC_APB1ENR_USART3EN_Msk>;

using USART6_t      = USARTx<USART6_BASE, DMA2stream1, DMA2stream6, RCC_APB2ENR_USART6EN_Msk>;
// альтернативы с другим потоком дма
using USART6alt17_t = USARTx<USART6_BASE, DMA2stream1, DMA2stream7, RCC_APB2ENR_USART6EN_Msk>;
using USART6alt27_t = USARTx<USART6_BASE, DMA2stream2, DMA2stream7, RCC_APB2ENR_USART6EN_Msk>;
using USART6alt26_t = USARTx<USART6_BASE, DMA2stream2, DMA2stream6, RCC_APB2ENR_USART6EN_Msk>;
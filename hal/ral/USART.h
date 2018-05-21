#pragma once

#if defined(STM32F405xx)
      #include "USART_F4_bits.h"
#include "bitbanding.h"
#elif defined(STM32F030x6)
   #include "USART_F0_bits.h"
#endif
#include "DMA.h"
#include "RCC.h"




/* STM32F4
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
/* STM32F0
typedef struct
{
  __IO uint32_t CR1;   // USART Control register 1,                 Address offset: 0x00
  __IO uint32_t CR2;   // USART Control register 2,                 Address offset: 0x04
  __IO uint32_t CR3;   // USART Control register 3,                 Address offset: 0x08
  __IO uint32_t BRR;   // USART Baud rate register,                 Address offset: 0x0C
  __IO uint32_t GTPR;  // USART Guard time and prescaler register,  Address offset: 0x10
  __IO uint32_t RTOR;  // USART Receiver Time Out register,         Address offset: 0x14 
  __IO uint32_t RQR;   // USART Request register,                   Address offset: 0x18
  __IO uint32_t ISR;   // USART Interrupt and status register,      Address offset: 0x1C
  __IO uint32_t ICR;   // USART Interrupt flag Clear register,      Address offset: 0x20
  __IO uint16_t RDR;   // USART Receive Data register,              Address offset: 0x24
  uint16_t  RESERVED1; // Reserved,                                                 0x26
  __IO uint16_t TDR;   // USART Transmit Data register,             Address offset: 0x28
  uint16_t  RESERVED2; // Reserved,                                                 0x2A
} USART_TypeDef;*/

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
class USARTx// : USART_t
{
public:
   enum Boudrate {
      BR9600   = 9600,
      BR14400  = 14400,
      BR19200  = 19200,
      BR28800  = 28800,
      BR38400  = 38400,
      BR57600  = 57600,
      BR76800  = 76800,
      BR115200 = 115200
   };
   using Parity = USART_ral::Parity;
   using StopBits = USART_ral::StopBits;
   using DMArx = DMAstreamRX;
   using DMAtx = DMAstreamTX;
   using Channels = DMA_ral::CR_t::Channels;

   static constexpr Channels DMAChannel = 
      USARTptr == USART6_BASE ? Channels::_5 : Channels::_4;
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
   static void Enable (bool val)      { BIT_BAND(conf1(), UE) = val; }
   static void RXenable (bool val)    { BIT_BAND(conf1(), RE) = val; }
   static void TXenable (bool val)    { BIT_BAND(conf1(), TE) = val; }
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
   static void ParityEnable (bool val)    { BIT_BAND(conf1(), PCE) = val; }
   static void SetParity (Parity val)     { BIT_BAND(conf1(), PS)  = val; }
   static void SetStopBits (StopBits val) { conf2().bits.STOP = val; }
   static void EnableIDLEinterrupt()      { BIT_BAND(conf1(), IDLEIE) = true; }
   static bool IDLEinterrupt()            { return status().bits.IDLE; }
   static void ClearIDLEinterruptFlag()
   {
      status().reg;
      data().reg;
   }
   static void sendByte (uint8_t val) { data().reg = val; }


protected:
#define MakeRef(Reg,Ref) USART_ral::Reg& Ref() { return (USART_ral::Reg&) *(uint32_t*)(Base + USART_ral::Reg::Offset); }
   static volatile MakeRef (SR_t,   status  );
   static volatile MakeRef (DR_t,   data    );
   static volatile MakeRef (BRR_t,  boudrate);
   static volatile MakeRef (CR1_t,  conf1   );
   static volatile MakeRef (CR2_t,  conf2   );
   static volatile MakeRef (CR3_t,  conf3   );
   static volatile MakeRef (GTPR_t, gtp     );
#undef MakeRef

private:
#if defined(STM32F405xx)
   USART_ral::SR_t   SR;
   USART_ral::DR_t   DR;
   USART_ral::BRR_t  BRR;
   USART_ral::CR1_t  CR1;
   USART_ral::CR2_t  CR2;
   USART_ral::CR3_t  CR3;
   USART_ral::GTPR_t GTPR;
#elif defined(STM32F030x6)
#endif

   static constexpr uint32_t ClkEnOffset = 
      bus == RCC_t::Bus::APB1 ? (uint32_t)RCC_ral::APB1ENR_t::Offset :
                                (uint32_t)RCC_ral::APB2ENR_t::Offset;


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
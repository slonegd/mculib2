#pragma once

#if defined(STM32F405xx)
   #include "USART_F4_bits.h"
   #include "bitbanding.h"
#elif defined(STM32F030x6)
   #include "USART_F0_bits.h"
#endif
#include "DMA.h"
#include "RCC.h"

extern const uint32_t fCPU;

template <uint32_t Adr, class DMArx_, class DMAtx_>
class USARTx
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
   using Parity   = USART_ral::Parity;
   using StopBits = USART_ral::StopBits;
   using DMArx    = DMArx_;
   using DMAtx    = DMAtx_;
   using Channels = DMA_ral::Channels;

   void makeDebugVar() { CR1.bits.res1 = 0; }

   static constexpr uint32_t  Base = Adr;
   static constexpr Channels  DMAChannel();
   static constexpr IRQn_Type IRQn();
   static constexpr PinConf_t PinConfigure();
   static constexpr uint32_t  ReceiveDataAdr();
   static constexpr uint32_t  TransmitDataAdr();

   template<class RXpin>  static constexpr bool IsRXsupport();
   template<class TXpin>  static constexpr bool IsTXsupport();
   template<class RTSpin> static constexpr bool IsRTSsupport();

   static void ClockEnable();
   static void Enable (bool val);
   static void RXenable (bool val);
   static void TXenable (bool val);
   static void RTSenable();
   static void DMAtxEnable();
   static void DMArxEnable();
   static void SetBoudRate (Boudrate val);
   static void ParityEnable (bool val);
   static void SetParity (Parity val);
   static void SetStopBits (StopBits val);
   static void EnableIDLEinterrupt();
   static bool IsIDLEinterrupt();
   static void ClearIDLEinterruptFlag();
   static void sendByte (uint8_t val);

#if defined(STM32F030x6)
   static void SetTimeOutBitQty (uint32_t val);
   static void EnableReceiveTimeout();
   static void EnableReceiveTimeoutInterupt();
   static bool IsReceiveTimeoutInterrupt();
   static void ClearReceiveTimeoutInterruptFlag();
#endif


protected:
#define MakeRef(Reg,Ref) USART_ral::Reg& Ref() { return (USART_ral::Reg&) *(uint32_t*)(Base + USART_ral::Reg::Offset); }
   static volatile MakeRef (BRR_t,  boudrate);
   static volatile MakeRef (CR1_t,  conf1   );
   static volatile MakeRef (CR2_t,  conf2   );
   static volatile MakeRef (CR3_t,  conf3   );
#if defined(STM32F405xx)
   static volatile MakeRef (SR_t,   status  );
   static volatile MakeRef (DR_t,   data    );
   static volatile MakeRef (GTPR_t, gtp     );
#elif defined(STM32F030x6)
   static volatile MakeRef (RTOR_t, recieverTmeout );
   static volatile MakeRef (RQR_t,  request );
   static volatile MakeRef (ISR_t,  interrupt );
   static volatile MakeRef (ICR_t,  clear );
   static volatile MakeRef (RDR_t,  receiveData );
   static volatile MakeRef (TDR_t,  transmitData );
#endif
#undef MakeRef

private:
#if defined(STM32F405xx)
   USART_ral::SR_t   SR;   // USART Status register
   USART_ral::DR_t   DR;   // USART Data register
   USART_ral::BRR_t  BRR;  // USART Baud rate register
   USART_ral::CR1_t  CR1;  // USART Control register 1
   USART_ral::CR2_t  CR2;  // USART Control register 2
   USART_ral::CR3_t  CR3;  // USART Control register 3
   USART_ral::GTPR_t GTPR; // USART Guard time and prescaler register
#elif defined(STM32F030x6)
   USART_ral::CR1_t  CR1; // USART Control register 1
   USART_ral::CR2_t  CR2; // USART Control register 2
   USART_ral::CR3_t  CR3; // USART Control register 3
   USART_ral::BRR_t  BRR; // USART Baud rate register
   Reserve_t<1>      reserve1;
   USART_ral::RTOR_t RTOR; // USART Receiver Time Out register
   USART_ral::RQR_t  RQR;  // USART Request register
   USART_ral::ISR_t  ISR;  // USART Interrupt and status register
   USART_ral::ICR_t  ICR;  // USART Interrupt flag Clear register
   USART_ral::RDR_t  RDR;  // USART Receive Data register
   USART_ral::TDR_t  TDR;  // USART Transmit Data register
#endif

#if defined(STM32F405xx)
   static constexpr RCC_t::Bus bus =
      Adr == USART1_BASE ? RCC_t::Bus::APB2 :
      Adr == USART6_BASE ? RCC_t::Bus::APB2 : RCC_t::Bus::APB1;
#endif

};

#if defined(STM32F405xx)

#undef USART1
using USART1        = USARTx<USART1_BASE, DMA2stream5, DMA2stream7>;
// альтернатива с другим потоком дма
using USART1alt   = USARTx<USART1_BASE, DMA2stream2, DMA2stream7>;

#undef USART2
using USART2        = USARTx<USART2_BASE, DMA1stream5, DMA1stream6>;

#undef USART3
using USART3        = USARTx<USART3_BASE, DMA1stream1, DMA1stream3>;
// альтернатива с другим потоком дма
using USART3alt   = USARTx<USART3_BASE, DMA1stream1, DMA1stream4>;

#undef USART6
using USART6        = USARTx<USART6_BASE, DMA2stream1, DMA2stream6>;
// альтернативы с другим потоком дма
using USART6alt17 = USARTx<USART6_BASE, DMA2stream1, DMA2stream7>;
using USART6alt27 = USARTx<USART6_BASE, DMA2stream2, DMA2stream7>;
using USART6alt26 = USARTx<USART6_BASE, DMA2stream2, DMA2stream6>;

#elif defined(STM32F030x6)

#undef USART1
using USART1    = USARTx<USART1_BASE, DMA1channel3, DMA1channel2>;
using USART1alt = USARTx<USART1_BASE, DMA1channel5, DMA1channel4>;

#endif

#include "USART_src.h"
//////////////////////////////////////////////////////////////////////////////
/** первые 2 параметры шаблона -кслассы перечисления от 0, без пропусков
 *  последним членом перечилсения должны быть Qty
 * 
 *      ПОПРОБАВАТЬ ВМЕСТО ПЕРЕЧИСЛЕНИЙ ИСПОЛЬЗОВАТЬ СТРУКТУРЫ
 *      А ВМЕСТО СВИТЧ/КЕЙС СПЕЦИАЛИЗАЦИИ ШАБЛОННЫХ ФУНКЦИЙ,
 *      КОТОРОЙ ПЕРЕДАЁТЬСЯ АДРЕСС
 * с шаблонной функцией не получиться, но со структурами работать удобнее
 * просто в кейсе надо не енум ставить а адрес, который вычисляеться макросом
 * не придумал как макрос на шаблон изменить
 *//////////////////////////////////////////////////////////////////////////// 
#pragma once

#include "usart.h"
#include "timers.h"
#include "crc.h"
#include <cstring>


template <class InRegs_t, class OutRegs_t, class UART>
class MBslave
{
public:
   static constexpr uint16_t InRegQty = sizeof(InRegs_t) / 2;
   static constexpr uint16_t OutRegQty = sizeof(OutRegs_t) / 2;

   uint8_t address;
   union {
      InRegs_t inRegs;
      uint16_t arInRegs[InRegQty];
   };
   union {
      OutRegs_t outRegs;
      uint16_t arOutRegs[OutRegQty];
   };
   union {
      InRegs_t inRegsMin;
      uint16_t arInRegsMin[InRegQty];
   };
   union {
      InRegs_t inRegsMax;
      uint16_t arInRegsMax[InRegQty];
   };


#if defined(STM32F405xx)
   MBslave ( UART& uart, Timer& timer );
#elif defined(STM32F030x6)
   MBslave ( UART& uart );
#endif

   void init (const typename UART::Settings& val);

   // вызываеться в прерывании по приёму данных USARTx_IRQHandler
   // где x - номер применяемого уарта
   void recieveInterruptHandler();

   // вызываеться в прерывании по передаче данных
   // для серии F4 DMAn_Streamx_IRQHandler
   // где x - номер канала ДМА, n - номер ДМА
   void transmitInterruptHandler();

   // обрабатывает поступивший запрос, по необходимости формирует ответ
   // если надо ответить, то переводит уарт на отправку зажигает индикатор
   // если ответа не надо, то переводит уарт на приём
   // function reaction - функция, описывающая реакцию на изменение входных регистров
   // единственный параметр function - адрес входного регистра
   template <class function>
   void operator() (function reaction);



private:
#if defined(STM32F405xx)
   Timer& timer;
#endif
   UART& uart;
   bool endMessage;
};

/// для определения адреса регистра по его положению в структуре
#define GET_ADR(struct, reg)     (offsetof(struct, reg) / 2)















#if defined(STM32F405xx)
template <class In, class Out, class UART>
MBslave<In,Out,UART>::MBslave ( UART& uart, Timer& timer)
   : address     {1},
     arInRegs    {0},
     arOutRegs   {0},
     arInRegsMin {0},
     arInRegsMax {0},
     timer       (timer),
     uart        (uart),
     endMessage  {false}
{ }
#elif defined(STM32F030x6)
template <class In, class Out, class UART>
MBslave<In,Out,UART>::MBslave ( UART& uart)
   : address     {1},
     arInRegs    {0},
     arOutRegs   {0},
     arInRegsMin {0},
     arInRegsMax {0},
     uart        (uart),
     endMessage  {false}
{ }
#endif





template <class In, class Out, class UART>
void MBslave<In,Out,UART>::init (const typename UART::Settings& val)
{
   uart.init (val);
}





template <class In, class Out, class UART>
void MBslave<In,Out,UART>::recieveInterruptHandler()
{
#if defined(STM32F405xx)
   if ( uart.idleHandler() )
      timer.start();
#elif defined(STM32F030x6)
   if ( uart.rxTimeOutHandler() )
      endMessage = true;
#endif
}





template <class In, class Out, class UART>
void MBslave<In,Out,UART>::transmitInterruptHandler()
{
   uart.txCompleteHandler();
}





template <class In, class Out, class UART>
template <class function>
void MBslave<In,Out,UART>::operator() (function reaction)
{
#if defined(STM32F405xx)
   endMessage = timer.done() ? timer.stop(), true : false;
#endif

   if (endMessage) {
      endMessage = false;
      // из спецификации на модбас
      enum ErrorCode {
         NoErr    = 0,
         FuncErr  = 1,
         RegErr   = 2,
         ValueErr = 3
      } error = NoErr;
      enum Step {
         Done = 0,
         AddrCheck,
         MinMessageCheck,
         CRCcheck,
         FuncCheck,
         RegCheck03,
         RegCheck16,
         ValCheck,
         ErrSet,
         Answer
      } step = Step::AddrCheck;
      uint32_t byteQty {uart.byteQtyRX()};
      uint16_t crc {0};
      uint16_t LowAddr{0};
      uint16_t HighAddr{0};
      uint16_t RegQty{0};
      bool allGood = true;
      uint16_t* registrValue = nullptr;
      while (step) {

         switch (step) {

         case Step::AddrCheck:
            if (uart.buffer[0] == address or uart.buffer[0] == 0)
               step = Step::MinMessageCheck;
            break;

         case Step::MinMessageCheck:
            if (byteQty >= 8)
               step = Step::CRCcheck;
            break;

         case Step::CRCcheck:
            crc = crc16 (uart.buffer, byteQty - 2);
            if (   (uint8_t) crc       != uart.buffer[byteQty-2]
                or (uint8_t)(crc >> 8) != uart.buffer[byteQty-1] )
            {
               step = Step::CRCcheck;
            } else {
               step = Step::FuncCheck;
            }
            break;

         case Step::FuncCheck:
            LowAddr = (uint16_t)uart.buffer[2] << 8 | uart.buffer[3];
            RegQty  = (uint16_t)uart.buffer[4] << 8 | uart.buffer[5];
            HighAddr = LowAddr + RegQty - 1;	
            if (uart.buffer[1] == 3)
               step = Step::RegCheck03;
            else if (uart.buffer[1] == 16)
               step = Step::RegCheck16;
            else {
               error = ErrorCode::FuncErr;
               step = Step::ErrSet;
            }
            break;	

         case Step::RegCheck03:
            if (byteQty != 8) { //длина пакета не соответсвует спецификации ModBus
               step = Step::Done;
            } else if (HighAddr > (OutRegQty - 1)) {
               error = ErrorCode::RegErr;
               step = Step::ErrSet;
            } else {
               byteQty =  RegQty * 2;
               uart.buffer[2] = byteQty;
               registrValue = reinterpret_cast<uint16_t*>(uart.buffer + 3);
               std::memcpy (registrValue, arOutRegs + LowAddr, byteQty);
               byteQty += 3;
            }
            break;

         case Step::RegCheck16:
            if (byteQty != (uint32_t)RegQty * 2 + 9) {	//длина пакета не соответсвует спецификации ModBus
               step = Step::Done;
            } else if (HighAddr > (InRegQty - 1)) {
               error = ErrorCode::RegErr;
               step = Step::ErrSet;
            } else {
               step = Step::ValCheck;
            }
            break;

         case Step::ValCheck:
            registrValue = reinterpret_cast<uint16_t*>(uart.buffer + 7);
            for (uint16_t i = 0; i < RegQty; ++i)
               allGood &= registrValue[i] >= arInRegsMin[i+LowAddr]
                  and (   registrValue[i] <= arInRegsMax[i+LowAddr]
                       or arInRegsMax[i+LowAddr] == 0
               );
            if (allGood) {
               std::memcpy (arInRegs + LowAddr, registrValue, RegQty * 2);
               while (LowAddr++ <= HighAddr)
                  reaction(LowAddr);
               byteQty = 6;
               step = Step::Answer;
            } else {
               error = ErrorCode::ValueErr;
               step = Step::ErrSet;
            }
            break;

         case Step::ErrSet:
            uart.buffer[1] |= 0b10000000;
            uart.buffer[2]  = error;
            byteQty = 3;
            step = Step::Answer;
            break;

         case Step::Answer:
            crc = crc16 (uart.buffer, byteQty);
            uart.buffer[byteQty++] = crc;
            uart.buffer[byteQty++] = crc >> 8;
            uart.startTX (byteQty);
            step = Step::Done;
            break;

         case Step::Done:
            break;
         } // switch (step) {
      } // while (step) {
   } // if (endMessage) {
}


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
#include <cstring>

// это с форума ОВЕНа - для ARM
uint16_t crc16(uint8_t* data, uint8_t length)
{
   int j;
   uint16_t reg_crc = 0xFFFF;
   while(length--)	{
      reg_crc ^= *data++;
      for(j = 0; j < 8; j++) {
         if (reg_crc & 0x01) {
            reg_crc=(reg_crc>>1) ^ 0xA001; // LSB(b0)=1
         } else {
            reg_crc=reg_crc>>1;
         }	
      }
   }
   return reg_crc;
}



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
   // для серии А4 DMAn_Streamx_IRQHandler
   // где x - номер канала ДМА, n - номер ДМА
   void transmitInterruptHandler();

   // обрабатывает поступивший запрос, по необходимости формирует ответ
   // если надо ответить, то переводит уарт на отправку зажигает индикатор
   // если ответа не надо, то переводит уарт на приём
   // function f - функция, описывающая реакцию на изменение входных регистров
   // единственный параметр function f - адрес входного регистра
   template <class function>
   void operator() (function reaction);





private:
#if defined(STM32F405xx)
   Timer& timer;
#endif
   UART& uart;
   bool endMessage;
};

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
   if ( UART::IsReceiveTimeoutInterrupt() ) {
      endMessage = true;
      UART::ClearReceiveTimeoutInterruptFlag();
   }
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
         ErrAnswer
      } step = Step::AddrCheck;
      uint8_t byteQty = uart.byteQtyRX();
      uint16_t crc = 0;
      uint16_t LowAddr, HighAddr, RegQty;
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
            if (    crc       != uart.buffer[byteQty-2]
                or (crc >> 8) != uart.buffer[byteQty-1] )
            {
               step = Step::CRCcheck;
            } else {
               step = Step::FuncCheck;
            }
            break;

         case Step::FuncCheck:
            if (uart.buffer[1] == 3)
               step = Step::RegCheck03;
            else if (uart.buffer[1] == 16)
               step = Step::RegCheck16;
            else {
               error = ErrorCode::FuncErr;
               step = Step::ErrAnswer;
            }
            break;	

         case Step::RegCheck03:
            LowAddr = (uint16_t)uart.buffer[2] << 8 | uart.buffer[3];
            RegQty  = (uint16_t)uart.buffer[4] << 8 | uart.buffer[5];
            HighAddr = LowAddr + RegQty - 1;	
            if (byteQty != 8) { //длина пакета не соответсвует спецификации ModBus
               step = Step::Done;
            } else if (HighAddr > (OutRegQty - 1)) {
               error = ErrorCode::RegErr;
               step = Step::ErrAnswer;
            }
            break;

         case Step::RegCheck16:
            LowAddr = (uint16_t)uart.buffer[2] << 8 | uart.buffer[3];
            RegQty  = (uint16_t)uart.buffer[4] << 8 | uart.buffer[5];
            HighAddr = LowAddr + RegQty - 1;
            if (byteQty != RegQty * 2 + 9) {	//длина пакета не соответсвует спецификации ModBus
               step = Step::Done;
            } else if (HighAddr > (InRegQty - 1)) {
               error = ErrorCode::RegErr;
               step = Step::ErrAnswer;
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
               std::memcpy (arInRegs, registrValue + LowAddr, RegQty * 2);
               while (LowAddr++ <= HighAddr)
                  reaction(LowAddr);
            }
            break;

         case Step::Done:
            break;
         } // switch (step) {
      } // while (step) {


   } // if (endMessage) {
}

   //  uint16_t LowAddr = 0;
   //  uint16_t RegQty = 0;
   //  uint16_t HighAddr = 0;
   //  uint16_t RegVal[QTY_IN_REG];
   //  uint16_t CRC;
   //  uint8_t CRC1st;
   //  uint8_t CRC2nd;

   //  enum MBSlaveStep{	//по порядку в switch
   //      StartCheck,
   //      MinMesCheck,
   //      AddrCheck,
   //      FuncCheck,
   //      RegCheck,
   //      ValueCheck,
   //      CRCCheck,
   //      AnswerErr,
   //      AnswerMB03,
   //      AnswerMB16,
   //      AnswerCRC,
   //      FuncDone,
   //  } Step = StartCheck;

        
   //  while (Step!=FuncDone) {
   //      switch (Step) {

   //      case RegCheck:

   //      case ValueCheck:
   //          if (MBFUNC16) {
   //              bool AllGood;
   //              AllGood = true;
   //              for (uint16_t i = 0; i < RegQty; i++) {
   //                  RegVal[i] = (uint16_t)Buf->Buf[i*2+7] << 8 | Buf->Buf[i*2+8];
   //                  AllGood = AllGood && RegVal[i] >= Reg->RegInMinVal[i+LowAddr]
   //                                  && (RegVal[i] <= Reg->RegInMaxVal[i+LowAddr] 
   //                                      || Reg->RegInMaxVal[i+LowAddr] == 0);
   //              }
   //              Err = AllGood ? Err : ValueErr;
   //              Step = CRCCheck;
   //          } else {
   //              Step=CRCCheck;
   //          }
   //          break;	
   //      case CRCCheck:
   //          CRC = crc16(&Buf->Buf[0], Buf->QtyByteRxTx - 2);
   //          CRC1st = CRC % 256;
   //          CRC2nd = CRC / 256;
   //          if ((CRC1st != Buf->Buf[Buf->QtyByteRxTx-2]) || (CRC2nd != Buf->Buf[Buf->QtyByteRxTx-1])) {
   //              Buf->EndMes = false;
   //              Buf->QtyByteRxTx = 0;
   //              Step = FuncDone;
   //          } else {
   //              if (Err != NoErr) {
   //                  Step = AnswerErr;
   //              } else if (MBFUNC03) {
   //                  Step = AnswerMB03;
   //              } else if (MBFUNC16) {
   //                  Step = AnswerMB16;
   //              } else {
   //                  Step=FuncDone; 
   //              }
   //          }	
   //          break;	
   //      case AnswerErr:
   //          if (ALLADDR) {
   //              Buf->EndMes = false;
   //              Buf->QtyByteRxTx = 0;
   //              Step = FuncDone; 
   //          } else {
   //              SetBit(Buf->Buf[1], 7);	//из спецификации MODBUS
   //              Buf->Buf[2] = Err;
   //              Buf->NeedSend = 3;		//адрес, функция, код ошибки
   //              Step = AnswerCRC; 
   //          }
   //          break;	
   //      case AnswerMB03:
   //          if (ALLADDR) {
   //              Buf->EndMes = false;
   //              Buf->QtyByteRxTx = 0;
   //              Step = FuncDone;
   //          } else {
   //              Buf->Buf[2] = RegQty * 2;
   //              for (uint16_t i = 0; i < RegQty; i++) {
   //                  Buf->Buf[2*i+3] = (uint8_t)(Reg->RegOut[LowAddr+i] >> 8);
   //                  Buf->Buf[2*i+4] = (uint8_t)Reg->RegOut[LowAddr+i];	
   //              }
   //              Buf->NeedSend = 3 + Buf->Buf[2];	//адрес, функция, qty байт данных, данные (в количестве qty	байт)
   //              Step = AnswerCRC;
   //          }
   //          break;
   //      case AnswerMB16:
   //          memcpy( (void*)(Reg->RegIn + LowAddr),
   //                  (void*)RegVal,
   //                  (size_t)(RegQty*2)
   //          );
   //          if (ALLADDR) {
   //              Buf->EndMes = false;
   //              Buf->QtyByteRxTx = 0;
   //              Step = FuncDone;
   //          } else {
   //              Buf->NeedSend = 6;	//ответ как запрос, только обрезаем данные
   //              Step = AnswerCRC;
   //          }
   //          break;	
   //      case AnswerCRC:
   //          CRC = crc16(&Buf->Buf[0], Buf->NeedSend);
   //          Buf->Buf[Buf->NeedSend] = CRC % 256;
   //          Buf->Buf[Buf->NeedSend+1] = CRC / 256;
   //          Buf->NeedSend = Buf->NeedSend + 2;
   //          Buf->EndMes = false;
   //          Buf->QtyByteRxTx = 0;
   //          Step = FuncDone;
   //          break;
   //      case FuncDone:
   //          break;											
   //      }//switch (Step) 
   //  }//while (Step != FuncDone) 
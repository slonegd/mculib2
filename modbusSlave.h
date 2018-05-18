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


template <class InRegs_t, class OutRegs_t, class UART_>
class MBslave
{
public:
    static const uint16_t InRegQty = sizeof(InRegs_t) / 2;
    static const uint16_t OutRegQty = sizeof(OutRegs_t) / 2;

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

    UART_& uart;
    
    
    
    MBslave (
        UART_& uart_,
        Timer& timer_
    ) : arInRegs{0}, arOutRegs{0}, arInRegsMin{0},arInRegsMax{0},
        uart(uart_), timer(timer_),
        inRegAdrForAction(InRegQty)
    { }



    // вызываеться в прерывании idle по приёму
    // запускает таймер определения конца пакета
    inline void idleHandler()
    {
        if ( uart.idleHandler() )
            timer.start();
    }

    // true когда пришло сообщение по модбасу, которое требует обработки
    inline bool incomingMessage()
    {
        bool tmp = timer.done();
        if (tmp)
            timer.stop();
        return tmp;
    }

    // обрабатывает поступивший запрос, по необходимости формирует ответ
    // если надо ответить, то переводит уарт на отправку зажигает индикатор
    // если ответа не надо, то переводит уарт на приём
    inline void handler()
    {

    }

    // перебирает все входные регистров, на которые пришел запрос
    // внутри функции вызывать метод getInRegAdrForAction для определения
    // адреса регистра
    template <class function>
    inline function foreachRegForActions (function f) 
    {
        for (; inRegAdrForAction <= lastInRegAdrForAction; ++inRegAdrForAction ) 
            f();
        return f;
    }
    inline uint16_t getInRegAdrForAction() { return inRegAdrForAction; }



private:
    Timer& timer;
    uint16_t inRegAdrForAction;
    uint16_t lastInRegAdrForAction;
    
};

#define GET_ADR(struct, reg)     (offsetof(struct, reg) / 2)
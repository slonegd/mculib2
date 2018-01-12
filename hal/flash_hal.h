/** шаблонный класс сохранения данных во flash
 *  при инициализации необходимо указать
 *      структуру, которая будет сохраняться
 *      сектор флеша, куда записывать
 *  Размер структуры не более 255 байт, поскольку кодируються во флеше
 *  в виде двух байт, один данные, второй их индекс в байтовом массиве
 * 
 *  Перед работой с данными, их надо сначала прочитать, и если результат
 *  отрицательный, то инициировать значениями по умолчанию
 * 
 *  Для обновления изменённых данных периодически вызывать update
 * 
 *////////////////////////////////////////////////////////////////////////////
  
#pragma once

#include <stdbool.h>
#include <string.h>
#include "FLASH_ral.h"
#include "constDef.h"

using AddresDef = ConstDef<uint32_t>;
using SizeDef = ConstDef<int32_t>;

template<uint8_t sector> constexpr ConstDef<uint32_t> Addres() { return {0, false}; }
template<uint8_t sector> constexpr ConstDef<int32_t>  Size()   { return {0, false}; }

template<> constexpr AddresDef Addres<1>() { return {0x08004000, true}; }
template<> constexpr SizeDef Size<1>()     { return {16*1024, true};    }

template<> constexpr AddresDef Addres<2>() { return {0x08008000, true}; }
template<> constexpr SizeDef Size<2>()     { return {16*1024, true};    }

template<> constexpr AddresDef Addres<3>() { return {0x0800C000, true}; }
template<> constexpr SizeDef Size<3>()     { return {16*1024, true};    }

template<> constexpr AddresDef Addres<4>() { return {0x08010000, true}; }
template<> constexpr SizeDef Size<4>()     { return {64*1024, true};    }

template<> constexpr AddresDef Addres<5>() { return {0x08020000, true}; }
template<> constexpr SizeDef Size<5>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<6>() { return {0x08040000, true}; }
template<> constexpr SizeDef Size<6>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<7>() { return {0x08060000, true}; }
template<> constexpr SizeDef Size<7>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<8>() { return {0x08080000, true}; }
template<> constexpr SizeDef Size<8>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<9>() { return {0x080A0000, true}; }
template<> constexpr SizeDef Size<9>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<10>() { return {0x080C0000, true}; }
template<> constexpr SizeDef Size<10>()     { return {128*1024, true};   }

template<> constexpr AddresDef Addres<11>() { return {0x080E0000, true}; }
template<> constexpr SizeDef Size<11>()     { return {128*1024, true};   }




template <class DATA, uint8_t sector>
class Flash 
{
public:
    // обязательно должен быть первым
    // потому что использую this как указатель к структуре
    DATA data;
    bool readFromFlash ();
    void update();
    Flash (DATA d)
    {
        static_assert (
            Addres<sector>().defined,
            "Недопустимый сектор памяти"
        );
        static_assert (
            sizeof(DATA) < 255,
            "Размер сохраняемой структцры не может превышать 255 байт"
        );
        FLASH_t::EndOfProgInterruptEn();
        if ( !readFromFlash() ) {
            memcpy (&data, &d, sizeof(DATA));
        }
    }
private:
    static constexpr uint8_t QtyBytes = sizeof(DATA);
    static const uint32_t SectorAddr = Addres<sector>().val;
    static const int32_t SectorSize = Size<sector>().val;
    uint8_t copy[QtyBytes];
    uint8_t* original = (uint8_t*)this;
    int32_t flashOffset;
    uint8_t needErase;
    struct ByteInd_t {
        uint8_t byte;
        uint8_t ind;   
    };
    union Flash_t {
        ByteInd_t data[SectorSize/2];
        uint16_t word[SectorSize/2];
    };
    volatile Flash_t& flash = *( (Flash_t *) SectorAddr );
};


template <class Data, uint8_t sector>
bool Flash<Data,sector>::readFromFlash ()
{
    // обнуляем буфер перед заполнением
    memset (copy, 0xFF, QtyBytes);
 
    // чтение данных в копию data в виде массива
    flashOffset = -1;
    bool indExist[QtyBytes] = {false};
    for (uint32_t i = 0; i < SectorSize; i++) {
        uint8_t index;
        index = flash.data[i].ind;
        if ( index < QtyBytes) {
            copy[index] = flash.data[i].byte;
            indExist[index] = true;
        } else if (index == 0xFF) {
            flashOffset = i;
            break;
        }
    }

    // проверка есть ли ещё место
    if ( flashOffset == -1) {
        needErase = true;
        return false;    
    }

    // проверка остальной части сектора флэш
    for (uint32_t i = flashOffset; i < SectorSize; i++) {
        if (flash.word[i] != 0xFFFF) {
            needErase = true;
            return false;    
        }
    }

    // проверка, что все данные прочитаны
    bool tmp = true;
    for (uint8_t i = 0; i < QtyBytes; i++) {
        tmp &= indExist[i];
    }
    if (tmp) {
        memcpy(original, copy, QtyBytes);
        return true;
    } else {
        return false;
    }

}
template <class Data, uint8_t sector>
void Flash<Data,sector>::update ()
{
    // реализация автоматом
	enum FuncState {
		CheckChanges,
		StartWrite,
		CheckWrite,
		Errase,
		CheckErase
	};
    static FuncState state = CheckChanges;
    static volatile uint8_t dataWrite = 0;
    static uint8_t byteN = 0;

	switch (state) {

    case CheckChanges:
        if (needErase) {
            state = Errase;
        } else if (original[byteN] == copy[byteN]) {
            byteN++;
            if (byteN == QtyBytes) {
                byteN = 0;
            }
        } else {
            state = StartWrite;
        }
		break;

    case StartWrite:
        if ( !FLASH_t::Busy() ) {
            FLASH_t::Unlock();
            FLASH_t::SetProgMode();
            FLASH_t::SetProgSize (FLASH_t::ProgSize::x16);
            dataWrite = original[byteN];
            flash.word[flashOffset] = (uint16_t)byteN << 8 | dataWrite;
            state = CheckWrite;
        }
        break;

    case CheckWrite:
        if ( FLASH_t::EndOfProg() ) {
            FLASH_t::ClearEndOfProgFlag();
            FLASH_t::Lock();
            copy[byteN] = dataWrite;
            flashOffset++;
            if ( flashOffset >= SectorSize ) {
                needErase = true;
            }
            state = CheckChanges;
        }
        break;

    case Errase:
        if ( !FLASH_t::Busy() ) {
            FLASH_t::Unlock();
            FLASH_t::template StartEraseSector<(FLASH_t::Sectors)sector>();
            state = CheckErase;
        }
        break;

    case CheckErase:
        if ( FLASH_t::EndOfProg() ) {
            FLASH_t::ClearEndOfProgFlag();
            FLASH_t::Lock();
            // проверка, что стёрли
            bool tmp = true;
            for (uint32_t i = 0; i < SectorSize; i++) {
                tmp &= (flash.word[i] == 0xFFFF);
            }
            if (tmp) {
                needErase = false;
                memset (copy, 0xFF, QtyBytes);
                flashOffset = 0;
            }
            state = CheckChanges;
        }
        break;
	} // switch
}










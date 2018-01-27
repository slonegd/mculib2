#pragma once

#include "SPI_ral.h"

template<class SPI_, class Data>
class SPI
{
public:
   union {
      Data data;
      uint8_t arr[sizeof(Data)];
   }






private:

};
#pragma once


#if defined(STM32F030x6)

template<uint32_t adr>
uint32_t SPIx<adr>::getDataAdr()
{
   return Base + SPI_ral::DR_t::Offset;
}


template<uint32_t adr>
void SPIx<adr>::clockEnable()
{
   RCC::template clockEnable<SPIx<adr>>();
}


template<uint32_t adr>
void SPIx<adr>::setAsMaster()
{
   SET (conf1(), MSTR);
}


template<uint32_t adr>
void SPIx<adr>::slaveSelectEnable()
{
   SET (conf2(), SSOE);
}


template<uint32_t adr>
void SPIx<adr>::txDMAenable()
{
   SET (conf2(), TXDMAEN);
}


template<uint32_t adr>
void SPIx<adr>::enable()
{
   SET (conf1(), SPE);
}


template<uint32_t adr>
void SPIx<adr>::slaveSelectPulseEnable()
{
   SET (conf2(), NSSP);
}


template<uint32_t adr>
template<typename SPIx<adr>::Div val>
void SPIx<adr>::setBoudRate()
{
   auto tmp = conf1().reg;
   tmp &= ~_3BIT_TO_MASK(conf1(), BR);
   tmp |= VAL_TO_MASK(conf1(), BR, val);
   conf1().reg = tmp;
}


template<uint32_t adr>
template<typename SPIx<adr>::DataSize val>
void SPIx<adr>::setDataSize()
{
   auto tmp = conf2().reg;
   tmp &= ~_4BIT_TO_MASK(conf2(), DS);
   tmp |= VAL_TO_MASK(conf2(), DS, val);
   conf2().reg = tmp;
}




#endif
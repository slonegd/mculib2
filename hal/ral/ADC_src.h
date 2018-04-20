template <uint32_t ADCadr>
void ADCx<ADCadr>::ClockEnable()
{
   RCC->APB2ENR |= ClkEnMask;
   while ( (RCC->APB2ENR & ClkEnMask) == 0 ) { }
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetClock ( Clock val )
{
   conf2().reg &= ~ADC_CFGR2_CKMODE_Msk;
   conf2().reg |= (uint32_t)val << ADC_CFGR2_CKMODE_Pos;
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetResolution ( Resolution val )
{
   conf1().reg &= ~ADC_CFGR1_RES_Msk;
   conf1().reg |= (uint32_t)val << ADC_CFGR1_RES_Pos;
}


template <uint32_t ADCadr>
void ADCx<ADCadr>::SetSampleTime ( SampleTime val )
{
   sampleTime().reg &= ~ADC_SMPR_SMP_Msk;
   sampleTime().reg |= (uint32_t)val << ADC_SMPR_SMP_Pos;
}

#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"

#ifndef ADC_H_
#define ADC_H_

typedef enum
{
	ADC_SCALER_2=0,
	ADC_SCALER_4=2,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
	
}ADC_scaler_Type;

typedef enum
{
	VREF_AVCC,
	VREF_AREF,
	VREF_A256V,
	}ADC_Vref_Type;

typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;



void ADC_Init(ADC_Vref_Type vref,ADC_scaler_Type scaler);
u16 ADC_Read(ADC_Channel_type ch);
//u8 ADC_Volt_Read(void);

#endif /* ADC_H_ */
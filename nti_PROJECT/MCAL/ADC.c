

#include "ADC.h"

void ADC_Init(ADC_Vref_Type vref,ADC_scaler_Type scaler)
{
	// REF select
	switch(vref)
	{
		case VREF_AREF:
			CLR_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
		case VREF_AVCC:
			SET_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
		case VREF_A256V:
			SET_BIT(ADMUX,REFS0);
			SET_BIT(ADMUX,REFS1);
			break;	
	}
	// scaler
	ADCSRA&=0xf8;
	ADCSRA|=scaler;
	
	//Adjusted right
	CLR_BIT(ADMUX,ADLAR);
		
	// Enable
	SET_BIT(ADCSRA,ADEN);
}
u16 ADC_Read(ADC_Channel_type ch)
{
	//return ADC;
	
	/*u16 adc = ((u16)ADCL<<2) | (ADCL>>6);	adc= (u16)ADCL<<2;*/

	/*u16 adc=((u16)ADCH<<8)|ADCL;
	return adc;*/
	
	
	//1.select channel
	ADMUX&=0xE0;
	ADMUX|=ch;
	
	//2.start conversion
	SET_BIT(ADCSRA,ADSC);
	while (GET_BIT(ADCSRA,ADSC));   //Polling till conversion completion
	
	//3.return read
	return ADC;
}
/*u8 ADC_Volt_Read(void)
{
	u16 adc;
	adc=ADC_Read()
	volt=((adc*5)/1024);  
	return volt;
}*/


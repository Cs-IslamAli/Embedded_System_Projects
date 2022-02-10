
#include "Sensors.h"

u16 POT_VoltRead(void)
{
	u16 volt,adc;
	adc=ADC_Read(POT_CH);				
	volt=((u32)adc*5000)/1024;        /*1- multiply by  5000 ->milli volt  3ashan n7l moshkelet el resolution  
										2- bn3ml Casting -> (5000*adc) bsbb el Truncation 
									  ex:5000 *1023  ->5115000 w dah y3tabar 2kbr mn 2bytes el hwa (default integer size).*/
	return volt;
}

u16 TEMP_Read(void)
{
	u16 volt,adc,temp;
	adc=ADC_Read(LM35_CH); // lm_ch
	volt=((u32)adc*5000)/1024; // el mfrod 1023
	temp=volt/10;
	return temp;
}
u8  Pot_Percentage_Read(void)
{   u16 volt,adc;
	u32 percentage;
	adc=ADC_Read(POT_CH);
	//volt=((u16)5000*adc)/1024;
	percentage= ((u32)100*adc)/1023; // lma kant 1024 kant el percent btfwt 2rkam 
	return percentage;
}
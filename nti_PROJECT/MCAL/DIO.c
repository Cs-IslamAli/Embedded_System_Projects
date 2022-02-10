#include "DIO_Interface.h"
extern  const DIO_Status_type PinsStatusArray[TOTAL_PINS];

void DIO_InitPin(DIO_Pin_type pin,DIO_Status_type status)
{	
	 u8 pin_num=pin%8;      // pin : 15 =15%8=7
	 DIO_Port_type port=pin/8;
	switch (status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:	
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
		
	}
} // End of  DIO_InitPin


void DIO_WritePin(DIO_Pin_type pin,DIO_Voltage_type volt)
{
	
	 u8 pin_num=pin%8;      // pin : 15 =15%8=7
	 DIO_Port_type port=pin/8;
	
	if (volt==HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
	}
	else if (volt==LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
			
}// end of DIO_WritePin



DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin)
	{
		 u8 pin_num=pin%8;      // pin : 15 =15%8=7
		 DIO_Port_type port=pin/8;
		
		DIO_Voltage_type volt=LOW;
		switch(port) 
		{					// variable or return 
			case PA:
			 volt= GET_BIT(PINA,pin_num);
			break;
			case PB:
			 volt= GET_BIT(PINB,pin_num);
			break;
			case PC:
			 volt= GET_BIT(PINC,pin_num);
			break;
			case PD:
			 volt= GET_BIT(PIND,pin_num);
			break;
		}
		return volt;
	}
// End of DIO_Read_Pin

void DIO_Write_Port(DIO_Port_type port,u8 value)
{
	switch(port)
	{
		case PA:
		PORTA=value;
		break;
		case PB:
		PORTB=value;
		break;
		case PC:
		PORTC=value;
		break;
		case PD:
		PORTD=value;
		break;
	}
	
}

u8 DIO_Read_Port(DIO_Port_type port) // Sh8ala 
{	u8 value=0;
	
	switch(port)
	{
		case PA:
		value=PINA;
		break;
		case PB:
		value=PINB;
		break;
		case PC:
		value=PINC;
		break;
		case PD:
		value=PINC;
		break;
	}
	return value;
	
}
void DIO_Toggle_pin(DIO_Pin_type pin)
{
	 u8 pin_num=pin%8;      // pin : 15 =15%8=7
	 DIO_Port_type port=pin/8;
	 switch(port)
	 {
		 case PA:
		 TOGGLE_BIT(PORTA,pin_num);
		 break;
		 case PB:
		 TOGGLE_BIT(PORTB,pin_num);
		 break;
		 case PC:
		 TOGGLE_BIT(PORTC,pin_num);
		 break;
		 case PD:
		 TOGGLE_BIT(PORTD,pin_num);
		 break;
	 }
	 
}

void DIO_Init(void)
{	
	DIO_Pin_type i;
	for (i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
	
	
}
 
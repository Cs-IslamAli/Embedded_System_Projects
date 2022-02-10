﻿#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

typedef enum{	
	OUTPUT,
	INFREE,
	INPULL  // input with pull up
	}DIO_Status_type;
	
	typedef enum{	
		PA,
		PB,
		PC,
		PD	
	}DIO_Port_type;
	
	typedef enum{
		LOW,
		HIGH	
	}DIO_Voltage_type;
	
	typedef enum{

	
	void DIO_InitPin(DIO_Pin_type pin,DIO_Status_type status);
	
	
	void DIO_WritePin(DIO_Pin_type pin,DIO_Voltage_type volt); 
	
	
	DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin);

	void DIO_Write_Port(DIO_Port_type port,u8 value);
	u8  DIO_Read_Port(DIO_Port_type port); //u8 DIO_Read_Port(DIO_Port_type port)
	void DIO_Toggle_pin(DIO_Pin_type pin);




	
void DIO_Init(void);

#endif /* DIO_INTERFACE_H_ */
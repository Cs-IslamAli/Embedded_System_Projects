#include "UART.h"




void UART_Init(void)
{
	// UART Frame
	// Asynchronous NormaL Speed
	CLR_BIT(UCSRA,U2X);

	// Baud Rate   9600 Normal Speed 
		UBRRL=51;
	// Enable RX AND TX 
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN); 
}
/*UART Main functions */

void UART_SendByte(u8 data)
{
	while(!GET_BIT(UCSRA,UDRE));
	UDR=data;
}
u8 UART_ReceiveByte_BusyWait(void)// using Polling
{
	while(!GET_BIT(UCSRA,RXC));
	return UDR;
}
u8 UART_ReceiveByte_PeriodiChecking(void)
{
	 if(GET_BIT(UCSRA,RXC))
	 {
		 return UDR;
	 }
	 else
	 {
		 return '#';
	 }
}
u8 UART_ReceiveByte_PeriodiChecking_AnotherWay(u8 *data)
{	
	 // flag is 1 -> data in buffer
    if(GET_BIT(UCSRA,RXC))
	{	
		*data=UDR;
		return 1;		
	}
	else 
	{
		return 0;
	}
	 // rg3 flag b zero 
	 //CLR_BIT(UCSRA,RXC);
}
// void UART_SendString(u8 *p_str)	// unsigned char 
// {
// 	u8 i=0;
// 	for (i=0;p_str[i]!='\0';i++)
// 	{
// 		UART_SendByte(p_str[i]);
// 	}
// }
// void UART_ReceiveString(u8 *ptr_str)         
// {
// 	u8 i=0;
// 	ptr_str[i]=UART_ReceiveByte_BusyWait();					// Using busyWait -> sh8ala bs el peridoic grbha 
// 	
// 	while(ptr_str[i]!='*' )
// 	{
// 			i++;
// 			ptr_str[i]=UART_ReceiveByte_BusyWait();
// 	}
// 	ptr_str[i]='\0';
// }
/*void UART_ReceiveString_tgroba(u8 *ptr_str)
{
	static u8 i=0;
	u8 data;
	u8 flagg=-1;
	flagg=UART_ReceiveByte_AnotherWay(&data);
	if (flagg)
	{
		ptr_str[i]=data;
	}
	else
	{	
	}					// Using busyWait -> sh8ala bs el peridoic grbha
	while(ptr_str[i]!='*' )
	{
		i++;
		flagg=UART_ReceiveByte_AnotherWay(&data);
		if (flagg)
		{
			ptr_str[i]=data;
		}
		
		else{
			}
		
	}
	ptr_str[i]='\0';
}
*/
void UART_SendByte_NoBlock(u8 data)
{
	 UDR=data;
}

u8 UART_ReceiveByte_NoBlock(void)
{
	return UDR;
}

void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}
void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}
void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}
void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_TX_SetCallBack(void(*local_fptr)(void))
{
	UART_TX_Fptr=local_fptr;
}
void UART_RX_SetCallBack(void(*local_fptr)(void))
{
	UART_RX_Fptr=local_fptr;
}
ISR(UART_RX_vect)
{
	if (UART_RX_Fptr != NULLPTR)
	{  
		UART_RX_Fptr();
	}
}
ISR(UART_TX_vect)
{
	if (UART_TX_Fptr != NULLPTR)
	{
		UART_TX_Fptr();
	}
}


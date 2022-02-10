

#ifndef UART_H_
#define UART_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

/*************************Pointer to functions to be assigned to ISR*********************************/

static void (*UART_TX_Fptr)(void)=NULLPTR;
static void (*UART_RX_Fptr)(void)=NULLPTR;

/******************************************************************************************/



/*UART Main functions */
void UART_Init(void);
void UART_SendByte(u8 data);
u8 UART_ReceiveByte_PeriodiChecking_AnotherWay(u8 *data);		 /* OR ANOTHER way		Pointer to data */		
u8 UART_ReceiveByte_BusyWait(void);
u8 UART_ReceiveByte_PeriodiChecking(void);
//void UART_SendString(u8 *p_str);				=> mwgoden f UART_Services
//void UART_ReceiveString(u8 *ptr_str);
//void UART_ReceiveString_tgroba(u8 *ptr_str);
void UART_SendByte_NoBlock(u8 data);
u8 UART_ReceiveByte_NoBlock(void);
void UART_RX_InterruptEnable(void);

void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);

void UART_RX_InterruptDisable(void);


void UART_TX_SetCallBack(void(*local_fptr)(void));

void UART_RX_SetCallBack(void(*local_fptr)(void));




#endif /* UART_H_ */
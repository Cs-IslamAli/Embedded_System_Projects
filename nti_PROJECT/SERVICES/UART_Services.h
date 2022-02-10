/*
 * UART_Services.h
 *
 * Created: 4/15/2021 2:47:29 PM
 *  Author: Islam
 */ 
#include "UART.h"



#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_
void UART_SendString(u8 *p_str);
void UART_ReceiveString(u8 *ptr_str);
void Uart_SendNumber(u32 Number);
u32 Uart_RecieveNumber(void);
void UART_SendStringCheckSum(u8 *str);
u8 UART_RecieveStringCheckSum(u8 *str);
void UART_SendString_Asynchronus(u8 *str);
void UART_RecieveString_Asynchronus(u8 *str);
void TX_Func(void);// deh el function el hdeha ll Isr by Call Back
void RX_Func(void);	




#endif /* UART_SERVICES_H_ */
/*
 * UART_Services.c
 *
 * Created: 4/15/2021 2:47:04 PM
 *  Author: Islam
 */ 
#include "UART_Services.h"

 static u8  *G_Ptr_str_Recieve=NULLPTR;
  static u8  *G_Ptr_str_Send=NULLPTR;
 static u8	Flag=0;



void UART_SendString(u8 *p_str)	// unsigned char
{
	u8 i=0;
	for (i=0;p_str[i]!='\0';i++)
	{
		UART_SendByte(p_str[i]);
	}
	UART_SendByte('#');
}
void UART_ReceiveString(u8 *ptr_str)
{
	u8 i=0;
	ptr_str[i]=UART_ReceiveByte_BusyWait();					// Using busyWait -> sh8ala bs el peridoic grbha
	
	while(ptr_str[i]!='#')					// Hena mst5dm el #                2b2a 8yrha -> # 
	{
		i++;
		ptr_str[i]=UART_ReceiveByte_BusyWait();
	}
	ptr_str[i]='\0';
}
void Uart_SendNumber(u32 Number)
{	
	/*
	u8 *Num_ptr=&Number;
	u8 i;
	for (i=0;i<4;i++)
	{
		UART_SendByte(Num_ptr[i]);
	}
	*/
	
	/*			Another Way			*/
	
	/*u8 *ptr=&Number;
	UART_SendByte(ptr[0]);
	UART_SendByte(ptr[1]);
	UART_SendByte(ptr[2])
	UART_SendByte(ptr[3]);
	*/
	
	
	
			/*		Another Way		*/
	 
	UART_SendByte((u8)Number);
	UART_SendByte((u8)(Number>>8));
	UART_SendByte((u8)(Number>>16));
	UART_SendByte((u8)(Number>>24));
	
}
u32 Uart_RecieveNumber(void)
{	
	//u32 Num;
	/*u8 *Num_ptr=(u8*)&Num;
	u8 i;
	
	for (i=0;i<4;i++)
	{
		Num_ptr[i]= UART_ReceiveByte_BusyWait();
	}
	return Num;*/
	/*		Another Way			*/
u8 b1=UART_ReceiveByte_BusyWait();
u8 b2=UART_ReceiveByte_BusyWait();
u8 b3=UART_ReceiveByte_BusyWait();
u8 b4=UART_ReceiveByte_BusyWait();
u32 Num=b1| (u32)b2<<8 |(u32)b3<<16 | (u32)b4<<24;
return Num;


/*		Another Way		*/
//u32 num;
//u8 *p=(u8*)&num;
/*p[0]=UART_ReceiveByte_BusyWait();
p[1]=UART_ReceiveByte_BusyWait();
p[2]=UART_ReceiveByte_BusyWait();
p[3]=UART_ReceiveByte_BusyWait();
*/ 
}

												/*A software protocol for data Checking*/
												/* 
													-string length ->1 byte
													- String
													-checkSum->2 bytes  
												*/	
void UART_SendStringCheckSum(u8 *str)
{	u16 checkSum=0;
	u8 length=0;
	u8 i;
	/*calculating string length*/
	for (length=0;str[length]!=0;length++);
	/*Sending first byte-> string length*/
	UART_SendByte(length);
	/*Sending whole String */
	for (i=0;i<length;i++)
	{
		UART_SendByte(str[i]);
	/*calculating checkSum Value*/
		checkSum+=str[i];
		// Check Sum -> i+s+l+a+m
	}
	/*Sending CheckSum Value 1st byte then 2nd one*/
	UART_SendByte(checkSum);
	UART_SendByte(checkSum>>8);
	
}
u8 UART_RecieveStringCheckSum(u8 *str)
{	u8 string_length;
	u8 i;
	u16 Received_checkSum,my_checkSum=0;
	/*Receiving String Length*/
	string_length=UART_ReceiveByte_BusyWait();
	// grb b while(string_length--) b3den
	/*Receiving Whole String*/
	for (i=0;i<string_length;i++)
	{
		str[i]=UART_ReceiveByte_BusyWait();
	/*Calculating my Own CheckSum*/
		my_checkSum+=str[i];
	}
	/*Receiving checkSum*/
	u8 b1=UART_ReceiveByte_BusyWait();
	u8 b2=UART_ReceiveByte_BusyWait();
	Received_checkSum=b1|(u16)b2<<8;
	/*Comparing CheckSum values*/
	if (my_checkSum==Received_checkSum)
	{
		return 1;
	}
	else 
	return 0;
	 
}
void UART_SendString_Asynchronus(u8 *str)
{	if(Flag==0)
	{
		UART_TX_SetCallBack(TX_Func);
		UART_SendByte_NoBlock(str[0]);		//
		UART_TX_InterruptEnable();			// hwa 3aks -> el UART_TX_InterruptEnable();  w b3d keda UART_SendByte_NoBlock(str[0]);
		G_Ptr_str_Recieve=str;
		Flag=1;
	}
	
}
void TX_Func(void)			// deh el function el hdeha ll Isr by Call Back
{
	static u8 i =1;
	if (G_Ptr_str_Recieve[i] !=0)
	{
		UART_SendByte_NoBlock(G_Ptr_str_Recieve[i]);
		i++;
	}
	else
	{
		i=1;
		Flag =0;
	}
}

void UART_RecieveString_Asynchronus(u8 *str)
{
	UART_TX_SetCallBack(TX_Func);
	UART_RX_InterruptEnable();	
	G_Ptr_str_Send=str;
}
void RX_Func(void)	
{
	static u8 i=0;
	G_Ptr_str_Send[i]=UART_ReceiveByte_NoBlock();
	i++;
}
/*
 * LCD.c
 *
 * Created: 1/13/2021 6:50:16 PM
 *  Author: samar
 */ 


#include "LCD.h"


#if (LCD_MODE==LCD_8B)

void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_Write_Port(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	
}

void LCD_WriteCommand(u8 com)
{
	DIO_WritePin(RS,LOW);
	DIO_Write_Port(LCD_PORT,com);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x38);  // set font 5*7===2 line ,8 bit mode
	_delay_ms(1);
	LCD_WriteCommand(0x0c);   //0x0f,0x0e display on ,cursor on
	_delay_ms(1);
	LCD_WriteCommand(0x01);       //LCD clear
	_delay_ms(2);
	LCD_WriteCommand(0x06);      //increase DDram address
	_delay_ms(1);
}

#elif  (LCD_MODE==LCD_4B)

void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D4,GET_BIT(data,4));
	DIO_WritePin(D5,GET_BIT(data,5));
	DIO_WritePin(D6,GET_BIT(data,6));
	DIO_WritePin(D7,GET_BIT(data,7));
	

	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D4,GET_BIT(data,0));
	DIO_WritePin(D5,GET_BIT(data,1));
	DIO_WritePin(D6,GET_BIT(data,2));
	DIO_WritePin(D7,GET_BIT(data,3));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	
}

void LCD_WriteCommand(u8 com)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D4,GET_BIT(com,4));
	
	DIO_WritePin(D5,GET_BIT(com,5));
	DIO_WritePin(D6,GET_BIT(com,6));
	DIO_WritePin(D7,GET_BIT(com,7));
	
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D4,GET_BIT(com,0));
	DIO_WritePin(D5,GET_BIT(com,1));
	DIO_WritePin(D6,GET_BIT(com,2));
	DIO_WritePin(D7,GET_BIT(com,3));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x02);

	_delay_ms(1);
	LCD_WriteCommand(0x28);  // set font 5*7===2 line ,8 bit mode
	_delay_ms(1);
	LCD_WriteCommand(0x0c);   //0x0f,0x0e display on ,cursor on
	_delay_ms(1);
	LCD_WriteCommand(0x01);       //LCD clear
	_delay_ms(2);
	LCD_WriteCommand(0x06);      //increase DDram address
	_delay_ms(1);
}


#endif


void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}



void LCD_WriteString(u8 *str)
{
	u8 i;
	for (i=0;str[i]!='\0';i++)
	{
		LCD_WriteData(str[i]);
	}
	
	
}

void LCD_WriteNumber(s64 num)
{
	
	u8 arr[20] ={0};
	u8 i=0 ;
	s8 x;
	if (num<0)
	{
		num*=(-1);
		LCD_WriteChar('-');
	}

	if (num==0)
	{
		LCD_WriteChar('0');
		
	}
	if (num>0) {
		while(num>0)
		{
			arr[i]=num%10 +'0';
			num/=10;
			i++;
		}
	}
	
	for (x=i-1;x>=0;x--)
	{
		LCD_WriteData(arr[x]);
		
	}
	
	
	
}


void LCD_WriteBinary(s64 num){
	
	u8 arr[20] ={0};
	u8 i=0 ;
	s8 x;
	if (num<0)
	{
		num*=(-1);
		LCD_WriteChar('-');
	}

	if (num==0)
	{
		LCD_WriteChar('0');
		
	}
	if (num>0) {
		while(num>0)
		{
			arr[i]=num%2 +'0';
			num/=2;
			i++;
		}
	}
	
	for (x=i-1;x>=0;x--)
	{
		LCD_WriteData(arr[x]);
		
	}
	
	
	
}

void LCD_WriteHex(s64 num){
	
	/*u8 x=num&0x0f;
	u8 y=num>>4;
	if(y<=9){
		LCD_WriteData(y+'0');
	}else{
		
		LCD_WriteData(y-10+'A');
	}*/
	

	
	
	u8 arr[32] ={0};
	u8 i=0 ,rem;
	s8 x;
	

	if (num==0)
	{
		LCD_WriteChar('0');
		
	}
	if (num>0) {
		while(num>0)
		{
			rem=num%16;
			num/=16;
			if (rem<10)
			{
				arr[i]= rem+48;
				i++;
			}//end if
			else if(rem>9&&rem<16)
			{
				arr[i]= rem+55;
				i++;
			}//end else
		
		}//end while
	}
	
	for (x=i-1;x>=0;x--)
	{
		LCD_WriteData(arr[x]);
		
	}

}// end hex func

void LCD_Wr_8_Binary(s16 num)
{
	s8 i ,bit  ;
	
	
	for(i=7;i>=0;i--)
	{
		bit=num>>i;
		if (bit&1)
		{
			LCD_WriteChar('1');
		}else{
			LCD_WriteChar('0');
		}
		
	}
	
	
}

void LCD_GoTo(u8 line ,u8 x)
{
	if (line==0)
	{
		LCD_WriteCommand(0x80+x);
	}else if (line==1)
	{
		LCD_WriteCommand(0x80+0x40+x);
	}
}

void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_GoToWriteNumber(u8 line ,u8 x,s64 num)
{
	LCD_GoTo(line,x);
	LCD_WriteNumber(num);
}

void LCD_ClearLoc(u8 line ,u8 x,u8 cells)
{
	u8 i ;
	LCD_GoTo(line,x);
	for (i=0;i<cells;i++)
	{
		LCD_WriteChar(' ');
	}
	LCD_GoTo(line,x);
}


void LCD_Wr_Binary(u16 decimal)
{
	
	s8 i ,flag=0;
	if (decimal==0)
	{
		LCD_WriteChar('0');
	}else{
		for(i=7;i>=0;i--)
		{
			if(GET_BIT(decimal,i)==1)
			{
				LCD_WriteChar('1');
				flag=1;
			}
			
			else if(flag==1)
			{
				LCD_WriteChar('0');
			}
		}
	}
	
}

void LCD_Draw_Pattern(u8 * ptr,u8 pos)   // to draw pattern we use CG RAM
{
	/*to write in CGram we sent (command=0x40) and the pos in CGRAM that we want to start with.
	one position consist of 8 rows
	*/
	LCD_WriteCommand(0x40|(pos*8));                
	
	for (u8 i=0;i<8;i++)
	{
		LCD_WriteData(ptr[i]);
	}
	// to back to DDRAM
	LCD_WriteCommand(0x80);
}
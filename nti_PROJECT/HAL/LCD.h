/*
 * LCD.h
 *
 * Created: 1/13/2021 11:06:01 AM
 *  Author: samar
 */ 


#ifndef LCD_H_
#define LCD_H_
//her includes 
//#include "DIO_Interface.h"
//#include "StdTypes.h"
//#include "Utils.h"

// mine 
#include "DIO_Interface.h"
#include "StdTypes.h"
#include "Utils.h"
#define  F_CPU 8000000 // clock

#include <util/delay.h>


#define  LCD_4B   0
#define  LCD_8B   1
/**************************confg ********/
#define LCD_MODE     LCD_4B



#define LCD_PORT      PB			// keda mohema fl 8bit bs lakn el 4 bit msh m7tag el lcd_port

/********************* lcd kit (4BIT) ************/
// #define RS      PINA1
// #define EN      PINA2
// 
// #define  D4     PINA3
// #define  D5     PINA4
// #define  D6     PINA5
// #define  D7     PINA6



//protus
#define RS      PINC1
#define EN      PINC2

#define  D4     PINC4
#define  D5     PINC5
#define  D6     PINC6
#define  D7     PINC7
/***********************************/
void LCD_Init(void);


void LCD_WriteData(u8 data);
void LCD_WriteCommand(u8 com);

void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s64 num);
void LCD_WriteString(u8 *str);
void LCD_Clear(void);


void LCD_WriteBinary(s64 num);
void LCD_Wr_Binary(u16 decimal);         //not mine
void LCD_WriteHex(s64 num);
void LCD_Wr_8_Binary(s16 num);

void LCD_GoTo(u8 line ,u8 x);          //set cursor
void LCD_WriteNumber_4D(u16 num);

void LCD_GoToWriteNumber(u8 line ,u8 x,s64 num);
void LCD_ClearLoc(u8 line ,u8 x,u8 cells);


void LCD_Draw_Pattern(u8 * ptr,u8 pos);     // draw any shap on lcd
#endif /* LCD_H_ */
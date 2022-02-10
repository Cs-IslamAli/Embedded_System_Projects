#define  F_CPU 8000000 // clock
#include <util/delay.h>
#include "ADC.h"
#include "Keypad.h"
#include "External_Interrupt.h"
#include "DIO_Interface.h"
#include "LCD.h"
#include "UART.h"
#include "UART_Services.h"
#include "Sensors.h"
#include "Timers.h"

#define ledon  0
#define ledoff 1
#define servo  2
#define color  3
u8 led_num=10;

u8 Comparing_String_to_Array_of_Strings(u8 *str,u8 str2[][7],u8 size,u8 *num)
{
    // works Fine ^_^
    s8 i, j,flag=1;
	*num=0;
    for(i=0; i<size; i++)
    {
        for(j=0; ((str[j] || str2[i][j]) && flag==1); j++)
        {
            if(str[j]>='0' && str[j]<='9')
            {
                *num=str[j]-'0'+((*num) *10);
                if(str[j+1]==0)
                    return i;
               
            }

            else
            {
                if(str[j]!= str2[i][j])
                {
                    flag=0;
                }

            }
        }
        if(flag ==1) return i;
        flag =1;   
    }
    return -2;
}
u16 Set_Servo_Angle(u8 angle)
{
	u16 Angle_num;
	Angle_num=(((u32)angle*999)/180)+999;
	return Angle_num;       
}
u8 colors_arr[][3]={{254,254,1},{1,254,254},{254,254,254}};// yellow lbny white
#define R 0
#define G 1
#define B 2

	
int main(void)	
{	
	sei();
	DIO_Init();
	LCD_Init();
	UART_Init();
	
	u8 str[20];
	

	
	s8 index;
	
	
	u8 name2[][7]= {"ledon","ledoff","servo","color"};
    while(1) 
    {		
		UART_ReceiveString(str);
		LCD_GoTo(0,2);
 		LCD_WriteString(str);
	
		
		
		
		index=Comparing_String_to_Array_of_Strings(str,name2,4,&led_num);
		
	
		switch (index)
		{
			case ledon:
			if(led_num>=4 && led_num <=7)
			{
				
				SET_BIT(PORTA,led_num);		
			}
			else
			{
				
				LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteString("Invalid led on");
			
			}
			break;
			case ledoff:
			if(led_num>=4 && led_num <=7)
			{
				
				CLR_BIT(PORTA,led_num);
			}
			else
			{	LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteString("invalid led off");
				
			}
			break;
			case color:
			if (led_num >=0 && led_num <=2)
			{
				/*RGB led need 3 pwm */
				/* Generating a PWM In timer 0: */
			
			TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
			TIMER0_OC0Mode(OC0_NON_INVERTING);
			OCR0=colors_arr[led_num][R];
				/* Generating a PWM In timer 1: */
					Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
					Timer1_OCRB1Mode(OCRB_NON_INVERTING);
					ICR1=256;
					OCR1B=colors_arr[led_num][G];
			
			/* Generating a PWM In timer 1: */
					
				TIMER2_Init(TIMER2_FASTPWM_MODE,TIMER2_SCALER_8);
				
				TIMER2_OC2Mode(OC2_NON_INVERTING);
				
				OCR2=colors_arr[led_num][B];
				
			}
			else
			{	LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteString("invalid color");
				
			}
			break;
			case servo:
			if(led_num>=0 && led_num <=180)
			{	
				
				
				Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
				Timer1_OCRA1Mode(OCRA_NON_INVERTING);
				ICR1=19999;
				OCR1A=999;
				OCR1A=Set_Servo_Angle(led_num);
				// ---addition :
				_delay_ms(100);     
				ICR1=256;
				
				
			}
			else
			{	LCD_Clear();
				LCD_GoTo(1,1);
				LCD_WriteString("Inv Servo Angle");
			
			}
			break;
			
			default:
			LCD_Clear();											//--> addition
			LCD_GoTo(1,1);
			LCD_WriteString("Invalid string");
			
			
		}
	}
			
}
			

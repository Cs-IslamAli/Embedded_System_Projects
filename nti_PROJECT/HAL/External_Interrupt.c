#include "External_Interrupt.h"
// global pointer to function
static void (*Ptr_F_INT0)(void)=NULLPTR;
static void (*Ptr_F_INT1)(void)=NULLPTR;
static void (*Ptr_F_INT2)(void)=NULLPTR;
/*************************** Interrupt Functions****************************************/
void EXI_Enable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt)
	{
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
		
	}
}
void EXI_Disable(ExInterruptSource_type Interrupt)
{
		switch(Interrupt)
		{
		case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;
		}
}
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge)
{
	switch(Interrupt)
	{
		case EX_INT0:
		switch(Edge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			SET_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
		}
		break;
		case EX_INT1:
		switch(Edge)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
		}
		break;
		case EX_INT2:
		switch(Edge)
		{
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);		
			break;	
			default:
			CLR_BIT(MCUCSR,ISC2); // by default falling egde 
			break;		
		}
		break;
	}
}

/************************************* CallBack_FUnctions************************/
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt)
	{
		case EX_INT0:
		Ptr_F_INT0=LocalPtr;
		break;
		case EX_INT1:
		Ptr_F_INT1=LocalPtr;
		break;
		case EX_INT2:
		Ptr_F_INT2=LocalPtr;
		break;
	}
	
}
/***************************** ISR**************************************************/
ISR(INT0_vect)
{	
	// Check for NullPtr to avoid Runtime Error / System Reset.
	if (Ptr_F_INT0!=NULLPTR)
	{
		Ptr_F_INT0();
	}
}
ISR(INT1_vect)
{	
		// Check for NullPtr to avoid Runtime Error / System Reset.

	if (Ptr_F_INT1!=NULLPTR)
	{
		Ptr_F_INT1();
	}	
}
ISR(INT2_vect)
{
		// Check for NullPtr to avoid Runtime Error / System Reset.

	if (Ptr_F_INT2!=NULLPTR)
	{
		Ptr_F_INT2();
	}
}
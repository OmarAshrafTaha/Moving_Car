/*
 * timers.c
 *
 * Created: 4/8/2023 5:02:04 PM
 *  Author: Omar Taha
 */ 
#include "timers.h"
static unsigned int t0_initial_value= 0;
static unsigned int t2_initial_value= 0;

/********************************************************************************************/
/*@Description: Set timer 0 control register to normal mode by clearing bits COM00 & COM01. */
/********************************************************************************************/
err_state set_timer0_normal_mode(void)
{
	Clear_Bit(4,TCCR0);
	Clear_Bit(5,TCCR0);
	return SUCCESS;
}

/****************************************************************************************/
/*@Description: Setting the initial value for the timer 0 counter register              */
/*@param value      =>  initial value to start timer 0 from						   	    */	
/****************************************************************************************/
err_state set_timer0_intitial_value(uint8_t value)
{
	TCNT0 = value;
	return SUCCESS;
}

/************************************************************************/
/*@Description: Sets the prescaler mode.                                */
/*Choose a prescaler mode from this list => TIMER_OFF_                  */
/*										 =>	NO_PRESCALE_			    */
/*										 => PRESCALE_8_					*/
/*										 => PRESCALE_64_				*/
/*										 => PRESCALE_256_				*/
/*										 => PRESCALE_1024_				*/
/*										 => PRESCALE_EXT_FALLING_		*/
/*										 => PRESCALE_EXT_RISING_        */
/************************************************************************/
err_state set_timer0_prescaler_mode(unsigned int prescaler)
{
	switch(prescaler)
	{
		case 0: //Timer off
			Clear_Bit(0,TCCR0);
			Clear_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;
			
		case 1: //No prescaling
			Set_Bit(0,TCCR0);
			Clear_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;
		
		case 8: //Prescaling set to clk/8
			Clear_Bit(0,TCCR0);
			Set_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;
			
		case 64: //Prescaling set to clk/64
			Set_Bit(0,TCCR0);
			Set_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;						

		case 256: //Prescaling set to clk/256
			Clear_Bit(0,TCCR0);
			Clear_Bit(1,TCCR0);
			Set_Bit(2,TCCR0);
			break;
			
		case 1024: //Prescaling set to clk/8
			Set_Bit(0,TCCR0);
			Clear_Bit(1,TCCR0);
			Set_Bit(2,TCCR0);
			break;
			
		case 11: //Prescaling set to external clock source on T0 pin. clock on falling edge
			Set_Bit(0,TCCR0);
			Set_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;								

		case 12: //Prescaling set to external clock source on T0 pin. clock on rising edge
			Set_Bit(0,TCCR0);
			Set_Bit(1,TCCR0);
			Set_Bit(2,TCCR0);
			break;

		default: //Timer off
			Clear_Bit(0,TCCR0);
			Clear_Bit(1,TCCR0);
			Clear_Bit(2,TCCR0);
			break;			
	}
	return SUCCESS;
}

/************************************************************************/
/*@Description: Stays in a busy loop until the delay is met			    */
/*@param delay_time_in_ms      =>  delay time needed in ms				*/	
/************************************************************************/
err_state timer0_delay(float delay_time_in_ms)
{
	//variable initialization
	unsigned int no_of_overflows;
	unsigned int count = 0;
	
	//get no of overflows needed to achieve the required delay
	no_of_overflows = get_timer0_initial_value(delay_time_in_ms);
	
	//Sets the prescaler mode to the mode chosen by the user (defined as a global variable in the timers.h file)

	
	//keep looping until achieving the number of overflows required
	while(count<no_of_overflows)	
	{	
		//busy loop until the timer interrupt flag is up
		TCNT0 = t0_initial_value;
		set_timer0_prescaler_mode(PRESCALER_MODE);
		while( (TIFR & (1<<0) ) ==0 );
		TCCR0 = 0;		
		Set_Bit(0,TIFR);
		//clear flag
		count++;
	}
	//close the timer
	return SUCCESS;
}

/************************************************************************************************************************************************************************/
/*@Description: Gets The timer initial value according to the delay needed, prescaler mode and CPU frequency, then sets the timer initial value accordingly.		    */
/*@param delay_time_in_ms      =>  delay time needed in ms																												*/
/************************************************************************************************************************************************************************/
unsigned int get_timer0_initial_value(float delay_time_in_ms)
{
	//variable initialization
	volatile unsigned int no_of_overflows=0;
	//Initial value calculations
	delay_time_in_ms = delay_time_in_ms * (0.001);
	no_of_overflows = ceil(delay_time_in_ms / t0_max_delay );
	t0_initial_value = 256.0 - ceil( (delay_time_in_ms/t_tick) / no_of_overflows );
	return no_of_overflows;
}






/************************************************************************/
/* Timer 2 Driver                                                       */
/************************************************************************/


/********************************************************************************************/
/*@Description: Set timer 2 control register to normal mode by clearing bits COM00 & COM01. */
/********************************************************************************************/
err_state set_timer2_normal_mode(void)
{
Clear_Bit(4,TCCR2);
Clear_Bit(5,TCCR2);
return SUCCESS;
}

/****************************************************************************************/
/*@Description: Setting the initial value for the timer 2 counter register              */
/*@param value      =>  initial value to start timer 0 from						   	    */
/****************************************************************************************/
err_state set_timer2_intitial_value(uint8_t value)
{
TCNT2 = value;
return SUCCESS;
}

/************************************************************************/
/*@Description: Sets the prescaler mode.                                */
/*Choose a prescaler mode from this list => TIMER_OFF_                  */
/*										 =>	NO_PRESCALE_			    */
/*										 => PRESCALE_8_					*/
/*										 => PRESCALE_64_				*/
/*										 => PRESCALE_256_				*/
/*										 => PRESCALE_1024_				*/
/*										 => PRESCALE_EXT_FALLING_		*/
/*										 => PRESCALE_EXT_RISING_        */
/************************************************************************/
err_state set_timer2_prescaler_mode(unsigned int prescaler)
{
	switch(prescaler)
	{
	case 0: //Timer off
	Clear_Bit(0,TCCR2);
	Clear_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;

	case 1: //No prescaling
	Set_Bit(0,TCCR2);
	Clear_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;

	case 8: //Prescaling set to clk/8
	Clear_Bit(0,TCCR2);
	Set_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;

	case 64: //Prescaling set to clk/64
	Set_Bit(0,TCCR2);
	Set_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;

	case 256: //Prescaling set to clk/256
	Clear_Bit(0,TCCR2);
	Clear_Bit(1,TCCR2);
	Set_Bit(2,TCCR2);
	break;

	case 1024: //Prescaling set to clk/8
	Set_Bit(0,TCCR2);
	Clear_Bit(1,TCCR2);
	Set_Bit(2,TCCR2);
	break;

	case 11: //Prescaling set to external clock source on T0 pin. clock on falling edge
	Set_Bit(0,TCCR2);
	Set_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;

	case 12: //Prescaling set to external clock source on T0 pin. clock on rising edge
	Set_Bit(0,TCCR2);
	Set_Bit(1,TCCR2);
	Set_Bit(2,TCCR2);
	break;

	default: //Timer off
	Clear_Bit(0,TCCR2);
	Clear_Bit(1,TCCR2);
	Clear_Bit(2,TCCR2);
	break;
	}
	return SUCCESS;
}

/************************************************************************/
/*@Description: Stays in a busy loop until the delay is met			    */
/*@param delay_time_in_ms      =>  delay time needed in ms				*/
/************************************************************************/
err_state timer2_delay(float delay_time_in_ms)
{
//variable initialization
unsigned int no_of_overflows;
unsigned int count = 0;

//get no of overflows needed to achieve the required delay
no_of_overflows = get_timer2_initial_value(delay_time_in_ms);



//keep looping until achieving the number of overflows required
	while(count<no_of_overflows)
	{
		//busy loop until the timer interrupt flag is up
		TCNT2 = t2_initial_value;
		set_timer2_prescaler_mode(PRESCALER_MODE);
		while( (TIFR & (1<<6) ) ==0 );
		TCCR2 = 0;
		Set_Bit(6,TIFR);
		//clear flag
		count++;
	}
		//close the timer
	return SUCCESS;
}

/************************************************************************************************************************************************************************/
/*@Description: Gets The timer initial value according to the delay needed, prescaler mode and CPU frequency, then sets the timer initial value accordingly.		    */
/*@param delay_time_in_ms      =>  delay time needed in ms																												*/
/************************************************************************************************************************************************************************/
unsigned int get_timer2_initial_value(float delay_time_in_ms)
{
//variable initialization
volatile unsigned int no_of_overflows=0;
//Initial value calculations
delay_time_in_ms = delay_time_in_ms * (0.001);
no_of_overflows = ceil( delay_time_in_ms / t2_max_delay );
t2_initial_value = 256.0 - ceil( (delay_time_in_ms/t_tick) / no_of_overflows );
return no_of_overflows;
}
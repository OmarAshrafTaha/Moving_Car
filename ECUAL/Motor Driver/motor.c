/*
 * motor.c
 *
 * Created: 4/6/2023 6:10:38 PM
 *  Author: Omar Taha
 */ 

#include "motor.h"

/***************************************************************************/
/*This error is calculated for the 100 milliseconds resolution(T-Period)!! */
/***************************************************************************/
double err =0.042;//error in the delay times due to context switching.The error is 4.2% of the difference between the required On/Off Time and 50% of the resolution(T-Period).


/************************************************************************/
/*Description: Initialize a motor pin as an output                      */
/*@param ledPin			=>	pin number									*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_init(uint8_t pinNumber, uint8_t portNumber)
{
	DIO_init(pinNumber,portNumber,OUTPUT);
	return SUCCESS;
}

/************************************************************************/
/*Description: Sets a motor pin as HIGH                                 */
/*@param mask			=>	mask for the pins							*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_on(uint8_t mask, uint8_t portNumber)
{
	DIO_array_write(mask,portNumber,HIGH);
	return SUCCESS;
}

/************************************************************************/
/*Description: Sets a motor pin as LOW                                  */
/*@param mask			=>	mask for the pins 							*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_off(uint8_t mask, uint8_t portNumber)
{
	DIO_array_write(mask,portNumber,LOW);
	return SUCCESS;
}

/****************************************************************************************************************************************************************************/
/*Description: Controls the motor speed depending on the given percentage of the maximum speed by setting the duty cycle to the required max_speed percentage               */
/*@param mask				=>	mask for the pins 		                                                                                                                  	*/
/*@param ledPort			=>  port number                                                                                                                                 */
/*@param speedPercentage	=>	duty cycle 		                                                                                                                  		    */
/*@param resolution_in_ms	=>  T-Period                                                                                                                                    */
/****************************************************************************************************************************************************************************/
err_state MOTOR_control(uint8_t mask, uint8_t portNumber,float speedPercentage,float resolution_in_ms)
{
	double on_TIME,off_TIME = 0;
	
	//error handling : the required output deviates depending on how close to the min and max values of the motor speed and also depending on the T-Period
	if(speedPercentage>50)//checks if the duty cycle is higher than 50%
	{
		speedPercentage = speedPercentage+((speedPercentage-50)*err);//adds 4.2% of the difference between the required duty cycle and 50% duty cycle
	}
	
	else//the required duty cycle is 50% or lower
	{
		speedPercentage = speedPercentage-((50-speedPercentage)*err);//subtracts 4.2% of the difference between the required duty cycle and 50% duty cycle
	}
	
	on_TIME = (double) (speedPercentage/100.0)*resolution_in_ms;//sets the duty cycle 
	off_TIME = resolution_in_ms - on_TIME;//gets the off time
	  	
	MOTOR_on(mask,portNumber);//motors on
	timer0_delay(on_TIME);//busy loop until the on time is met
		
	MOTOR_off(mask,portNumber);//motors off	
	timer0_delay(off_TIME);////busy loop until the off time is met
		
	return SUCCESS;
}



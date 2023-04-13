/*
 * motor.c
 *
 * Created: 4/6/2023 6:10:38 PM
 *  Author: Omar Taha
 */ 

#include "motor.h"

/***************************************************************************/
/*This error is calculated for the 100 milliseconds T-Period !!            */
/***************************************************************************/
double d_g_err =0.042;//error in the delay times due to context switching.The error is 4.2% of the difference between the required On/Off Time and 50% of the T-Period.


/************************************************************************/
/*Description: Initialize a motor pin as an output                      */
/*@param u8_a_pinNumber pin number                                      */
/*@param u8_a_portNumber port number                                    */
/************************************************************************/
err_state MOTOR_init(uint8_t u8_a_pinNumber, uint8_t u8_a_portNumber)
{
    DIO_init(u8_a_pinNumber,u8_a_portNumber,OUTPUT);
    return SUCCESS;
}

/************************************************************************/
/*Description: Sets a motor pin as HIGH                                 */
/*@param u8_a_mask mask for the pins                                    */
/*@param u8_a_portNumber port number                                    */
/************************************************************************/
err_state MOTOR_on(uint8_t u8_a_mask, uint8_t u8_a_portNumber)
{
    DIO_array_write(u8_a_mask,u8_a_portNumber,HIGH);
    return SUCCESS;
}

/************************************************************************/
/*Description: Sets a motor pin as LOW                                  */
/*@param u8_a_mask u8_a_mask for the pins                               */
/*@param u8_a_portNumber port number                                    */
/************************************************************************/
err_state MOTOR_off(uint8_t u8_a_mask, uint8_t u8_a_portNumber)
{
    DIO_array_write(u8_a_mask,u8_a_portNumber,LOW);
    return SUCCESS;
}

/*****************************************************************************************************************************************************************************/
/*Description: Controls the motor speed depending on the given percentage of the maximum speed by setting the duty cycle to the required max_speed percentage (Uses timer 0) */
/*@param u8_a_mask u8_a_mask for the pins                                                                                                                                    */
/*@param u8_a_portNumber port number                                                                                                                                         */
/*@param f_a_speedPercentage duty cycle                                                                                                                                      */
/*@param f_a_tPeriod T-Period                                                                                                                                                */
/*****************************************************************************************************************************************************************************/
err_state MOTOR_control(uint8_t u8_a_mask, uint8_t u8_a_portNumber,float f_a_speedPercentage)
{
    double d_l_onTime,d_l_offTime = 0;
    
    //error handling : the required output deviates depending on how close to the min and max values of the motor speed and also depending on the T-Period
    if(f_a_speedPercentage>50)//checks if the duty cycle is higher than 50%
    {
        f_a_speedPercentage = f_a_speedPercentage+((f_a_speedPercentage-50)*d_g_err);//adds 4.2% of the difference between the required duty cycle and 50% duty cycle
    }
    
    else//the required duty cycle is 50% or lower
    {
        f_a_speedPercentage = f_a_speedPercentage-((50-f_a_speedPercentage)*d_g_err);//subtracts 4.2% of the difference between the required duty cycle and 50% duty cycle
    }
    
    d_l_onTime = (double) (f_a_speedPercentage/100.0)*f_g_tPeriod;//sets the duty cycle 
    d_l_offTime = f_g_tPeriod - d_l_onTime;//gets the off time
          
    MOTOR_on(u8_a_mask,u8_a_portNumber);//motors on
    TIMER0_delay(d_l_onTime);//busy loop until the on time is met
        
    MOTOR_off(u8_a_mask,u8_a_portNumber);//motors off	
    TIMER0_delay(d_l_offTime);////busy loop until the off time is met
        
    return SUCCESS;
}



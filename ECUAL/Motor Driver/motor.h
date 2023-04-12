/*
 * motor.h
 *
 * Created: 4/6/2023 6:10:51 PM
 *  Author: Omar Taha
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/Timers Driver/timers.h"

/************************************************************************/
/*Description: Initialize a motor pin as an output                      */
/*@param ledPin			=>	pin number									*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_init(uint8_t pinNumber, uint8_t portNumber);

/************************************************************************/
/*Description: Sets a motor pin as HIGH                                 */
/*@param mask			=>	mask for the pins							*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_on(uint8_t mask, uint8_t portNumber);

/************************************************************************/
/*Description: Sets a motor pin as LOW                                  */
/*@param mask			=>	mask for the pins 							*/
/*@param ledPort		=>  port number									*/
/************************************************************************/
err_state MOTOR_off(uint8_t mask, uint8_t portNumber);

/*****************************************************************************************************************************************************************************/
/*Description: Controls the motor speed depending on the given percentage of the maximum speed by setting the duty cycle to the required max_speed percentage (Uses timer 0) */
/*@param mask				=>	mask for the pins 		                                                                                                                  	 */
/*@param ledPort			=>  port number                                                                                                                                  */
/*@param speedPercentage	=>	duty cycle 		                                                                                                                  		     */
/*@param resolution_in_ms	=>  T-Period                                                                                                                                     */
/*****************************************************************************************************************************************************************************/
err_state MOTOR_control(uint8_t mask, uint8_t portNumber,float speedPercentage,float resolution_in_ms);





#endif /* MOTOR_H_ */
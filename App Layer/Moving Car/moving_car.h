/*
 * moving_car.h
 *
 * Created: 4/6/2023 5:10:27 PM
 *  Author: Omar Taha
 */ 


#ifndef MOVING_CAR_H_
#define MOVING_CAR_H_

#include "../../ECUAL/Motor Driver/motor.h"
#include "../../ECUAL/LED Driver/led.h"
#include "../../ECUAL/Button Driver/button.h"
#include "../../MCAL/Interrupts Driver/interrupts.h"
#include "../../MCAL/Timers Driver/timers.h"

//PWM T-Period is 100 milliseconds
#define resolution 100  

//Motor direction and enable pins
#define L1 0
#define L2 1
#define R1 2
#define R2 3
#define ENB_L 4
#define ENB_R 5

//Controlling Enable pins at the same instruction with masks
#define ENB_PINS_MASK	 0x30
#define FORWARD_MASK_ON  0x05
#define FORWARD_MASK_OFF 0x0A
#define ROTATE_MASK_ON   0x09
#define ROTATE_MASK_OFF  0x06

//Car States
typedef enum car_dir
{
    FORWARD_LONG_SIDE,FORWARD_SHORT_SIDE,ROTATE_RIGHT
}car_dir;

/*************************************************************************************************************************************************************/
/*Description: Setting timer 0 and timer 2 normal modes, enabling global interrupt and timer 2 interrupt and also initializing motor,leds and button pins    */
/*@param void																																				 */
/*************************************************************************************************************************************************************/
err_state car_init(void);

/***************************************************************************************************************************************************************************************************************************************/
/*Description: Moves the car according to the given direction by setting the motor direction pins, sets the speed of the car and keeps the car in the required state until the timer reaches the required time for the current state   */
/*@param value      =>  direction						   	                                                                                                                                                                           */
/***************************************************************************************************************************************************************************************************************************************/
err_state move_car(car_dir direction); //Checks the direction, speed and delay and moves the car accordingly

/*************************************************************************************************************************************************************/
/*Description: Looping on the car states                                                                                                                     */
/*@param void																																				 */
/*************************************************************************************************************************************************************/
err_state car_cycle(void);

#endif /* MOVING_CAR_H_ */
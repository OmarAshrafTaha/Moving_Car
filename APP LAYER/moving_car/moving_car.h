/*
 * moving_car.h
 *
 * Created: 4/6/2023 5:10:27 PM
 *  Author: Omar Taha
 */ 


#ifndef MOVING_CAR_H_
#define MOVING_CAR_H_

#include "../../ECUAL/motor/motor.h"
#include "../../ECUAL/led/led.h"
#include "../../ECUAL/button/button.h"
#include "../../MCAL/interrupts/interrupts.h"
#include "../../MCAL/timers/timers.h"

//PWM T-Period is 100 milliseconds
 

//Motor direction and enable pins
#define u8_g_L1 0
#define u8_g_L2 1
#define u8_g_R1 2
#define u8_g_R2 3
#define u8_g_enbL 4
#define u8_g_enbR 5

//Enable pins masks for the rerquired states
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
/*@param void                                                                                                                                                */
/*************************************************************************************************************************************************************/
err_state car_init(void);

/***************************************************************************************************************************************************************************************************************************************/
/*Description: Moves the car according to the given direction by setting the motor direction pins, sets the speed of the car and keeps the car in the required state until the timer reaches the required time for the current state   */
/*@param en_a_direction direction                                                                                                                                                                                                      */
/***************************************************************************************************************************************************************************************************************************************/
err_state move_car(car_dir en_a_direction);

/*************************************************************************************************************************************************************/
/*Description: Looping on the car states                                                                                                                     */
/*@param void                                                                                                                                                */
/*************************************************************************************************************************************************************/
err_state car_cycle(void);

#endif /* MOVING_CAR_H_ */
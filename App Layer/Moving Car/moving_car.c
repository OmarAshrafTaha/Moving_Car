/*
 * moving_car.c
 *
 * Created: 4/6/2023 5:10:42 PM
 *  Author: Omar Taha
 */ 
#include "moving_car.h"

static unsigned int current_count=0; //counter which increments everytime the ISR is called
static uint8_t start = 0;//start flag
static uint8_t stop  = 0;//stop flag
/*************************************************************************************************************************************************************/
/*Description: Setting timer 0 and timer 2 normal modes, enabling global interrupt and timer 2 interrupt and also initializing motor,leds and button pins    */
/*@param void   																																			 */
/*************************************************************************************************************************************************************/
err_state car_init(void)
{
    //Interrupt initialization
    SREG  |= (1<<7);//enable global interrupt
    MCUCR |= (1<<0) | (1<<1);//setting interrupt 0 sense control to rising edge
    MCUCR |= (1<<2) | (1<<3);//setting interrupt 1 sense control to rising edge
    GICR  |= (1<<6) | (1<<7);//enable external interrupt 0 & External Interrupt 1
    TIMSK |= (1<<6);//enable timer 2 interrupt	
            
    set_timer0_normal_mode();//Set timer 0 to normal mode
    set_timer2_normal_mode();//Set timer 2 to normal mode
    
    //Button ports initialization
    BUTTON_init(2,PORT_D);//initialize button pin as input
    BUTTON_init(3,PORT_D);//initialize button pin as input
        
    //LED ports initialization
    LED_init(0,PORT_B);
    LED_init(1,PORT_B);
    LED_init(2,PORT_B);
    LED_init(3,PORT_B);
    
    //Motor ports initialization
    MOTOR_init(ENB_L,PORT_A);
    MOTOR_init(ENB_R,PORT_A);
    MOTOR_init(L1,PORT_A);
    MOTOR_init(L2,PORT_A);
    MOTOR_init(R1,PORT_A);
    MOTOR_init(R2,PORT_A);
    
    //Set motors enable pins to off
    MOTOR_off(ENB_PINS_MASK,PORT_A);
    return SUCCESS;	
}

/***************************************************************************************************************************************************************************************************************************************/
/*Description: Moves the car according to the given direction by setting the motor direction pins, sets the speed of the car and keeps the car in the required state until the timer reaches the required time for the current state   */
/*@param value      =>  direction						   	                                                                                                                                                                           */
/***************************************************************************************************************************************************************************************************************************************/
err_state move_car(car_dir direction)
{
    unsigned int ovf;
    switch(direction)
    {
        //LONG SIDE 50% MAX SPEED for 3 seconds then stop	
        case 0:		
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(0,PORT_B);//turn moving forward long side led on
            MOTOR_on(FORWARD_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(FORWARD_MASK_OFF,PORT_A);//motors pin2 direction
            ovf = get_timer2_initial_value(3000);//gets the number of overflows needed to reach 3 secs on timer2
            set_timer2_prescaler_mode(PRESCALER_MODE);//sets the prescaler and starts timer2
            while(current_count<ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,50,resolution);//Moves the car with 50% Duty Cycle of T-Period = resolution 
            }
            set_timer2_prescaler_mode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            current_count = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            timer0_delay(500);//wait for 0.5 sec using timer 0
            return SUCCESS;
        
        //SHORT SIDE 30% MAX SPEED for 2 seconds then stop		
        case 1:		   
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(1,PORT_B);//turn moving forward short side led on
            MOTOR_on(FORWARD_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(FORWARD_MASK_OFF,PORT_A);//motors pin2 direction
            ovf = get_timer2_initial_value(2000);//gets the number of overflows needed to reach 2 secs on timer2
            set_timer2_prescaler_mode(PRESCALER_MODE);//sets the prescaler and starts timer2
            while(current_count<ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,30,resolution);//Moves the car with 30% Duty Cycle of T-Period = resolution 
            }
            set_timer2_prescaler_mode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            current_count = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            timer0_delay(500);//wait for 0.5 sec using timer 0
            return SUCCESS;
        
        //ROTATE 90 Degrees then stop		
        case 2:					
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(3,PORT_B);//turn rotating led on
            MOTOR_on(ROTATE_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(ROTATE_MASK_OFF,PORT_A);//motors pin2 direction
            ovf = get_timer2_initial_value(2500);//gets the number of overflows needed to reach 2.5 secs on timer2
            set_timer2_prescaler_mode(PRESCALER_MODE);//sets the prescaler and starts timer2
            while(current_count<ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,20,resolution);//Moves the car with 30% Duty Cycle of T-Period = resolution
            }
            set_timer2_prescaler_mode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            current_count = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            timer0_delay(500);//wait for 0.5 sec using timer 0		
            return SUCCESS;            
    }
    return FAIL;
}

/*************************************************************************************************************************************************************/
/*Description: Looping on the car states                                                                                                                     */
/*@param void																																				 */
/*************************************************************************************************************************************************************/
err_state car_cycle(void)
{
    //all modules initializations
    car_init();
    while(start!=1);
    timer0_delay(1000);
    while(stop!=1)
    {
        move_car(FORWARD_LONG_SIDE);
        move_car(ROTATE_RIGHT);
        move_car(FORWARD_SHORT_SIDE);
        move_car(ROTATE_RIGHT);
    }
return FAIL;
}

//ISR for timer 2 overflow which increments the current_count
ISR(TIMER2_OVF)
{
    current_count++;
}

//ISR for external interrupt 0 on PD2 which alternates between which group of LEDs are ON or OFF
ISR(EXT_INT_0)
{
    start = 1;
    stop = 0;
}

//ISR for external interrupt 1 on PD3 which acts as an emergency stop and keep motors off until start button is pushed again 
ISR(EXT_INT_1)
{
    SREG |= (1<<7);//enabling the global interrupt to check if start is pushed again
    stop = 1;
    start = 0;
    //Set motors enable pins to off	
    MOTOR_off(ENB_PINS_MASK,PORT_A);
    LED_array_off(0xFF,PORT_B);//turn off all leds

    while(start!=1)//busy loop until start is pressed again
    {
        LED_blink(2,PORT_B,500,500);//blink the stop led
    }
}
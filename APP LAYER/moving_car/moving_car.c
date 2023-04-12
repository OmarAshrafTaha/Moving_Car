/*
 * moving_car.c
 *
 * Created: 4/6/2023 5:10:42 PM
 *  Author: Omar Taha
 */ 
#include "moving_car.h"

static unsigned int u16_gs_currentCount=0; //counter which increments everytime the ISR is called
static uint8_t u8_gs_start = 0;//u8_gs_start flag
static uint8_t u8_gs_stop  = 0;//u8_gs_stop flag

/*************************************************************************************************************************************************************/
/*Description: Setting timer 0 and timer 2 normal modes, enabling global interrupt and timer 2 interrupt and also initializing motor,leds and button pins    */
/*@param void                                                                                                                                                */
/*************************************************************************************************************************************************************/
err_state car_init(void)
{
    //Interrupt initialization
    SREG  |= (1<<7);//enable global interrupt
    MCUCR |= (1<<0) | (1<<1);//setting interrupt 0 sense control to rising edge
    MCUCR |= (1<<2) | (1<<3);//setting interrupt 1 sense control to rising edge
    GICR  |= (1<<6) | (1<<7);//enable external interrupt 0 & External Interrupt 1
    TIMSK |= (1<<6);//enable timer 2 interrupt	
            
    TIMER0_normalMode();//Set timer 0 to normal mode
    TIMER2_normalMode();//Set timer 2 to normal mode
    
    //Button ports initialization
    BUTTON_init(2,PORT_D);//initialize button pin as input
    BUTTON_init(3,PORT_D);//initialize button pin as input
        
    //LED ports initialization
    LED_init(0,PORT_B);
    LED_init(1,PORT_B);
    LED_init(2,PORT_B);
    LED_init(3,PORT_B);
    
    //Motor ports initialization
    MOTOR_init(u8_g_enbL,PORT_A);
    MOTOR_init(u8_g_enbR,PORT_A);
    MOTOR_init(u8_g_L1,PORT_A);
    MOTOR_init(u8_g_L2,PORT_A);
    MOTOR_init(u8_g_R1,PORT_A);
    MOTOR_init(u8_g_R2,PORT_A);
    
    //Set motors enable pins to off
    MOTOR_off(ENB_PINS_MASK,PORT_A);
    return SUCCESS;	
}

/***************************************************************************************************************************************************************************************************************************************/
/*Description: Moves the car according to the given direction by setting the motor direction pins, sets the speed of the car and keeps the car in the required state until the timer reaches the required time for the current state   */
/*@param en_a_direction direction                                                                                                                                                                                                      */
/***************************************************************************************************************************************************************************************************************************************/
err_state move_car(car_dir en_a_direction)
{
    unsigned int u16_l_ovf;
    switch(en_a_direction)
    {
        //LONG SIDE 50% MAX SPEED for 3 seconds then u8_gs_stop	
        case 0:		
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(0,PORT_B);//turn moving forward long side led on
            MOTOR_on(FORWARD_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(FORWARD_MASK_OFF,PORT_A);//motors pin2 direction
            u16_l_ovf = TIMER2_getInitialValue(3000);//gets the number of overflows needed to reach 3 secs on timer2
            TIMER2_perscalerMode(PRESCALER_MODE);//sets the prescaler and u8_gs_starts timer2
            while(u16_gs_currentCount<u16_l_ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,50,f_g_tPeriod);//Moves the car with 50% Duty Cycle of T-Period = f_g_tPeriod 
            }
            TIMER2_perscalerMode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            u16_gs_currentCount = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set u8_gs_stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            TIMER0_delay(500);//wait for 0.5 sec using timer 0
            return SUCCESS;
        
        //SHORT SIDE 30% MAX SPEED for 2 seconds then u8_gs_stop		
        case 1:		   
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(1,PORT_B);//turn moving forward short side led on
            MOTOR_on(FORWARD_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(FORWARD_MASK_OFF,PORT_A);//motors pin2 direction
            u16_l_ovf = TIMER2_getInitialValue(2000);//gets the number of overflows needed to reach 2 secs on timer2
            TIMER2_perscalerMode(PRESCALER_MODE);//sets the prescaler and u8_gs_starts timer2
            while(u16_gs_currentCount<u16_l_ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,30,f_g_tPeriod);//Moves the car with 30% Duty Cycle of T-Period = f_g_tPeriod 
            }
            TIMER2_perscalerMode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            u16_gs_currentCount = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set u8_gs_stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            TIMER0_delay(500);//wait for 0.5 sec using timer 0
            return SUCCESS;
        
        //ROTATE 90 Degrees then u8_gs_stop		
        case 2:					
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(3,PORT_B);//turn rotating led on
            MOTOR_on(ROTATE_MASK_ON,PORT_A);//motors pin1 direction
            MOTOR_off(ROTATE_MASK_OFF,PORT_A);//motors pin2 direction
            u16_l_ovf = TIMER2_getInitialValue(2500);//gets the number of overflows needed to reach 2.5 secs on timer2
            TIMER2_perscalerMode(PRESCALER_MODE);//sets the prescaler and u8_gs_starts timer2
            while(u16_gs_currentCount<u16_l_ovf)//keep looping until reaching the number of overflows required
            {
                MOTOR_control(ENB_PINS_MASK,PORT_A,20,f_g_tPeriod);//Moves the car with 30% Duty Cycle of T-Period = f_g_tPeriod
            }
            TIMER2_perscalerMode(TIMER_OFF_);//close the timer
            TCNT2 = 0;//set the timer counter register value to 0
            u16_gs_currentCount = 0;//reset the counter
            LED_array_off(0xFF,PORT_B);//turn off all leds
            LED_on(2,PORT_B);//set u8_gs_stop led to on
            MOTOR_off(ENB_PINS_MASK,PORT_A);//turn off motors' enable pins
            TIMER0_delay(500);//wait for 0.5 sec using timer 0		
            return SUCCESS;            
    }
    return FAIL;
}

/*************************************************************************************************************************************************************/
/*Description: Looping on the car states                                                                                                                     */
/*@param void                                                                                                                                                */
/*************************************************************************************************************************************************************/
err_state car_cycle(void)
{
    //all modules initializations
    car_init();
    while(u8_gs_start!=1);
    TIMER0_delay(1000);//wait 1 sec then start moving
    while(u8_gs_stop!=1)
    {
        move_car(FORWARD_LONG_SIDE);
        move_car(ROTATE_RIGHT);
        move_car(FORWARD_SHORT_SIDE);
        move_car(ROTATE_RIGHT);
    }
return FAIL;
}

//ISR for timer 2 overflow which increments the u16_gs_currentCount
ISR(TIMER2_OVF)
{
    u16_gs_currentCount++;
}

//ISR for external interrupt 0 on PD2 which sets the u8_gs_start flag
ISR(EXT_INT_0)
{
    u8_gs_start = 1;
    u8_gs_stop = 0;
}

//ISR for external interrupt 1 on PD3 sets the emergency u8_gs_stop flag and keep motors off until u8_gs_start button is pushed again 
ISR(EXT_INT_1)
{
    SREG |= (1<<7);//enabling the global interrupt to check if u8_gs_start is pushed again
    u8_gs_stop = 1;
    u8_gs_start = 0;
    //Set motors enable pins to off	
    MOTOR_off(ENB_PINS_MASK,PORT_A);
    LED_array_off(0xFF,PORT_B);//turn off all leds

    while(u8_gs_start!=1)//busy loop until u8_gs_start is pressed again
    {
        LED_blink(2,PORT_B,500,500);//blink the u8_gs_stop led
    }
}
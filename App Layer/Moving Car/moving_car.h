/*
 * moving_car.h
 *
 * Created: 4/6/2023 5:10:27 PM
 *  Author: Omar Taha
 */ 


#ifndef MOVING_CAR_H_
#define MOVING_CAR_H_
#include "../../MCAL/DIO Driver/dio.h"
#include "../../ECUAL/LED Driver/led.h"
#include "../../ECUAL/Button Driver/button.h"

typedef enum car_dir
{
	FORWARD,STOP,ROTATE_RIGHT,ROTATE_LEFT
}car_dir;

err_state car_init(void); //Initializes all car's buttons and motors
err_state move_car(car_dir direction,uint8_t speed,uint8_t delay); //Checks the direction, speed and delay and moves the car accordingly
err_state car_cycle(void);//alternates between longest and shortest sides (main Algorithm)

#endif /* MOVING_CAR_H_ */
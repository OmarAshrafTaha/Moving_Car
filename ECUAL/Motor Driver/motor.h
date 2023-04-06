/*
 * motor.h
 *
 * Created: 4/6/2023 6:10:51 PM
 *  Author: Omar Taha
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

err_state MOTOR_init(uint8_t pinNumber, uint8_t portNumber);
err_state MOTOR_on(uint8_t pinNumber, uint8_t portNumber);
err_state MOTOR_off(uint8_t pinNumber, uint8_t portNumber);
err_state MOTOR_control(uint8_t pinNumber, uint8_t portNumber,uint8_t speedPercentage);





#endif /* MOTOR_H_ */
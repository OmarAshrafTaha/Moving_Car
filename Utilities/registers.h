/*
 * registers.h
 *
 * Created: 4/5/2023 3:16:02 PM
 *  Author: Omar Taha
 */ 

/************************************************************************/
/* All microcontroller registers                                        */
/************************************************************************/
#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "types.h"

/************************************************************************/
/* DIO Registers								                        */
/************************************************************************/
//PORTA registers
#define PORTA *((volatile uint8_t*)0x3B)
#define DDRA  *((volatile uint8_t*)0x3A)
#define PINA  *((volatile uint8_t*)0x39)

//PORTB registers
#define PORTB *((volatile uint8_t*)0x38)
#define DDRB  *((volatile uint8_t*)0x37)
#define PINB  *((volatile uint8_t*)0x36)

//PORTC registers
#define PORTC *((volatile uint8_t*)0x35)
#define DDRC  *((volatile uint8_t*)0x34)
#define PINC  *((volatile uint8_t*)0x33)

//PORTD registers
#define PORTD *((volatile uint8_t*)0x32)
#define DDRD  *((volatile uint8_t*)0x31)
#define PIND  *((volatile uint8_t*)0x30)




#endif /* REGISTERS_H_ */
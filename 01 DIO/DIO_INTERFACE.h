/*
 * Author: Mhmd Aly
 * Date: 24/5/2021
 * This file is used to AVR Atmega32 for DIO Interface
 * */
#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_


void DIO_VoidSetPinDirection(u8 PORT,u8 PIN,u8 DIRECTION);
void DIO_VoidSetPORTDirection(u8 PORT,u8 DIRECTION);

void DIO_VoidSetPinValue(u8 PORT,u8 PIN,u8 VALUE);
void DIO_VoidSetPortValue(u8 PORT,u8 VALUE);

void DIO_VoidTogglePin(u8 PORT,u8 PIN);
void DIO_VoidTogglePort(u8 PORT);

u8	DIO_U8GetPinValue(u8 PORT,u8 PIN);
u8	DIO_U8GetPortValue(u8 PORT);

void DIO_VoidFloating(u8 PORT, u8 PIN);
void DIO_VoidSetPullUp(u8 PORT, u8 PIN);

#define INPUT		0
#define OUTPUT		1

#define LOW			0
#define HIGH		1

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define PORT_A		1
#define PORT_B		2
#define PORT_C		3
#define PORT_D		4

#define PORT_OP		0XFF
#define PORT_IP		0



#endif

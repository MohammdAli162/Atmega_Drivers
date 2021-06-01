#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_INTERFACE.h"
#include "LCD_Config.h"
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
/*
static u8 data_DataPort = PORT_C;
static u8 data_RSpin = PORT_C;
static u8 data_RWpin = PORT_C;
*/
static volatile u8 LCD_GlobalMode = LCD_8BIT_LEN;

#ifdef LCD_16_2
/*static u8 GLOPAL_U8Row = 2;
static u8 GLOPAL_U8Col = 16;*/
static u8 Line = 0;
static u8 Row  = 0;
#elif LCD_40_2
static u8 GLOPAL_U8Row = 2;
static u8 GLOPAL_U8Col = 40;
#endif

static void LCD_VoidsendData(u8 U8_Data){
	/*RS = 1 */
	DIO_VoidSetPinValue(PORT_C ,PIN0 ,HIGH);
	/*R/W = 0  */
	DIO_VoidSetPinValue(PORT_C ,PIN1 ,LOW);
	/*Set port data*/

	switch(LCD_GlobalMode){
		case LCD_8BIT_LEN:
			DIO_VoidSetPortValue(PORT_D,U8_Data);
			/*Enable Sequance*/
			DIO_VoidSetPinValue(PORT_C,2,1);
			_delay_us(2);
			DIO_VoidSetPinValue(PORT_C,2,0);
			_delay_us(2);
		break;
		case LCD_4BIT_LEN:
			/*Sending Higher Nibble*/
			DIO_VoidSetPortValue(PORT_D,(U8_Data & 0XF0));
			/*Enable Sequance*/
			DIO_VoidSetPinValue(PORT_C,2,1);
			_delay_us(2);
			DIO_VoidSetPinValue(PORT_C,2,0);
			_delay_us(2);
				/*Sending Lower Nibble*/
			DIO_VoidSetPortValue(PORT_D,((U8_Data << 4)& 0XF0));
				/*Enable Sequance*/
			DIO_VoidSetPinValue(PORT_C,2,1);
			_delay_us(2);
			DIO_VoidSetPinValue(PORT_C,2,0);
			_delay_us(2);
			break;
		default:
			//error state
			break;
	}
	
}

static void LCD_VoidsendCommand(u8 U8_Command){
	/*RS = 0 */
	DIO_VoidSetPinValue(PORT_C,0,0);
	/*R/W = 0  */
	DIO_VoidSetPinValue(PORT_C,1,0);

	/*Set port data*/
	switch(LCD_GlobalMode){
	case LCD_8BIT_LEN:
		DIO_VoidSetPortValue(PORT_D,U8_Command);
		/*Enable Sequance*/
		DIO_VoidSetPinValue(PORT_C,2,1);
		_delay_us(2);
		DIO_VoidSetPinValue(PORT_C,2,0);
		_delay_us(2);
	break;
	case LCD_4BIT_LEN:
		/*Sending Higher Nibble*/
			DIO_VoidSetPortValue(PORT_D,(U8_Command & 0XF0));
			/*Enable Sequance*/
			DIO_VoidSetPinValue(PORT_C,2,1);
			_delay_us(2);
			DIO_VoidSetPinValue(PORT_C,2,0);
			_delay_us(2);
			/*Sending Lower Nibble*/
			DIO_VoidSetPortValue(PORT_D,((U8_Command << 4)& 0XF0));
			/*Enable Sequance*/
			DIO_VoidSetPinValue(PORT_C,2,1);
			_delay_us(2);
			DIO_VoidSetPinValue(PORT_C,2,0);
			_delay_us(2);
		break;
	default:
		//error state
		break;
	}
}



void LCD_VoidSendChar(u8 U8_Data){
	Line++;
	if(Line == 17 ){
		Line = 0;
		switch(Row){
		case 0:
			Row = 1;
			break;
		case 1:
			Row = 0;
			break;
		}
		LCD_VoidSetPosition(Row,Line);
	}
	LCD_VoidsendData(U8_Data);
}

void LCD_VoidInit(u8 Copy_U8DataLen){

	DIO_VoidSetPinDirection(PORT_C,PIN0,OUTPUT);
	DIO_VoidSetPinDirection(PORT_C,PIN1,OUTPUT);
	DIO_VoidSetPinDirection(PORT_C,PIN2,OUTPUT);
	LCD_GlobalMode = Copy_U8DataLen;
	switch(Copy_U8DataLen){
	case LCD_8BIT_LEN:
		DIO_VoidSetPORTDirection(PORT_D,PORT_OP);
		_delay_us(40);
		//SET FUNCTION
		LCD_VoidsendCommand(0x20 | Copy_U8DataLen | 0x08);
		_delay_us(45);
		//DISPLAY OPTIONS
		LCD_VoidsendCommand(0b00001100);
		_delay_us(40);
		//CLEARING DISPLAY
		LCD_VoidClearDisplay(0);
		_delay_ms(2);
		break;
	case LCD_4BIT_LEN:
		DIO_VoidSetPORTDirection(PORT_D,0XF0);
		_delay_us(40);
		//SET FUNCTION
		LCD_VoidsendCommand(0x02);
		_delay_us(45);
		LCD_VoidsendCommand(0x28);
		_delay_us(45);
		//DISPLAY OPTIONS
		LCD_VoidsendCommand(0x08 | 0x04);
		_delay_us(40);
		//CLEARING DISPLAY
		LCD_VoidClearDisplay(0);
		_delay_ms(2);
		break;
	default:
		//error state
		break;
	}
}

void LCD_VoidSendNumber(u32 Copy_U32Number){
	u8 Local_StrCount[20] ;
	sprintf(Local_StrCount, "%ld", Copy_U32Number);
	LCD_VoidSendString( Local_StrCount);
}

void LCD_VoidSendString(u8 *Copy_StringData){
	while(*Copy_StringData != '\0')
	{
		LCD_VoidSendChar(*Copy_StringData);
		Copy_StringData++;
	}
}

void LCD_VoidClearDisplay(u8 COPY_U8ReturnHome){
	LCD_VoidsendCommand(0X01);
	_delay_ms(2);
	switch(COPY_U8ReturnHome){
	case 0:
		Row = 0;Line = 0;
		LCD_VoidSetPosition(Row,Line);
		break;
	case 1:
		LCD_VoidSetPosition(Row,Line);
		break;
	}
}
void LCD_VoidAddPatern(u8 *COPY_U8Pattern,u8 COPY_U8Address){
	if(COPY_U8Address < 8){
		LCD_VoidsendCommand(0x40 + COPY_U8Address*8);
		_delay_us(40);
		for(int i = 0;i < 8 ; i++){
		LCD_VoidsendData(COPY_U8Pattern[i]);_delay_us(45);
		}
		LCD_VoidSetPosition(Row,Line);
}
}

void LCD_VoidSetPosition(u8 COPY_U8Row,u8 COPY_U8Col){
	Row = COPY_U8Row;
	Line = COPY_U8Col;
	switch(COPY_U8Row){
	case 0:

		break;
	case 1:
		COPY_U8Col += 64;
		break;
	default:
		break;
	}
	_delay_us(40);
	LCD_VoidsendCommand(0x80|COPY_U8Col);

}

void LCD_VoidLineFlib(void){
	switch(Row){
	case 0:
		Row = 1;
		break;
	case 1:
		Row = 0;
		break;
	}
	LCD_VoidSetPosition(Row,Line);
}
void LCD_VoidClearChar(u8 COPY_U8Row,u8 COPY_U8Col){
	u8 COPY_U8Rowtemp = Row;
	u8 COPY_U8Coltemp = Line;
	LCD_VoidSetPosition(COPY_U8Row,COPY_U8Col);
	LCD_VoidsendData(' ');/*Clear Bit*/
	LCD_VoidSetPosition(COPY_U8Rowtemp,COPY_U8Coltemp);

}

void LCD_VoidWriteChar(u8 COPY_U8Row,u8 COPY_U8Col,u8 COPY_U8Data){
	u8 COPY_U8Rowtemp = Row;
	u8 COPY_U8Coltemp = Line;
	LCD_VoidSetPosition(COPY_U8Row,COPY_U8Col);
	LCD_VoidsendData(COPY_U8Data);/*Clear Bit*/
	LCD_VoidSetPosition(COPY_U8Rowtemp,COPY_U8Coltemp);
}


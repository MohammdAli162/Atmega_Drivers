#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H
#define DL	4
#define N	3
#define LCD_8BIT_LEN	(1<<DL)
#define LCD_4BIT_LEN	0
#define LCD_2LINES		(1<<N)
#define LCD_1LINES		0
#define LCD_16_2		0
#define LCD_40_2		1

#define LCD_VoidReturnHome		 LCD_VoidsendCommand(0x02)

void LCD_VoidSendChar(u8 U8_Data);
void LCD_VoidInit(u8 Copy_U8DataLen);
void LCD_VoidSendString(u8 *Copy_StringData);
void LCD_VoidSendNumber(u32 Number);
void LCD_VoidClearDisplay(u8 COPY_U8ReturnHome);
void LCD_VoidSetPosition(u8 COPY_U8Row,u8 COPY_U8Col);
void LCD_VoidAddPatern(u8 *COPY_U8Pattern,u8 COPY_U8Address);
void LCD_VoidLineFlib(void);
void LCD_VoidClearChar(u8 COPY_U8Row,u8 COPY_U8Col);
void LCD_VoidWriteChar(u8 COPY_U8Row,u8 COPY_U8Col,u8 COPY_U8Data);
#endif

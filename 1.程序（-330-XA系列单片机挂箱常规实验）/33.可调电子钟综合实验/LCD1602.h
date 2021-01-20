#ifndef		__LCD1602_H__
#define 	__LCD1602_H__

#include "reg52.h"


#define 	MSB 		0x80
#define 	LSB 		0x00
#define 	TRUE 		1
#define 	FALSE		0
#define 	HIGH 		1
#define 	LOW 		0
//*****************************************
#define  	LINE1     			0
#define  	LINE2     			1
#define  	LINE1_HEAD    			0x80
#define  	LINE2_HEAD    			0xC0
#define  	DATA_MODE    			0x38
#define  	OPEN_SCREEN    			0x0e  //0x0c
#define  	DISPLAY_ADDRESS   		0x80
#define  	CLEARSCREEN    			LCD_en_com(0x01)


//*************************************************************
//change this part at different board

#define  LCDIO     P0
sbit LCD1602_RS=P2^3;   //data command select  1 data  0 command  pin 4 
sbit LCD1602_RW=P2^4;   //read write select   1 read   0 write     pin 5
sbit LCD1602_EN=P2^5;   //LCD enable signal             pin 6
//**********************************************************************
void LCD_en_com(unsigned char command);
	//write command function
void LCD_en_dat(unsigned char temp);
	//write data function
void LCD_set_xy(unsigned char x, unsigned char y);
	//set display address function
void LCD_write_char(unsigned x,unsigned char y,unsigned char dat);
	//write lcd a character function
void LCD_write_string(unsigned char x,unsigned char y,unsigned char *s);
	//write lcd string function
void LCD_init(void);
	//lcd initize function
void LCD_Read_BF(void);
	//LCD Read busy flag
//**********************************************************************

#endif

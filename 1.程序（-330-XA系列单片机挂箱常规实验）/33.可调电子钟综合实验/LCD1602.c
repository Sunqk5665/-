#include <LCD1602.h>



void LCD_Read_BF(void)
{
	unsigned char read=0; 

	//-------------------------------
	//增加读忙超时处理，万一LCD故障，程序可以跳出
	//另外，亦可使用看门狗，如果跳不出去就等狗复位
	unsigned int temp=10000;
	//-------------------------------
	
	LCD1602_RS = LOW;		//RS 0
	LCD1602_RW = HIGH;		//RW 1
	LCD1602_EN = HIGH;		//EN 1	Read BF
	
	LCDIO = 0xFF;
	LCDIO = 0xFF;
	do{
		read = LCDIO;
		//-----------我增加的代码--------------------
		if(--temp==0)
			return;
		//---------------------------------------------
	}while(read&MSB);
}
//*************************************
void LCD_en_com(unsigned char command)
{
	LCD_Read_BF(); 
	
	LCD1602_RS = LOW;   
	LCD1602_RW = LOW;		
	
	LCD1602_EN = HIGH;	
	LCDIO = command;
	LCD1602_EN = LOW;
}
//*********************************
void LCD_en_dat(unsigned char dat)
{
	LCD_Read_BF();
	
	LCD1602_RS = HIGH; 
	LCD1602_RW = LOW;		
	
	LCD1602_EN = HIGH;
	LCDIO = dat;
	LCD1602_EN = LOW;
}
//**********************************************
void LCD_set_xy(unsigned char x,unsigned char y)
{
	unsigned char address;
	if(x == LINE1)	
		address = LINE1_HEAD + y;
	else 			
		address = LINE2_HEAD + y;
	LCD_en_com(address);     
}
//**********************************************
void LCD_write_char(unsigned x,unsigned char y,unsigned char dat)
{
	LCD_set_xy(x,y); 
	LCD_en_dat(dat);
}   
//**********************************************
void LCD_write_string(unsigned char x,unsigned char y,unsigned char *s)
{
	LCD_set_xy(x,y); 
	while(*s)  
	{
		LCDIO = *s;
		LCD_en_dat(*s);   
		s++;
	}
}
//**********************************************
void LCD_init(void)
{ 
	LCD_en_com(DATA_MODE);
		//set 8 bit data transmission mode 
	LCD_en_com(OPEN_SCREEN);
		//open display (enable lcd display)
	LCD_en_com(DISPLAY_ADDRESS);
		//set lcd first display address 
	LCD_en_com(0x18);
	CLEARSCREEN;
		//clear screen
}
//**********************************************

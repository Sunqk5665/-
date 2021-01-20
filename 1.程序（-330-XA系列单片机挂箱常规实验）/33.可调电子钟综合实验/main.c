/*********************************
名称：	LCD显示1302时钟
***********************************/

#include <reg52.h>
#include "1302.h"
#include "LCD1602.h"
sbit SPK = P3^5;

unsigned char num,AC_hour=0,AC_minute=0x01;
unsigned char tab[]="Alarm Clock";
void delay(unsigned char i);

/************************ 自定义字符区***********************************************************/
#define		YEAR	0
#define		MONTH	1
#define		DAY		2

code unsigned char Chinese_Table[]={
    		 						0x08,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x02,     //年: 00H 
             						0x0F,0x09,0x0F,0x09,0x0F,0x09,0x11,0x00,     //月: 01H
             						0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,0x00, 	 //日: 02H
									};   

void Write_My_Data(void)														 
{
	unsigned char num,i;
	i=0;
	num=sizeof(Chinese_Table);
    LCD_en_com(0x40);	//Set start address of CGRAM
	while(num--)
		LCD_en_dat(Chinese_Table[i++]);//write data into CGRAM    
}
/******************************************************************************************************/


//---------------------------日期变量定义------------------------------------------------
#define	second	Day_Table[0]
#define	minute	Day_Table[1]
#define	hour	Day_Table[2]
#define	day 	Day_Table[3]
#define	month	Day_Table[4]
#define	week	Day_Table[5]
#define	year_l	Day_Table[6]

//						   秒   	 分   	   时     日	  月	   星期   年		
unsigned char Day_Table[]={0x56,	0x59,	  0x23,	  0x9,	  0x1,     0x7,	  0x12 };
unsigned char year_h = 0x20;

union	DATA_UNION	{
						unsigned char a,b,c,d,e,f,g;
						unsigned char Day_Tab[7];
					};

//------------------------------------------------------------------------------------------


void LCD_display_all(void)
{
	LCD_set_xy(0,0);//第一行，第一个位
	LCD_en_dat(hour>>4     	|0x30);
	LCD_en_dat(hour&0x0f   	|0x30);//小时
	LCD_en_dat(':');
	LCD_en_dat(minute>>4   	|0x30);
	LCD_en_dat(minute&0x0f 	|0x30);//分
	LCD_en_dat(':');
	LCD_en_dat(second>>4   	|0x30);
	LCD_en_dat(second&0x0f 	|0x30);//秒

	LCD_write_char(0,13,week|0x30);//星期

	LCD_set_xy(1,5);//第二行，第6个位
	LCD_en_dat(year_h>>4 	|0x30);
	LCD_en_dat(year_h&0x0f  |0x30);//年
	LCD_en_dat(year_l>>4 	|0x30);
	LCD_en_dat(year_l&0x0f  |0x30);
	LCD_en_dat(YEAR);
	LCD_en_dat(month>>4     |0x30);
	LCD_en_dat(month&0x0f   |0x30);
	LCD_en_dat(MONTH);
	LCD_en_dat(day>>4       |0x30);
	LCD_en_dat(day&0x0f     |0x30);
	LCD_en_dat(DAY);	
}




void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
/*************************************************
**名    称：矩阵键盘扫描函数
**入口参数：无
**返 回 值：按下键的 键值
*************************************************/
unsigned char keyscan()
{
	P1=0xfe;
	if(P1!=0xef)
	{
		delayms(10);
		if(P1!=0xfe)
		{
			switch(P1)
			{
				case 0xee : num=0;
							break;
				case 0xde :	num=1;
							break;
				case 0xbe : num=2;
							break;
				case 0x7e : num=3;
							break;
			}
		}
	}

	P1=0xfd;
	if(P1!=0xfd)
	{
		delayms(10);
		if(P1!=0xfd)
		{
			switch(P1)
			{
				case 0xed : num=4;
							break;
				case 0xdd :	num=5;
							break;
				case 0xbd : num=6;
							break;
				case 0x7d : num=7;
							break;
			}
		}
	}

	P1=0xfb;
	if(P1!=0xfb)
	{
		delayms(10);
		if(P1!=0xfb)
		{
			switch(P1)
			{
				case 0xeb : num=8;
							break;
				case 0xdb :	num=9;
							break;
				case 0xbb : num=10;
							break;
				case 0x7b : num=11;
							break;
			}
		}
	}

	P1=0xf7;
	if(P1!=0xf7)
	{
		delayms(10);
		if(P1!=0xf7)
		{
			switch(P1)
			{
				case 0xe7 : num=12;
							break;
				case 0xd7 :	num=13;
							break;
				case 0xb7 : num=14;
							break;
				case 0x77 : num=15;
							break;
			}
		}
	}

	return num;
	
}

void AC_Clock()
{
			LCD_write_string(0,0,tab);
			LCD_set_xy(1,9);
			LCD_en_dat(AC_hour>>4     	|0x30);
			LCD_en_dat(AC_hour&0x0f   	|0x30);//小时
			LCD_en_dat(':');
			LCD_en_dat(AC_minute>>4   	|0x30);
			LCD_en_dat(AC_minute&0x0f 	|0x30);//分
}
//==============================================================================================

void main(void)
{
	unsigned char tem;
	SPK=1;
	LCD_init();
	Write_My_Data();
	v_Set1302(Day_Table);
	while(1)
	{	
		LCD_display_all();
		v_Get1302(Day_Table);
		tem=keyscan();
		if(tem==15)
		{
			LCD_en_com(0x0e);
			LCD_en_com(0x02);
			
			while(tem==15) tem=keyscan(); 
			while((tem>=10)&&(tem<14)) tem=keyscan();			
			while(tem>=0&&tem<=9)
			{
				hour=(tem<<4)|(hour&0x0f);				
				LCD_display_all();
				LCD_set_xy(0,0);
				tem=keyscan();						
			}
			
			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan(); 
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				hour=tem|(hour&0xf0);				
				LCD_display_all(); 
				LCD_set_xy(0,1); 				
				tem=keyscan();
			}
			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);  LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				minute=(tem<<4)|(minute&0x0f); 
				LCD_display_all();
				LCD_set_xy(0,3);
				tem=keyscan();
			}
			
			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				minute=tem|(minute&0xf0);
				LCD_display_all();
				LCD_set_xy(0,4);
				tem=keyscan();
			}
			
			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				second=(tem<<4)|(second&0x0f);
				LCD_display_all();
				LCD_set_xy(0,6);
				tem=keyscan();
			}			

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				second=tem|(second&0xf0); 
				LCD_display_all();
				LCD_set_xy(0,7);
				tem=keyscan();
			}

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);LCD_en_com(0x14);LCD_en_com(0x14);
			LCD_en_com(0x14);LCD_en_com(0x14);LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=7)
			{
				week=tem; 
				LCD_display_all();
				LCD_set_xy(0,13);
				tem=keyscan();
			}

			while(tem!=14) tem=keyscan();
			LCD_set_xy(1,6);
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				year_l=(tem<<4)|(year_l&0x0f);
				LCD_display_all();
				LCD_set_xy(1,7);
				tem=keyscan();
			}			

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				year_l=tem|(year_l&0xf0); 
				LCD_display_all();
				LCD_set_xy(1,8);
				tem=keyscan();
			}

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14); LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				month=(tem<<4)|(month&0x0f);
				LCD_display_all();
				LCD_set_xy(1,10);
				tem=keyscan();
			}			

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				month=tem|(month&0xf0); 
				LCD_display_all();
				LCD_set_xy(1,11);
				tem=keyscan();
			}

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				day=(tem<<4)|(day&0x0f);
				LCD_display_all();
				LCD_set_xy(1,13);
				tem=keyscan();
			}			

			while(tem!=14) tem=keyscan();
			LCD_en_com(0x14);
			while(tem==14) tem=keyscan();
			while((tem>=10)&&(tem<14)) tem=keyscan();
			while(tem>=0&&tem<=9)
			{
				day=tem|(day&0xf0); 
				LCD_display_all();
				LCD_set_xy(1,14);
				tem=keyscan();
			}
			while(tem==15) tem=keyscan();
			v_Set1302(Day_Table);
			LCD_en_com(0x0c);
		}
		if(tem==12)
		{
			LCD_en_com(0x01);
			AC_Clock();
			LCD_en_com(0x0c);
			tem=keyscan();
			while(tem!=13)
			{
				tem=keyscan();
				if(tem==15)
				{	
					LCD_set_xy(1,9);
					LCD_en_com(0x0e);
					while(tem==15) tem=keyscan();
					LCD_set_xy(1,9);
					while(tem>=0&&tem<=9)
					{
						AC_hour=(tem<<4)|(AC_hour&0x0f);
						AC_Clock();
						LCD_set_xy(1,9);
						tem=keyscan();		
					}
			
					while(tem!=14) tem=keyscan();
					LCD_set_xy(1,10);
					while(tem==14) tem=keyscan();
					
					while(tem>=0&&tem<=9)
					{
						AC_hour=tem|(AC_hour&0xf0);
						AC_Clock();
						LCD_set_xy(1,10);
						tem=keyscan();
					}
				
					while(tem!=14) tem=keyscan();
					LCD_set_xy(1,12);
					while(tem==14) tem=keyscan();
					
					while(tem>=0&&tem<=9)
					{
						AC_minute=(tem<<4)|(AC_minute&0x0f); 
						AC_Clock();
						LCD_set_xy(1,12);
						tem=keyscan();
					}
			
					while(tem!=14) tem=keyscan();
					LCD_set_xy(1,13);
					while(tem==14) tem=keyscan();
					
					while(tem>=0&&tem<=9)
					{
						AC_minute=tem|(AC_minute&0xf0);
						AC_Clock();
						LCD_set_xy(1,13);
						tem=keyscan();
					}
					LCD_en_com(0x0c);	
			 }
			}
			while(tem!=13) tem=keyscan(); //
			LCD_en_com(0x01);
		}
		if(hour==AC_hour&&minute==AC_minute&&tem!=11)//
			SPK=0;
		else 
			SPK=1;				
		delay(5000);
	}	
}

//--------------------------------------------------------------------------------------------------

void delay(unsigned char i)
{
	while(i--)
		;
}

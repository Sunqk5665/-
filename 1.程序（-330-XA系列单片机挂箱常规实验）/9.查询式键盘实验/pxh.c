/********************************
**名称：触摸式查询键盘实验
**功能：每按下一个按键盘，在数码管上显示对应显示一个数字。
**时间：2017.3.10
*********************************/
#include<reg52.h>
unsigned char key=8;
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //共阳数码管段码0-9，a-f，灰
unsigned char scankey();
void display(unsigned char *pl);
void delayms(unsigned char t);
void main()
{
	while(1)
	{
		key=scankey();
		display(&key);		
	}
}

unsigned char scankey()
{
	static unsigned char num;
	if(P3!=0xff)
	{
		delayms(5);
		if(P3!=0xff)
		{
			switch(P3)
			{
				case 0xfe: num=0; 
					  	   break;
				case 0xfd: num=1; 
						   break;
				case 0xfb: num=2; 
						   break;
				case 0xf7: num=3; 
						   break;
				case 0xef: num=4;
						   break;
				case 0xdf: num=5;
						   break;
				case 0xbf: num=6; 
						   break;
				case 0x7f: num=7; 
						   break;
				default:
				           break;
			}
		}
	}
	return num;
}
/********************************************************
**名称：显示子函数       
**功能：动态扫描P2口做为位选，P0口送段码
**输入：pl指向要显示数据的地址，最后一位
**返回：无
*******************************************************/
void display(unsigned char *pl)
{
	P2=0x01;
	P0=tab[*pl]; 
	delayms(5);
	P0=0xff;		 
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

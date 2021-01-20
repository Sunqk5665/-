/********************************************************************
**名称：计时器实验
**功能：在动态显示的左边两位显示秒0-59
**时间：2017.3.9
********************************************************************/
#include<reg52.h>
#include<intrins.h>

unsigned char count,second;
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //共阳数码管段码0-9，a-f，灰
unsigned char teptab[]={0xff,0xff};

void init(void);
void display(unsigned char *pl);
void delayms(unsigned char t);

void main()
{
	init();
	while(1)
	{
		teptab[0]=second%10;
		teptab[1]=second/10;
		display(teptab);
	}
}

void init(void)
{
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	ET0=1;
	EA=1;
	TR0=1;
}

void time0() interrupt 1 
{
	TH0=0x3c;
	TL0=0xb0;
	count++;
	if(count==20)
	{
		count=0;
		second++;
		if(second==60)
			second=0;
	}
}

/********************************************************
**名称：显示子函数       
**功能：动态扫描P2口做为位选，P0口送段码
**输入：pl指向要显示数据的地址，只显示右边的2位
**返回：无
*******************************************************/
void display(unsigned char *pl)
{ 
	P2=0x02;
	P0=tab[*pl];
	delayms(20);
	P0=0xff;
	P2=0x01;
	P0=tab[*(pl+1)];
	delayms(20);
	P0=0xff;		 
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
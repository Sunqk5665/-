/********************************************************
**名称：ADC0809模数转换实验
**功能：0809采集电压并在数码管上精确的显示
**时间：2017.3.15
*********************************************************/
#include<reg52.h>
#include<intrins.h>

/***********ad0809与单片机的接口定义**********************/
sbit OE=P3^5;		 
sbit EOC=P3^6;
sbit START=P3^4;
sbit CLK=P3^3;
sbit P30=P3^0;	 
=
unsigned int key;
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
unsigned char temdat[]={0,0,0};  //低-高

void init();
void display(unsigned char *pl);
void delayms(unsigned char t);

void main(void)
{
	
	init();
	
	while(1)
	{
		P1=0xf8;	  // 选择IN0通道输入
		START=0;
		START=1;
		START=0;	  //启动AD转换
		while(EOC==0) display(temdat);	 //等待转换结束，如果这里用空语句，显示会很闪
		OE=1;							 //所以等待的时候，就让它显示转换前的值
		key=P1;
		OE=0;		  //OE是将锁存器中的数据送出
		key=1.96*key;		  //将AD转换回来的数（0—255)  化为相应的电压y=(5/255)*x
		temdat[2]=key/100;	  // x∈(0,255) y∈(0,5)
		temdat[1]=key/10%10;
		temdat[0]=key%10;
		display(temdat);
	}
}

void init()
{
	TMOD=0x02;
	TH0=0x14;
	TL0=0x14;
	TR0=1;
	ET0=1;
	EA=1;
}

void time0() interrupt 1
{
	CLK=~CLK;
}

/********************************************************
**名称：显示子函数       
**功能：动态扫描P2口做为位选，P0口送段码
**输入：pl指向要显示数据的地址，最后3位
**返回：无
*******************************************************/
void display(unsigned char *pl)
{
	P2=0x04;
	P0=tab[*pl]; 		    //低
	delayms(3);
	P0=0xff;
	
	P2=0x02;
	P0=tab[*(pl+1)]; 	   	//中
	delayms(3);
	P0=0xff;
	
	P2=0x01;
	P0=tab[*(pl+2)]&0x7f;   //高	//高位数码管总是带小数，因为电压的范围：0—5V
	delayms(3);
	P0=0xff;		 
}

void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

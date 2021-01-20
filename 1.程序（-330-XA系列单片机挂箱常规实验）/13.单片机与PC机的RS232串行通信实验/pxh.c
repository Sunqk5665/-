/******************************************************************************
**名称：单片机与PC机的RS232串行通信实验
**功能：用STC_ISP_V6.85.exe的串口助手 发送数据，然后再数码管上会显示发送的数0——f
**时间：2017.3.13
********************************************************************************/
#include<reg52.h>

unsigned char temp;

unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //共阳数码管段码0-9，a-f，灰
void init(void);
void display(unsigned char dat);
void delayms(unsigned char t);

void main()
{
	init();
	while(1)
	{
		display(temp);
	}
}

void init(void)
{
	TMOD=0x20;	 //T1工作模式2
	TH1=0xfd;	 //波特率9600 
	TL1=0xfd;
	SCON=0x40;   //串口模式1 
	PCON=0x00;	 //波特率不倍增 
	REN=1;
	EA=1;
	ES=1;
	ET1=0;
	TR1=1;
}
void ser() interrupt 4
{
	//if(RI==0) return;
	ES=0;
	RI=0;
	temp=SBUF;		//接收
	ES=1;	
}
void display(unsigned char dat)
{
	P2=0x01;
	P0=tab[dat]; 
	delayms(5);
	P0=0xff;		 
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
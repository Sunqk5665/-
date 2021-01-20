#include<reg52.h>
sbit   output=P1^1 ;
unsigned  char  num=1;
unsigned  int  a=70;   //pwm占空比7:3，通过改变此值来改变占空比：  1<=a<=100

void Init(void)
{
   TMOD=0x01;
	 TH0=(65535-1000)/256;    //（65535-1000）为定时器初值，定时10ms
	 TL0=(65535-1000)%256;
	 EA=1;
	 ET0=1;
	 TR0=1;
}

void  main(void)
{
  Init();
	while(1)
	{
    if(num<=a)
			output=1;
		else
			output=0;
  }
}

void Timer_0()  interrupt  1
{
    TH0=(65535-1000)/256;
	  TL0=(65535-1000)%256;
	
	  num++;
	
	  if(num>100)
			   num=1;
}

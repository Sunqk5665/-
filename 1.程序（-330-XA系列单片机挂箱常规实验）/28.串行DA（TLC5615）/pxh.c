#include<reg52.h>

sbit CS =P1^0;
sbit SCK=P1^1;
sbit DIN=P1^2;

void TLC5615(unsigned int dat)
{
	unsigned char i;
	CS=1;
	SCK=0;
	DIN=0;
	CS=0;
	dat=dat<<6;
	for(i=0;i<12;i++)
	{
		DIN=dat&0x8000;
		SCK=1;
		dat=dat<<1;
		SCK=0;
	}
	CS=1;
}

void main(void)
{
	unsigned int V_dat=0;
	unsigned char i;
	while(1)
	{
		if(V_dat<0x201)
			V_dat+=1;
		else
			V_dat=0;
		TLC5615(V_dat);
		i=100;
		while(i--);
	}
}




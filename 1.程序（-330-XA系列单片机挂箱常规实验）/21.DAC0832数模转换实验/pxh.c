/********************************************************
**���ƣ�DAC0832��ģת��ʵ��
**���ܣ���������������𽥵���,�������𽥵���.
**ʱ�䣺2017.3.14
*********************************************************/
#include<reg52.h>
#include<intrins.h>
sbit CS=P2^7;
sbit WR1=P3^6;

void delayms(unsigned char t);
void main(void)
{
	unsigned char i;
	CS=0;
	WR1=0;
	while(1)
	{
		for(i=0;i<50;i++)
		{
			WR1=1;
			P0=i;
			_nop_();
			WR1=0;
			delayms(250);  //Ϊ��ʹ��������ܾ������������ĸо�
			delayms(250);  //����ʱ����
			delayms(250);
		} 
			WR1=0;	
		for(i=50;i>0;i--)
		{
			WR1=1;
			P0=i;
			_nop_();
			WR1=0;
			delayms(250);
			delayms(250);
			delayms(250);
		} 
	}	
}

void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
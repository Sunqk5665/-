/*************************************************
**���ƣ�������ת��������ʵ��
**���ܣ��������벢������������ô�����չ8��IO��
**ʱ�䣺2017.3.13
*************************************************/
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char 

sbit CLE=P1^0; 	      //164������λ

void delayms(uchar t);
void main(void)
{
	uchar temp;
	temp=0x01;
	ES=0;		      //���ڹ����ڷ�ʽ0����չ����IO�ڣ�����Ҫ�����ж�
	SCON=0x00;	      //���ô��пڿ��ƼĴ���
	while(1)
	{
		CLE=1;
		SBUF=temp;
		while(!TI);	  //������8λ�����жϱ�־λ��1���������0
		TI=0;
		delayms(250);
		delayms(250);
		temp=_cror_(temp,1);
	}
}

void delayms(uchar t)
{
	uchar x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}


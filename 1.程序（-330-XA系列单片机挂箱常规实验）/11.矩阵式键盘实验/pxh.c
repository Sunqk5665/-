/******************************************************************************
**���ƣ�����ʽ����ʵ��
**���ܣ���������ʱ��������ܵ�һλ��ʾ��Ӧ��ֵ0��F
**ʱ�䣺2017.3.10
********************************************************************************/
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char

uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //��������ܶ���0-9��a-f����
uchar num=16,keydat=16;
uchar keyscan();
void display(uchar *pl);
void delayms(uchar t);
void main(void)
{
	while(1)
	{
		keydat=keyscan();
		display(&keydat);		
	}
}
/*************************************************
**��    �ƣ��������ɨ�躯��
**��ڲ�������
**�� �� ֵ�����¼��� ��ֵ
*************************************************/
uchar keyscan()
{
	P3=0xfe;
	if(P3!=0xfe)
	{
		delayms(10);
		if(P3!=0xfe)
		{
			switch(P3)
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

	P3=0xfd;
	if(P3!=0xfd)
	{
		delayms(10);
		if(P3!=0xfd)
		{
			switch(P3)
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

	P3=0xfb;
	if(P3!=0xfb)
	{
		delayms(10);
		if(P3!=0xfb)
		{
			switch(P3)
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

	P3=0xf7;
	if(P3!=0xf7)
	{
		delayms(10);
		if(P3!=0xf7)
		{
			switch(P3)
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
/********************************************************
**���ƣ���ʾ�Ӻ���       
**���ܣ���̬ɨ��P2����Ϊλѡ��P0���Ͷ���
**���룺plָ��Ҫ��ʾ���ݵĵ�ַ�����һλ
**���أ���
*******************************************************/
void display(unsigned char *pl)
{
	P2=0x01;
	P0=tab[*pl]; 
	delayms(5);
	P0=0xff;		 
}
void delayms(uchar t)
{
	uchar x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
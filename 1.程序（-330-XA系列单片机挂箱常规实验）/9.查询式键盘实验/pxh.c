/********************************
**���ƣ�����ʽ��ѯ����ʵ��
**���ܣ�ÿ����һ�������̣������������ʾ��Ӧ��ʾһ�����֡�
**ʱ�䣺2017.3.10
*********************************/
#include<reg52.h>
unsigned char key=8;
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //��������ܶ���0-9��a-f����
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
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

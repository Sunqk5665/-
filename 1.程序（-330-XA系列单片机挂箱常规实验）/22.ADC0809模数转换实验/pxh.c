/********************************************************
**���ƣ�ADC0809ģ��ת��ʵ��
**���ܣ�0809�ɼ���ѹ����������Ͼ�ȷ����ʾ
**ʱ�䣺2017.3.15
*********************************************************/
#include<reg52.h>
#include<intrins.h>

/***********ad0809�뵥Ƭ���Ľӿڶ���**********************/
sbit OE=P3^5;		 
sbit EOC=P3^6;
sbit START=P3^4;
sbit CLK=P3^3;
sbit P30=P3^0;	 
=
unsigned int key;
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
unsigned char temdat[]={0,0,0};  //��-��

void init();
void display(unsigned char *pl);
void delayms(unsigned char t);

void main(void)
{
	
	init();
	
	while(1)
	{
		P1=0xf8;	  // ѡ��IN0ͨ������
		START=0;
		START=1;
		START=0;	  //����ADת��
		while(EOC==0) display(temdat);	 //�ȴ�ת����������������ÿ���䣬��ʾ�����
		OE=1;							 //���Եȴ���ʱ�򣬾�������ʾת��ǰ��ֵ
		key=P1;
		OE=0;		  //OE�ǽ��������е������ͳ�
		key=1.96*key;		  //��ADת������������0��255)  ��Ϊ��Ӧ�ĵ�ѹy=(5/255)*x
		temdat[2]=key/100;	  // x��(0,255) y��(0,5)
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
**���ƣ���ʾ�Ӻ���       
**���ܣ���̬ɨ��P2����Ϊλѡ��P0���Ͷ���
**���룺plָ��Ҫ��ʾ���ݵĵ�ַ�����3λ
**���أ���
*******************************************************/
void display(unsigned char *pl)
{
	P2=0x04;
	P0=tab[*pl]; 		    //��
	delayms(3);
	P0=0xff;
	
	P2=0x02;
	P0=tab[*(pl+1)]; 	   	//��
	delayms(3);
	P0=0xff;
	
	P2=0x01;
	P0=tab[*(pl+2)]&0x7f;   //��	//��λ��������Ǵ�С������Ϊ��ѹ�ķ�Χ��0��5V
	delayms(3);
	P0=0xff;		 
}

void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

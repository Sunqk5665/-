/******************************************************************************
**���ƣ���Ƭ����PC����RS232����ͨ��ʵ��
**���ܣ���STC_ISP_V6.85.exe�Ĵ������� �������ݣ�Ȼ����������ϻ���ʾ���͵���0����f
**ʱ�䣺2017.3.13
********************************************************************************/
#include<reg52.h>

unsigned char temp;

unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //��������ܶ���0-9��a-f����
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
	TMOD=0x20;	 //T1����ģʽ2
	TH1=0xfd;	 //������9600 
	TL1=0xfd;
	SCON=0x40;   //����ģʽ1 
	PCON=0x00;	 //�����ʲ����� 
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
	temp=SBUF;		//����
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
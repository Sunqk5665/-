/*************************************************
**���ƣ����п�ת�����п�ʵ��
**���ܣ�����165��������,�������
**ʱ�䣺2017.3.14
*************************************************/
#include<reg52.h>

sbit sh=P1^0;
void init();
void delayms(unsigned char t);
void main()
{
	init();
	while(1)
	{
		sh=0;	 //����(load)�� ���벢������ڵ�8 λ����
		sh=1;	 //��λ(shift)���������뱻����������ת����ʼ
		while(!RI);
		RI=0;
		P2=SBUF;
		delayms(0);
	}
}

void init()
{
	SCON=0x10; //�贮�ڷ�ʽ0,�������
	ES=0;	   //�������ж�
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
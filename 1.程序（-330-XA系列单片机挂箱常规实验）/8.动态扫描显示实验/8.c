/********************************
**���ƣ���̬ɨ����ʾʵ��
**���ܣ��ڹ���������϶�̬��ʾ��01234567��
**ʱ�䣺2017.3.10
*********************************/
#include<reg52.h>
#include<intrins.h>	//�ڲ�����  ͷ�ļ�
					//����һ������ѭ�����ң���n���ڶ���������λ
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //��������ܶ���0-9��a-f����
unsigned char dat[]={0,1,2,3,4,5,6,7};//��Ҫ��ʾ������
void display(unsigned char *pl,tem);
void delayms(unsigned char t);
void main(void)
{
	while(1)
	{
		display(dat,8);
	}
}

/********************************************************
**���ƣ���ʾ�Ӻ���       
**���ܣ���̬ɨ��P2����Ϊλѡ��P0���Ͷ���
**���룺plָ��Ҫ��ʾ���ݵĵ�ַ��temҪ��ʾ��λ��
**���أ���
*******************************************************/
void display(unsigned char *pl,tem)
{
	unsigned char i,dt;
	P2=0x01;
	dt=0x01;
	for(i=0;i<tem;i++)
	{
		P0=tab[*(pl+i)];
		delayms(10);	//��ʱ̫�����������˸
		dt=_crol_ (dt,1);
		P2=dt;
		P0=0xff;		
	}			 
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

/*************************************************
**���ƣ����п�ת�����п�ʵ��(IO��ģ��)
**ʱ�䣺2017.3.14
*************************************************/
#include <reg52.h> 
#include <intrins.h>

#define uchar unsigned char 
#define uint unsigned int 

sbit pl=P1^0;  
sbit clk=P1^1; 
sbit dat =P1^2;

uchar conver_seir()
{
	uchar i,buf ;
	pl=0;		 //���벢������
	_nop_();
	pl=1;		//����������λ��׼����
	clk=0;
	for(i=0;i<8;i++)
	{
		ACC=ACC>>1;
		clk=0;
		if(dat==1)
		ACC=ACC|0X80;
		clk=1;	 		//����������
		buf=ACC;  //�������Ƴ���8λ���ݴ���DATA_data��
	} 
	return(buf);
}

void main()
{
	P2=0xff;
	ACC=0X00;
	while(1)
	{
		P2=conver_seir();
	}
}
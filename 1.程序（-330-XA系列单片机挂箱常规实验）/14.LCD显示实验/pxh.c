/*************************************************
**���ƣ�LCD��ʾʵ��
**���ܣ���Һ����ʾģ������ʾzhejiang Qiu Shi,jiaoxueyiqi.
**ʱ�䣺2017.3.13
*************************************************/
#include<reg52.h>
#define uchar unsigned char
sbit lcdEN=P1^0;  //ʹ���ź�
sbit lcdRW=P1^1;  //����дѡ��
sbit lcdRS=P1^2;  //���ݡ�����ѡ��
uchar code tab[]="Zhejiang Qiu Shi";
uchar code tabl[]="Jiao Xue Yi Qi";
void delayms(uchar t);
void write_dat(uchar dat);
void write_com(uchar com);
void init(void);
void main(void)
{
	uchar i;
	init();
	for(i=0;i<16;i++)
		write_dat(tab[i]);
	write_com(0x80+0x40);
	for(i=0;i<14;i++)
		write_dat(tabl[i]);
	while(1);
}
/*************************************************
**��    �ƣ���ʼ���Ӻ���
**��ڲ�������
**�� �� ֵ����
*************************************************/
void init(void)
{
	lcdRW=0;               //һֱ��д���д����
	write_com(0x38);	   //��ʾģʽ����
	delayms(5);			   
	write_com(0x0c);	   //��ʾ���ء���������
	delayms(5);
	write_com(0x06);	   //��ַָ������
	delayms(5); 
	write_com(0x01);	   //��ʾ����
}
/*************************************************
**��    �ƣ�д�����Ӻ���
**��ڲ�����״̬��    �����ʱ��
**�� �� ֵ����
*************************************************/
void write_com(uchar com)
{
	lcdEN=0;
	lcdRS=1;
	delayms(10);
	lcdRS=0;
	P0=com;
	delayms(5);
	lcdEN=1;
	delayms(5);
	lcdEN=0;
}
/*************************************************
**��    �ƣ�д�����Ӻ���
**��ڲ�������ʾ���ַ�    �����ʱ��
**�� �� ֵ����
*************************************************/
void write_dat(uchar dat)
{
	lcdEN=0;
	lcdRS=0;
	delayms(10);
	lcdRS=1;
	P0=dat;
	delayms(5);
	lcdEN=1;
	delayms(5);
	lcdEN=0;
}
void delayms(uchar t)
{
	uchar x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
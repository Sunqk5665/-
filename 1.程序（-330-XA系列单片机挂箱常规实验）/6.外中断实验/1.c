/********************************
**ʵ�����ƣ����ж�ʵ��
**Ӳ�����ӣ�P0�����Ӷ�̬�����a-h��P2������H1-H8��P3�����Ӵ���ʽ��ѯ����
**ʵ�ֹ��ܣ���̬����ܵ�һλѭ����ʾ��0-F�����°���S3�������¿�ʼѭ����ʾ��
**���ʱ�䣺2017.3.9
/*********************************/
#include <reg52.h>
unsigned int t;
unsigned int z;
sbit P3_2=P3^2;
unsigned char a,b;
void delay(unsigned int t);
unsigned char tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
                     0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
void main()
{
	EA=1;
	EX0=1;
	IT0=0;
	while(1)
	{
		for(z=0;z<16;z++)
		 {			    
		  P0=tab[z];
			P2=0x01;
			delay(1000);
		 }							  
	 }
}
void delay(unsigned int t)
{
	unsigned char j;
	unsigned int i;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);	
}					 
void ext0() interrupt 0 using 1
{
	   while(!P3_2)
	   {
	    P0=tab[z];
		  P2=0x01;
		}	   
	  	z=16;
}
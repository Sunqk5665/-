/***************************************************************************
**ʵ������: 16X16���������ʾ
**ʵ��Ч��: "�㽭���ǿƽ��豸���޹�˾"��16X16�ĵ��������������ƶ�.
**ʱ��: 2017.3.13
**��    ˾: �㽭��ʵ�ƽ��豸���޹�˾
***************************************************************************/
/*****************************ͷ�ļ�����**************************************/
#include<reg52.h>
#include<intrins.h>
#include<pxh.h>
/*****************************IO���Ŷ���*************************************/
sbit ser=P1^0;
sbit nss=P1^1;
sbit clk=P1^2;
/******************************���ݶ���*************************************/
unsigned char count;
unsigned int offset;

unsigned char lietab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
/*************************��������********************************************/
void sendbyte(unsigned char dat);
void delayms(unsigned char t);
void init();

/***********************��������ʼ********************************************/
void main()
{
	unsigned char i;
	init();
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			nss=0;
			sendbyte(0xff);			   	//�����Ļ��ʾ
			sendbyte(lietab[i]);       	//������ɨ�� ��lietab[]��ȡֵ
			sendbyte(tab[2*i+1+offset]);//���·��tab[]�й�
			sendbyte(tab[2*i+offset]);	//���·��tab[]�й�
			nss=1;						//595���벢�� 4��ֵ��������,��һ����ʾ,
			delayms(3);					//��Ȼ��һ����ʾһ������˸
		}
		for(i=8;i<16;i++)
		{
			nss=0;
			sendbyte(lietab[i-8]);	   	//������ɨ�� ��lietab[]��ȡֵ
			sendbyte(0xff);			   	//�Ұ���Ļ��ʾ
			sendbyte(tab[2*i+1+offset]);
			sendbyte(tab[2*i+offset]);
			nss=1;
			delayms(3);
		} 
	 }
}
/*************************��ʱ��T0��ʼ��*****************************************/
void init()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TH0=0x3c;
	TL0=0xb0;
	TR0=1;
}
/*************************��ʱ���жϷ����ӳ���*************************************/
void time0() interrupt 1 
{
	TH0=0x3c;
	TL0=0xb0;
	count++;
	if(count==2)		 //���ƹ������ٶ�
	{
		count=0;
		offset+=2;		 //������ƫ����offset
		if(offset==4900)
			offset=0;	 //ѭ���Ķ�
	}		
}
/***************************** �������ݸ�595********************************/
void sendbyte(unsigned char dat)
{
	unsigned char i,temp;	   //��ת����һ�㷽��
	temp=dat;
	for(i=0;i<8;i++)
	{
//		nss=0;
		if(temp&0x01)
			ser=1;
		else
			ser=0;
		clk=0;
		_nop_();
		_nop_();
		clk=1;
		temp>>=1;
//		nss=1;
	}	
}
void delayms(unsigned char t)  //��ʱtms
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
/***************************************************************************
**ʵ������: 16X16������ʾ����
**ʵ��Ч��: ѭ����ʾ"ɽ���Ƽ���ѧ"�������֣���ʾʱ����5���л���ʽ���ֱ�Ϊ�����������ơ����ơ����ƺ�����
**ʵ�����ߣ�Sunqker
**ʱ��: 2021/01/07
***************************************************************************/
/*****************************ͷ�ļ�����**************************************/
#include<reg52.h>
#include<intrins.h>
#include<pxh.h>
#define uchar unsigned char
#define uint unsigned int
/*****************************IO���Ŷ���*************************************/
sbit ser=P1^0;//595���������(DS)
sbit nss=P1^1;
sbit clk=P1^2;
sbit k1 =P2^0;  //k1���Ű���
sbit k2 =P2^1;  //k2��ͣ����
sbit k3 =P3^2;  //k3ģʽ�л�����
/******************************���ݶ���*************************************/
uchar count;
int flag=1;
uint offset=0;
uint offsetb; 	//���Ʋ�ͬ�Ӻ�����ƫ����
uint v=2;		//�����ٶ�
uint a=1;		//ģʽѡ���־λ
uchar lietab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//��ɨ��
uchar lietab2[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//��ɨ��

/*************************��������********************************************/
void sendbyte(uchar dat);
void delayms(uchar t);
void DelayUs(uint M);
void init();
void display1();//������ʾ
void display2();//������ʾ
void display3();//������ʾ
void display4();//������ʾ
void display5();//ѭ����ʾ
void stop();  	//ֹͣ����
void start();	//���ź���	  
/***********************************/
void DelayUs(uint M)  //������ʱ��������ʱ(M) ms
{
    uint i;
	uint j;
	for(i=0;i<M;i++)
	{
		for(j=0;j<200;j++);
		for(j=0;j<102;j++);
	}
}
/***********************��������ʼ********************************************/
void main()
{
	init();    	//�����жϳ�ʼ�� 
	while(1)    //��ѭ��
	{
		stop();
		start();
		if(a==1)	 //ģʽ1
		{
			display1();
		}
    	else if(a==2)  //ģʽ2
		{
		 	display2();
		}
		else if(a==3)  //ģʽ3
		{ 
		    display3();
		}
		else if(a==4)  //ģʽ4
		{ 
		    display4();
		}
		else if(a==5)  //ģʽ5
		{ 
		    display5();
		}
	}
}
/*************************ģʽ1��������ʾ*****************************************/
void display1()
{
	uchar i;
	v=2;
	offsetb=2*offset;
	if(offsetb>=224)
		offset=0;	 //ѭ������
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(0xff);			   	 //�����Ļ��ʾ
		sendbyte(lietab[i]);       	 //������ɨ�� ��lietab[]��ȡֵ
		sendbyte(tab[2*i+1+offsetb]);//���·��tab[]�й�
		sendbyte(tab[2*i+offsetb]);	 //���·��tab[]�й�
		nss=1;						 //595���벢�� 4��ֵ��������,��һ����ʾ,��Ȼ��һ����ʾһ������˸
		delayms(3);					 //
	}
	for(i=8;i<16;i++)
	{
		nss=0;
		sendbyte(lietab[i-8]);	   	//������ɨ�� ��lietab[]��ȡֵ
		sendbyte(0xff);			   	//�Ұ���Ļ��ʾ
		sendbyte(tab[2*i+1+offsetb]);
		sendbyte(tab[2*i+offsetb]);
		nss=1;
		delayms(3);
	} 
}
 /************************ģʽ2��������ʾ*****************************************/
 void display2()
{
	uchar i;
	v=2;
	offsetb=2*offset;					//ÿ��ƫ��һ��
	if(offsetb>=224)					
		    offset=0;
	for(i=0;i<8;i++)
		{
			nss=0;
			sendbyte(0xff);			   	//�����Ļ��ʾ
			sendbyte(lietab[i]);       	//������ɨ�� ��lietab[]��ȡֵ
			sendbyte(tab[2*i+1+224-offsetb]);//���·��tab[]�й�
			sendbyte(tab[2*i+224-offsetb]);	//���·��tab[]�й�
			nss=1;						//595���벢�� 4��ֵ��������,��һ����ʾ,
			delayms(3);					//��Ȼ��һ����ʾһ������˸
		}
		for(i=8;i<16;i++)
		{
			nss=0;
			sendbyte(lietab[i-8]);	   	//������ɨ�� ��lietab[]��ȡֵ
			sendbyte(0xff);			   	//�Ұ���Ļ��ʾ
			sendbyte(tab[2*i+1+224-offsetb]);
			sendbyte(tab[2*i+224-offsetb]);
			nss=1;
			delayms(3);
		} 		
}

/*************************ģʽ3��������ʾ****************************************/
 void display3()
{
	uchar i;
	v=2;
	offsetb=2*offset;					//ÿ��ƫ��һ��
	 if(offsetb>=224)
		offset=0;
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(tab2[2*i+1+offsetb]);
		sendbyte(tab2[2*i+offsetb]);
		sendbyte(0x00);			   	//�ϰ���Ļ��ʾ
		sendbyte(lietab2[i]);       //������ɨ�� ��lietab2[]��ȡֵ
		nss=1;						//595���벢�� 4��ֵ��������,��һ����ʾ,
		delayms(3);					//��Ȼ��һ����ʾһ������˸
	}
	for(i=8;i<16;i++)
	{
		nss=0;	
		sendbyte(tab2[2*i+1+offsetb]);
		sendbyte(tab2[2*i+offsetb]); 
		sendbyte(lietab2[i-8]);	   	//������ɨ�� ��lietab2[]��ȡֵ
		sendbyte(0x00);			   	//�°���Ļ��ʾ
		nss=1;
		delayms(3);
	} 
} 
/*************************ģʽ4��������ʾ******************************************/
 void display4()
{								  
	uchar i;
	v=2;
	offsetb=2*offset;					//ÿ��ƫ��һ��
	if(offsetb>=224)
		offset=0; 
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(tab2[2*i+1+224-offsetb]);//���·��tab[]�й�
		sendbyte(tab2[2*i+224-offsetb]);	//���·��tab[]�й�
		sendbyte(0x00);			   	//�ϰ���Ļ��ʾ
		sendbyte(lietab2[i]);       	//������ɨ�� ��lietab2[]��ȡֵ
		nss=1;						//595���벢�� 4��ֵ��������,��һ����ʾ,
		delayms(3);					//��Ȼ��һ����ʾһ������˸
	}
	for(i=8;i<16;i++)
	{
		nss=0;	
		sendbyte(tab2[2*i+1+224-offsetb]);
		sendbyte(tab2[2*i+224-offsetb]); 
		sendbyte(lietab2[i-8]);	   	//������ɨ�� ��lietab2[]��ȡֵ
		sendbyte(0x00);			   	//�°���Ļ��ʾ
		nss=1;
		delayms(3);
	} 
} 
/*************************ģʽ5��ѭ����ʾ*****************************************/
void display5()
{
	uchar i;
	v=20;
	offsetb=32*offset+32;				//����ƫ��16�м�һ����Ļ�ľ�����ѭ����ʾ
	if(offsetb>=224)
		offset=0;
	for(i=0;i<8;i++)
	{		
		nss=0;
		sendbyte(0xff);			   	//�����Ļ��ʾ
		sendbyte(lietab[i]);       	//������ɨ�� ��lietab[]��ȡֵ
		sendbyte(tab[2*i+1+offsetb]);//���·��tab[]�й�
		sendbyte(tab[2*i+offsetb]);	//���·��tab[]�й�
		nss=1;						//595���벢�� 4��ֵ��������,��һ����ʾ,
		delayms(3);					//��Ȼ��һ����ʾһ������˸
	}
	for(i=8;i<16;i++)
	{
		nss=0;
		sendbyte(lietab[i-8]);	   	//������ɨ�� ��lietab[]��ȡֵ
		sendbyte(0xff);			   	//�Ұ���Ļ��ʾ
		sendbyte(tab[2*i+1+offsetb]);
		sendbyte(tab[2*i+offsetb]);
		nss=1;
		delayms(3);
	} 
}
/************************�жϳ�ʼ��*****************************************/
void init()		//�ж�
{	/*T0��ʼ��*/
	TMOD=0x01; 	//T0�ķ�ʽ0����ʱ��16λ��ʱ��
	TR0=1;		//����T0
	TH0=0x3c;
	TL0=0xb0;
	/*�жϳ�ʼ��*/
    IT0=1;		//�ⲿ�ж�0�½��ش���
	IT1=1;		//�ⲿ�ж�1�½��ش���
	EA=1; 		//�����ж�
	ET0=1;		//��ʱ��0�ж�
	EX0=1;		//�ⲿ�ж�0
	EX1=1;		//�ⲿ�ж�1
}
/*************************��ʱ��0�жϷ���(INT1)�ӳ���*************************************/
void time0() interrupt 1 
{
	TH0=0x3c;
	TL0=0xb0;	//��ʱ����ֵ
	count++;
	if(count>=v)		 //���ƹ������ٶ�
	{
		if(flag==1)		  //���ƿ�ʼ
		{
			count=0;
			offset+=1;
		}		 		//������ƫ����offset
		if(flag==0)		  //������ͣ
		{
			count=0;
			offset+=0;
		}
	}		
}
/*************************����3:ģʽ�л�,�����ⲿ�ж�0�����ӳ���*************************************/
void int0() interrupt 0 
{
  	a=a+1;
	offset=0;
	if(a==6)a=1;
}
void start()	//����1
{
	if(k1==0)
	{
		DelayUs(10);//����
		if(k1==0)
		{
			flag=1;
		}
	}
}
void stop()
{
	if(k2==0)
	{
		DelayUs(10);//����
		if(k2==0)
		{
			flag=0;
		}
	}	
}

/***************************** �������ݸ�595********************************/
void sendbyte(unsigned char dat)
{
	uchar i,temp;	  
	temp=dat;
	for(i=0;i<8;i++)
	{	
	    clk=0;
		if(temp&0x01)
			ser=1;
		else
			ser=0;		
		clk=1;
		temp>>=1;
	}	
}
void delayms(unsigned char t)  //��ʱtms
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
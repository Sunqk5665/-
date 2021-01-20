 /********************************************************
**���ƣ�ADC0831ģ��ת��ʵ��
**���ܣ�0831�ɼ���ѹ����������Ͼ�ȷ����ʾ
**ʱ�䣺2017.3.15
*********************************************************/
#include<reg52.h>
#include<intrins.h>

/***********ad0832�뵥Ƭ���Ľӿڶ���**********************/
sbit CS =P1^0;		 
sbit CLK=P1^1;
sbit OUT=P1^2;	 

unsigned int key;
unsigned char code tab[]={	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
unsigned char temdat[]={0,0,0};  //��-��

unsigned char adc0832(void);
void display(unsigned char *pl);
void delayms(unsigned char t);
void main(void)
{
	unsigned int i,tep;
	while(1)
	{
			tep=1.96*adc0832();
			key=key+tep;
			i++;
			if(i==30)			//ƽ��ֵ�ǲ�,ȥ����ÿ�β���ֵ��ͬ������
			{
				key=key/30;
				temdat[2]=key/100;
				temdat[1]=key/10%10;
				temdat[0]=key%10;	
			//	display(temdat);  
				i=0;
				key=0;
			}
			display(temdat);
	}
}
/*********************************************
**����������AD��������
**д���������
**���ز�������ѹ0-5V��Ӧ��8λ����������0��255
************************************************/
unsigned char adc0832(void)
{
	unsigned char i,l_key;
	OUT=1;
	CS=0;
	_nop_();_nop_();
	CLK=0;
	_nop_();_nop_();
	CLK=1;
	_nop_();_nop_();
	CLK=0;
	_nop_();_nop_();
	CLK=1;
	_nop_();_nop_();
	CLK=0;
	_nop_();_nop_();  //ad0831��ͬ����ģ��ת����������ʱ��д����
	for(i=0;i<8;i++)
	{
		l_key<<=1;
		if(OUT)
			l_key++;
		CLK=1;
		_nop_();_nop_();
		CLK=0;
		_nop_();_nop_(); //����ʱ���½��Ӻ�������һ�����ݣ���һ��ͬ������ͨ��Э��
	}
	CS=1;
	return l_key;
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
 /********************************************************
**名称：ADC0831模数转换实验
**功能：0831采集电压并在数码管上精确的显示
**时间：2017.3.15
*********************************************************/
#include<reg52.h>
#include<intrins.h>

/***********ad0832与单片机的接口定义**********************/
sbit CS =P1^0;		 
sbit CLK=P1^1;
sbit OUT=P1^2;	 

unsigned int key;
unsigned char code tab[]={	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
unsigned char temdat[]={0,0,0};  //低-高

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
			if(i==30)			//平均值虑波,去除因每次采样值不同而跳动
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
**函数描述：AD采样函数
**写入参数：无
**返回参数：电压0-5V对应的8位二进制数即0—255
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
	_nop_();_nop_();  //ad0831是同步型模数转换器，根据时序写代码
	for(i=0;i<8;i++)
	{
		l_key<<=1;
		if(OUT)
			l_key++;
		CLK=1;
		_nop_();_nop_();
		CLK=0;
		_nop_();_nop_(); //两个时钟下降延后就输出第一个数据，是一个同步串行通信协议
	}
	CS=1;
	return l_key;
}
/********************************************************
**名称：显示子函数       
**功能：动态扫描P2口做为位选，P0口送段码
**输入：pl指向要显示数据的地址，最后3位
**返回：无
*******************************************************/
void display(unsigned char *pl)
{
	P2=0x04;
	P0=tab[*pl]; 		    //低
	delayms(3);
	P0=0xff;
	
	P2=0x02;
	P0=tab[*(pl+1)]; 	   	//中
	delayms(3);
	P0=0xff;
	
	P2=0x01;
	P0=tab[*(pl+2)]&0x7f;   //高	//高位数码管总是带小数，因为电压的范围：0—5V
	delayms(3);
	P0=0xff;		 
}

void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
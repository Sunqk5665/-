/***************************************************************************
**实验名称: 16X16点阵滚动显示
**实验效果: "浙江求是科教设备有限公司"在16X16的点阵上有右至左移动.
**时间: 2017.3.13
**公    司: 浙江求实科教设备有限公司
***************************************************************************/
/*****************************头文件声明**************************************/
#include<reg52.h>
#include<intrins.h>
#include<pxh.h>
/*****************************IO引脚定义*************************************/
sbit ser=P1^0;
sbit nss=P1^1;
sbit clk=P1^2;
/******************************数据定义*************************************/
unsigned char count;
unsigned int offset;

unsigned char lietab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
/*************************函数声明********************************************/
void sendbyte(unsigned char dat);
void delayms(unsigned char t);
void init();

/***********************主函数开始********************************************/
void main()
{
	unsigned char i;
	init();
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			nss=0;
			sendbyte(0xff);			   	//左半屏幕显示
			sendbyte(lietab[i]);       	//采用列扫描 在lietab[]中取值
			sendbyte(tab[2*i+1+offset]);//与电路和tab[]有关
			sendbyte(tab[2*i+offset]);	//与电路和tab[]有关
			nss=1;						//595串入并出 4个值都送完了,才一起显示,
			delayms(3);					//不然送一个显示一个会闪烁
		}
		for(i=8;i<16;i++)
		{
			nss=0;
			sendbyte(lietab[i-8]);	   	//采用列扫描 在lietab[]中取值
			sendbyte(0xff);			   	//右半屏幕显示
			sendbyte(tab[2*i+1+offset]);
			sendbyte(tab[2*i+offset]);
			nss=1;
			delayms(3);
		} 
	 }
}
/*************************定时器T0初始化*****************************************/
void init()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TH0=0x3c;
	TL0=0xb0;
	TR0=1;
}
/*************************定时器中断服务子程序*************************************/
void time0() interrupt 1 
{
	TH0=0x3c;
	TL0=0xb0;
	count++;
	if(count==2)		 //控制滚动的速度
	{
		count=0;
		offset+=2;		 //滚动的偏移量offset
		if(offset==4900)
			offset=0;	 //循环鼓动
	}		
}
/***************************** 发送数据给595********************************/
void sendbyte(unsigned char dat)
{
	unsigned char i,temp;	   //串转并的一般方法
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
void delayms(unsigned char t)  //延时tms
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
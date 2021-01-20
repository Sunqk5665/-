/*************************************************
**名称：串行数转换并行数实验
**功能：串行输入并行输出，就是用串口扩展8个IO口
**时间：2017.3.13
*************************************************/
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char 

sbit CLE=P1^0; 	      //164的清零位

void delayms(uchar t);
void main(void)
{
	uchar temp;
	temp=0x01;
	ES=0;		      //串口工作在方式0，扩展并行IO口，不需要进入中断
	SCON=0x00;	      //设置串行口控制寄存器
	while(1)
	{
		CLE=1;
		SBUF=temp;
		while(!TI);	  //发送完8位数据中断标志位置1，由软件清0
		TI=0;
		delayms(250);
		delayms(250);
		temp=_cror_(temp,1);
	}
}

void delayms(uchar t)
{
	uchar x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}


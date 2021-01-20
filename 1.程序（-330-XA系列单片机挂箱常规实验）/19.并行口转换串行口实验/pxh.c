/*************************************************
**名称：并行口转换串行口实验
**功能：利用165并行输入,串口输出
**时间：2017.3.14
*************************************************/
#include<reg52.h>

sbit sh=P1^0;
void init();
void delayms(unsigned char t);
void main()
{
	init();
	while(1)
	{
		sh=0;	 //置数(load)， 读入并行输入口的8 位数据
		sh=1;	 //移位(shift)，并口输入被封锁，串行转换开始
		while(!RI);
		RI=0;
		P2=SBUF;
		delayms(0);
	}
}

void init()
{
	SCON=0x10; //设串口方式0,允许接受
	ES=0;	   //不进入中断
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
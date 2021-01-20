/*************************************************
**名称：并行口转换串行口实验(IO口模拟)
**时间：2017.3.14
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
	pl=0;		 //置入并行数据
	_nop_();
	pl=1;		//启动串行移位，准备好
	clk=0;
	for(i=0;i<8;i++)
	{
		ACC=ACC>>1;
		clk=0;
		if(dat==1)
		ACC=ACC|0X80;
		clk=1;	 		//上升沿脉冲
		buf=ACC;  //将串行移出的8位数据存在DATA_data中
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
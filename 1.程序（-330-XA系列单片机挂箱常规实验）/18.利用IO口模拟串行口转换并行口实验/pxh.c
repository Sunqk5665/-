/*************************************************
**名称：串行数转换并行数实验(模拟串口)
**功能：用普通3个IO口和164扩展8位的IO口
**时间：2017.3.14
*************************************************/
#include<reg52.h>
#include<intrins.h>

/*IO口与164之间接口定义*/
sbit dat=P1^1;
sbit clk=P1^2;
sbit clr=P1^0;
 
void sendbyte(unsigned char byte);
void delayms(unsigned int t);
void main(void)
{
	unsigned char y;
	clr=1;
	y=0x80;
	while(1)
	{
		sendbyte(y);
		y=_cror_(y,1);
		delayms(500);
	}
		
}

void sendbyte(unsigned char byte)
{
	unsigned char i,temp;
	temp=byte;
	for(i=0;i<8;i++)
	{
		clk=0;
		temp>>=1;  /*模拟串口最低位先输出*/
		if(CY)
			dat=1;
		else
			dat=0;
		_nop_();
		_nop_();
		_nop_();
		clk=1;
	}
}

void delayms(unsigned int t)
{
	unsigned char y;
	unsigned int x;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
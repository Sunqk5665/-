/********************************
**名称：动态扫描显示实验
**功能：在共阳数码管上动态显示“01234567”
**时间：2017.3.10
*********************************/
#include<reg52.h>
#include<intrins.h>	//内部函数  头文件
					//将第一个参数循环左（右）移n（第二个参数）位
unsigned char code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff};
							  //共阳数码管段码0-9，a-f，灰
unsigned char dat[]={0,1,2,3,4,5,6,7};//需要显示的数据
void display(unsigned char *pl,tem);
void delayms(unsigned char t);
void main(void)
{
	while(1)
	{
		display(dat,8);
	}
}

/********************************************************
**名称：显示子函数       
**功能：动态扫描P2口做为位选，P0口送段码
**输入：pl指向要显示数据的地址，tem要显示的位数
**返回：无
*******************************************************/
void display(unsigned char *pl,tem)
{
	unsigned char i,dt;
	P2=0x01;
	dt=0x01;
	for(i=0;i<tem;i++)
	{
		P0=tab[*(pl+i)];
		delayms(10);	//延时太长，会出现闪烁
		dt=_crol_ (dt,1);
		P2=dt;
		P0=0xff;		
	}			 
}
void delayms(unsigned char t)
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

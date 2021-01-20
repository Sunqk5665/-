/*************************************************
**名称：LCD显示实验
**功能：在液晶显示模块上显示zhejiang Qiu Shi,jiaoxueyiqi.
**时间：2017.3.13
*************************************************/
#include<reg52.h>
#define uchar unsigned char
sbit lcdEN=P1^0;  //使能信号
sbit lcdRW=P1^1;  //读、写选择
sbit lcdRS=P1^2;  //数据、命令选择
uchar code tab[]="Zhejiang Qiu Shi";
uchar code tabl[]="Jiao Xue Yi Qi";
void delayms(uchar t);
void write_dat(uchar dat);
void write_com(uchar com);
void init(void);
void main(void)
{
	uchar i;
	init();
	for(i=0;i<16;i++)
		write_dat(tab[i]);
	write_com(0x80+0x40);
	for(i=0;i<14;i++)
		write_dat(tabl[i]);
	while(1);
}
/*************************************************
**名    称：初始化子函数
**入口参数：无
**返 回 值：无
*************************************************/
void init(void)
{
	lcdRW=0;               //一直是写命令、写数据
	write_com(0x38);	   //显示模式设置
	delayms(5);			   
	write_com(0x0c);	   //显示开关、光标的设置
	delayms(5);
	write_com(0x06);	   //地址指针设置
	delayms(5); 
	write_com(0x01);	   //显示清屏
}
/*************************************************
**名    称：写命令子函数
**入口参数：状态字    （相关时序）
**返 回 值：无
*************************************************/
void write_com(uchar com)
{
	lcdEN=0;
	lcdRS=1;
	delayms(10);
	lcdRS=0;
	P0=com;
	delayms(5);
	lcdEN=1;
	delayms(5);
	lcdEN=0;
}
/*************************************************
**名    称：写数据子函数
**入口参数：显示的字符    （相关时序）
**返 回 值：无
*************************************************/
void write_dat(uchar dat)
{
	lcdEN=0;
	lcdRS=0;
	delayms(10);
	lcdRS=1;
	P0=dat;
	delayms(5);
	lcdEN=1;
	delayms(5);
	lcdEN=0;
}
void delayms(uchar t)
{
	uchar x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
/********************************
**名称：数据存储器扩展实验
**功能：通过片外RAM来进行流水灯现象
**时间：2017.3.10
*********************************/
#include <reg52.h>
unsigned char xdata tab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
void delay(unsigned char t);
void main(void)
{
	unsigned char xdata i;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P1=tab[i];
			delay(250);
		}	
	}
}

void delay(unsigned char t)
{
	unsigned char xdata i,j;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);
}
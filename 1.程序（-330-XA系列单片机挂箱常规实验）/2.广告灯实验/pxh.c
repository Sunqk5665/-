/********************************
**名称：广告灯实验
**功能：LED左移动,然后右移动  循环下去
**时间：2017.3.8
*********************************/
#include <reg52.h>

unsigned char tab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x81,0x42,0x24,0x18};

void delay(unsigned char t);

void main(void)
{
	unsigned char i;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P1=tab[i];
			delay(1000);
			delay(1000);
		
		}
		for(i=0;i<8;i++)
		{
			P1=tab[7-i];
			delay(1000);
			delay(1000);
			
		}					  
		for(i=8;i<12;i++)
		{
			P1=tab[i];
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			
		}
			for(i=11;i>7;i--)
		{
			P1=tab[i];
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
			delay(1000);
		}					  
	} 

}

void delay(unsigned int t)
{
	unsigned char j;
	unsigned int i;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);		
}
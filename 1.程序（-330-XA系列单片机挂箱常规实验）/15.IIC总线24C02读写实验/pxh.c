/********************************
**名称：IIC 总线24C01读写实验
**功能：把流水灯的8个数据存储到24C01中
**时间：2017.3.13
*********************************/
#include<reg52.h>

#define uchar unsigned char

sbit SCL=P1^4;
sbit SDA=P1^5;

uchar code tab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void init(void);
void start(void);
void stop(void);
void respons(void);
void writebyte(uchar date);
uchar readbyte(void);
void writeadd(uchar address,uchar info);
uchar readadd(uchar address);
void delay(void);
void delayms(uchar);

void main(void)
{
	uchar i;
	init();
	for(i=0;i<8;i++)
	{
		writeadd(i+1,tab[i]);
		delayms(100);
	}
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			P0=readadd(i+1);
			delayms(250);  delayms(250); delayms(250);
		}
	}  	

}

void init(void)
{
	SDA=1;	   //总线初始化，此时任何从器件都不占用总线
	delay();
	SCL=1;
	delay();	
}
void start(void)
{
	SDA=1;
	delay();
	SCL=1;
	delay();
	SDA=0;
	delay();
}
void stop(void)
{
	SDA=0;
	delay();
	SCL=1;
	delay();
	SDA=1;
	delay();
}
void respons(void)
{
	uchar i;
	SCL=1;
	delay();
	while((SDA==1)&&(i<250)) i++;	
	SCL=0;
	delay();
}
void writebyte(uchar date) //	写一个字节
{
	uchar i,temp;
	temp=date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		SCL=0;
		delay();
		SDA=CY;
		delay();
		SCL=1;
		delay();
	}
	SCL=0;
	delay();
	SDA=1;    //释放总线 ，以便respons应答
	delay();
}
uchar readbyte(void)
{
	uchar i,result;
	SCL=0;
	delay();
	SDA=1;
	delay();
	for(i=0;i<8;i++)
	{
		SCL=1;
		delay();
		result=(result<<1)|SDA;
		SCL=0;
		delay();			
	}
	return result;
}
void writeadd(uchar address,uchar info)
{
	start();
	writebyte(0xa0);
	respons();
	writebyte(address);
	respons();
	writebyte(info);
	respons();
	stop();
}
uchar readadd(uchar address)
{
	uchar date;
	start();
	writebyte(0xa0);
	respons();
	writebyte(address);
	respons();
	start();
	writebyte(0xa1);
	respons();
	date=readbyte();
	stop();
	return date;
		
}
void delay(void)
{
	;;
}
void delayms(uchar t)
{
	uchar i,j;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);
}
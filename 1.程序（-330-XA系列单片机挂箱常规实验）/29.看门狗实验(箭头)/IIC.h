#ifndef __IIC_H__
#define __IIC_H__
#define uchar unsigned char
sbit SCL=P1^4;
sbit SDA=P1^5;

void delay(void)
{ 

//	unsigned char j;
//	unsigned int i;
//	for(i=300;i>0;i--)
//		for(j=110;j>0;j--);	

	
}
void init_IIC(void)
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

#endif
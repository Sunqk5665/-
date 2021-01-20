/***************************************************************************
**实验名称: 16X16点阵显示汉字
**实验效果: 循环显示"山东科技大学"六个汉字，显示时共有5中切换方式，分别为：轮流、左移、右移、下移和上移
**实验作者：Sunqker
**时间: 2021/01/07
***************************************************************************/
/*****************************头文件声明**************************************/
#include<reg52.h>
#include<intrins.h>
#include<pxh.h>
#define uchar unsigned char
#define uint unsigned int
/*****************************IO引脚定义*************************************/
sbit ser=P1^0;//595串行输入端(DS)
sbit nss=P1^1;
sbit clk=P1^2;
sbit k1 =P2^0;  //k1播放按键
sbit k2 =P2^1;  //k2暂停按键
sbit k3 =P3^2;  //k3模式切换按键
/******************************数据定义*************************************/
uchar count;
int flag=1;
uint offset=0;
uint offsetb; 	//控制不同子函数的偏移量
uint v=2;		//控制速度
uint a=1;		//模式选择标志位
uchar lietab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//列扫描
uchar lietab2[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//行扫描

/*************************函数声明********************************************/
void sendbyte(uchar dat);
void delayms(uchar t);
void DelayUs(uint M);
void init();
void display1();//左移显示
void display2();//右移显示
void display3();//上移显示
void display4();//下移显示
void display5();//循环显示
void stop();  	//停止函数
void start();	//播放函数	  
/***********************************/
void DelayUs(uint M)  //毫秒延时函数，延时(M) ms
{
    uint i;
	uint j;
	for(i=0;i<M;i++)
	{
		for(j=0;j<200;j++);
		for(j=0;j<102;j++);
	}
}
/***********************主函数开始********************************************/
void main()
{
	init();    	//所用中断初始化 
	while(1)    //主循环
	{
		stop();
		start();
		if(a==1)	 //模式1
		{
			display1();
		}
    	else if(a==2)  //模式2
		{
		 	display2();
		}
		else if(a==3)  //模式3
		{ 
		    display3();
		}
		else if(a==4)  //模式4
		{ 
		    display4();
		}
		else if(a==5)  //模式5
		{ 
		    display5();
		}
	}
}
/*************************模式1：左移显示*****************************************/
void display1()
{
	uchar i;
	v=2;
	offsetb=2*offset;
	if(offsetb>=224)
		offset=0;	 //循环滚动
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(0xff);			   	 //左半屏幕显示
		sendbyte(lietab[i]);       	 //采用列扫描 在lietab[]中取值
		sendbyte(tab[2*i+1+offsetb]);//与电路和tab[]有关
		sendbyte(tab[2*i+offsetb]);	 //与电路和tab[]有关
		nss=1;						 //595串入并出 4个值都送完了,才一起显示,不然送一个显示一个会闪烁
		delayms(3);					 //
	}
	for(i=8;i<16;i++)
	{
		nss=0;
		sendbyte(lietab[i-8]);	   	//采用列扫描 在lietab[]中取值
		sendbyte(0xff);			   	//右半屏幕显示
		sendbyte(tab[2*i+1+offsetb]);
		sendbyte(tab[2*i+offsetb]);
		nss=1;
		delayms(3);
	} 
}
 /************************模式2：右移显示*****************************************/
 void display2()
{
	uchar i;
	v=2;
	offsetb=2*offset;					//每次偏移一列
	if(offsetb>=224)					
		    offset=0;
	for(i=0;i<8;i++)
		{
			nss=0;
			sendbyte(0xff);			   	//左半屏幕显示
			sendbyte(lietab[i]);       	//采用列扫描 在lietab[]中取值
			sendbyte(tab[2*i+1+224-offsetb]);//与电路和tab[]有关
			sendbyte(tab[2*i+224-offsetb]);	//与电路和tab[]有关
			nss=1;						//595串入并出 4个值都送完了,才一起显示,
			delayms(3);					//不然送一个显示一个会闪烁
		}
		for(i=8;i<16;i++)
		{
			nss=0;
			sendbyte(lietab[i-8]);	   	//采用列扫描 在lietab[]中取值
			sendbyte(0xff);			   	//右半屏幕显示
			sendbyte(tab[2*i+1+224-offsetb]);
			sendbyte(tab[2*i+224-offsetb]);
			nss=1;
			delayms(3);
		} 		
}

/*************************模式3：上移显示****************************************/
 void display3()
{
	uchar i;
	v=2;
	offsetb=2*offset;					//每次偏移一行
	 if(offsetb>=224)
		offset=0;
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(tab2[2*i+1+offsetb]);
		sendbyte(tab2[2*i+offsetb]);
		sendbyte(0x00);			   	//上半屏幕显示
		sendbyte(lietab2[i]);       //采用行扫描 在lietab2[]中取值
		nss=1;						//595串入并出 4个值都送完了,才一起显示,
		delayms(3);					//不然送一个显示一个会闪烁
	}
	for(i=8;i<16;i++)
	{
		nss=0;	
		sendbyte(tab2[2*i+1+offsetb]);
		sendbyte(tab2[2*i+offsetb]); 
		sendbyte(lietab2[i-8]);	   	//采用行扫描 在lietab2[]中取值
		sendbyte(0x00);			   	//下半屏幕显示
		nss=1;
		delayms(3);
	} 
} 
/*************************模式4：下移显示******************************************/
 void display4()
{								  
	uchar i;
	v=2;
	offsetb=2*offset;					//每次偏移一行
	if(offsetb>=224)
		offset=0; 
	for(i=0;i<8;i++)
	{
		nss=0;
		sendbyte(tab2[2*i+1+224-offsetb]);//与电路和tab[]有关
		sendbyte(tab2[2*i+224-offsetb]);	//与电路和tab[]有关
		sendbyte(0x00);			   	//上半屏幕显示
		sendbyte(lietab2[i]);       	//采用行扫描 在lietab2[]中取值
		nss=1;						//595串入并出 4个值都送完了,才一起显示,
		delayms(3);					//不然送一个显示一个会闪烁
	}
	for(i=8;i<16;i++)
	{
		nss=0;	
		sendbyte(tab2[2*i+1+224-offsetb]);
		sendbyte(tab2[2*i+224-offsetb]); 
		sendbyte(lietab2[i-8]);	   	//采用行扫描 在lietab2[]中取值
		sendbyte(0x00);			   	//下半屏幕显示
		nss=1;
		delayms(3);
	} 
} 
/*************************模式5：循环显示*****************************************/
void display5()
{
	uchar i;
	v=20;
	offsetb=32*offset+32;				//整体偏移16列即一个屏幕的距离达成循环显示
	if(offsetb>=224)
		offset=0;
	for(i=0;i<8;i++)
	{		
		nss=0;
		sendbyte(0xff);			   	//左半屏幕显示
		sendbyte(lietab[i]);       	//采用列扫描 在lietab[]中取值
		sendbyte(tab[2*i+1+offsetb]);//与电路和tab[]有关
		sendbyte(tab[2*i+offsetb]);	//与电路和tab[]有关
		nss=1;						//595串入并出 4个值都送完了,才一起显示,
		delayms(3);					//不然送一个显示一个会闪烁
	}
	for(i=8;i<16;i++)
	{
		nss=0;
		sendbyte(lietab[i-8]);	   	//采用列扫描 在lietab[]中取值
		sendbyte(0xff);			   	//右半屏幕显示
		sendbyte(tab[2*i+1+offsetb]);
		sendbyte(tab[2*i+offsetb]);
		nss=1;
		delayms(3);
	} 
}
/************************中断初始化*****************************************/
void init()		//中断
{	/*T0初始化*/
	TMOD=0x01; 	//T0的方式0，定时器16位定时器
	TR0=1;		//启动T0
	TH0=0x3c;
	TL0=0xb0;
	/*中断初始化*/
    IT0=1;		//外部中断0下降沿触发
	IT1=1;		//外部中断1下降沿触发
	EA=1; 		//开总中断
	ET0=1;		//定时器0中断
	EX0=1;		//外部中断0
	EX1=1;		//外部中断1
}
/*************************定时器0中断服务(INT1)子程序*************************************/
void time0() interrupt 1 
{
	TH0=0x3c;
	TL0=0xb0;	//定时器初值
	count++;
	if(count>=v)		 //控制滚动的速度
	{
		if(flag==1)		  //控制开始
		{
			count=0;
			offset+=1;
		}		 		//滚动的偏移量offset
		if(flag==0)		  //控制暂停
		{
			count=0;
			offset+=0;
		}
	}		
}
/*************************按键3:模式切换,采用外部中断0服务子程序*************************************/
void int0() interrupt 0 
{
  	a=a+1;
	offset=0;
	if(a==6)a=1;
}
void start()	//按键1
{
	if(k1==0)
	{
		DelayUs(10);//防抖
		if(k1==0)
		{
			flag=1;
		}
	}
}
void stop()
{
	if(k2==0)
	{
		DelayUs(10);//消抖
		if(k2==0)
		{
			flag=0;
		}
	}	
}

/***************************** 发送数据给595********************************/
void sendbyte(unsigned char dat)
{
	uchar i,temp;	  
	temp=dat;
	for(i=0;i<8;i++)
	{	
	    clk=0;
		if(temp&0x01)
			ser=1;
		else
			ser=0;		
		clk=1;
		temp>>=1;
	}	
}
void delayms(unsigned char t)  //延时tms
{
	unsigned char x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
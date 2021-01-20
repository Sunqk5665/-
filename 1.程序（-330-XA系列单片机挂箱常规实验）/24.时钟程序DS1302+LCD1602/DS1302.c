/***************************************************************************
标题：	DS1302时钟程序+LCD1602显示
效果：	程序在LCD1602上显示时间信息，万年历
工作于：LY51(AVR)-L3A开发板
作者：	林洋电子吧
网站：	www.lydz8.com
说明：	DS1302和LCD1602两例子结合
******************************************************************************/
#include <reg51.h>
#include <intrins.h>

/********定义宏*************************************************************/
#define LCD_Data P0
#define Busy    0x80

/********IO引脚定义***********************************************************/
sbit SCL2=P1^0;		//SCL2定义为P1口的第3位脚，连接DS1302SCL和ADC0831SCL脚
sbit SDA2=P1^1;		//SDA2定义为P1口的第4位脚，连接DS1302SCL和ADC0831SDA脚
sbit RST = P1^2;   // DS1302片选脚

sbit LCD_RS=P2^2;
sbit LCD_RW=P2^1;
sbit LCD_E=P2^0;

/********数据定义*************************************************************/
unsigned char l_tmpdate[8]={0x00,0x06,0x03,0x07,0x07,0x07,0x0c,0};				//用于读时间信息缓冲，初值为第一次的写入时间
							//秒，分，时，日，月，星期，年
code unsigned char write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; 	//写时间信息地址
code unsigned char read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};	//读时间信息地址
unsigned char l_tmpdisplay[16]={"Data 20        "};					//设好显示的内容，变化的地方，保留
unsigned char l_tmpdisplay2[16]={"time "};

/********函数声明*************************************************************/
void Write_Ds1302_byte(unsigned char temp); 
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void Read_RTC(void);
void Set_RTC(void);

void WriteDataLCD(unsigned char WDLCD);
void WriteCommandLCD(unsigned char WCLCD,unsigned char BuysC);
unsigned char ReadDataLCD(void);
unsigned char ReadStatusLCD(void);
void LCDInit(void);
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char *DData);
void Delay5Ms(void);
void Delay400Ms(void);


/***********主函数开始********************************************************/	
void main(void)
{
	Set_RTC();			//写时间
	Delay400Ms(); 		//启动等待，等LCD讲入工作状态
 	LCDInit(); 			//LCD初始化
	Delay5Ms();
	while(1){
		Read_RTC();		//读时间
			l_tmpdisplay[7]=(l_tmpdate[6]/16)+0X30;			//这里加上0X30是在ASCII字符编码中的地址
															//这里除以16是因为读出的数据是BCD码
			l_tmpdisplay[8]=(l_tmpdate[6]&0x0f)+0X30;
			l_tmpdisplay[9]=0X3A;						
			l_tmpdisplay[10]=(l_tmpdate[4]/16)+0X30;
			l_tmpdisplay[11]=(l_tmpdate[4]&0x0f)+0X30;
			l_tmpdisplay[12]=0X3A;
			l_tmpdisplay[13]=(l_tmpdate[3]/16)+0X30;
			l_tmpdisplay[14]=(l_tmpdate[3]&0x0f)+0X30;	
			DisplayListChar(0, 0, l_tmpdisplay);			//输出液晶显示第一行
		
			l_tmpdisplay2[5]=(l_tmpdate[2]/16)+0X30;
			l_tmpdisplay2[6]=(l_tmpdate[2]&0x0f)+0X30;
			l_tmpdisplay2[7]=0X3A;
			l_tmpdisplay2[8]=(l_tmpdate[1]/16)+0X30;
			l_tmpdisplay2[9]=(l_tmpdate[1]&0x0f)+0X30;
			l_tmpdisplay2[10]=0X3A;
			l_tmpdisplay2[11]=(l_tmpdate[0]/16)+0X30;
			l_tmpdisplay2[12]=(l_tmpdate[0]&0x0f)+0X30;
			DisplayListChar(0, 5, l_tmpdisplay2);			//输出液晶显示第二行
			Delay400Ms();			
	}
}

/************写字节到DS1302*******************************************/
void Write_Ds1302_Byte(unsigned  char temp) 
{
 unsigned char i;
 for (i=0;i<8;i++)     		//写一个字节
  { 
	 SCL2=0;
     SDA2=temp&0x01;     	//获取低位数据，低位在前高位在后
     temp>>=1;  			//右移一位
     SCL2=1;
   }
}   

/************根据地址写数据*************************************************/
void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCL2=0;						//准备
	_nop_();
 	RST=1;						//开始
   	_nop_();
 	Write_Ds1302_Byte(address);	//发送地址
 	Write_Ds1302_Byte(dat);		//发送数据
 	RST=0;  					//恢复
}

/***********根据地址读数据*************************************************/
unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;
	_nop_();
 	SCL2=0;
	_nop_();
 	RST=1;
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 			//读一字节
 	{
		temp>>=1;				//右移一位，低位在前高位在后
		SCL2=0;			  
		_nop_();	
 		if(SDA2)
 			temp|=0x80;			//低位在前高位在后
		SCL2=1;						
	} 
 	RST=0;
	_nop_();
	SDA2=0;
	return (temp);				//返回相应值
}

/**********读秒，分，时，日，月，星期，年*************************************/
void Read_RTC(void)		//读取 日历
{
 unsigned char i,*p;
 p=read_rtc_address; 				//读地址
 for(i=0;i<7;i++)					//分7次读取 年月日时分秒星期
 {
  l_tmpdate[i]=Read_Ds1302(*p);
  p++;
 }
}

/**********写秒，分，时，日，月，星期，年*************************************/
void Set_RTC(void)
{
	unsigned char i,*p,tmp;
	for(i=0;i<7;i++){				//将数据转为BCD码
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}
 	Write_Ds1302(0x8E,0X00);		//打开写允许
	
 	p=write_rtc_address;			//写地址	
 	for(i=0;i<7;i++)				//写入 年月日时分秒星期
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		 p++;  
	 }
	 Write_Ds1302(0x8E,0x80);		//关闭写允许
}

//以下为LCD1602内容
/***********写数据********************************************************/	
void WriteDataLCD(unsigned char WDLCD)
{
 ReadStatusLCD(); //检测忙
 LCD_Data = WDLCD;
 LCD_RS = 1;
 LCD_RW = 0;
 LCD_E = 0; 		//若晶振速度太高可以在这后加小的延时
 LCD_E = 0; 		//延时
 LCD_E = 1;
}

/***********写指令********************************************************/	
void WriteCommandLCD(unsigned char WCLCD,unsigned char BuysC) //BuysC为0时忽略忙检测
{
 if (BuysC) ReadStatusLCD(); //根据需要检测忙
 LCD_Data = WCLCD;
 LCD_RS = 0;
 LCD_RW = 0; 
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1; 
}

/***********读数据********************************************************/	
unsigned char ReadDataLCD(void)
{
 LCD_RS = 1; 
 LCD_RW = 1;
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1;
 return(LCD_Data);
}

/***********读状态*******************************************************/	
unsigned char ReadStatusLCD(void)
{
 LCD_Data = 0xFF; 
 LCD_RS = 0;
 LCD_RW = 1;
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1;
 while (LCD_Data & Busy); //检测忙信号
 return(LCD_Data);
}

/***********初始化********************************************************/	
void LCDInit(void)
{
 LCD_Data = 0;
 WriteCommandLCD(0x38,0); 	//三次模式设置，不检测忙信号
 Delay5Ms(); 
 WriteCommandLCD(0x38,0);
 Delay5Ms(); 
 WriteCommandLCD(0x38,0);
 Delay5Ms(); 

 WriteCommandLCD(0x38,1); 	//显示模式设置,开始要求每次检测忙信号
 WriteCommandLCD(0x08,1); 	//关闭显示
 WriteCommandLCD(0x01,1); 	//显示清屏
 WriteCommandLCD(0x06,1); 	//显示光标移动设置
 WriteCommandLCD(0x0C,1); 	//显示开及光标设置
}

/***********按指定位置显示一个字符*******************************************/	
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
 Y &= 0x1;
 X &= 0xF; 				//限制X不能大于15，Y不能大于1
 if (Y) X |= 0x40; 		//当要显示第二行时地址码+0x40;
 X |= 0x80; 			//算出指令码
 WriteCommandLCD(X, 0); //这里不检测忙信号，发送地址码
 WriteDataLCD(DData);
}

/***********按指定位置显示一串字符*****************************************/	
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char *DData)
{
 unsigned char ListLength;

 ListLength = 0;
 Y &= 0x1;
 X &= 0xF; 				//限制X不能大于15，Y不能大于1
 while (DData[ListLength]>=0x20) //若到达字串尾则退出
  {
   if (X <= 0xF) 		//X坐标应小于0xF
    {
     DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
     ListLength++;
     X++;
    }
  }
}

/***********短延时********************************************************/	
void Delay5Ms(void)
{
 unsigned int TempCyc = 5552;
 while(TempCyc--);
}

/***********长延时********************************************************/	
void Delay400Ms(void)
{
 unsigned char TempCycA = 5;
 unsigned int TempCycB;
 while(TempCycA--)
 {
  TempCycB=7269;
  while(TempCycB--);
 };
}

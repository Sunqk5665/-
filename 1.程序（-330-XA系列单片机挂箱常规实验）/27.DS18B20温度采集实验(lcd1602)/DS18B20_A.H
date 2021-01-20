
#ifndef __DS18B20_A_H__
#define __DS18B20_A_H__

sbit DQ = P1^7; 				//数据接口定义
unsigned char TempBuffer[6];	//温度数据字符
bit  symbol = 0;					//温度数据正负号



/*--------------------------------------------*/
//函数声明
bit Init_DS18B20(void);              //DS18B20初始化函数,如果bit=0则初始化成功,bit=1则初始化失败
unsigned char ReadOneChar(void);     //DS18B20读出一个字节
void WriteOneChar(unsigned char dat);//DS18B20写入一个字节
unsigned char ReadTemp(void);		 //读出DS18B20当前的温度
void Temp_To_String(void);			 //温度数据转化成液晶字符显示//函数返回值为TempBuffer



/*--------------------------------------------*/
//延迟时间函数
void delay(unsigned char x, unsigned char y, unsigned char z)
{
    unsigned char tempx,tempy,tempz=z;
    do{tempy=y;do{tempx=x;while(--tempx);}while(--tempy);}while(--tempz);
}



/*--------------------------------------------*/
//DS18B20初始化函数
bit Init_DS18B20(void)
{
	bit Status=0;
	DQ=1;			//DS18B20复位
	//delay(1,1,1);	//17us
	DQ=0;			//低电平复位
	delay(9,1,19);	//500us		//保持低电平大于480us
	DQ=1;			//释放总线
	delay(2,1,2);	//30us		//延时15us~60us  准备接收数据
	Status=DQ;		//如果Status=0则初始化成功,Status=1则初始化失败
	delay(10,5,1);	//130us		//必要延迟时间
	return (Status);
}



/*--------------------------------------------*/
//DS18B20读出一个字节
unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat=0;
	for(i=8;i>0;i--)
	{
		DQ=0;			//读出数据开始//_nop_();
		dat>>=1;		//由低到高位依次读出
		DQ=1;			//释放总线
		if(DQ)
			dat|=0x80;	//15us内必须完成读数据
		delay(4,5,1);	//70us 	//60us~120us释放总线
	}
	return (dat);
}



/*--------------------------------------------*/
//DS18B20写入一个字节
void WriteOneChar(unsigned char dat)
{	
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		DQ=0;			//写开始
		DQ=dat&0x01;	//由低到高依次写入
		delay(3,5,1);	//60us	//写入数据时间间隙为:至少60us连续写2位间的间隙应大于1us
		DQ=1;			//释放总线	
		dat>>=1;
	}
}



/*--------------------------------------------*/
//读出DS18B20当前的温度
unsigned char ReadTemp(void)
{
	unsigned char TempL=0;
	unsigned char TempH=0;
	unsigned char Temp_Value; 


	Init_DS18B20();			//先复位,再写ROM,最后写RAM
	WriteOneChar(0xcc);		//跳过读出序列号的操作
	WriteOneChar(0x44);		//启动温度转换,默认的【12Bits】转化
	delay(217,94,17);		//700ms	//12Bits转换时间750ms

	Init_DS18B20();			//先复位,再写ROM,最后写RAM
	WriteOneChar(0xcc);		//跳过读出序列号的操作
	WriteOneChar(0xbe);		//读出温度寄存器
	//delay(1,1,1);			//17us	

	TempL=ReadOneChar();	//读出温度值低8位/低四位为小数位
	TempH=ReadOneChar();	//读出温度值高8位/高四位和第四位为符号位
	
	if((TempH>>4)==0x0f)	//1111=负数 0000=正数
		symbol = 1;
	else
		symbol = 0;

	Temp_Value=TempH<<4 | TempL>>4;
	return (Temp_Value);			
}



/*--------------------------------------------*/
//温度数据转化成液晶字符显示
void Temp_To_String(void)
{

	unsigned char  Temp_Value;
	Temp_Value = ReadTemp();
	if(symbol==1)
	{
		Temp_Value = 256 - Temp_Value;
		TempBuffer[0]=Temp_Value/100+'-';	//符号位
	}		
	else
	TempBuffer[0]=Temp_Value/100+'0';	//百位	
	TempBuffer[1]=Temp_Value/10%10+'0';	//十位
	TempBuffer[2]=Temp_Value%10+'0';	//个位
	TempBuffer[3]=0xdf;					//温度符号
	TempBuffer[4]='C';
	TempBuffer[5]='\0';					//字符串结束标志符
}



/*--------------------------------------------*/
#endif 





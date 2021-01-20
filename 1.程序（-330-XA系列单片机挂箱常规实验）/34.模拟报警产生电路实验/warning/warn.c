#include<reg52.H>   //包含51单片机寄存器定义的头文件
sbit S=P3^2;      //将S位定义为P3.2，
sbit cruise=P2^0;      //将cruise位定义为P1.0，接LED状态指示
sbit buzzer=P1^1;      //将buzzer位定义为P1.1，接蜂鸣器状态指示
/*******************************************
函数声明
******************************************/	
void Time_init(void);
void delay5s(void);
int  time_count=0,i=0;
int  buzzer_flag=0;// 标志位
/******************************************
函数功能：主函数
******************************************/	
void main(void)
 {
	 Time_init();
//	 EA=1;                  //开总中断
   EX0=1;  //允许使用外中断
   IT0=1;  //选择负跳变来触发外中断	 
	 while(1)
	 {
   if(buzzer_flag==1)
	 {  
		  delay5s();		  
		  buzzer=1;
	    cruise=1;
	    buzzer_flag=0;
		  TR1=1;
	 }
    } ;            
 }
/**************************************************************
函数功能：外中断T0的中断服务程序
**************************************************************/
void int0(void) interrupt 0 using 0  //外中断0的中断编号为0
{ 
	TR1=0;
  cruise=1;
	buzzer=0;
  buzzer_flag=1;
 }
void Time_init(void)//定时器初始化
{	
  EA=1;                  //开总中断
	ET1=1;                 //定时器T1中断允许         
	TMOD=0x10;             //使用定时器T1的模式1
	TH1=(65536-46083)/256; //定时器T1的高8位赋初值  50ms定时初值
	TL1=(65536-46083)%256; //定时器T1的高8位赋初值
	TR1=1;                 //启动定时器T1
  buzzer=1;              //初始化蜂鸣器
	cruise=1;
}
void Time1(void) interrupt 3 using 0  //实现一秒定时
                 //“interrupt”声明函数为中断服务函数
                 //其后的3为定时器T1的中断编号；0表示使用第0组工作寄存器 
 {
     time_count++;
	 if(time_count>10)
	 {
		 cruise=~cruise;
		 time_count=0;
   }
  	TH1=(65536-46083)/256; //定时器T1的高8位重新赋初值
	  TL1=(65536-46083)%256; //定时器T1的高8位重新赋初值
 }
 
void delay5s(void)   
{
    unsigned char a,b,c;
    for(c=155;c>0;c--)
        for(b=178;b>0;b--)
            for(a=82;a>0;a--);
}

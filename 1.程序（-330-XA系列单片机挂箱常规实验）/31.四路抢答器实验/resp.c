#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

char s;
uchar num=0;
char time=20;         //抢答时间
char datitime=30;        //答题限时时间
uint tt,t1;           //T0,T1定时器定一秒时

bit flag,s_flag=1,b_flag,fall_flag;        //标志位
bit K_startcountflag,K_timecountflag;        //时间调整标志位

sbit K0=P3^6;///
sbit beep=P3^7;         //蜂鸣器输出口
sbit rled=P3^5;  /////              //指示灯输出口

sbit K1=P1^0;               
sbit K2=P1^1;
sbit K3=P1^2;
sbit K4=P1^3;

sbit K_Time=P3^2;              //答题计时键
//sbit K_startcount=P3^3;        //开始抢答时间调整键
//sbit K_timecount=P3^4;         //答题计时时间调整键

void delay(uchar ms)
{
        uchar y;
        for(;ms>0;ms--)
                for(y=120;y>0;y--);
}
uchar code tabledu[]=
{
    0xc0,0xf9,0xa4,0xb0,			
		0x99,0x92,0x82,0xf8,
		0x80,0x90,0x88,0x83,
		0xc6,0xa1,0x86,0x8e,
};
uchar code tablewe[]={0X01,0X02,0X04,0X08};
void T0_Init(void)
{
        TMOD=0X01;
        TH0=(65536-2000)/256;
        TL0=(65536-2000)%256;
        TH1=(65536-2000)/256;
        TL1=(65536-2000)%256;
        ET0=1;
        ET1=1;
        EA=1;
        P0=0;
}
void Key_Scan(void)                //开始键扫描,检测开始键是否按下
{
        if(K0==0)
        {
                delay(10);
                if(K0==0)
                {
                        while(!K0);
                        TR0=1;
                        s=time;
                        tt=0;
                        flag=1;
                        s_flag=1;
                        b_flag=1;
                        num=0;
                        beep=1;
                        rled=1;
                        fall_flag=0;        //清除违规标志位
//                        K_startcountflag=0;
//                        K_timecountflag=0;
                }
        }
}

void Scan(void)                               //四路热键扫描(哪个键先按下,哪个优先级最高)
{
        if(K1==0)
        {
                delay(10);
                if(K1==0)
                {
                        while(!K1);
                        num=1;                //数码管显示1号"1"
                        TR0=0;                //关闭定时器0,时间停止
                        TR1=1;                //打开定时器1,使扬声器响一声
                        s_flag=0;             //关闭开始键标志位,使再按其他三个键不会响应
                }
        }
        if(K2==0)                             //下面三个键的处理同上
        {
                delay(10);
                if(K2==0)
                {
                        while(!K2);
                        num=2;               
                        TR0=0;
                        TR1=1;
                        s_flag=0;             //重要
                }
        }
        if(K3==0)
        {
                delay(10);
                if(K3==0)
                {
                        while(!K3);
                        num=3;
                        TR0=0;
                        TR1=1;
                        s_flag=0;
                }
        }
        if(K4==0)
        {
                delay(10);
                if(K4==0)
                {
                        while(!K4);
                        num=4;
                        TR0=0;
                        TR1=1;
                        s_flag=0;
                }
        }
}
void display(void)
{
        if(flag==1)                //开始键按下,开始计时抢答
        {
                if(num!=0)         //如果有人抢答,则显示相应的几号
                {
                        P0=tabledu[num];        //显示几号抢到了
                        P2=tablewe[0];
                        delay(2);
                        P0=0;
                        P2=0X01;
                }
                else                            //否则没人抢答,则前面不显示几号
                {
                        P0=0;               
                        P2=0X01;
                }
                P0=tabledu[s/10];                //下面为显示抢答倒计时
                P2=tablewe[2];
                delay(2);
                P0=0;
                P2=0X04;
								
                P0=tabledu[s%10];
                P2=tablewe[3];
                delay(2);
								P0=0;
                P2=0X08;
               
								
        }
               
}
//void Time_Scan(void)                //调整时间键扫描
//{
//        if(K_startcount==0)                //抢答时间调整
//        {
//                delay(10);
//                if(K_startcount==0)       
//                {
//                        while(!K_startcount);
//                        time++;                       
//                        if(time==50)
//                        {
//                                time=20;
//                        }
//                        K_startcountflag=1;        //将抢答时间标志位置1
//                        K_timecountflag=0;        //同时关闭答题时间标志位
//                }
//        }
//        if(K_timecount==0)                //答题时间调整
//        {
//                delay(10);
//                if(K_timecount==0)
//                {
//                        while(!K_timecount);
//                        datitime++;
//                        if(datitime==60)
//                        {
//                                datitime=30;
//                        }
//                        K_timecountflag=1;
//                        K_startcountflag=0;
//                }
//        }
//}
void main(void)
{
        T0_Init();
        while(1)
        {
                Key_Scan();                //开始键扫描
//                if((flag==0)&(s_flag==1))        //当开始键没按下及没有人违规时才可进行时间调整
//                {
//                        Time_Scan();
//                }
                if((flag==1)&(s_flag==0))//当开始键按下及有人抢答才进行开始回答计时倒计时
                {
                        if(K_Time==0)
                        {
                                delay(10);
                                if(K_Time==0)
                                {
                                        while(!K_Time);
                                        s=datitime;
                                        TR0=1;
                                        tt=0;
                                        TR1=1;
                                }
                        }
                }       
                if((flag==0)&(s_flag==1))        //违规
                {
                        Scan();
                        if(num!=0)                //开始键没有按下时,有人按下了抢答器,则置违规标志位
                        {
                                fall_flag=1;
                                rled=0;
                        }
                }
                if((flag==1)&(s_flag==1))        //如果开始键按下且抢答键没有人按下,则进行八路抢答键扫描
                {
                        Scan();
                }       
                display();                //显示到数码管上
        }
}
void timer0(void) interrupt 1
{
        TH0=(65536-2000)/256;        //2ms
        TL0=(65536-2000)%256;
        if(b_flag)        //开始(START)键按下,嘟一声(长1秒),表示开始抢答
        {
                beep=~beep;
        }
        else
        beep=1;
        if(s<5)        //抢答时间快到报警,隔1秒响一声且红灯闪烁,响三声
        {
                if(s%2==0)
                {
                        b_flag=1;
                        rled=0;       
                }
                else
                {
                        b_flag=0;
                        rled=1;
                }
        }
        tt++;       
        if(tt==500)                //1秒
        {
                tt=0;
                s--;
                b_flag=0;        //关闭开始键按下响一秒的嘟声
                if(s==-1)
                {
                        s=20;       
                        TR0=0;
                        flag=0;        //显示F FF
                        s_flag=1;
                        num=0;
                        rled=1;
                }
        }
}
void timer1(void) interrupt 3        //定时器1处理有人按下抢答器嘟一声(长1秒)
{
        TH1=(65536-2000)/256;
        TL1=(65536-2000)%256;
        beep=~beep;
        t1++;
        if(t1==500)
        {
                t1=0;
                TR1=0;
        }
}
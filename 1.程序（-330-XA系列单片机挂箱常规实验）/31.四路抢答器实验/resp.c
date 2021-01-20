#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

char s;
uchar num=0;
char time=20;         //����ʱ��
char datitime=30;        //������ʱʱ��
uint tt,t1;           //T0,T1��ʱ����һ��ʱ

bit flag,s_flag=1,b_flag,fall_flag;        //��־λ
bit K_startcountflag,K_timecountflag;        //ʱ�������־λ

sbit K0=P3^6;///
sbit beep=P3^7;         //�����������
sbit rled=P3^5;  /////              //ָʾ�������

sbit K1=P1^0;               
sbit K2=P1^1;
sbit K3=P1^2;
sbit K4=P1^3;

sbit K_Time=P3^2;              //�����ʱ��
//sbit K_startcount=P3^3;        //��ʼ����ʱ�������
//sbit K_timecount=P3^4;         //�����ʱʱ�������

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
void Key_Scan(void)                //��ʼ��ɨ��,��⿪ʼ���Ƿ���
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
                        fall_flag=0;        //���Υ���־λ
//                        K_startcountflag=0;
//                        K_timecountflag=0;
                }
        }
}

void Scan(void)                               //��·�ȼ�ɨ��(�ĸ����Ȱ���,�ĸ����ȼ����)
{
        if(K1==0)
        {
                delay(10);
                if(K1==0)
                {
                        while(!K1);
                        num=1;                //�������ʾ1��"1"
                        TR0=0;                //�رն�ʱ��0,ʱ��ֹͣ
                        TR1=1;                //�򿪶�ʱ��1,ʹ��������һ��
                        s_flag=0;             //�رտ�ʼ����־λ,ʹ�ٰ�����������������Ӧ
                }
        }
        if(K2==0)                             //�����������Ĵ���ͬ��
        {
                delay(10);
                if(K2==0)
                {
                        while(!K2);
                        num=2;               
                        TR0=0;
                        TR1=1;
                        s_flag=0;             //��Ҫ
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
        if(flag==1)                //��ʼ������,��ʼ��ʱ����
        {
                if(num!=0)         //�����������,����ʾ��Ӧ�ļ���
                {
                        P0=tabledu[num];        //��ʾ����������
                        P2=tablewe[0];
                        delay(2);
                        P0=0;
                        P2=0X01;
                }
                else                            //����û������,��ǰ�治��ʾ����
                {
                        P0=0;               
                        P2=0X01;
                }
                P0=tabledu[s/10];                //����Ϊ��ʾ���𵹼�ʱ
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
//void Time_Scan(void)                //����ʱ���ɨ��
//{
//        if(K_startcount==0)                //����ʱ�����
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
//                        K_startcountflag=1;        //������ʱ���־λ��1
//                        K_timecountflag=0;        //ͬʱ�رմ���ʱ���־λ
//                }
//        }
//        if(K_timecount==0)                //����ʱ�����
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
                Key_Scan();                //��ʼ��ɨ��
//                if((flag==0)&(s_flag==1))        //����ʼ��û���¼�û����Υ��ʱ�ſɽ���ʱ�����
//                {
//                        Time_Scan();
//                }
                if((flag==1)&(s_flag==0))//����ʼ�����¼���������Ž��п�ʼ�ش��ʱ����ʱ
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
                if((flag==0)&(s_flag==1))        //Υ��
                {
                        Scan();
                        if(num!=0)                //��ʼ��û�а���ʱ,���˰�����������,����Υ���־λ
                        {
                                fall_flag=1;
                                rled=0;
                        }
                }
                if((flag==1)&(s_flag==1))        //�����ʼ�������������û���˰���,����а�·�����ɨ��
                {
                        Scan();
                }       
                display();                //��ʾ���������
        }
}
void timer0(void) interrupt 1
{
        TH0=(65536-2000)/256;        //2ms
        TL0=(65536-2000)%256;
        if(b_flag)        //��ʼ(START)������,�һ��(��1��),��ʾ��ʼ����
        {
                beep=~beep;
        }
        else
        beep=1;
        if(s<5)        //����ʱ��쵽����,��1����һ���Һ����˸,������
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
        if(tt==500)                //1��
        {
                tt=0;
                s--;
                b_flag=0;        //�رտ�ʼ��������һ������
                if(s==-1)
                {
                        s=20;       
                        TR0=0;
                        flag=0;        //��ʾF FF
                        s_flag=1;
                        num=0;
                        rled=1;
                }
        }
}
void timer1(void) interrupt 3        //��ʱ��1�������˰����������һ��(��1��)
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
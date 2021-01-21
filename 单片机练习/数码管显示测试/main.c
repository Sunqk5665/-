#include<reg52.h>
char code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
delay(unsigned int i){while(i--);}
int main()
{ 	
	int i;
	P2=0x5<<5;	   //010100000
	P0=0x80;
	while(1)
	{
		for(i=0;i<8;i++)
		{
		//P2=0x4<<5;
		//P0=~(0x01<<i);
		//delay(20000);
			P2=0x7<<5;P0=~smgduan[i];	//第一步，共阳极，送段码
			P2=0x6<<5;P0=0x01<<i;		//第二步，送位码，1、2、4、8、16、32、64、128，分别为1-8位
			delay(300);					//第三步，延时，必须大于20ms让我们看到断续
			P2=0x7<<5;P0=00;			//第四步，清除段码，消去重影
		}
	}
}
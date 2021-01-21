#include<reg52.h>
delay(unsigned int i)
{
	while(i--);
}
int  main()
{
	int i;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P0=~(0x01<<i);
			delay(30000);
		}
	}
	return 0;
}
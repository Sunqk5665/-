/*-----------------------------------------*/
#include<REG52.H>
#include"LCD1602_8.H"
#include"DS18B20_A.H"




/*-----------------------------------------*/
void main(void)
{
	lcd_init();
	lcd_pos(0,0);
	prints("DS18B20-ZJQS");
	lcd_pos(0,1);
	prints("T:");
	while(1)
	{	
		Temp_To_String();
		lcd_pos(7,1);
		prints(TempBuffer);	
		delay(244,7,29);
	}
}

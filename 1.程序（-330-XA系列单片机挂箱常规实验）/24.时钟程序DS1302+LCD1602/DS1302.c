/***************************************************************************
���⣺	DS1302ʱ�ӳ���+LCD1602��ʾ
Ч����	������LCD1602����ʾʱ����Ϣ��������
�����ڣ�LY51(AVR)-L3A������
���ߣ�	������Ӱ�
��վ��	www.lydz8.com
˵����	DS1302��LCD1602�����ӽ��
******************************************************************************/
#include <reg51.h>
#include <intrins.h>

/********�����*************************************************************/
#define LCD_Data P0
#define Busy    0x80

/********IO���Ŷ���***********************************************************/
sbit SCL2=P1^0;		//SCL2����ΪP1�ڵĵ�3λ�ţ�����DS1302SCL��ADC0831SCL��
sbit SDA2=P1^1;		//SDA2����ΪP1�ڵĵ�4λ�ţ�����DS1302SCL��ADC0831SDA��
sbit RST = P1^2;   // DS1302Ƭѡ��

sbit LCD_RS=P2^2;
sbit LCD_RW=P2^1;
sbit LCD_E=P2^0;

/********���ݶ���*************************************************************/
unsigned char l_tmpdate[8]={0x00,0x06,0x03,0x07,0x07,0x07,0x0c,0};				//���ڶ�ʱ����Ϣ���壬��ֵΪ��һ�ε�д��ʱ��
							//�룬�֣�ʱ���գ��£����ڣ���
code unsigned char write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; 	//дʱ����Ϣ��ַ
code unsigned char read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};	//��ʱ����Ϣ��ַ
unsigned char l_tmpdisplay[16]={"Data 20        "};					//�����ʾ�����ݣ��仯�ĵط�������
unsigned char l_tmpdisplay2[16]={"time "};

/********��������*************************************************************/
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


/***********��������ʼ********************************************************/	
void main(void)
{
	Set_RTC();			//дʱ��
	Delay400Ms(); 		//�����ȴ�����LCD���빤��״̬
 	LCDInit(); 			//LCD��ʼ��
	Delay5Ms();
	while(1){
		Read_RTC();		//��ʱ��
			l_tmpdisplay[7]=(l_tmpdate[6]/16)+0X30;			//�������0X30����ASCII�ַ������еĵ�ַ
															//�������16����Ϊ������������BCD��
			l_tmpdisplay[8]=(l_tmpdate[6]&0x0f)+0X30;
			l_tmpdisplay[9]=0X3A;						
			l_tmpdisplay[10]=(l_tmpdate[4]/16)+0X30;
			l_tmpdisplay[11]=(l_tmpdate[4]&0x0f)+0X30;
			l_tmpdisplay[12]=0X3A;
			l_tmpdisplay[13]=(l_tmpdate[3]/16)+0X30;
			l_tmpdisplay[14]=(l_tmpdate[3]&0x0f)+0X30;	
			DisplayListChar(0, 0, l_tmpdisplay);			//���Һ����ʾ��һ��
		
			l_tmpdisplay2[5]=(l_tmpdate[2]/16)+0X30;
			l_tmpdisplay2[6]=(l_tmpdate[2]&0x0f)+0X30;
			l_tmpdisplay2[7]=0X3A;
			l_tmpdisplay2[8]=(l_tmpdate[1]/16)+0X30;
			l_tmpdisplay2[9]=(l_tmpdate[1]&0x0f)+0X30;
			l_tmpdisplay2[10]=0X3A;
			l_tmpdisplay2[11]=(l_tmpdate[0]/16)+0X30;
			l_tmpdisplay2[12]=(l_tmpdate[0]&0x0f)+0X30;
			DisplayListChar(0, 5, l_tmpdisplay2);			//���Һ����ʾ�ڶ���
			Delay400Ms();			
	}
}

/************д�ֽڵ�DS1302*******************************************/
void Write_Ds1302_Byte(unsigned  char temp) 
{
 unsigned char i;
 for (i=0;i<8;i++)     		//дһ���ֽ�
  { 
	 SCL2=0;
     SDA2=temp&0x01;     	//��ȡ��λ���ݣ���λ��ǰ��λ�ں�
     temp>>=1;  			//����һλ
     SCL2=1;
   }
}   

/************���ݵ�ַд����*************************************************/
void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCL2=0;						//׼��
	_nop_();
 	RST=1;						//��ʼ
   	_nop_();
 	Write_Ds1302_Byte(address);	//���͵�ַ
 	Write_Ds1302_Byte(dat);		//��������
 	RST=0;  					//�ָ�
}

/***********���ݵ�ַ������*************************************************/
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
 	for (i=0;i<8;i++) 			//��һ�ֽ�
 	{
		temp>>=1;				//����һλ����λ��ǰ��λ�ں�
		SCL2=0;			  
		_nop_();	
 		if(SDA2)
 			temp|=0x80;			//��λ��ǰ��λ�ں�
		SCL2=1;						
	} 
 	RST=0;
	_nop_();
	SDA2=0;
	return (temp);				//������Ӧֵ
}

/**********���룬�֣�ʱ���գ��£����ڣ���*************************************/
void Read_RTC(void)		//��ȡ ����
{
 unsigned char i,*p;
 p=read_rtc_address; 				//����ַ
 for(i=0;i<7;i++)					//��7�ζ�ȡ ������ʱ��������
 {
  l_tmpdate[i]=Read_Ds1302(*p);
  p++;
 }
}

/**********д�룬�֣�ʱ���գ��£����ڣ���*************************************/
void Set_RTC(void)
{
	unsigned char i,*p,tmp;
	for(i=0;i<7;i++){				//������תΪBCD��
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}
 	Write_Ds1302(0x8E,0X00);		//��д����
	
 	p=write_rtc_address;			//д��ַ	
 	for(i=0;i<7;i++)				//д�� ������ʱ��������
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		 p++;  
	 }
	 Write_Ds1302(0x8E,0x80);		//�ر�д����
}

//����ΪLCD1602����
/***********д����********************************************************/	
void WriteDataLCD(unsigned char WDLCD)
{
 ReadStatusLCD(); //���æ
 LCD_Data = WDLCD;
 LCD_RS = 1;
 LCD_RW = 0;
 LCD_E = 0; 		//�������ٶ�̫�߿���������С����ʱ
 LCD_E = 0; 		//��ʱ
 LCD_E = 1;
}

/***********дָ��********************************************************/	
void WriteCommandLCD(unsigned char WCLCD,unsigned char BuysC) //BuysCΪ0ʱ����æ���
{
 if (BuysC) ReadStatusLCD(); //������Ҫ���æ
 LCD_Data = WCLCD;
 LCD_RS = 0;
 LCD_RW = 0; 
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1; 
}

/***********������********************************************************/	
unsigned char ReadDataLCD(void)
{
 LCD_RS = 1; 
 LCD_RW = 1;
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1;
 return(LCD_Data);
}

/***********��״̬*******************************************************/	
unsigned char ReadStatusLCD(void)
{
 LCD_Data = 0xFF; 
 LCD_RS = 0;
 LCD_RW = 1;
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1;
 while (LCD_Data & Busy); //���æ�ź�
 return(LCD_Data);
}

/***********��ʼ��********************************************************/	
void LCDInit(void)
{
 LCD_Data = 0;
 WriteCommandLCD(0x38,0); 	//����ģʽ���ã������æ�ź�
 Delay5Ms(); 
 WriteCommandLCD(0x38,0);
 Delay5Ms(); 
 WriteCommandLCD(0x38,0);
 Delay5Ms(); 

 WriteCommandLCD(0x38,1); 	//��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
 WriteCommandLCD(0x08,1); 	//�ر���ʾ
 WriteCommandLCD(0x01,1); 	//��ʾ����
 WriteCommandLCD(0x06,1); 	//��ʾ����ƶ�����
 WriteCommandLCD(0x0C,1); 	//��ʾ�����������
}

/***********��ָ��λ����ʾһ���ַ�*******************************************/	
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
 Y &= 0x1;
 X &= 0xF; 				//����X���ܴ���15��Y���ܴ���1
 if (Y) X |= 0x40; 		//��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
 X |= 0x80; 			//���ָ����
 WriteCommandLCD(X, 0); //���ﲻ���æ�źţ����͵�ַ��
 WriteDataLCD(DData);
}

/***********��ָ��λ����ʾһ���ַ�*****************************************/	
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char *DData)
{
 unsigned char ListLength;

 ListLength = 0;
 Y &= 0x1;
 X &= 0xF; 				//����X���ܴ���15��Y���ܴ���1
 while (DData[ListLength]>=0x20) //�������ִ�β���˳�
  {
   if (X <= 0xF) 		//X����ӦС��0xF
    {
     DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
     ListLength++;
     X++;
    }
  }
}

/***********����ʱ********************************************************/	
void Delay5Ms(void)
{
 unsigned int TempCyc = 5552;
 while(TempCyc--);
}

/***********����ʱ********************************************************/	
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

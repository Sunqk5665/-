#include "1302.h"
void v_RTInputByte(unsigned char ucDa) 
{ 
	unsigned char i;
	ACC = ucDa;
	for(i=8; i>0; i--)
	{
 		T_IO = ACC0; /*�൱�ڻ���е� RRC */
 		T_CLK = 1;
 		T_CLK = 0;
 		ACC = ACC >> 1; 
	} 
}


/******************************************************************** 
*
* ����: unsigned char uc_RTOutputByte
* ˵��: 
* ����: ��DS1302��ȡ1Byte����
* ����: 
* ����: 
* ����ֵ: ACC
***********************************************************************/
unsigned char uc_RTOutputByte(void) 
{ 
	unsigned char i;
	for(i=8; i>0; i--)
	{
		ACC = ACC >>1; /*�൱�ڻ���е� RRC */
		ACC7 = T_IO;
		T_CLK = 1;
		T_CLK = 0;
	} 
	return(ACC); 
}


/******************************************************************** 
*
* ����: v_W1302
* ˵��: ��д��ַ����д����/����
* ����: ��DS1302д������
* ����: v_RTInputByte() 
* ����: ucAddr: DS1302��ַ, ucDa: Ҫд������
* ����ֵ: ��
***********************************************************************/
void v_W1302(unsigned char ucAddr, unsigned char ucDa)
{
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	v_RTInputByte(ucAddr); /* ��ַ������ */
	v_RTInputByte(ucDa); /* д1Byte����*/
	T_CLK = 1;
	T_RST =0;
} 


/******************************************************************** 
*
* ����: uc_R1302
* ˵��: ��д��ַ���������/����
* ����: ��ȡDS1302ĳ��ַ������
* ����: v_RTInputByte() , uc_RTOutputByte()
* ����: ucAddr: DS1302��ַ
* ����ֵ: ucDa :��ȡ������
***********************************************************************/
unsigned char uc_R1302(unsigned char ucAddr)
{
	unsigned char ucDa;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	v_RTInputByte(ucAddr); /* ��ַ������ */
	ucDa = uc_RTOutputByte(); /* ��1Byte���� */
	T_CLK = 1;
	T_RST =0;
	return(ucDa);
}

/******************************************************************** 
*
* ����: v_Set1302
* ˵��: 
* ����: ���ó�ʼʱ��
* ����: v_W1302() 
* ����: pSecDa: ��ʼʱ���ַ����ʼʱ���ʽΪ: �� �� ʱ �� �� ���� �� 
* 7Byte (BCD��) 1B 1B 1B 1B 1B 1B 1B
* ����ֵ: ��
***********************************************************************/
void v_Set1302(unsigned char *pSecDa) 
{
	unsigned char i;
	unsigned char ucAddr = 0x80; 
	v_W1302(0x8e,0x00); /* ��������,WP=0,д����?*/
	for(i =7;i>0;i--)
	{ 
		v_W1302(ucAddr,*pSecDa); /* �� �� ʱ �� �� ���� �� */

		pSecDa++;
		ucAddr +=2;
	}
	v_W1302(0x8e,0x80); /* ��������,WP=1,д����?*/
}


/******************************************************************** 
*
* ����: v_Get1302
* ˵��: 
* ����: ��ȡDS1302��ǰʱ��
* ����: uc_R1302() 
* ����: ucCurtime: ���浱ǰʱ���ַ����ǰʱ���ʽΪ: �� �� ʱ �� �� ���� �� 
* 7Byte (BCD��) 1B 1B 1B 1B 1B 1B 1B
* ����ֵ: ��
***********************************************************************/
void v_Get1302(unsigned char ucCurtime[]) 
{
	unsigned char i;
	unsigned char ucAddr = 0x81;
	for (i=0;i<7;i++)
	{
		ucCurtime[i] = uc_R1302(ucAddr);/*��ʽΪ: �� �� ʱ �� �� ���� �� */
		ucAddr += 2;
	}
} 

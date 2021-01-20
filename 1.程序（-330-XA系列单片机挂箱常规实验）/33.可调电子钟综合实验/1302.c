#include "1302.h"
void v_RTInputByte(unsigned char ucDa) 
{ 
	unsigned char i;
	ACC = ucDa;
	for(i=8; i>0; i--)
	{
 		T_IO = ACC0; /*相当于汇编中的 RRC */
 		T_CLK = 1;
 		T_CLK = 0;
 		ACC = ACC >> 1; 
	} 
}


/******************************************************************** 
*
* 名称: unsigned char uc_RTOutputByte
* 说明: 
* 功能: 从DS1302读取1Byte数据
* 调用: 
* 输入: 
* 返回值: ACC
***********************************************************************/
unsigned char uc_RTOutputByte(void) 
{ 
	unsigned char i;
	for(i=8; i>0; i--)
	{
		ACC = ACC >>1; /*相当于汇编中的 RRC */
		ACC7 = T_IO;
		T_CLK = 1;
		T_CLK = 0;
	} 
	return(ACC); 
}


/******************************************************************** 
*
* 名称: v_W1302
* 说明: 先写地址，后写命令/数据
* 功能: 往DS1302写入数据
* 调用: v_RTInputByte() 
* 输入: ucAddr: DS1302地址, ucDa: 要写的数据
* 返回值: 无
***********************************************************************/
void v_W1302(unsigned char ucAddr, unsigned char ucDa)
{
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	v_RTInputByte(ucAddr); /* 地址，命令 */
	v_RTInputByte(ucDa); /* 写1Byte数据*/
	T_CLK = 1;
	T_RST =0;
} 


/******************************************************************** 
*
* 名称: uc_R1302
* 说明: 先写地址，后读命令/数据
* 功能: 读取DS1302某地址的数据
* 调用: v_RTInputByte() , uc_RTOutputByte()
* 输入: ucAddr: DS1302地址
* 返回值: ucDa :读取的数据
***********************************************************************/
unsigned char uc_R1302(unsigned char ucAddr)
{
	unsigned char ucDa;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	v_RTInputByte(ucAddr); /* 地址，命令 */
	ucDa = uc_RTOutputByte(); /* 读1Byte数据 */
	T_CLK = 1;
	T_RST =0;
	return(ucDa);
}

/******************************************************************** 
*
* 名称: v_Set1302
* 说明: 
* 功能: 设置初始时间
* 调用: v_W1302() 
* 输入: pSecDa: 初始时间地址。初始时间格式为: 秒 分 时 日 月 星期 年 
* 7Byte (BCD码) 1B 1B 1B 1B 1B 1B 1B
* 返回值: 无
***********************************************************************/
void v_Set1302(unsigned char *pSecDa) 
{
	unsigned char i;
	unsigned char ucAddr = 0x80; 
	v_W1302(0x8e,0x00); /* 控制命令,WP=0,写操作?*/
	for(i =7;i>0;i--)
	{ 
		v_W1302(ucAddr,*pSecDa); /* 秒 分 时 日 月 星期 年 */

		pSecDa++;
		ucAddr +=2;
	}
	v_W1302(0x8e,0x80); /* 控制命令,WP=1,写保护?*/
}


/******************************************************************** 
*
* 名称: v_Get1302
* 说明: 
* 功能: 读取DS1302当前时间
* 调用: uc_R1302() 
* 输入: ucCurtime: 保存当前时间地址。当前时间格式为: 秒 分 时 日 月 星期 年 
* 7Byte (BCD码) 1B 1B 1B 1B 1B 1B 1B
* 返回值: 无
***********************************************************************/
void v_Get1302(unsigned char ucCurtime[]) 
{
	unsigned char i;
	unsigned char ucAddr = 0x81;
	for (i=0;i<7;i++)
	{
		ucCurtime[i] = uc_R1302(ucAddr);/*格式为: 秒 分 时 日 月 星期 年 */
		ucAddr += 2;
	}
} 

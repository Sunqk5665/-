#ifndef __1302_h
#define	__1302_h

#include <reg52.h>
/*********************************************************************/
 /* ʵʱʱ��ģ�� ʱ��оƬ�ͺţ�DS1302 */ 

/*********************************************************************/

sbit ACC0  = ACC^0;
sbit ACC7  = ACC^7;

sbit T_CLK = P2^2;  /*ʵʱʱ��ʱ�������� */
sbit T_IO =  P2^1;  /*ʵʱʱ������������ */
sbit T_RST = P2^0; /*ʵʱʱ�Ӹ�λ������ */

void v_Set1302(unsigned char *pSecDa) ;
void v_Get1302(unsigned char ucCurtime[]) ;

#endif

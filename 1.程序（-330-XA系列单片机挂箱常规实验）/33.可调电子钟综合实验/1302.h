#ifndef __1302_h
#define	__1302_h

#include <reg52.h>
/*********************************************************************/
 /* 实时时钟模块 时钟芯片型号：DS1302 */ 

/*********************************************************************/

sbit ACC0  = ACC^0;
sbit ACC7  = ACC^7;

sbit T_CLK = P2^2;  /*实时时钟时钟线引脚 */
sbit T_IO =  P2^1;  /*实时时钟数据线引脚 */
sbit T_RST = P2^0; /*实时时钟复位线引脚 */

void v_Set1302(unsigned char *pSecDa) ;
void v_Get1302(unsigned char ucCurtime[]) ;

#endif

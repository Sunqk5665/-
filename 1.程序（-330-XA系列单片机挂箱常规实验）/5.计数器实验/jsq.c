#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit k1 = P1^0;                 
sbit k2 = P1^1;                   
sbit k3 = P1^2;                  
void key(void);
void display(void);

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,
                    0x92,0x82,0xf8,0x80,0x90};          
                        
/*---------------------------------------
char m=00,n=00;    

void delayms(uint xms)
{
   uint i,j;
   for(i=xms;i>0;i--)
   for(j=110;j>0;j--);
}

void display(void)
{
        P2=0X80;
                P0=table[m%10];   
                delayms(5);  
        P2=0X40; 
                P0=table[m/10];          
                delayms(5);                                                              
        P2=0X20;
                P0=table[n%10];         
                delayms(5); 
        P2=0X10;
                P0=table[n/10];         
                delayms(5); 
}

void key()
{
  if(k1==0)                                        
   {                                                
           delayms(10);                         
        if(k1==0)                                 
        {
          m++;                                        
          if(m>=100)                         
          {
                  n++;                               
                m=0;                               
                if(n>=100)                        
                {
                  m=99;                                 
                  n=99;
                }
          }
        }
        while(!k1);                                
   }

  if(k2==0)                                        
   {                                               
           delayms(10);                         
        if(k2==0)
        {                                               
          m--;
          if(m<=0)                                 
          {                                                 
            m=99;                                
                  n--;                                 
                if(n==-1)                        
                {
                 n=0;                                 
                 m=0;
                }
          }
        }
        while(!k2);                                
   }

 if(k3==0)                                        
 {
   delayms(10);                                
   if(k3==0)                                 
   {
            m=0;                                        
         n=0;
   }
   while(!k3);                                
 }
}

void main()
{ 
  while(1)
  {                                                         
   key();                                        
   display(); 
  }

}                                   
---------------------------------*/
char m=00;    

void delayms(uint xms)
{
   uint i,j;
   for(i=xms;i>0;i--)
   for(j=110;j>0;j--);
}

void display(void)
{
        P2=0X02;
                P0=table[m%10];   
                delayms(5);  
        P2=0X01; 
                P0=table[m/10];          
                delayms(5);                                                               
}

void key()
{
  if(k1==0)                                        
   {                                                
           delayms(10);                         
        if(k1==0)                                 
        {
          m++;                                        
          if(m>=100)                         
          {                               
                m=00;                               
          }
        }
        while(!k1);                                
   }

  if(k2==0)                                        
   {                                               
           delayms(10);                         
        if(k2==0)
        {                                               
          m--;
          if(m<=0)                                 
          {                                                 
            m=99;                                                                
          }
        }
        while(!k2);                                
   }

 if(k3==0)                                        
 {
   delayms(10);                                
   if(k3==0)                                 
   {
            m=0;                                        
   }
   while(!k3);                                
 }
}

void main()
{ 
  while(1)
  {                                                         
   key();                                        
   display(); 
  }

}  
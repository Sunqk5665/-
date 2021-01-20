           
ORG         0000H
LJMP        MAIN   
          
ORG         1000H
MAIN:
     MOV SP,#60h
     MOV  R4,#0
     DJNZ R4,$
              ;设置138译码器的使能
     CLR  P1.5
     CLR  P1.4
     SETB  P1.3
               ;;138译码器数据输入
     CLR   P1.0;对应138的A  可以改变相应状态的值而改变138译码器的输出
     CLR   P1.1;对应138的B
     CLR   P1.2;对应138的C
     SJMP  $

     END

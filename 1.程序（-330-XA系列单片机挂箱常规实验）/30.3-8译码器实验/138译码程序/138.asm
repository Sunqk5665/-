           
ORG         0000H
LJMP        MAIN   
          
ORG         1000H
MAIN:
     MOV SP,#60h
     MOV  R4,#0
     DJNZ R4,$
              ;����138��������ʹ��
     CLR  P1.5
     CLR  P1.4
     SETB  P1.3
               ;;138��������������
     CLR   P1.0;��Ӧ138��A  ���Ըı���Ӧ״̬��ֵ���ı�138�����������
     CLR   P1.1;��Ӧ138��B
     CLR   P1.2;��Ӧ138��C
     SJMP  $

     END

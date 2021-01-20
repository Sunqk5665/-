    ;电子琴  -----------连续型   查询式键盘
    ;P3.2（INT0）   接扬声器

                  ;P1 键盘读入口    查询式
Pulse    equ 10h  ;脉冲
PulseCNT equ 50h  ;脉冲计数
ToneHigh equ 40h  ;高音调
ToneLow  equ 41h  ;低音调
Tone     equ 42h  ;音调
KeyBuf   equ 54h

Speaker  BIT  P2.0
         ORG  0000H
         ljmp  Start
         org   000bh
	 LJMP  Timer0Int
	 ORG   0030H
Timer0Int:        ;定时中断
       push  PSW
       clr   TR0
       mov   TH0, ToneHigh
       mov   TL0, ToneLow
       setb  TR0
       mov   C, Pulse
       MOV   Speaker,C

       CPL   Pulse
       pop   PSW
       reti

ToneTable:
      
        DW    64578,64686,64778,64821
        DW    64898,64968,65029
        
TestKey:
        MOV   P1,  #0FFH
        MOV   A,   P1
        CPL   A                ; 读入键状态

        ret

KeyTable:DB 0FEH,0FDH,0FBH,0F7H
         DB 0EFH,0DFH,0BFH,07FH    ; 键码定义


GETKEY:
        MOV       R6,#10
        ACALL     DELAY
        MOV       A,P1
        CJNE      A,#0FFH,K01               ;确有键按下
        LJMP      MLOOP
K01:    MOV       R3,#8                    ;8个键
        MOV       R2,#0                    ;键码
        MOV       B,A                      ;暂存键值
        MOV       DPTR,#KeyTable
K02:    MOV       A,R2
        MOVC      A,@A+DPTR                ;从键值表中取键值
        CJNE      A,B,K04                  ;键值比较
        MOV       A,R2                     ;得键码
        INC       A
        RET
K04:    INC       R2            ;不相等，到继续访问键值表
        DJNZ      R3,K02
        MOV       A,#0FFH       ;键值不在键值中，即多键同时按下
        LJMP      MLOOP

Delay:               ; 延时子程序
       mov   r7, #0
DelayLoop:
       djnz  r7, DelayLoop
       djnz  r6, Delay
       ret


             ;#########################
Start:

       mov  sp, #70h
       mov  TMOD, #01  ;  Timer
       mov  IE, #82h   ;  EA=1, IT0 = 1
       mov  Tone,#0
MLoop:
       call TestKey
       jz   MLoop
       call GetKey
       mov  b, a
       jz   MLoop      ; = 0, < 1
       anl  a, #8
       jnz  MLoop      ; > 8
       dec  b
       mov  a, b
       rl   a          ; a = a*2
       mov  b, a
       mov  dptr, #ToneTable
       movc a, @a+dptr
       mov  ToneHigh, a
       mov  TH0, a
       mov  a, b
       inc  a
       movc a, @a+dptr
       mov  ToneLow, a
       mov  TL0, a
        SETB      TR0
        MOV       P1,#0FFH
WAIT:
        MOV       A,P1

        CJNE      A,#0FFH, WAIT
        MOV       R6,#10
        ACALL     DELAY
        CLR       TR0
        LJMP      MLOOP
        END

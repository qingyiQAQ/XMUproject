        DATA  SEGMENT
         ARR  DB        31H,21H,42H,52H,87H,23H,98H,01H     ;����Ҫ�Ƚϵ����ݴ���
        EQUA  DB        48
          UP  DB        48
        DOWN  DB        48          ;��ʼ����������ֵΪ48���������asc���Ӧ�������
     STRING1  DB        'UP=','$'
     STRING2  DB        'EQUA=','$'
     STRING3  DB        'DOWN=','$'
      STRING  DB        0AH,0DH,'$' ;��ʼ�������ַ����Լ��س�
        DATA  ENDS
        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA
      START:  MOV       AX,DATA
              MOV       DS,AX
              MOV       DI,-1       ;��ʼ��diΪ-1���ڱ�������
      AGAIN:  INC       DI
              CMP       DI,8        ;di����81ʱ�˳�
              JE        QUIT
              CMP       ARR[DI],42H
              JE        E
              JA        U
              JB        D           ;��Ӧ���жϺ���ת
          U:
              INC       UP
              JMP       AGAIN
          E:
              INC       EQUA
              JMP       AGAIN
          D:
              INC       DOWN
              JMP       AGAIN       ;��ת������ۼӲ���ת��ѭ��
       QUIT:
              MOV       DX,OFFSET STRING1
              MOV       AH,09H
              INT       21H
              MOV       AH,02H
              MOV       DL,UP
              INT       21H
              MOV       DX,OFFSET STRING
              MOV       AH,09H
              INT       21H
              MOV       DX,OFFSET STRING2
              MOV       AH,09H
              INT       21H
              MOV       AH,02H
              MOV       DL,EQUA
              INT       21H
              MOV       DX,OFFSET STRING
              MOV       AH,09H
              INT       21H
              MOV       DX,OFFSET STRING3
              MOV       AH,09H
              INT       21H
              MOV       AH,02H
              MOV       DL,DOWN
              INT       21H
              MOV       AH,4CH
              INT       21H         ;��ʾ�����Ӧֵ
        CODE  ENDS
              END       START


        DATA  SEGMENT
    UPSTRING  DB        0AH,0DH,'$'
        DATA  ENDS

        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA

      START:  MOV       AX,DATA
              MOV       DS,AX
              MOV       BL,10H      ;bl���ڴ���ַ����
              MOV       CX,10H      ;cx���ڴ��ÿ��δ����ַ�����
   LINELOOP:  MOV       AH,02H
              MOV       DL,BL
              INT       21H         ;������Ϊbl���ַ�
              MOV       AH,02H
              MOV       DL,20H
              INT       21H         ;���һ���ո�
              INC       BL
              CMP       BL,0FFH
              JE        ENDPRO      ;bl����ffhʱ��������
              DEC       CX
              CMP       CX,0        ;����Ƿ�����ɸ���16���ַ�
              JA        LINELOOP
 CHANGELINE:  MOV       CX,10H
              MOV       AH,09H
              MOV       DX,OFFSET UPSTRING      ;�������
              INT       21H
              JMP       LINELOOP
     ENDPRO:  MOV       AX,4C00H             ;��������
              INT       21H
        CODE  ENDS
              END       START


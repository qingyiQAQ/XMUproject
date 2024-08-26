        DATA  SEGMENT
    UPSTRING  DB        0AH,0DH,'$'
        DATA  ENDS

        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA

      START:  MOV       AX,DATA
              MOV       DS,AX
              MOV       BL,10H      ;bl用于存放字符序号
              MOV       CX,10H      ;cx用于存放每行未输出字符个数
   LINELOOP:  MOV       AH,02H
              MOV       DL,BL
              INT       21H         ;输出序号为bl的字符
              MOV       AH,02H
              MOV       DL,20H
              INT       21H         ;输出一个空格
              INC       BL
              CMP       BL,0FFH
              JE        ENDPRO      ;bl到达ffh时结束程序
              DEC       CX
              CMP       CX,0        ;检查是否已完成该行16个字符
              JA        LINELOOP
 CHANGELINE:  MOV       CX,10H
              MOV       AH,09H
              MOV       DX,OFFSET UPSTRING      ;输出换行
              INT       21H
              JMP       LINELOOP
     ENDPRO:  MOV       AX,4C00H             ;结束程序
              INT       21H
        CODE  ENDS
              END       START


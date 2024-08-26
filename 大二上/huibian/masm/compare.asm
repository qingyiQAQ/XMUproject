        DATA  SEGMENT
         ARR  DB        31H,21H,42H,52H,87H,23H,98H,01H     ;将需要比较的数据存入
        EQUA  DB        48
          UP  DB        48
        DOWN  DB        48          ;初始化三个变量值为48方便后面以asc码对应数字输出
     STRING1  DB        'UP=','$'
     STRING2  DB        'EQUA=','$'
     STRING3  DB        'DOWN=','$'
      STRING  DB        0AH,0DH,'$' ;初始化三个字符串以及回车
        DATA  ENDS
        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA
      START:  MOV       AX,DATA
              MOV       DS,AX
              MOV       DI,-1       ;初始化di为-1用于遍历数组
      AGAIN:  INC       DI
              CMP       DI,8        ;di到达81时退出
              JE        QUIT
              CMP       ARR[DI],42H
              JE        E
              JA        U
              JB        D           ;相应的判断和跳转
          U:
              INC       UP
              JMP       AGAIN
          E:
              INC       EQUA
              JMP       AGAIN
          D:
              INC       DOWN
              JMP       AGAIN       ;跳转后进行累加并跳转回循环
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
              INT       21H         ;显示输出对应值
        CODE  ENDS
              END       START


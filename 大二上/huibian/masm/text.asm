        DATA  SEGMENT
          D1  DW        10H,11H,12H,13H,14H,15H,16H,17H     ;在数据段中依次存入10H,11H,12H,13H,14H,15H,16H,17H
        DATA  ENDS
       STACK  SEGMENT   STACK
              DW        1024 DUP(?)
       STACK  ENDS
        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA,SS:STACK
      START:
              MOV       AX,DATA
              MOV       DS,AX
 ;主程序      ;初始化寄存器
              MOV       BX,0
              MOV       DX,0
              MOV       CX,8
              ;循环相加
          S:  ADD       DX,DS:[BX]
              ADD       BX,2
              LOOP      S
              ;退出程序
              MOV       AX,4C00H
              INT       21H
        CODE  ENDS
              END       START





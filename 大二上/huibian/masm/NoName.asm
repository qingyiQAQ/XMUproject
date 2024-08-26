        DATA  SEGMENT
        DATA  ENDS
       STACK  SEGMENT   STACK
              DW        1024 DUP(?)
       STACK  ENDS
        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA,SS:STACK
      START:
              MOV       AX,DATA
              MOV       DS,AX
              MOV       AL,89H
              ADD       AL,AL
              ADD       AL,9DH
              CMP       AL,0BCH
              SUB       AL,AL
              DEC       AL
              INC       AL
              MOV       AX,4C00H
              INT       21H
        CODE  ENDS
              END       START


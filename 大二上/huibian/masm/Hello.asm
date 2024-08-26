data SEGMENT	
	d1     DB 21H,23H,25H
	d2     DW 55H,0ABCDH,32
	string DB 'hello world!',0ah,0dh,'$'
data ENDS
stack SEGMENT STACK
	DW 512 DUP(?)
stack ENDS

code SEGMENT
	ASSUME CS:code,DS:data,SS:stack
start:
	MOV AX,DATA
	MOV DS,AX

	MOV CX,1234
	MOV CH,0FFH

	MOV DX,OFFSET string
	MOV AH,09H
	INT 21H

	MOV AX,4C00H
	INT 21H
code ENDS
END start 
	
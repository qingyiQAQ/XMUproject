      
.486
.model flat, stdcall
option casemap:none
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\gdi32.lib
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\masm32.lib
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
include \masm32\include\windows.inc
include \masm32\include\msvcrt.inc
include \masm32\include\masm32.inc
include \masm32\macros\macros.asm

.data
    data dd 8,1,5,2,7,9,6,4,3,10
.code
main:
    mov si,10
loop1:
    mov eax,0
    dec si
    cmp si,0
    je stop
    mov di,si
loop2:
    dec di
    mov ebx,data[eax]
    mov ecx,data[eax+4]
    cmp ebx,ecx
    ja loop3
    mov data[eax],ecx
    mov data[eax+4],ebx
loop3:
    add eax,4
    cmp di,0
    ja loop2
    cmp di,0
    je loop1
stop: 
    mov eax,0
stop1:
    print str$(data[0])
    print str$(data[4])
    print str$(data[8])
    print str$(data[12])
    print str$(data[16])
    print str$(data[20])
    print str$(data[24])
    print str$(data[28])
    print str$(data[32])
    print str$(data[36])
end main
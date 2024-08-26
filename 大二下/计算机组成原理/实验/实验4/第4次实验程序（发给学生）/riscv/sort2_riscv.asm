.data
data: .word 8,1,5,2,7,9,6,4,3,10
.text
ori a3,zero,0
ori a4,zero,40
ori a5,zero,1
ori a6,zero,-4
ori a7,zero,4
main:
ori a0,zero,0
add a4,a4,a6
loop1:
lw a1,(a0)
lw a2,4(a0)
ori a3,zero,0
slt a3,a2,a1
beq a3,zero,loop2
sw a1,4(a0)
sw a2,(a0)
loop2:
add a0,a0,a7
ori a3,zero,0
slt a3,a0,a4
beq a3,a5,loop1
ori a3,zero,0
slt a3,a4,a7
beq a3,zero,main
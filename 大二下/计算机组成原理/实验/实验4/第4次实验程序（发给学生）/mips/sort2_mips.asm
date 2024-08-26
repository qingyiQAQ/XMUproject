.data
data: .word 8,1,5,2,7,9,6,4,3,10
.text
addi $t3,$zero,0
addi $t4,$zero,40
addi $t5,$zero,1
main:
addi $t0,$zero,0
addi $t4,$t4,-4
loop1:
lw $t1,($t0)
lw $t2,4($t0)
addi $t3,$zero,0
slt $t3,$t2,$t1
bne $t3,$t5,loop2
sw $t1,4($t0)
sw $t2,($t0)
loop2:
addi $t0,$t0,4
addi $t3,$zero,0
slt $t3,$t0,$t4
beq $t3,$t5,loop1
addi $t3,$zero,0
slti $t3,$t4,4
bne $t3,$t5,main
syscall  